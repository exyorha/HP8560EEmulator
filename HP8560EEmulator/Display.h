#ifndef DISPLAY__H
#define DISPLAY__H

#include "BusDevice.h"

#include <vector>

class DisplayHost;

class Display final : public BusDevice {
public:
    Display();
    ~Display();

    virtual uint16_t readMemory(uint32_t address, uint16_t mask) override;
    virtual void writeMemory(uint32_t address, uint16_t value, uint16_t mask) override;

    void setDisplayHost(DisplayHost *host);

private:
    size_t adjustAddress(uint32_t address);

    DisplayHost *m_host;
    std::vector<uint16_t> m_videoRAM;
};

#endif
