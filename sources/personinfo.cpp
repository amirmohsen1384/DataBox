#include "../headers/personinfo.h"
#include <QDebug>

PersonInfo::PersonInfo(QObject *parent) : QObject(parent) {}
PersonInfo::PersonInfo(const PersonInfo &target, QObject *parent) : QObject(parent) { *this = target; }
QString PersonInfo::getFirstName() const { return firstName; }
QString PersonInfo::getLastName() const { return lastName; }
QString PersonInfo::getFatherName() const { return fatherName; }
PersonInfo::GenderType PersonInfo::getGender() const { return gender; }
QString PersonInfo::getNationality() const { return nationality; }
QDate PersonInfo::getBirthday() const { return birthday; }
QString PersonInfo::getBornProvince() const { return bornProvince; }
QPixmap PersonInfo::getPhoto() const { return photo; }
QDateTime PersonInfo::getCreated() const { return createdDateTime; }
QDateTime PersonInfo::getLastModified() const { return lastModifiedDateTime; }
PersonInfo::HiddenInfoFlags PersonInfo::getHiddenInfo() const { return hiddenInfo; }
void PersonInfo::setFirstName(const QString &value)
{
    firstName = value;
    lastModifiedDateTime = QDateTime::currentDateTime();
    emit firstNameChanged(value);
    emit lastModifiedChanged(lastModifiedDateTime);
}
void PersonInfo::setLastName(const QString &value)
{
    lastName = value;
    lastModifiedDateTime = QDateTime::currentDateTime();
    emit lastNameChanged(value);
    emit lastModifiedChanged(lastModifiedDateTime);
}
void PersonInfo::setFatherName(const QString &value)
{
    fatherName = value;
    lastModifiedDateTime = QDateTime::currentDateTime();
    emit fatherNameChanged(value);
    emit lastModifiedChanged(lastModifiedDateTime);
}
void PersonInfo::setGender(const PersonInfo::GenderType &value)
{
    gender = value;
    lastModifiedDateTime = QDateTime::currentDateTime();
    emit genderChanged(value);
    emit lastModifiedChanged(lastModifiedDateTime);
}
void PersonInfo::setBirthday(const QDate &value)
{
    birthday = value;
    lastModifiedDateTime = QDateTime::currentDateTime();
    emit birthdayChanged(value);
    emit lastModifiedChanged(lastModifiedDateTime);
}
void PersonInfo::setNationality(const QString &value)
{
    nationality = value;
    lastModifiedDateTime = QDateTime::currentDateTime();
    emit nationalityChanged(value);
    emit lastModifiedChanged(lastModifiedDateTime);
}
void PersonInfo::setBornProvince(const QString &value)
{
    bornProvince = value;
    lastModifiedDateTime = QDateTime::currentDateTime();
    emit bornProvinceChanged(value);
    emit lastModifiedChanged(lastModifiedDateTime);
}
void PersonInfo::setPhoto(const QPixmap &value)
{
    photo = value;
    lastModifiedDateTime = QDateTime::currentDateTime();
    emit photoChanged(value);
    emit lastModifiedChanged(lastModifiedDateTime);
}
void PersonInfo::setHiddenInfo(HiddenInfoFlag flag, bool active)
{
    hiddenInfo.setFlag(flag, active);
    lastModifiedDateTime = QDateTime::currentDateTime();
    emit hiddenInfoChanged(hiddenInfo);
    emit lastModifiedChanged(lastModifiedDateTime);
}
void PersonInfo::setHiddenInfo(HiddenInfoFlags flags)
{
    hiddenInfo = flags;
    lastModifiedDateTime = QDateTime::currentDateTime();
    emit hiddenInfoChanged(hiddenInfo);
    emit lastModifiedChanged(lastModifiedDateTime);
}
PersonInfo& PersonInfo::operator=(const PersonInfo &value)
{
    setFirstName(value.firstName);
    setLastName(value.lastName);
    setFatherName(value.fatherName);
    setGender(value.gender);
    setBirthday(value.birthday);
    setBornProvince(value.bornProvince);
    setNationality(value.nationality);
    setPhoto(value.photo);
    setHiddenInfo(value.hiddenInfo);
    return *this;
}
QDataStream& operator<<(QDataStream &stream, const PersonInfo &target)
{
    stream << target.firstName << target.lastName << target.fatherName << static_cast<quint16>(target.gender);
    stream << target.birthday << target.nationality << target.bornProvince << target.photo;
    stream << target.createdDateTime << target.lastModifiedDateTime << static_cast<quint32>(target.hiddenInfo);
    return stream;
}
QDataStream& operator>>(QDataStream &stream, PersonInfo &target)
{
    stream >> target.firstName >> target.lastName >> target.fatherName >> reinterpret_cast<quint16&>(target.gender);
    stream >> target.birthday >> target.nationality >> target.bornProvince >> target.photo;
    stream >> target.createdDateTime >> target.lastModifiedDateTime;
    quint32 value;
    stream >> static_cast<quint32&>(value);
    target.hiddenInfo.setFlag(PersonInfo::FirstName, (value & PersonInfo::FirstName) == PersonInfo::FirstName);
    target.hiddenInfo.setFlag(PersonInfo::HiddenInfoFlag::LastName, (value & PersonInfo::LastName) == PersonInfo::LastName);
    target.hiddenInfo.setFlag(PersonInfo::FatherName, (value & PersonInfo::FatherName) == PersonInfo::FatherName);
    target.hiddenInfo.setFlag(PersonInfo::Gender, (value & PersonInfo::Gender) == PersonInfo::Gender);
    target.hiddenInfo.setFlag(PersonInfo::Birthday, (value & PersonInfo::Birthday) == PersonInfo::Birthday);
    target.hiddenInfo.setFlag(PersonInfo::Nationality, (value & PersonInfo::Nationality) == PersonInfo::Nationality);
    target.hiddenInfo.setFlag(PersonInfo::BornProvince, (value & PersonInfo::BornProvince) == PersonInfo::BornProvince);
    target.hiddenInfo.setFlag(PersonInfo::Photo, (value & PersonInfo::Photo) == PersonInfo::Photo);
    target.hiddenInfo.setFlag(PersonInfo::Created, (value & PersonInfo::Created) == PersonInfo::Created);
    target.hiddenInfo.setFlag(PersonInfo::LastModified, (value & PersonInfo::LastModified) == PersonInfo::LastModified);
    return stream;
}
bool operator==(const PersonInfo &one, const PersonInfo &two)
{
    if(one.firstName != two.firstName)
        return false;
    else if(one.lastName != two.lastName)
        return false;
    else if(one.fatherName != two.fatherName)
        return false;
    else if(one.birthday != two.birthday)
        return false;
    else if(one.gender != two.gender)
        return false;
    else if(one.nationality != two.nationality)
        return false;
    else if(one.bornProvince != two.bornProvince)
        return false;
    else if(one.photo != two.photo)
        return false;

    return true;
}
bool operator!=(const PersonInfo &one, const PersonInfo &two) { return !(one == two); }
