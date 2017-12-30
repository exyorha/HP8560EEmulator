#include "simulatorthread.h"

extern "C" {
#include "m68k.h"
}

#include "HP8560E.h"

#include <QTime>

std::unique_ptr<HP8560E> machine;

unsigned int m68k_read_memory_masked(unsigned int address, unsigned int mask) {
    if (address & 1)
        fprintf(stderr, "Misaligned address on read: %08X\n", address);

    return machine->readMemory(address & ~1, mask);
}

unsigned int m68k_read_memory_8(unsigned int address) {
    if (address & 1)
        return m68k_read_memory_masked(address & ~1, 0xFF) & 0xFF;
    else
        return m68k_read_memory_masked(address & ~1, 0xFF00) >> 8;
}

unsigned int m68k_read_memory_16(unsigned int address) {
    return m68k_read_memory_masked(address, 0xFFFF);
}

unsigned int m68k_read_memory_32(unsigned int address) {
    return (m68k_read_memory_16(address) << 16) | m68k_read_memory_16(address + 2);
}

void m68k_write_memory_masked(unsigned int address, unsigned int value, unsigned int mask) {
    if (address & 1)
        fprintf(stderr, "Misaligned address on write: %08X\n", address);

    machine->writeMemory(address, value, mask);
}

void m68k_write_memory_8(unsigned int address, unsigned int value) {
    if (address & 1) {
        m68k_write_memory_masked(address & ~1, value, 0x00FF);
    }
    else {
        m68k_write_memory_masked(address, value << 8, 0xFF00);
    }
}

void m68k_write_memory_16(unsigned int address, unsigned int value) {
    m68k_write_memory_masked(address, value, 0xFFFF);
}

void m68k_write_memory_32(unsigned int address, unsigned int value) {
    m68k_write_memory_16(address, value >> 16);
    m68k_write_memory_16(address + 2, value & 0xFFFF);
}

unsigned int m68k_read_disassembler_8(unsigned int address) {
    return m68k_read_memory_8(address);
}

unsigned int m68k_read_disassembler_16(unsigned int address) {
    return m68k_read_memory_16(address);
}

unsigned int m68k_read_disassembler_32(unsigned int address) {
    return m68k_read_memory_32(address);
}

int m68k_int_callback(int prio) {
    return machine->interruptAck(prio);
}

SimulatorThread::SimulatorThread(QObject *parent) : QThread(parent) {
    if(!machine) {
        machine = std::make_unique<HP8560E>();
    }
}

SimulatorThread::~SimulatorThread() {
    requestInterruption();
    wait();
}

void SimulatorThread::run() {
    m68k_init();
    m68k_set_cpu_type(M68K_CPU_TYPE_68000);
    m68k_set_int_ack_callback(m68k_int_callback);
    m68k_pulse_reset();

    unsigned int totalCycles = 0;
    QTime cycleTime;
    cycleTime.start();

    int slice = 100;

    while(!isInterruptionRequested()) {
        unsigned int cycles = m68k_execute(32);

        machine->cycles(cycles);

        totalCycles += cycles;
        if(totalCycles > 1600000) {
            int elapsed = cycleTime.restart();

            if(elapsed < slice) {
                int toSleep = slice - elapsed;

                msleep(toSleep);
                int sleepElapsed = cycleTime.restart();

                if(sleepElapsed > toSleep)
                    slice = 100 - (sleepElapsed - toSleep);
                else
                    slice = 100;
            } else {
                slice = 100;
            }

            totalCycles = 0;
        }
    }
}

void SimulatorThread::setDisplay(DisplayHost *display) {
    machine->setDisplay(display);
}

void SimulatorThread::setKeyState(unsigned int key, bool state) {
    machine->setKeyState(key, state);
}
