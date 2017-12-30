#include "Display.h"
#include "DisplayHost.h"

Display::Display() : m_host(nullptr), m_videoRAM(8192) {

}

Display::~Display() {

}

uint16_t Display::readMemory(uint32_t address, uint16_t mask) {
    (void)mask;

    return m_videoRAM[adjustAddress(address)];
}

void Display::writeMemory(uint32_t address, uint16_t value, uint16_t mask) {
    auto &word = m_videoRAM[adjustAddress(address)];

    word = (value & mask) | (word & ~mask);

    if(m_host)
        m_host->updateFrame();
}

size_t Display::adjustAddress(uint32_t address) {
    return (address >> 1) & 8191;
}

void Display::setDisplayHost(DisplayHost *host) {
    m_host = host;
    if(m_host) {
        m_host->setFrameBuffer(m_videoRAM);
    }
}
