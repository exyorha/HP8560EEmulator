#ifndef BUS_ROUTER__H
#define BUS_ROUTER__H

#include <vector>
#include <unordered_set>

#include "BusDevice.h"

class BusRouter final: public BusDevice {
public:
    BusRouter();
    ~BusRouter();

    virtual uint16_t readMemory(uint32_t address, uint16_t mask) override;
    virtual void writeMemory(uint32_t address, uint16_t value, uint16_t mask) override;

    inline void setAddressMask(uint32_t addressMask) {
        m_addressMask = addressMask;
    }

    inline void setReportingEnabled(bool reportingEnabled) {
        m_reportingEnabled = reportingEnabled;
    }

    void addAddressRange(uint32_t rangeBegin, uint32_t rangeEnd, BusDevice *device);

private:
    void reportUnknownAddress(uint32_t address);

    struct AddressRange {
        uint32_t rangeBegin;
        uint32_t rangeEnd;
        BusDevice *device;
    };
    
    uint32_t m_addressMask;
    std::vector<AddressRange> m_addressRanges;
    std::unordered_set<uint32_t> m_unknownAddresses;
    bool m_reportingEnabled;
};

#endif
