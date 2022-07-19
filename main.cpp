#include <QApplication>
#include "include/dataeditor.h"
#include "include/dataviewer.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    DataEditor editor;
    if(editor.exec() == QDialog::Accepted) {
        DataViewer view(editor.container());
        view.exec();
    }

    return EXIT_SUCCESS;
}