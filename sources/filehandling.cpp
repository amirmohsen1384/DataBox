#include "../headers/rootwindow.h"
#include "ui_rootwindow.h"
#include "../headers/dialogs.h"
#include "../headers/messages.h"
#include "../headers/exceptions.h"
#include <QSaveFile>
#include <QFileInfo>
#include <QFile>
#define MAGIC_NUMBER 0xDA43EF756FFDBC5
QDataStream& writeMagicNumber(QDataStream &stream)
{
    stream << static_cast<quint64>(MAGIC_NUMBER);
    if(stream.status() != QDataStream::Ok)
        throw WriteFailedException();

    return stream;
}
quint64 readMagicNumber(QDataStream &stream)
{
    quint64 magicNumber;
    stream >> static_cast<quint64&>(magicNumber);
    if(stream.status() != QDataStream::Ok)
        throw CorruptFileException();

    else if(magicNumber != MAGIC_NUMBER)
        throw UnsupportedFormatException();

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
            throw OpenFailedException();

        QDataStream stream(&file);
        readMagicNumber(stream);
        if((stream >> *workingSheet).status() != QDataStream::Ok)
            throw CorruptFileException();
    }
    catch(const AbstractException &exception)
    {
        exception.showMessage();
        if(first == nullptr)
            delete workingSheet;
        else
            first->wipe();
        return nullptr;
    }
    catch(...)
    {
        Messages::unknownError();
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
            throw OpenFailedException();

        QDataStream stream(&file);
        writeMagicNumber(stream);
        if((stream << target).status() != QDataStream::Ok)
            throw WriteFailedException();
    }
    catch(const AbstractException &exception)
    {
        exception.showMessage();
        file.cancelWriting();
        return nullptr;
    }
    catch(...)
    {
        Messages::unknownError();
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
