#include "headers/dialogs.h"
#include <QFileDialog>
QStringList Dialogs::Open(QWidget *parent)
{
    QFileDialog dialog(parent);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setNameFilter("PersonBox files (*.pbd)");
    dialog.setFileMode(QFileDialog::ExistingFiles);
    if(dialog.exec() == QDialog::Accepted)
        return dialog.selectedFiles();
    else
        return QStringList();
}
QString Dialogs::Save(QWidget *parent)
{
    QFileDialog dialog(parent);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setNameFilter("PersonBox data files (*.pbd)");
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setDefaultSuffix("pbd");
    if(dialog.exec() == QDialog::Accepted)
        return dialog.selectedFiles().constFirst();
    else
        return QString();
}
