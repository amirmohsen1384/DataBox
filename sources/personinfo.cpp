#include "../headers/personinfo.h"
PersonInfo::PersonInfo(QObject *parent) : QObject(parent) {}
PersonInfo::PersonInfo(const PersonInfo &target, QObject *parent) : QObject(parent) { *this = target; }
void PersonInfo::updateLastModifiedDateTime()
{
    lastModifiedDateTime = QDateTime::currentDateTime();
    emit lastModifiedDateTimeChanged(lastModifiedDateTime);
}
QString PersonInfo::getFirstName() const { return firstName; }
QString PersonInfo::getLastName() const { return lastName; }
QString PersonInfo::getFatherName() const { return fatherName; }
PersonInfo::GenderType PersonInfo::getGender() const { return gender; }
QString PersonInfo::getNationality() const { return nationality; }
QDate PersonInfo::getBirthday() const { return birthday; }
QString PersonInfo::getBornProvince() const { return bornProvince; }
QPixmap PersonInfo::getPhoto() const { return photo; }
QDateTime PersonInfo::getCreatedDateTime() const { return createdDateTime; }
QDateTime PersonInfo::getLastModifiedDateTime() const { return lastModifiedDateTime; }
PersonInfo::HiddenInfoFlags PersonInfo::getHiddenInfo() const { return hiddenInfo; }
void PersonInfo::setFirstName(const QString &value)
{
    firstName = value;
    emit firstNameChanged(value);
    updateLastModifiedDateTime();
}
void PersonInfo::setLastName(const QString &value)
{
    lastName = value;
    emit lastNameChanged(value);
    updateLastModifiedDateTime();
}
void PersonInfo::setFatherName(const QString &value)
{
    fatherName = value;;
    emit fatherNameChanged(value);
    updateLastModifiedDateTime();
}
void PersonInfo::setGender(const PersonInfo::GenderType &value)
{
    gender = value;
    emit genderChanged(value);
    updateLastModifiedDateTime();
}
void PersonInfo::setBirthday(const QDate &value)
{
    birthday = value;;
    emit birthdayChanged(value);
    updateLastModifiedDateTime();
}
void PersonInfo::setNationality(const QString &value)
{
    nationality = value;
    emit nationalityChanged(value);
    updateLastModifiedDateTime();
}
void PersonInfo::setBornProvince(const QString &value)
{
    bornProvince = value;
    emit bornProvinceChanged(value);
    updateLastModifiedDateTime();
}
void PersonInfo::setPhoto(const QPixmap &value)
{
    photo = value;
    emit photoChanged(value);
    updateLastModifiedDateTime();
}
void PersonInfo::setHiddenInfo(const HiddenInfoFlag &flag, bool active)
{
    hiddenInfo.setFlag(flag, active);
    emit hiddenInfoChanged(hiddenInfo);
    updateLastModifiedDateTime();
}
void PersonInfo::setHiddenInfo(const HiddenInfoFlags &flags)
{
    hiddenInfo = flags;
    emit hiddenInfoChanged(hiddenInfo);
    updateLastModifiedDateTime();
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
QDataStream& operator<<(QDataStream &stream, const PersonInfo::HiddenInfoFlags &target)
{
    stream << static_cast<quint32>(target);
    return stream;
}
QDataStream& operator>>(QDataStream &stream, PersonInfo::HiddenInfoFlags &target)
{
    quint32 value;
    stream >> static_cast<quint32&>(value);
    target.setFlag(PersonInfo::FirstName, (value & PersonInfo::FirstName) == PersonInfo::FirstName);
    target.setFlag(PersonInfo::HiddenInfoFlag::LastName, (value & PersonInfo::LastName) == PersonInfo::LastName);
    target.setFlag(PersonInfo::FatherName, (value & PersonInfo::FatherName) == PersonInfo::FatherName);
    target.setFlag(PersonInfo::Gender, (value & PersonInfo::Gender) == PersonInfo::Gender);
    target.setFlag(PersonInfo::Birthday, (value & PersonInfo::Birthday) == PersonInfo::Birthday);
    target.setFlag(PersonInfo::Nationality, (value & PersonInfo::Nationality) == PersonInfo::Nationality);
    target.setFlag(PersonInfo::BornProvince, (value & PersonInfo::BornProvince) == PersonInfo::BornProvince);
    target.setFlag(PersonInfo::Photo, (value & PersonInfo::Photo) == PersonInfo::Photo);
    target.setFlag(PersonInfo::CreatedDateTime, (value & PersonInfo::CreatedDateTime) == PersonInfo::CreatedDateTime);
    target.setFlag(PersonInfo::LastModifiedDateTime, (value & PersonInfo::LastModifiedDateTime) == PersonInfo::LastModifiedDateTime);
    return stream;
}
QDataStream& operator<<(QDataStream &stream, const PersonInfo &target)
{
    stream << target.firstName << target.lastName << target.fatherName << static_cast<quint16>(target.gender);
    stream << target.birthday << target.nationality << target.bornProvince << target.photo;
    stream << target.hiddenInfo << target.createdDateTime << target.lastModifiedDateTime;
    return stream;
}
QDataStream& operator>>(QDataStream &stream, PersonInfo &target)
{
    stream >> target.firstName >> target.lastName >> target.fatherName >> reinterpret_cast<quint16&>(target.gender);
    stream >> target.birthday >> target.nationality >> target.bornProvince >> target.photo;
    stream >> target.hiddenInfo >> target.createdDateTime >> target.lastModifiedDateTime;
    emit target.firstNameChanged(target.firstName);
    emit target.lastNameChanged(target.lastName);
    emit target.fatherNameChanged(target.fatherName);
    emit target.genderChanged(target.gender);
    emit target.birthdayChanged(target.birthday);
    emit target.nationalityChanged(target.nationality);
    emit target.bornProvinceChanged(target.bornProvince);
    emit target.photoChanged(target.photo);
    emit target.hiddenInfoChanged(target.hiddenInfo);
    emit target.createdDateTimeChanged(target.createdDateTime);
    emit target.lastModifiedDateTimeChanged(target.lastModifiedDateTime);
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
