#include <QApplication>
#include "emulatorwindow.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    EmulatorWindow win;
    win.show();

    return app.exec();
}
