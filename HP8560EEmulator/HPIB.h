#ifndef HPIB__H
#define HPIB__H

#include "BusDevice.h"

class HPIB final : public BusDevice {
public:
    HPIB();
    ~HPIB();

    virtual uint16_t readMemory(uint32_t address, uint16_t mask) override;
    virtual void writeMemory(uint32_t address, uint16_t value, uint16_t mask) override;

private:
    uint8_t readRegister(uint32_t address);
    void writeRegister(uint32_t address, uint8_t value);
};

#endif
