#include "emulatorwindow.h"
#include "ui_emulatorwindow.h"
#include "simulatorthread.h"

#include <QSignalMapper>

EmulatorWindow::EmulatorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EmulatorWindow) {
    ui->setupUi(this);

    m_keyPressedMapper = new QSignalMapper(this);
    m_keyReleasedMapper = new QSignalMapper(this);

#define MAP_KEY(name, index) \
    connect(ui->name, &QPushButton::pressed, m_keyPressedMapper, static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map)); \
    m_keyPressedMapper->setMapping(ui->name, index); \
    connect(ui->name, &QPushButton::released, m_keyReleasedMapper, static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map)); \
    m_keyReleasedMapper->setMapping(ui->name, index)

    MAP_KEY(config, 0);
    MAP_KEY(save, 1);
    MAP_KEY(recall, 2);
    MAP_KEY(kGHz, 3);
    MAP_KEY(kMHz, 4);
    MAP_KEY(kkHz, 5);
    MAP_KEY(kHz, 6);
    MAP_KEY(preset, 7);
    MAP_KEY(module, 8);
    MAP_KEY(trig, 9);
    MAP_KEY(display, 10);
    MAP_KEY(k9, 11);
    MAP_KEY(k6, 12);
    MAP_KEY(k3, 13);
    MAP_KEY(kMinusBkSp, 14);
    MAP_KEY(stepUp, 15);
    MAP_KEY(peakSearch, 16);
    MAP_KEY(bw, 17);
    MAP_KEY(trace, 18);
    MAP_KEY(k8, 19);
    MAP_KEY(k5, 20);
    MAP_KEY(k2, 21);
    MAP_KEY(kDot, 22);
    MAP_KEY(stepDown, 23);
    MAP_KEY(freqCount, 24);
    MAP_KEY(autoCouple, 25);
    MAP_KEY(mkrNext, 26);
    MAP_KEY(k7, 27);
    MAP_KEY(k4, 28);
    MAP_KEY(k1, 29);
    MAP_KEY(k0, 30);
    MAP_KEY(hold, 31);
    MAP_KEY(sweep, 32);
    MAP_KEY(softkey1, 33);
    MAP_KEY(softkey2, 34);
    MAP_KEY(softkey3, 35);
    MAP_KEY(softkey4, 36);
    MAP_KEY(softkey5, 37);
    MAP_KEY(softkey6, 38);
    MAP_KEY(mkr, 39);
    MAP_KEY(auxCtrl, 40);
    MAP_KEY(measUser, 41);
    MAP_KEY(cal, 42);
    MAP_KEY(copy, 43);
    MAP_KEY(sglSwp, 44);
    MAP_KEY(frequency, 45);
    MAP_KEY(span, 46);
    MAP_KEY(amplitude, 47);

#undef MAP_KEY

    connect(m_keyPressedMapper, static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped), this, &EmulatorWindow::onKeyPressed);
    connect(m_keyReleasedMapper, static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped), this, &EmulatorWindow::onKeyReleased);
    connect(ui->rpgCCW, &QPushButton::clicked, this, &EmulatorWindow::onRPGCCW);
    connect(ui->rpgCW, &QPushButton::clicked, this, &EmulatorWindow::onRPGCW);

    m_simulator = new SimulatorThread(this);
    m_simulator->setDisplay(ui->displayWidget);
    m_simulator->start();
}

EmulatorWindow::~EmulatorWindow() {
    m_simulator->requestInterruption();
    m_simulator->wait();

    delete ui;
}

void EmulatorWindow::onKeyPressed(int key) {
    m_simulator->setKeyState(key, true);
}

void EmulatorWindow::onKeyReleased(int key) {
    m_simulator->setKeyState(key, false);
}

void EmulatorWindow::onRPGCCW() {
    qDebug("RPG CCW");
}

void EmulatorWindow::onRPGCW() {
    qDebug("RPG CW");
}
