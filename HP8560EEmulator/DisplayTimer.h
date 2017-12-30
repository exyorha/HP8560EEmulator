#ifndef DISPLAY_TIMER__H
#define DISPLAY_TIMER__H

class InterruptReceiver;

class DisplayTimer {
public:
    DisplayTimer(InterruptReceiver *receiver, unsigned int interruptLine);
    ~DisplayTimer();

    DisplayTimer(const DisplayTimer &other) = delete;
    DisplayTimer &operator =(const DisplayTimer &other) = delete;

    void cycles(unsigned int cycles);

    void setInterruptAck(bool ack);

private:
    enum : unsigned int {
        InterruptPeriod = 16000
    };

    InterruptReceiver *m_receiver;
    unsigned int m_interruptLine;
    unsigned int m_cyclesBeforeInterrupt;
    bool m_ack;
};

#endif
