TEMPLATE = app
QT += widgets
TARGET = HP8560EEmulator
SOURCES = main.cpp \
    emulatorwindow.cpp \
    displaywidget.cpp \
    simulatorthread.cpp \
    HP8560E.cpp \
    BusDevice.cpp \
    BusRouter.cpp \
    EmbeddedROM.cpp \
    Display.cpp \
    DisplayTimer.cpp \
    EEROM.cpp \
    RAM.cpp \
    HPIB.cpp \
    InterruptReceiver.cpp \
    RegisterSet.cpp \
    m68kcpu.c \
    m68kdasm.c \
    m68kopac.c \
    m68kopdm.c \
    m68kopnz.c \
    m68kops.c \
    DisplayHost.cpp \
    Keypad.cpp \
    BDFStream.cpp \
    BDFFile.cpp \
    BDFCharacter.cpp

FORMS += \
    emulatorwindow.ui

HEADERS += \
    emulatorwindow.h \
    displaywidget.h \
    simulatorthread.h \
    HP8560E.h \
    BusDevice.h \
    BusRouter.h \
    EmbeddedROM.h \
    Display.h \
    DisplayTimer.h \
    EEROM.h \
    RAM.h \
    HPIB.h \
    InterruptReceiver.h \
    RegisterSet.h \
    m68k.h \
    m68kconf.h \
    m68kcpu.h \
    m68kops.h \
    DisplayHost.h \
    Keypad.h \
    BDFStream.h \
    BDFGlyphOffsets.h \
    BDFFile.h \
    BDFBoundingBox.h \
    BDFCharacter.h

RC_FILE = hp8560e.rc

RESOURCES += \
    resources.qrc
