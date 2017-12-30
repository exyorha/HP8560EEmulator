#ifndef EMBEDDED_ROM__H
#define EMBEDDED_ROM__H

#include "BusDevice.h"

class EmbeddedROM final : public BusDevice {
public:
    EmbeddedROM(unsigned int resource);
    ~EmbeddedROM();

    virtual uint16_t readMemory(uint32_t address, uint16_t mask) override;
    virtual void writeMemory(uint32_t address, uint16_t value, uint16_t mask) override;

private:
    const uint8_t *m_rom;
    size_t m_romSize;
};

#endif
