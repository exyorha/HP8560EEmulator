#ifndef REGISTER_SET__H
#define REGISTER_SET__H

#include "BusDevice.h"

#include <functional>
#include <vector>
#include <unordered_set>

class RegisterSet final : public BusDevice {
public:
    RegisterSet();
    ~RegisterSet();

    virtual uint16_t readMemory(uint32_t address, uint16_t mask) override;
    virtual void writeMemory(uint32_t address, uint16_t value, uint16_t mask) override;

    void addRegister(uint32_t address, uint32_t addressMask,
        std::function<uint16_t(uint16_t)> &&readFunction,
        std::function<void(uint16_t, uint16_t)> &&writeFunction);

private:
    struct Register {
        uint32_t address;
        uint32_t addressMask;
        std::function<uint16_t(uint16_t)> readFunction;
        std::function<void(uint16_t, uint16_t)> writeFunction;
    };

    void reportUnknownAddress(uint32_t address);

    std::vector<Register> m_registers;
    std::unordered_set<uint32_t> m_unknownAddresses;
};

#endif
