#ifndef BUS_DEVICE__H
#define BUS_DEVICE__H

#include <stdint.h>

class BusDevice {
protected:
    BusDevice();
    ~BusDevice();

public:
    BusDevice(const BusDevice &other) = delete;
    BusDevice &operator =(const BusDevice &other) = delete;

    virtual uint16_t readMemory(uint32_t address, uint16_t mask) = 0;
    virtual void writeMemory(uint32_t address, uint16_t value, uint16_t mask) = 0;
};

#endif
