#include <QApplication>
#include "include/dataeditor.h"
#include "include/dataviewer.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    DataContainer container;
    container.setFirstName("John");
    container.setLastName("Speraw");
    container.setFatherName("Michael");
    container.setBirthday(QDate(1971, 6, 9));
    container.setCountry("Japan");
    container.setGender(DataContainer::GenderContainer::Female);
    container.setPhoto(QPixmap("C:/Users/Amir Mohsen Ghasemi/Downloads/John Speraw.jpg"));

    DataEditor editor;
    editor.setContainer(&container);

    if(editor.exec() == QDialog::Accepted) {
        if(editor.container() != &container) {
            qDebug() << "FAILED! Checkout and try again!";
        }
        DataViewer view(*editor.container());
        view.exec();
    }

    return EXIT_SUCCESS;
}