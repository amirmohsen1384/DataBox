#include "include/personinfo.h"

PersonInfo::PersonInfo(QObject *parent) : QObject(parent) {}
PersonInfo::PersonInfo(const PersonInfo &target, QObject *parent) : QObject(parent) { *this = target; }
const QString& PersonInfo::getFirstName() const { return firstName; }
const QString&  PersonInfo::getLastName() const { return lastName; }
const QString& PersonInfo::getFatherName() const { return fatherName; }
const PersonInfo::GenderContainer& PersonInfo::getGender() const { return gender; }
const QString& PersonInfo::getNationality() const { return nationality; }
const QDate& PersonInfo::getBirthday() const { return birthday; }
const QString& PersonInfo::getBornProvince() const { return bornProvince; }
const QPixmap& PersonInfo::getPhoto() const { return photo; }
const QDateTime &PersonInfo::getCreation() const { return creation; }
const QDateTime &PersonInfo::getLastModification() const { return lastModification; }
void PersonInfo::setFirstName(const QString &value)
{
    firstName = value;
    lastModification = QDateTime::currentDateTime();
}
void PersonInfo::setLastName(const QString &value)
{
    lastName = value;
    lastModification = QDateTime::currentDateTime();
}
void PersonInfo::setFatherName(const QString &value)
{
    fatherName = value;
    lastModification = QDateTime::currentDateTime();
}
void PersonInfo::setGender(const PersonInfo::GenderContainer &value)
{
    gender = value;
    lastModification = QDateTime::currentDateTime();
}
void PersonInfo::setBirthday(const QDate &value)
{
    birthday = value;
    lastModification = QDateTime::currentDateTime();
}
void PersonInfo::setNationality(const QString &value)
{
    nationality = value;
    lastModification = QDateTime::currentDateTime();
}
void PersonInfo::setBornProvince(const QString &value)
{
    bornProvince = value;
    lastModification = QDateTime::currentDateTime();
}
void PersonInfo::setPhoto(const QPixmap &value)
{
    photo = value;
    lastModification = QDateTime::currentDateTime();
}
PersonInfo& PersonInfo::operator=(const PersonInfo &value)
{
    firstName = value.firstName;
    lastName = value.lastName;
    fatherName = value.fatherName;
    gender = value.gender;
    birthday = value.birthday;
    nationality = value.nationality;
    bornProvince = value.bornProvince;
    photo = value.photo;
    lastModification = QDateTime::currentDateTime();
    return *this;
}
QDataStream& operator<<(QDataStream &stream, const PersonInfo &target)
{
    stream << target.firstName << target.lastName << target.fatherName << static_cast<quint16>(target.gender);
    stream << target.birthday << target.nationality << target.bornProvince << target.photo;
    stream << target.creation << target.lastModification;
    return stream;
}
QDataStream& operator>>(QDataStream &stream, PersonInfo &target)
{
    stream >> target.firstName >> target.lastName >> target.fatherName >> reinterpret_cast<quint16&>(target.gender);
    stream >> target.birthday >> target.nationality >> target.bornProvince >> target.photo;
    stream >> target.creation >> target.lastModification;
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
    else if(one.photo.toImage() != two.photo.toImage())
        return false;

    return true;
}
bool operator!=(const PersonInfo &one, const PersonInfo &two) { return !(one == two); }
