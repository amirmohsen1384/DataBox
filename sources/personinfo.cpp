#include "../headers/personinfo.h"
#include <QDebug>

PersonInfo::PersonInfo(QObject *parent) : QObject(parent) {}
PersonInfo::PersonInfo(const PersonInfo &target, QObject *parent) : QObject(parent) { *this = target; }
QString PersonInfo::getFirstName() const { return firstName; }
QString PersonInfo::getLastName() const { return lastName; }
QString PersonInfo::getFatherName() const { return fatherName; }
QString PersonInfo::getGender() const { return gender; }
QString PersonInfo::getNationality() const { return nationality; }
QDate PersonInfo::getBirthday() const { return birthday; }
QString PersonInfo::getBornProvince() const { return bornProvince; }
QPixmap PersonInfo::getPhoto() const { return photo; }
void PersonInfo::setFirstName(const QString &value)
{
    firstName = value;
    emit firstNameChanged(value);
}
void PersonInfo::setLastName(const QString &value)
{
    lastName = value;
    emit lastNameChanged(value);
}
void PersonInfo::setFatherName(const QString &value)
{
    fatherName = value;;
    emit fatherNameChanged(value);  
}
void PersonInfo::setGender(const QString &value)
{
    gender = value;
    emit genderChanged(value);   
}
void PersonInfo::setBirthday(const QDate &value)
{
    birthday = value;;
    emit birthdayChanged(value);    
}
void PersonInfo::setNationality(const QString &value)
{
    nationality = value;
    emit nationalityChanged(value);    
}
void PersonInfo::setBornProvince(const QString &value)
{
    bornProvince = value;
    emit bornProvinceChanged(value);    
}
void PersonInfo::setPhoto(const QPixmap &value)
{
    photo = value;
    emit photoChanged(value);   
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
QString connectFirstAndLastName(const QString &firstName, const QString &lastName)
{
    QString result(firstName);
    if(!lastName.isEmpty())
        result.append(!firstName.isEmpty() ? ' ' + lastName : lastName);

    return result;
}
