#include "HPIB.h"

#include <stdio.h>

HPIB::HPIB() {

}

HPIB::~HPIB() {

}

uint16_t HPIB::readMemory(uint32_t address, uint16_t mask) {
    uint16_t value = 0;

    if (mask & 0xFF00) {
        value |= readRegister(address) << 8;
    }

    if (mask & 0x00FF) {
        value |= readRegister(address + 1);
    }

    return value;
}

void HPIB::writeMemory(uint32_t address, uint16_t value, uint16_t mask) {
    if (mask & 0xFF00) {
        writeRegister(address, value >> 8);
    }

    if (mask & 0x00FF) {
        writeRegister(address + 1, value & 0xFF);
    }
}

uint8_t HPIB::readRegister(uint32_t address) {
    address &= 7;

    printf("HP-IB: read register %u\n", address);

    return 0;
}

void HPIB::writeRegister(uint32_t address, uint8_t value) {
    address &= 7;
    
    if(address != 5)
        printf("HP-IB: write %02X to register %u\n", value, address);
}
