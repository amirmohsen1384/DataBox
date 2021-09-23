#include "headers/rootwindow.h"
#include <QApplication>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    RootWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
