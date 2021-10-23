#include "../headers/rootwindow.h"
#include "ui_rootwindow.h"
#include "../headers/dialogs.h"
#include "../headers/messages.h"
#include <QSaveFile>
#include <QFileInfo>
#include <QFile>
#define MAGIC_NUMBER 0xDFA31EF67B90
#define WRITE_FAILED -1
#define CORRUPT_FILE -2
#define OPEN_FAILED -3
#define UNSUPPORTED_FORMAT -4

QDataStream& writeMagicNumber(QDataStream &stream)
{
    stream << static_cast<quint64>(MAGIC_NUMBER);
    if(stream.status() != QDataStream::Ok)
        throw WRITE_FAILED;
    return stream;
}
quint64 readMagicNumber(QDataStream &stream)
{
    quint64 magicNumber;
    stream >> static_cast<quint64&>(magicNumber);
    if(stream.status() != QDataStream::Ok)
        throw CORRUPT_FILE;
    return magicNumber;
}
void updateInfoSheetFileName(InfoSheet &sheet, const QString &fileName)
{
    sheet.recentFileName = fileName;
    sheet.setWindowTitle(QFileInfo(fileName).fileName());
}
InfoSheet* readSheetFromFile(const QString &fileName, InfoSheet *first = nullptr)
{
    InfoSheet *workingSheet = first;
    if(workingSheet == nullptr)
        workingSheet = new InfoSheet;

    QFile file(fileName);
    try
    {
        if(!file.open(QFile::ReadOnly))
            throw OPEN_FAILED;

        QDataStream stream(&file);
        if(readMagicNumber(stream) != MAGIC_NUMBER)
            throw UNSUPPORTED_FORMAT;

        if((stream >> *workingSheet).status() != QDataStream::Ok)
            throw CORRUPT_FILE;
    }
    catch(qint64 errorCode)
    {
        switch(errorCode)
        {
        case OPEN_FAILED:
            Messages::openFailed();
            break;
        case CORRUPT_FILE:
            Messages::corruptFile();
            break;
        case UNSUPPORTED_FORMAT:
            Messages::unsupportedFormat();
            break;
        }
        if(first == nullptr)
            delete workingSheet;
        else
            first->wipe();
        return nullptr;
    }
    updateInfoSheetFileName(*workingSheet, file.fileName());
    return workingSheet;
}
InfoSheet* writeSheetToFile(const QString &filename, InfoSheet &target)
{
    QSaveFile file(filename);
    try
    {
        if(!file.open(QFile::WriteOnly))
            throw OPEN_FAILED;

        QDataStream stream(&file);
        writeMagicNumber(stream);
        if((stream << target).status() != QDataStream::Ok)
            throw WRITE_FAILED;
    }
    catch(qint64 errorCode)
    {
        switch(errorCode)
        {
        case OPEN_FAILED:
            Messages::openFailed();
            break;
        case WRITE_FAILED:
            Messages::saveFailed();
            break;
        }
        return nullptr;
    }
    file.commit();
    updateInfoSheetFileName(target, file.fileName());
    return &target;
}
void RootWindow::on_actionOpen_triggered()
{
    QStringList files = Dialogs::Open(this);
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
    {
        Messages::noSheetFound(this);
        return;
    }
    QString targetFileName = !currentSheet->recentFileName.isEmpty() ? currentSheet->recentFileName : Dialogs::Save(this);
    if(!targetFileName.isEmpty())
    {
        writeSheetToFile(targetFileName, *currentSheet);
        ui->sheetViewer->setTabText(getCurrentIndex(), currentSheet->windowTitle());
    }
}
void RootWindow::on_actionSaveAs_triggered()
{
    InfoSheet *currentSheet = getCurrentSheet();
    if(currentSheet == nullptr)
    {
        Messages::noSheetFound(this);
        return;
    }
    QString targetFileName = Dialogs::Save(this);
    if(!targetFileName.isEmpty())
    {
        writeSheetToFile(targetFileName, *currentSheet);
        ui->sheetViewer->setTabText(getCurrentIndex(), currentSheet->windowTitle());
    }
}
