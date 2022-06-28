#include "include/infocontainer.h"
InfoContainer::InfoContainer(const InfoContainer &value, QObject *parent) : QObject(parent)
{
    firstName = value.firstName;
    lastName = value.lastName;
    fatherName = value.fatherName;
    gender = value.gender;
    birthday = value.birthday;
    nationality = value.nationality;
    bornProvince = value.bornProvince;
    lastModification = value.lastModification;
    photo = value.photo;
}
const QString& InfoContainer::getFirstName() const
{
    return firstName;
}
const QString&  InfoContainer::getLastName() const
{
    return lastName;
}
const QString& InfoContainer::getFatherName() const
{
    return fatherName;
}
const InfoContainer::GenderContainer& InfoContainer::getGender() const
{
    return gender;
}
const QString& InfoContainer::getNationality() const
{
    return nationality;
}
const QDate& InfoContainer::getBirthday() const
{
    return birthday;
}
const QString& InfoContainer::getBornProvince() const
{
    return bornProvince;
}
const QPixmap& InfoContainer::getPhoto() const
{
    return photo;
}
const QDateTime &InfoContainer::getCreation() const
{
    return creation;
}
const QDateTime &InfoContainer::getLastModification() const
{
    return lastModification;
}
void InfoContainer::setFirstName(const QString &value)
{
    firstName = value;
    lastModification = QDateTime::currentDateTime();
}
void InfoContainer::setLastName(const QString &value)
{
    lastName = value;
    lastModification = QDateTime::currentDateTime();
}
void InfoContainer::setFatherName(const QString &value)
{
    fatherName = value;
    lastModification = QDateTime::currentDateTime();
}
void InfoContainer::setGender(const InfoContainer::GenderContainer &value)
{
    gender = value;
    lastModification = QDateTime::currentDateTime();
}
void InfoContainer::setBirthday(const QDate &value)
{
    birthday = value;
    lastModification = QDateTime::currentDateTime();
}
void InfoContainer::setNationality(const QString &value)
{
    nationality = value;
    lastModification = QDateTime::currentDateTime();
}
void InfoContainer::setBornProvince(const QString &value)
{
    bornProvince = value;
    lastModification = QDateTime::currentDateTime();
}
void InfoContainer::setPhoto(const QPixmap &value)
{
    photo = value;
    lastModification = QDateTime::currentDateTime();
}
InfoContainer& InfoContainer::operator=(const InfoContainer &value)
{
    firstName = value.firstName;
    lastName = value.lastName;
    fatherName = value.fatherName;
    gender = value.gender;
    birthday = value.birthday;
    nationality = value.nationality;
    bornProvince = value.bornProvince;
    photo = value.photo;
    creation = value.creation;
    lastModification = value.lastModification;
    return *this;
}
QDataStream& operator<<(QDataStream &stream, const InfoContainer &target)
{
    stream << target.firstName << target.lastName << target.fatherName << static_cast<quint16>(target.gender);
    stream << target.birthday << target.nationality << target.bornProvince << target.photo;
    stream << target.creation << target.lastModification;
    return stream;
}
QDataStream& operator>>(QDataStream &stream, InfoContainer &target)
{
    stream >> target.firstName >> target.lastName >> target.fatherName >> reinterpret_cast<quint16&>(target.gender);
    stream >> target.birthday >> target.nationality >> target.bornProvince >> target.photo;
    stream >> target.creation >> target.lastModification;
    return stream;
}
bool operator==(const InfoContainer &one, const InfoContainer &two)
{
    if(one.firstName != two.firstName) {
        return false;
    } else if(one.lastName != two.lastName) {
        return false;
    } else if(one.fatherName != two.fatherName) {
        return false;
    } else if(one.birthday != two.birthday) {
        return false;
    } else if(one.gender != two.gender) {
        return false;
    } else if(one.nationality != two.nationality) {
        return false;
    } else if(one.bornProvince != two.bornProvince) {
        return false;
    } else if(one.photo.toImage() != two.photo.toImage()) {
        return false;
    } else {
        return true;
    }
}
bool operator!=(const InfoContainer &one, const InfoContainer &two) { return !(one == two); }

#include <QDebug>
QDebug operator<<(QDebug debugger, const InfoContainer &target)
{
    QDebug output = debugger.noquote().nospace();
    output << "First name: " << target.firstName << Qt::endl;
    output << "Last name: " << target.lastName << Qt::endl;
    output << "Father name: " << target.fatherName << Qt::endl;
    output << "Gender: " << (target.gender == InfoContainer::GenderContainer::Male ? "Male" : "Female") << Qt::endl;
    output << "Birthday: " << target.birthday.toString() << Qt::endl;
    output << "Nationality: " << target.nationality << Qt::endl;
    output << "Born province: " << target.bornProvince << Qt::endl;
    output << "Creation: " << target.creation.toString() << Qt::endl;
    output << "Last Modification: " << target.lastModification.toString() << Qt::endl;
    return output;
}
