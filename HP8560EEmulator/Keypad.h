#ifndef KEYPAD__H
#define KEYPAD__H

#include <stdint.h>
#include <mutex>
#include <bitset>

class InterruptReceiver;

class Keypad {
public:
    Keypad(InterruptReceiver *receiver, unsigned int interruptLine);
    ~Keypad();

    Keypad(const Keypad &other) = delete;
    Keypad &operator =(const Keypad &other) = delete;

    void setKeyState(unsigned int key, bool state);

    inline uint8_t readSENSE_KBD() {
        return m_senseKbd;
    }
    uint8_t readINT_PRIOR();

    void writeSCAN_KBD(uint16_t value, uint16_t mask);

    void tick();

private:
    InterruptReceiver *m_receiver;
    unsigned int m_interruptLine;
    uint8_t m_scanKbd, m_senseKbd;
    bool m_interruptRequestKeypad;
    std::mutex m_stateMutex;
    std::bitset<48> m_keypadState;
};

#endif
