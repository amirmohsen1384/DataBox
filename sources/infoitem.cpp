#include "../headers/infoitem.h"

void InfoItem::setInitialItemProperties()
{
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    item->setCheckState(Qt::Unchecked);
}
InfoItem &InfoItem::operator=(const InfoItem &another)
{
    this->info = another.info;
    *this->item = *another.item;
    return *this;
}
void InfoItem::addToQListWidget(QListWidget *parent) const
{
    parent->addItem(item);
}
void InfoItem::insertToQListWidget(QListWidget *parent, int row) const
{
    parent->insertItem(row, item);
}
void InfoItem::setItemText(const QString &newText)
{
    item->setText(newText);
    emit itemTextChanged(newText);
}
void InfoItem::setTextColor(const QColor &newColor)
{
    item->setTextColor(newColor);
    emit textColorChanged(newColor);
}
void InfoItem::setBackgroundColor(const QColor &newColor)
{
    item->setBackgroundColor(newColor);
    emit backgroundColorChanged(newColor);
}
void InfoItem::setChecked(const bool &newStatus)
{
    item->setCheckState(newStatus == true ? Qt::Checked : Qt::Unchecked);
    emit checkStatusChanged(newStatus);
}
void InfoItem::setHidden(const bool &newStatus)
{
    item->setHidden(newStatus);
    emit hiddenStatusChanged(newStatus);
}
InfoItem::InfoItem(QObject *parent) : QObject(parent)
{
    setInitialItemProperties();
}
InfoItem::InfoItem(const PersonInfo &data, QObject *parent) : QObject(parent)
{
    setInitialItemProperties();
    this->info = data;
}
InfoItem::InfoItem(const InfoItem &another, QObject *parent) : QObject(parent)
{
    setInitialItemProperties();
    *this = another;
}
InfoItem::~InfoItem()
{
    delete item;
}
QString InfoItem::getItemText() const
{
    return item->text();
}
QColor InfoItem::getTextColor() const
{
    return item->textColor();
}
QColor InfoItem::getBackgroundColor() const
{
    return item->backgroundColor();
}
bool InfoItem::isChecked() const
{
    return (item->checkState() == Qt::Checked || item->checkState() == Qt::PartiallyChecked) ? true : false;
}
bool InfoItem::isHidden() const
{
    return item->isHidden();
}
QDataStream& operator<<(QDataStream &stream, const InfoItem &target)
{
    stream << *target.item << target.info;
    return stream;
}
QDataStream& operator>>(QDataStream &stream, InfoItem &target)
{
    stream >> *target.item >> target.info;
    return stream;
}
bool operator==(const InfoItem &one, const InfoItem &two)
{
    if(one.item->text() != two.item->text())
        return false;
    else if(one.isChecked() != two.isChecked())
        return false;
    else if(one.item->isHidden() != two.item->isHidden())
        return false;
    else if(one.item->textColor() != two.item->textColor())
        return false;
    else if(one.item->backgroundColor() != two.item->backgroundColor())
        return false;
    else if(one.info != two.info)
        return false;
    return true;
}
bool operator!=(const InfoItem &one, const InfoItem &two) { return !(one == two); }
