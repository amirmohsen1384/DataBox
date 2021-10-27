#include "../headers/dialogs.h"
#include <QStringList>
#include <QWidget>
#include <QFileDialog>
QStringList Dialogs::Open(QWidget *parent)
{
    QFileDialog openDialog(parent);
    openDialog.setAcceptMode(QFileDialog::AcceptOpen);
    openDialog.setNameFilter("PersonBox files (*.pbd)");
    openDialog.setFileMode(QFileDialog::ExistingFiles);
    if(openDialog.exec() == QDialog::Accepted)
        return openDialog.selectedFiles();
    else
        return QStringList();
}
QString Dialogs::Save(QWidget *parent)
{
    QFileDialog saveDialog(parent);
    saveDialog.setAcceptMode(QFileDialog::AcceptSave);
    saveDialog.setNameFilter("PersonBox files (*.pbd)");
    saveDialog.setFileMode(QFileDialog::AnyFile);
    if(saveDialog.exec() == QDialog::Accepted)
    {
        QString fileName = saveDialog.selectedFiles().at(0);
        QString suffix = QFileInfo(fileName).completeSuffix();
        if(suffix.isEmpty() || suffix != "pbd")
            fileName.append(".pbd");
        return fileName;
    }
    else
        return QString();
}
