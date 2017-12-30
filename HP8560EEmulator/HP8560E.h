#ifndef HP8560E__H
#define HP8560E__H

#include "BusRouter.h"
#include "EmbeddedROM.h"
#include "RAM.h"
#include "EEROM.h"
#include "RegisterSet.h"
#include "DisplayTimer.h"
#include "InterruptReceiver.h"
#include "HPIB.h"
#include "Display.h"
#include "Keypad.h"

#include <bitset>

class HP8560E final : public BusDevice, private InterruptReceiver {
public:
    HP8560E();
    ~HP8560E();

    virtual uint16_t readMemory(uint32_t address, uint16_t mask) override;
    virtual void writeMemory(uint32_t address, uint16_t value, uint16_t mask) override;

    void cycles(unsigned int cycles);

    unsigned int interruptAck(unsigned int priority);

    inline void setDisplay(DisplayHost *display) {
        m_display.setDisplayHost(display);
    }

    inline void setKeyState(unsigned int key, bool state) {
        m_keypad.setKeyState(key, state);
    }

private:
    virtual void setInterruptAsserted(unsigned int interrupt, bool asserted) override;
    
private:
    void writePSAK(uint16_t value, uint16_t mask);
    uint16_t readSENSE_KBD_INT_PRIO(uint16_t mask);

    std::bitset<7> m_interruptRequests;
    BusRouter m_controlRouter;
    EmbeddedROM m_firmwareROM;
    RAM m_ram1;
    RAM m_ram2;
    RAM m_ram3;
    RAM m_ram4;
    RAM m_ram5;
    EEROM m_eerom;
    RegisterSet m_controlRegisters;
    DisplayTimer m_displayTimer;
    HPIB m_hpib;
    BusRouter m_interface;
    Display m_display;
    Keypad m_keypad;
    RegisterSet m_interfaceRegisters;
};

#endif
