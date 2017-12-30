#include "RAM.h"

RAM::RAM(size_t size) : m_ram(size) {

}

RAM::~RAM() {

}


uint16_t RAM::readMemory(uint32_t address, uint16_t mask) {
    auto val = reinterpret_cast<uint16_t *>(&m_ram[address % m_ram.size()]);

    return *val;
}

void RAM::writeMemory(uint32_t address, uint16_t value, uint16_t mask) {
    auto val = reinterpret_cast<uint16_t *>(&m_ram[address % m_ram.size()]);

    *val = (value & mask) | (*val & ~mask);
}
