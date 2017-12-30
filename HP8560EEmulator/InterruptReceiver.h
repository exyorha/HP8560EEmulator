#ifndef INTERRUPT_RECEIVER__H
#define INTERRUPT_RECEIVER__H

class InterruptReceiver {
protected:
    InterruptReceiver();
    ~InterruptReceiver();

public:
    InterruptReceiver(const InterruptReceiver &other) = delete;
    InterruptReceiver &operator =(const InterruptReceiver &other) = delete;

    virtual void setInterruptAsserted(unsigned int interrupt, bool asserted) = 0;
};

#endif
