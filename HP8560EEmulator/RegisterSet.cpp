#include "RegisterSet.h"

RegisterSet::RegisterSet() {

}

RegisterSet::~RegisterSet() {

}


uint16_t RegisterSet::readMemory(uint32_t address, uint16_t mask) {
    for (const auto &reg : m_registers) {
        if ((address & reg.addressMask) == reg.address) {
            if (!reg.readFunction) {
                fprintf(stderr, "RegisterSet(%p): register %08X is not readable\n", this, address);
                return 0xFFFF;
            }
            else {
                return reg.readFunction(mask);
            }
        }
    }

    reportUnknownAddress(address);

    return 0xFFFF;
}

void RegisterSet::writeMemory(uint32_t address, uint16_t value, uint16_t mask) {
    for (const auto &reg : m_registers) {
        if ((address & reg.addressMask) == reg.address) {
            if (!reg.writeFunction) {
                fprintf(stderr, "RegisterSet(%p): register %08X is not writable\n", this, address);
                return;
            }
            else {
                reg.writeFunction(value, mask);
                return;
            }
        }
    }

    reportUnknownAddress(address);
}

void RegisterSet::reportUnknownAddress(uint32_t address) {
    auto result = m_unknownAddresses.insert(address);
    if (result.second) {
        fprintf(stderr, "RegisterSet(%p): no device has address %08X\n", this, address);
    }
}


void RegisterSet::addRegister(uint32_t address, uint32_t addressMask,
    std::function<uint16_t(uint16_t)> &&readFunction,
    std::function<void(uint16_t, uint16_t)> &&writeFunction) {

    m_registers.emplace_back(Register{
        address & addressMask,
        addressMask,
        std::move(readFunction),
        std::move(writeFunction)
    });
}
