#include "../headers/personinfo.h"
#include <QDebug>

PersonInfo::PersonInfo(QObject *parent) : QObject(parent)
{
    connectToUpdateLastModification();
}
PersonInfo::PersonInfo(const PersonInfo &target, QObject *parent) : QObject(parent)
{
    *this = target;
    connectToUpdateLastModification();
}
void PersonInfo::updateLastModification()
{
    lastModification = QDateTime::currentDateTime();
    emit lastModificationChanged(lastModification);
}
const QString& PersonInfo::getFirstName() const { return firstName; }
const QString&  PersonInfo::getLastName() const { return lastName; }
const QString& PersonInfo::getFatherName() const { return fatherName; }
const QString& PersonInfo::getGender() const { return gender; }
const QString& PersonInfo::getNationality() const { return nationality; }
const QDate& PersonInfo::getBirthday() const { return birthday; }
const QString& PersonInfo::getBornProvince() const { return bornProvince; }
const QPixmap& PersonInfo::getPhoto() const { return photo; }
const QDateTime &PersonInfo::getCreation() const { return creation; }
const QDateTime &PersonInfo::getLastModification() const { return lastModification; }

void PersonInfo::setFirstName(const QString &value)
{
    firstName = value;
    emit firstNameChanged(firstName);
}
void PersonInfo::setLastName(const QString &value)
{
    lastName = value;
    emit lastNameChanged(lastName);
}
void PersonInfo::setFatherName(const QString &value)
{
    fatherName = value;;
    emit fatherNameChanged(fatherName);
}
void PersonInfo::setGender(const QString &value)
{
    gender = value;
    emit genderChanged(gender);
}
void PersonInfo::setBirthday(const QDate &value)
{
    birthday = value;;
    emit birthdayChanged(birthday);
}
void PersonInfo::setNationality(const QString &value)
{
    nationality = value;
    emit nationalityChanged(nationality);
}
void PersonInfo::setBornProvince(const QString &value)
{
    bornProvince = value;
    emit bornProvinceChanged(bornProvince);
}
void PersonInfo::setPhoto(const QPixmap &value)
{
    photo = value;
    emit photoChanged(photo);
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
    return *this;
}
void PersonInfo::connectToUpdateLastModification()
{
#define UPDATE_LAST_MODIFICATION_WHEN(SIGNAL) \
    connect(this, &PersonInfo::SIGNAL, this, &PersonInfo::updateLastModification);

    UPDATE_LAST_MODIFICATION_WHEN(firstNameChanged)
    UPDATE_LAST_MODIFICATION_WHEN(lastNameChanged)
    UPDATE_LAST_MODIFICATION_WHEN(fatherNameChanged)
    UPDATE_LAST_MODIFICATION_WHEN(birthdayChanged)
    UPDATE_LAST_MODIFICATION_WHEN(bornProvinceChanged)
    UPDATE_LAST_MODIFICATION_WHEN(genderChanged)
    UPDATE_LAST_MODIFICATION_WHEN(nationalityChanged)
    UPDATE_LAST_MODIFICATION_WHEN(photoChanged)

#undef UPDATE_LAST_MODIFICATION_WHEN
}
QDataStream& operator<<(QDataStream &stream, const PersonInfo &target)
{
    stream << target.firstName << target.lastName << target.fatherName << target.gender;
    stream << target.birthday << target.nationality << target.bornProvince << target.photo;
    return stream;
}
QDataStream& operator>>(QDataStream &stream, PersonInfo &target)
{
    stream >> target.firstName >> target.lastName >> target.fatherName >> target.gender;
    stream >> target.birthday >> target.nationality >> target.bornProvince >> target.photo;
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
