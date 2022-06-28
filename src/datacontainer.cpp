#include "include/datacontainer.h"
DataContainer::DataContainer(const DataContainer &value)
{
    m_firstName = value.m_firstName;
    m_lastName = value.m_lastName;
    m_fatherName = value.m_fatherName;
    m_gender = value.m_gender;
    m_birthday = value.m_birthday;
    m_nationality = value.m_nationality;
    m_bornProvince = value.m_bornProvince;
    m_lastModification = value.m_lastModification;
    m_photo = value.m_photo;
}
const QString& DataContainer::firstName() const
{
    return m_firstName;
}
const QString&  DataContainer::lastName() const
{
    return m_lastName;
}
const QString& DataContainer::fatherName() const
{
    return m_fatherName;
}
const DataContainer::GenderContainer& DataContainer::gender() const
{
    return m_gender;
}
const QString& DataContainer::nationality() const
{
    return m_nationality;
}
const QDate& DataContainer::birthday() const
{
    return m_birthday;
}
const QString& DataContainer::bornProvince() const
{
    return m_bornProvince;
}
const QPixmap& DataContainer::photo() const
{
    return m_photo;
}
const QDateTime &DataContainer::creation() const
{
    return m_creation;
}
const QDateTime &DataContainer::lastModification() const
{
    return m_lastModification;
}
QString DataContainer::toFullName() const
{
    QString result = m_firstName;
    if(!m_lastName.isEmpty()) {
       result.append(QChar(' '));
       result.append(m_lastName);
    }
    return result;
}
void DataContainer::setFirstName(const QString &value)
{
    m_firstName = value;
    m_lastModification = QDateTime::currentDateTime();
}
void DataContainer::setLastName(const QString &value)
{
    m_lastName = value;
    m_lastModification = QDateTime::currentDateTime();
}
void DataContainer::setFatherName(const QString &value)
{
    m_fatherName = value;
    m_lastModification = QDateTime::currentDateTime();
}
void DataContainer::setGender(const DataContainer::GenderContainer &value)
{
    m_gender = value;
    m_lastModification = QDateTime::currentDateTime();
}
void DataContainer::setBirthday(const QDate &value)
{
    m_birthday = value;
    m_lastModification = QDateTime::currentDateTime();
}
void DataContainer::setNationality(const QString &value)
{
    m_nationality = value;
    m_lastModification = QDateTime::currentDateTime();
}
void DataContainer::setBornProvince(const QString &value)
{
    m_bornProvince = value;
    m_lastModification = QDateTime::currentDateTime();
}
void DataContainer::setPhoto(const QPixmap &value)
{
    m_photo = value;
    m_lastModification = QDateTime::currentDateTime();
}
DataContainer& DataContainer::operator=(const DataContainer &value)
{
    m_firstName = value.m_firstName;
    m_lastName = value.m_lastName;
    m_fatherName = value.m_fatherName;
    m_gender = value.m_gender;
    m_birthday = value.m_birthday;
    m_nationality = value.m_nationality;
    m_bornProvince = value.m_bornProvince;
    m_photo = value.m_photo;
    m_creation = value.m_creation;
    m_lastModification = value.m_lastModification;
    return *this;
}
QDataStream& operator<<(QDataStream &stream, const DataContainer &target)
{
    stream << target.m_firstName << target.m_lastName << target.m_fatherName << target.m_gender;
    stream << target.m_birthday << target.m_nationality << target.m_bornProvince << target.m_photo;
    stream << target.m_creation << target.m_lastModification;
    return stream;
}
QDataStream& operator>>(QDataStream &stream, DataContainer &target)
{
    stream >> target.m_firstName >> target.m_lastName >> target.m_fatherName >> target.m_gender;
    stream >> target.m_birthday >> target.m_nationality >> target.m_bornProvince >> target.m_photo;
    stream >> target.m_creation >> target.m_lastModification;
    return stream;
}
bool operator==(const DataContainer &one, const DataContainer &two)
{
    if(one.m_gender != two.m_gender) {
        return false;
    } else if(one.m_firstName != two.m_firstName) {
        return false;
    } else if(one.m_lastName != two.m_lastName) {
        return false;
    } else if(one.m_fatherName != two.m_fatherName) {
        return false;
    } else if(one.m_birthday != two.m_birthday) {
        return false;
    }  else if(one.m_nationality != two.m_nationality) {
        return false;
    } else if(one.m_bornProvince != two.m_bornProvince) {
        return false;
    } else if(one.m_photo.toImage() != two.m_photo.toImage()) {
        return false;
    } else {
        return true;
    }
}

#include <QDebug>
QDebug operator<<(QDebug debugger, const DataContainer &target)
{
    debugger.noquote().nospace();
    debugger << "First name: " << target.m_firstName << Qt::endl;
    debugger << "Last name: " << target.m_lastName << Qt::endl;
    debugger << "Father name: " << target.m_fatherName << Qt::endl;
    debugger << "Gender: " << (target.m_gender == DataContainer::GenderContainer::Male ? "Male" : "Female") << Qt::endl;
    debugger << "Birthday: " << target.m_birthday.toString() << Qt::endl;
    debugger << "Nationality: " << target.m_nationality << Qt::endl;
    debugger << "Born province: " << target.m_bornProvince << Qt::endl;
    debugger << "Creation: " << target.m_creation.toString() << Qt::endl;
    debugger << "Last Modification: " << target.m_lastModification.toString() << Qt::endl;
    return debugger;
}
