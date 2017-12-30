#ifndef EEROM__H
#define EEROM__H

#include "BusDevice.h"

#include <memory>

class EEROM final : public BusDevice {
public:
    EEROM(const wchar_t *filename, size_t size);
    ~EEROM();

    virtual uint16_t readMemory(uint32_t address, uint16_t mask) override;
    virtual void writeMemory(uint32_t address, uint16_t value, uint16_t mask) override;

private:
    struct HandleDeleter {
        void operator()(void *handle);
    };

    struct MappingDeleter {
        void operator()(void *handle);
    };

    std::unique_ptr<void, HandleDeleter> m_fileHandle;
    std::unique_ptr<void, HandleDeleter> m_mappingHandle;
    std::unique_ptr<void, MappingDeleter> m_mapping;
    size_t m_size;
};

#endif
