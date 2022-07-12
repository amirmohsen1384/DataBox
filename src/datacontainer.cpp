#include "include/datacontainer.h"

DataContainer::DataContainer(const DataContainer &value)
{
    *this = value;
}
QString DataContainer::fullName() const
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
    updateModified();
}
void DataContainer::setLastName(const QString &value)
{
    m_lastName = value;
    updateModified();
}
void DataContainer::setFatherName(const QString &value)
{
    m_fatherName = value;
    updateModified();
}
void DataContainer::setGender(const DataContainer::GenderContainer &value)
{
    m_gender = value;
    updateModified();
}
void DataContainer::setBirthday(const QDate &value)
{
    m_birthday = value;
    updateModified();
}
void DataContainer::setCountry(const QString &value)
{
    m_country = value;
    updateModified();
}
void DataContainer::setPhoto(const QPixmap &value)
{
    m_photo = value;
    updateModified();
}
DataContainer& DataContainer::operator=(const DataContainer &value)
{
    m_firstName = value.m_firstName;
    m_lastName = value.m_lastName;
    m_fatherName = value.m_fatherName;
    m_gender = value.m_gender;
    m_birthday = value.m_birthday;
    m_country = value.m_country;
    m_photo = value.m_photo;
    m_created = value.m_created;
    m_modified = value.m_modified;
    return *this;
}
const QString &DataContainer::firstName() const
{
    return m_firstName;
}
const QString &DataContainer::lastName() const
{
    return m_lastName;
}
const QString &DataContainer::fatherName() const
{
    return m_fatherName;
}
const DataContainer::GenderContainer &DataContainer::gender() const
{
    return m_gender;
}
const QDate &DataContainer::birthday() const
{
    return m_birthday;
}
const QString &DataContainer::country() const
{
    return m_country;
}
const QPixmap &DataContainer::photo() const
{
    return m_photo;
}
const QDateTime &DataContainer::created() const
{
    return m_created;
}
const QDateTime &DataContainer::modified() const
{
    return m_modified;
}
QDataStream& operator<<(QDataStream &stream, const DataContainer &target)
{
    stream << target.m_firstName << target.m_lastName << target.m_fatherName << target.m_gender;
    stream << target.m_birthday << target.m_country << target.m_photo << target.m_created << target.m_modified;
    return stream;
}
QDataStream& operator>>(QDataStream &stream, DataContainer &target)
{
    stream >> target.m_firstName >> target.m_lastName >> target.m_fatherName >> target.m_gender;
    stream >> target.m_birthday >> target.m_country >> target.m_photo >> target.m_created >> target.m_modified;
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
    }  else if(one.m_country != two.m_country) {
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
    debugger << "First name: " << target.m_firstName << '\n';
    debugger << "Last name: " << target.m_lastName << '\n';
    debugger << "Father name: " << target.m_fatherName << '\n';
    debugger << "Gender: " << (target.m_gender == DataContainer::GenderContainer::Male ? "Male" : "Female") << '\n';
    debugger << "Birthday: " << target.m_birthday.toString() << '\n';
    debugger << "Country: " << target.m_country << '\n';
    debugger << "Date created: " << target.m_created.toString() << '\n';
    debugger << "Date modified: " << target.m_modified.toString() << Qt::flush;
    return debugger;
}
