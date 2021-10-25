#include "../headers/infoitem.h"

void InfoItem::setInitialProperties()
{
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    item->setBackground(QBrush(Qt::white));
    item->setCheckState(Qt::Unchecked);
    connect(&info, &PersonInfo::firstNameChanged, this, &InfoItem::updateLastModifiedDateTime);
    connect(&info, &PersonInfo::lastNameChanged, this, &InfoItem::updateLastModifiedDateTime);
    connect(&info, &PersonInfo::fatherNameChanged, this, &InfoItem::updateLastModifiedDateTime);
    connect(&info, &PersonInfo::birthdayChanged, this, &InfoItem::updateLastModifiedDateTime);
    connect(&info, &PersonInfo::bornProvinceChanged, this, &InfoItem::updateLastModifiedDateTime);
    connect(&info, &PersonInfo::genderChanged, this, &InfoItem::updateLastModifiedDateTime);
    connect(&info, &PersonInfo::nationalityChanged, this, &InfoItem::updateLastModifiedDateTime);
    connect(&info, &PersonInfo::photoChanged, this, &InfoItem::updateLastModifiedDateTime);
}
void InfoItem::setCreatedDateTime(const QDateTime &date)
{
    createdDateTime = date;
    emit createdDateTimeChanged(createdDateTime);
}
void InfoItem::setLastModifiedDateTime(const QDateTime &date)
{
    lastModifiedDateTime = date;
    emit lastModifiedDateTimeChanged(lastModifiedDateTime);
}
void InfoItem::updateLastModifiedDateTime()
{
    setLastModifiedDateTime(QDateTime::currentDateTime());
}
InfoItem &InfoItem::operator=(const InfoItem &another)
{
    this->info = another.info;
    setItemText(another.item->text());
    setBackgroundColor(another.item->background().color());
    setTextColor(another.item->foreground().color());
    setHidden(another.item->isHidden());
    setChecked(another.isChecked());
    setHiddenInfo(another.hiddenInfo);
    setCreatedDateTime(another.createdDateTime);
    setLastModifiedDateTime(another.lastModifiedDateTime);
    return *this;
}
void InfoItem::setHiddenInfo(const HiddenInfoFlag &flag, bool active)
{
    hiddenInfo.setFlag(flag, active);
    emit hiddenInfoChanged(hiddenInfo);
}
void InfoItem::setHiddenInfo(const HiddenInfoFlags &flags)
{
    hiddenInfo = flags;
    emit hiddenInfoChanged(hiddenInfo);
}
void InfoItem::addToQListWidget(QListWidget *parent) const
{
    parent->addItem(item);
}
void InfoItem::insertToQListWidget(QListWidget *parent, int row) const
{
    parent->insertItem(row, item);
}
bool InfoItem::isPrivate() const
{
    return hiddenInfo.testFlag(HideEverything);
}
void InfoItem::setItemText(const QString &newText)
{
    item->setText(newText);
    emit itemTextChanged(newText);
    updateLastModifiedDateTime();
}
void InfoItem::setTextColor(const QColor &newColor)
{
    item->setTextColor(newColor);
    emit textColorChanged(newColor);
    updateLastModifiedDateTime();
}
void InfoItem::setBackgroundColor(const QColor &newColor)
{
    item->setBackgroundColor(newColor);
    emit backgroundColorChanged(newColor);
    updateLastModifiedDateTime();
}
void InfoItem::setChecked(const bool &newStatus)
{
    item->setCheckState(newStatus == true ? Qt::Checked : Qt::Unchecked);
    emit checkStatusChanged(newStatus);
    updateLastModifiedDateTime();
}
void InfoItem::setHidden(const bool &newStatus)
{
    item->setHidden(newStatus);
    emit hiddenStatusChanged(newStatus);
    updateLastModifiedDateTime();
}
InfoItem::InfoItem(QObject *parent) : QObject(parent)
{
    setInitialProperties();
}
InfoItem::InfoItem(const PersonInfo &data, QObject *parent) : QObject(parent)
{
    setInitialProperties();
    this->info = data;
}
InfoItem::InfoItem(const InfoItem &another, QObject *parent) : QObject(parent)
{
    setInitialProperties();
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
InfoItem::HiddenInfoFlags InfoItem::getHiddenInfo() const
{
    return hiddenInfo;
}
bool InfoItem::isChecked() const
{
    return (item->checkState() == Qt::Checked || item->checkState() == Qt::PartiallyChecked) ? true : false;
}
bool InfoItem::isHidden() const
{
    return item->isHidden();
}
QDateTime InfoItem::getCreatedDateTime() const
{
    return createdDateTime;
}
QDateTime InfoItem::getLastModifiedDateTime() const
{
    return lastModifiedDateTime;
}
QDataStream& operator<<(QDataStream &stream, const InfoItem &target)
{
    stream << *target.item << target.info << target.createdDateTime << target.lastModifiedDateTime << target.hiddenInfo;
    return stream;
}
QDataStream& operator>>(QDataStream &stream, InfoItem &target)
{
    stream >> *target.item >> target.info >> target.createdDateTime >> target.lastModifiedDateTime >> target.hiddenInfo;
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
    else if(one.hiddenInfo != two.hiddenInfo)
        return false;
    else if(one.info != two.info)
        return false;
    return true;
}
bool operator!=(const InfoItem &one, const InfoItem &two) { return !(one == two); }
QDataStream& operator<<(QDataStream &stream, const InfoItem::HiddenInfoFlags &target)
{
    stream << static_cast<quint32>(target);
    return stream;
}
QDataStream& operator>>(QDataStream &stream, InfoItem::HiddenInfoFlags &target)
{
    quint32 value;
    stream >> static_cast<quint32&>(value);
    target.setFlag(InfoItem::HideFirstName, (value & InfoItem::HideFirstName) == InfoItem::HideFirstName);
    target.setFlag(InfoItem::HiddenInfoFlag::HideLastName, (value & InfoItem::HideLastName) == InfoItem::HideLastName);
    target.setFlag(InfoItem::HideFatherName, (value & InfoItem::HideFatherName) == InfoItem::HideFatherName);
    target.setFlag(InfoItem::HideGender, (value & InfoItem::HideGender) == InfoItem::HideGender);
    target.setFlag(InfoItem::HideBirthday, (value & InfoItem::HideBirthday) == InfoItem::HideBirthday);
    target.setFlag(InfoItem::HideNationality, (value & InfoItem::HideNationality) == InfoItem::HideNationality);
    target.setFlag(InfoItem::HideBornProvince, (value & InfoItem::HideBornProvince) == InfoItem::HideBornProvince);
    target.setFlag(InfoItem::HidePhoto, (value & InfoItem::HidePhoto) == InfoItem::HidePhoto);
    return stream;
}
