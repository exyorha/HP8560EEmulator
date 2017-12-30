#ifndef EMULATORWINDOW_H
#define EMULATORWINDOW_H

#include <QMainWindow>

namespace Ui {
class EmulatorWindow;
}

class SimulatorThread;

QT_FORWARD_DECLARE_CLASS(QSignalMapper)

class EmulatorWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit EmulatorWindow(QWidget *parent = 0);
    virtual ~EmulatorWindow();

private slots:
    void onKeyPressed(int key);
    void onKeyReleased(int key);
    void onRPGCCW();
    void onRPGCW();

private:
    Ui::EmulatorWindow *ui;
    QSignalMapper *m_keyPressedMapper;
    QSignalMapper *m_keyReleasedMapper;
    SimulatorThread *m_simulator;
};

#endif // EMULATORWINDOW_H
