#include "EmbeddedROM.h"

#include <Windows.h>
#include <comdef.h>
#include <stdio.h>

EmbeddedROM::EmbeddedROM(unsigned int resource) {
    auto firmwareResource = FindResource(nullptr, MAKEINTRESOURCE(resource), RT_RCDATA);
    if (!firmwareResource)
        _com_raise_error(HRESULT_FROM_WIN32(GetLastError()));

    m_romSize = SizeofResource(nullptr, firmwareResource);

    auto firmwareResourceGlobal = LoadResource(nullptr, firmwareResource);
    if (!firmwareResourceGlobal)
        _com_raise_error(HRESULT_FROM_WIN32(GetLastError()));

    m_rom = static_cast<const uint8_t *>(LockResource(firmwareResourceGlobal));
}

EmbeddedROM::~EmbeddedROM() {

}

uint16_t EmbeddedROM::readMemory(uint32_t address, uint16_t mask) {
    return _byteswap_ushort(*reinterpret_cast<const uint16_t *>(&m_rom[address % m_romSize]));
}

void EmbeddedROM::writeMemory(uint32_t address, uint16_t value, uint16_t mask) {
    fprintf(stderr, "EmbeddedROM(%p): address %08X is not writable\n", this, address);
}
