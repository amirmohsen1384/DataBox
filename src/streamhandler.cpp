#include <QSaveFile>
#include <QFileDialog>
#include "include/exceptions.h"
namespace Dialog
{
    QStringList open(QWidget *parent)
    {
        QFileDialog dialog(parent);
        dialog.setAcceptMode(QFileDialog::AcceptOpen);
        dialog.setNameFilter("PersonBox files (*.pbd)");
        dialog.setFileMode(QFileDialog::ExistingFiles);
        return dialog.exec() == QDialog::Accepted ? dialog.selectedFiles() : QStringList();
    }
    QString save(QWidget *parent)
    {
        QFileDialog dialog(parent);
        dialog.setAcceptMode(QFileDialog::AcceptSave);
        dialog.setNameFilter("PersonBox data files (*.pbd)");
        dialog.setFileMode(QFileDialog::AnyFile);
        dialog.setDefaultSuffix("pbd");
        return dialog.exec() == QDialog::Accepted ? dialog.selectedFiles().constFirst() : QString();
    }
}
namespace MagicNumber
{
    const quint64 magicNumber = 0xDA43EF756FFDBC5;
    void write(QDataStream &stream)
    {
        stream << static_cast<quint64>(magicNumber);
        if(stream.status() != QDataStream::Ok)
            throw WriteFailedException();
    }
    void read(QDataStream &stream)
    {
        quint64 readNumber;
        stream >> static_cast<quint64&>(readNumber);
        if(stream.status() != QDataStream::Ok)
            throw CorruptFileException();

        else if(readNumber != magicNumber)
            throw UnsupportedFormatException();
    }
}
