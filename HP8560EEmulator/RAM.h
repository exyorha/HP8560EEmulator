#ifndef RAM__H
#define RAM__H

#include "BusDevice.h"

#include <vector>

class RAM final : public BusDevice {
public:
    RAM(size_t size);
    ~RAM();

    virtual uint16_t readMemory(uint32_t address, uint16_t mask) override;
    virtual void writeMemory(uint32_t address, uint16_t value, uint16_t mask) override;

private:
    std::vector<uint8_t> m_ram;
};

#endif
