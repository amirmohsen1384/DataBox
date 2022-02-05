#include <QSaveFile>
#include <QFileDialog>
#include <QListWidgetItem>
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
void saveDataToFile(const QString &fileName, const QList<QListWidgetItem*> &target)
{
    QSaveFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
        throw OpenFailedException();

    QDataStream stream(&file);

    MagicNumber::write(stream);
    if((stream << static_cast<quint64>(target.size())).status() != QDataStream::Ok)
        throw WriteFailedException();

    QListIterator<QListWidgetItem*> iterator(target);
    while(iterator.hasNext())
    {
        if((stream << *iterator.next()).status() != QDataStream::Ok)
            throw WriteFailedException();
    }
    file.commit();
}
void loadDataFromFile(const QString &fileName, QList<QListWidgetItem*> &target)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
        throw OpenFailedException();

    QDataStream stream(&file);

    MagicNumber::read(stream);

    quint64 size{};
    if((stream >> static_cast<quint64&>(size)).status() != QDataStream::Ok)
        throw CorruptFileException();

    target.clear();
    target.reserve(size);

    QListWidgetItem *item{};
    for(quint64 i = 0; i < size; ++i)
    {
        item = new QListWidgetItem;

        if((stream >> *item).status() != QDataStream::Ok)
            throw CorruptFileException();

        target.append(item);
    }

    file.close();
}
