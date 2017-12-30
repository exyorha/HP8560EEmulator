#include "HP8560E.h"

#include <QCoreApplication>
#include <QDir>

extern "C" {
#include "m68k.h"
}

HP8560E::HP8560E() :
    m_firmwareROM(1),
    m_ram1(0x10000),
    m_ram2(0x20000),
    m_ram3(0x10000),
    m_ram4(0x04000),
    m_ram5(0x04000),
    m_eerom(QDir::toNativeSeparators(QCoreApplication::applicationDirPath() + "/eerom.bin").toStdWString().c_str(), 8192),
    m_displayTimer(this, 1),
    m_keypad(this, 2) {
    
    using namespace std::placeholders;

    m_controlRouter.setAddressMask(0x9FFFFF);
    m_controlRouter.addAddressRange(0x000000, 0x800000, &m_firmwareROM);
    m_controlRouter.addAddressRange(0x970000, 0x980000, &m_ram1);
    m_controlRouter.addAddressRange(0xF80000, 0xFA0000, &m_ram2);
    m_controlRouter.addAddressRange(0xFC0000, 0xFC8000, &m_ram3);
    m_controlRouter.addAddressRange(0xFC8000, 0xFD0000, &m_display);
    m_controlRouter.addAddressRange(0xFF0000, 0xFF2000, &m_eerom);
    m_controlRouter.addAddressRange(0xFF2000, 0xFF2010, &m_hpib); // HPIB overlay - MUST be before controlRegisters
    m_controlRouter.addAddressRange(0xFF2000, 0xFF3000, &m_controlRegisters);
    m_controlRouter.addAddressRange(0xFF4000, 0xFF8000, &m_ram4);
    m_controlRouter.addAddressRange(0xFFA000, 0xFFC000, &m_interface);
    m_controlRouter.addAddressRange(0xFFC000, 0x1000000, &m_ram5);
    
    m_controlRegisters.addRegister(0x30, 0x70, nullptr, std::bind(&HP8560E::writePSAK, this, _1, _2));

    m_interface.setAddressMask(0x7FF);
    m_interface.setReportingEnabled(false);
    m_interface.addAddressRange(0x000, 0x400, &m_interfaceRegisters);

    m_interfaceRegisters.addRegister(0x200, 0x60E, nullptr, std::bind(&Keypad::writeSCAN_KBD, &m_keypad, _1, _2));
    m_interfaceRegisters.addRegister(0x008, 0x60E, std::bind(&HP8560E::readSENSE_KBD_INT_PRIO, this, _1), nullptr);
}

HP8560E::~HP8560E() {

}

uint16_t HP8560E::readMemory(uint32_t address, uint16_t mask) {
    return m_controlRouter.readMemory(address, mask);
}

void HP8560E::writeMemory(uint32_t address, uint16_t value, uint16_t mask) {
    m_controlRouter.writeMemory(address, value, mask);
}

void HP8560E::cycles(unsigned int cycles) {
    m_displayTimer.cycles(cycles);
    m_keypad.tick();
}

void HP8560E::writePSAK(uint16_t value, uint16_t mask) {
    value >>= 8;
    mask >>= 8;

    if(mask & 0xFF) {
        if (value & ~(1 << 5)) {
            fprintf(stderr, "HP8560E: PSAK: %04X\n", value);
        }

        m_displayTimer.setInterruptAck((value & (1 << 5)) != 0);
    }
}

void HP8560E::setInterruptAsserted(unsigned int interrupt, bool asserted) {
    m_interruptRequests[interrupt] = asserted;
    size_t interruptLevel = 0;

    for (size_t interrupt = 0; interrupt < m_interruptRequests.size(); interrupt++) {
        if (m_interruptRequests[interrupt]) {
            interruptLevel = interrupt + 1;
        }
    }

    m68k_set_irq(interruptLevel);
}


unsigned int HP8560E::interruptAck(unsigned int priority) {
    return 63 + priority;
}

uint16_t HP8560E::readSENSE_KBD_INT_PRIO(uint16_t mask) {
    uint16_t value = 0;
    if(mask & 0xFF00) {
        value |= m_keypad.readSENSE_KBD() << 8;
    }

    if(mask & 0x00FF) {
        value |= m_keypad.readINT_PRIOR() | 12;
    }

    return value;
}
