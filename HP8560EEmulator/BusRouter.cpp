#include <stdio.h>

#include "BusRouter.h"

BusRouter::BusRouter() : m_addressMask(0xFFFFFFFF), m_reportingEnabled(true) {
    
}

BusRouter::~BusRouter() {

}

uint16_t BusRouter::readMemory(uint32_t address, uint16_t mask) {
    address &= m_addressMask;

    for (const auto &range : m_addressRanges) {
        if (range.rangeBegin <= address && range.rangeEnd >= address) {
            return range.device->readMemory(address, mask);
        }
    }

    reportUnknownAddress(address);
    
    return 0xFFFF;
}

void BusRouter::writeMemory(uint32_t address, uint16_t value, uint16_t mask) {
    address &= m_addressMask;

    for (const auto &range : m_addressRanges) {
        if (range.rangeBegin <= address && range.rangeEnd >= address) {
            range.device->writeMemory(address, value, mask);
            return;
        }
    }

    reportUnknownAddress(address);
}

void BusRouter::addAddressRange(uint32_t rangeBegin, uint32_t rangeEnd, BusDevice *device) {
    m_addressRanges.emplace_back(AddressRange{
        rangeBegin & m_addressMask,
        (rangeEnd - 1) & m_addressMask,
        device
    });
}

void BusRouter::reportUnknownAddress(uint32_t address) {
    if (m_reportingEnabled) {
        auto result = m_unknownAddresses.insert(address);
        if (result.second) {
            fprintf(stderr, "BusRouter(%p): no device has address %08X\n", this, address);
        }
    }
}
