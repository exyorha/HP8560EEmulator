#include "DisplayTimer.h"
#include "InterruptReceiver.h"

DisplayTimer::DisplayTimer(InterruptReceiver *receiver, unsigned int interruptLine) : 
    m_receiver(receiver), m_interruptLine(interruptLine),
    m_cyclesBeforeInterrupt(InterruptPeriod),
    m_ack(false) {

}

DisplayTimer::~DisplayTimer() {

}

void DisplayTimer::cycles(unsigned int cycles) {
    m_cyclesBeforeInterrupt -= cycles;
    if (static_cast<int>(m_cyclesBeforeInterrupt) < 0) {
        m_cyclesBeforeInterrupt += InterruptPeriod;
        m_receiver->setInterruptAsserted(m_interruptLine, true);
    }
}

void DisplayTimer::setInterruptAck(bool ack) {
    if (!m_ack && ack) {
        m_receiver->setInterruptAsserted(m_interruptLine, false);
    }

    m_ack = ack;
}
