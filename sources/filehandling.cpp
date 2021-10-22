#include "../headers/rootwindow.h"
#include "ui_rootwindow.h"
#include <QMessageBox>
#include <QSaveFile>
#include <QFile>
#include <QFileDialog>
#define MAGIC_NUMBER 0xDFA31EF67B90
void showSaveFailed(QWidget *parent = nullptr)
{
    QMessageBox saveFailed;
    saveFailed.setParent(parent);
    saveFailed.setWindowTitle("Failed to write to file");
    saveFailed.setIcon(QMessageBox::Warning);
    saveFailed.setText("An error occurred when saving information");
    saveFailed.setInformativeText("The selected file is probably not allowed to be saved to.");
    saveFailed.exec();
}
void showOpenFailed(QWidget *parent = nullptr)
{
    QMessageBox openFailed;
    openFailed.setParent(parent);
    openFailed.setIcon(QMessageBox::Warning);
    openFailed.setWindowTitle("Failed to open file");
    openFailed.setText("The chosen filename is no longer available");
    openFailed.setInformativeText("Check if the selected file is not moved, renamed or unavailable and then try again");
    openFailed.exec();
}
void showWrongFormat(QWidget *parent = nullptr)
{
    QMessageBox wrongFormat;
    wrongFormat.setParent(parent);
    wrongFormat.setIcon(QMessageBox::Critical);
    wrongFormat.setWindowTitle("Failed to read from file");
    wrongFormat.setText("The selected file is corrupt or has an unsupported format.");
    wrongFormat.setInformativeText("Please select another one and try again");
    wrongFormat.exec();
}
QStringList showOpenDialog(QWidget *parent = nullptr)
{
    QFileDialog openDialog;
    openDialog.setParent(parent);
    openDialog.setAcceptMode(QFileDialog::AcceptOpen);
    openDialog.setNameFilter("PersonBox database files (*.pbd)");
    openDialog.setFileMode(QFileDialog::ExistingFiles);
    if(openDialog.exec() == QDialog::Accepted)
        return openDialog.selectedFiles();
    else
        return QStringList();
}
QString showSaveDialog(QWidget *parent = nullptr)
{
    QFileDialog saveDialog;
    saveDialog.setParent(parent);
    saveDialog.setAcceptMode(QFileDialog::AcceptSave);
    saveDialog.setNameFilter("PersonBox database files (*.pbd)");
    saveDialog.setFileMode(QFileDialog::AnyFile);
    if(saveDialog.exec() == QDialog::Accepted)
        return saveDialog.selectedFiles().at(0);
    else
        return QString();
}
QDataStream& writeMagicNumber(QDataStream &stream)
{
    stream << static_cast<quint64>(MAGIC_NUMBER);
    return stream;
}
QDataStream& readMagicNumber(QDataStream &stream)
{
    quint64 magicNumber;
    stream >> static_cast<quint64&>(magicNumber);
    if(magicNumber != MAGIC_NUMBER)
        stream.setStatus(QDataStream::ReadCorruptData);
    return stream;
}
void updateInfoSheetFileName(InfoSheet *sheet, const QString &fileName)
{
    if(sheet != nullptr)
    {
        sheet->recentFileName = fileName;
        sheet->setWindowTitle(QFileInfo(fileName).fileName());
    }
}
InfoSheet* readSheetFromFile(const QString &fileName, InfoSheet *first = nullptr)
{
    InfoSheet *workingSheet = first;
    if(workingSheet == nullptr)
        workingSheet = new InfoSheet;

    QFile file(fileName);
    if(!file.open(QFile::ReadOnly))
    {
        showOpenFailed();
        if(first == nullptr)
            delete workingSheet;
        else
            first->wipe();
        return nullptr;
    }
    QDataStream stream(&file);
    if(readMagicNumber(stream).status() != QDataStream::Ok)
    {
        showWrongFormat();
        if(first == nullptr)
            delete workingSheet;
        else
            first->wipe();
        return nullptr;
    }
    if((stream >> *workingSheet).status() != QDataStream::Ok)
    {
        showWrongFormat();
        if(first == nullptr)
            delete workingSheet;
        else
            first->wipe();
        return nullptr;
    }
    updateInfoSheetFileName(workingSheet, file.fileName());
    return workingSheet;
}
InfoSheet* writeSheetToFile(const QString &filename, InfoSheet *target)
{
    if(target == nullptr)
        return nullptr;

    QSaveFile file(filename);
    if(!file.open(QFile::WriteOnly))
    {
        showOpenFailed();
        return nullptr;
    }
    QDataStream stream(&file);
    if(writeMagicNumber(stream).status() != QDataStream::Ok || (stream << *target).status() != QDataStream::Ok)
    {
        showSaveFailed();
        return nullptr;
    }
    file.commit();
    updateInfoSheetFileName(target, file.fileName());

    return target;
}
void RootWindow::on_actionOpen_triggered()
{
    QStringList files = showOpenDialog();
    QStringListIterator iterator(files);
    if(!sheetContainer.isEmpty())
    {
        InfoSheet *lastSheet = sheetContainer.last();
        if(lastSheet->isEmpty() && iterator.hasNext())
        {
            readSheetFromFile(iterator.next(), lastSheet);
            ui->sheetViewer->setTabText(ui->sheetViewer->count() - 1, lastSheet->windowTitle());
        }
    }
    while(iterator.hasNext())
    {
        InfoSheet *sheet = readSheetFromFile(iterator.next());
        if(sheet != nullptr)
            createNewSheet(sheet);
    }
}
void RootWindow::on_actionSave_triggered()
{
    InfoSheet *currentSheet = getCurrentSheet();
    if(currentSheet == nullptr)
        return;
    QString targetFileName = !currentSheet->recentFileName.isEmpty() ? currentSheet->recentFileName : showSaveDialog();
    if(!targetFileName.isEmpty())
    {
        writeSheetToFile(targetFileName, currentSheet);
        ui->sheetViewer->setTabText(getCurrentIndex(), currentSheet->windowTitle());
    }
}
void RootWindow::on_actionSaveAs_triggered()
{
    InfoSheet *currentSheet = getCurrentSheet();
    if(currentSheet == nullptr)
        return;
    QString targetFileName = showSaveDialog();
    if(!targetFileName.isEmpty())
    {
        writeSheetToFile(targetFileName, currentSheet);
        ui->sheetViewer->setTabText(getCurrentIndex(), currentSheet->windowTitle());
    }
}
