#ifndef SIMULATORTHREAD_H
#define SIMULATORTHREAD_H

#include <QThread>

class DisplayHost;

class SimulatorThread final : public QThread {
    Q_OBJECT

public:
    explicit SimulatorThread(QObject *parent = 0);
    ~SimulatorThread();

    void setDisplay(DisplayHost *display);

    void setKeyState(unsigned int key, bool state);

protected:
    virtual void run();
};

#endif // SIMULATORTHREAD_H
