#include <Windows.h>
#include <comdef.h>

#include "EEROM.h"

EEROM::EEROM(const wchar_t *filename, size_t size) : m_size(size) {
    HANDLE rawHandle = CreateFile(
        filename,
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        nullptr,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        nullptr);
    
    if (rawHandle == INVALID_HANDLE_VALUE)
        _com_raise_error(HRESULT_FROM_WIN32(GetLastError()));

    m_fileHandle.reset(rawHandle);

    rawHandle = CreateFileMapping(
        m_fileHandle.get(),
        nullptr,
        PAGE_READWRITE,
        0,
        size,
        nullptr);
    if (rawHandle == nullptr)
        _com_raise_error(HRESULT_FROM_WIN32(GetLastError()));
    m_mappingHandle.reset(rawHandle);

    void *rawMapping = MapViewOfFile(
        m_mappingHandle.get(),
        FILE_MAP_READ | FILE_MAP_WRITE,
        0,
        0,
        size);

    if(rawMapping == nullptr)
        _com_raise_error(HRESULT_FROM_WIN32(GetLastError()));

    m_mapping.reset(rawMapping);

}

EEROM::~EEROM() {

}

void EEROM::HandleDeleter::operator()(void *handle) {
    CloseHandle(handle);
}

void EEROM::MappingDeleter::operator()(void *mapping) {
    UnmapViewOfFile(mapping);
}

uint16_t EEROM::readMemory(uint32_t address, uint16_t mask) {
    auto val = reinterpret_cast<uint16_t *>(&static_cast<char *>(m_mapping.get())[address % m_size]);

    return _byteswap_ushort(*val);
}

void EEROM::writeMemory(uint32_t address, uint16_t value, uint16_t mask) {
    auto val = reinterpret_cast<uint16_t *>(&static_cast<char *>(m_mapping.get())[address % m_size]);

    *val = _byteswap_ushort((value & mask) | (_byteswap_ushort(*val) & ~mask));
}
