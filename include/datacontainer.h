#ifndef DATACONTAINER_H
#define DATACONTAINER_H

#include <QPixmap>
#include <QDateTime>

class DataContainer
{
public:
    enum class GenderContainer {Male = 0x01, Female = 0x02};
private:
    QString m_firstName;
    QString m_lastName;
    QString m_fatherName;
    GenderContainer m_gender = GenderContainer::Male;
    QDate m_birthday = QDate::currentDate();
    QString m_nationality;
    QString m_bornProvince;
    QPixmap m_photo;
    QDateTime m_creation = QDateTime::currentDateTime();
    QDateTime m_lastModification = QDateTime::currentDateTime();
public:
    DataContainer() {}
    DataContainer(const DataContainer &value);
    DataContainer& operator=(const DataContainer &value);

    friend QDataStream& operator<<(QDataStream &stream, const DataContainer &target);
    friend QDataStream& operator>>(QDataStream &stream, DataContainer &target);
    friend bool operator==(const DataContainer &one, const DataContainer &two);
    friend inline bool operator!=(const DataContainer &one, const DataContainer &two);
    friend QDebug operator<<(QDebug debuggger, const DataContainer &target);
    friend class DataEditor;

    const QString& firstName() const;
    const QString& lastName() const;
    const QString& fatherName() const;
    const DataContainer::GenderContainer &gender() const;
    const QDate& birthday() const;
    const QString& nationality() const;
    const QString& bornProvince() const;
    const QPixmap& photo() const;
    const QDateTime& creation() const;
    const QDateTime& lastModification() const;

    QString toFullName() const;

    void setFirstName(const QString &value);
    void setLastName(const QString &value);
    void setFatherName(const QString &value);
    void setGender(const DataContainer::GenderContainer &value);
    void setBirthday(const QDate &value);
    void setBornProvince(const QString &value);
    void setNationality(const QString &value);
    void setPhoto(const QPixmap &value);
};

typedef QList<DataContainer> DataList;
typedef QListIterator<DataContainer> DataListIterator;

QDataStream& operator<<(QDataStream &stream, const DataContainer &target);
QDataStream& operator>>(QDataStream &stream, DataContainer &target);
QDebug operator<<(QDebug debugger, const DataContainer &target);

bool operator==(const DataContainer &one, const DataContainer &two);
inline bool operator!=(const DataContainer &one, const DataContainer &two) { return !(one == two); }

Q_DECLARE_METATYPE(DataContainer)

#endif // DATACONTAINER_H
