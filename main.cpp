#include "channelcommandmodel.h"
#include "mainwindow.h"
#include <QApplication>
#include <QTableView>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    mainWindow.presetWindow->move(mainWindow.pos() += QPoint(mainWindow.width(), 0));

    return a.exec();
}
