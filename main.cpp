#include <QApplication>
#include "include/dataviewer.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    DataViewer view;
    view.exec();

    return app.exec();
}