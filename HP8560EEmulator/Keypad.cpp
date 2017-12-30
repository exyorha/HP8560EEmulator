#include "Keypad.h"

#include <stdio.h>

extern "C" {
#include "m68k.h"
}

#include "InterruptReceiver.h"

Keypad::Keypad(InterruptReceiver *receiver, unsigned int interruptLine) :
    m_receiver(receiver), m_interruptLine(interruptLine),
    m_scanKbd(0), m_senseKbd(0xFF), m_interruptRequestKeypad(false) {

}

Keypad::~Keypad() {

}

void Keypad::setKeyState(unsigned int key, bool state) {
    std::lock_guard<std::mutex> locker(m_stateMutex);
    m_keypadState[key] = state;
}

void Keypad::writeSCAN_KBD(uint16_t value, uint16_t mask) {
    (void)mask;

    value >>= 8;
    mask >>= 8;

    if(mask & 0xFF) {
        m_scanKbd = value & 0xFF;
        m68k_end_timeslice();
    }
}

void Keypad::tick() {
    unsigned char sense = 0xFF;

    {
        std::lock_guard<std::mutex> locker(m_stateMutex);
        for(unsigned int scanBit = 0; scanBit < 6; scanBit++) {
            if(!(m_scanKbd & (1 << scanBit))) {
                for(unsigned int senseBit = 0; senseBit < 8; senseBit++) {
                    if(m_keypadState[scanBit * 8 + senseBit]) {
                        sense &= ~(1 << senseBit);
                    }
                }
            }
        }
    }

    if(!(m_scanKbd & 0x40)) {
        if(m_interruptRequestKeypad) {
            m_interruptRequestKeypad = false;
            m_receiver->setInterruptAsserted(m_interruptLine, m_interruptRequestKeypad);
        }
    } else if(m_senseKbd == 0xFF && sense != 0xFF) {
        if(!m_interruptRequestKeypad) {
            m_interruptRequestKeypad = true;
            m_receiver->setInterruptAsserted(m_interruptLine, m_interruptRequestKeypad);
        }
    }

    m_senseKbd = sense;
}

uint8_t Keypad::readINT_PRIOR() {
    uint8_t value = 0;

    if(m_interruptRequestKeypad)
        value |= 2;

    return value;
}
