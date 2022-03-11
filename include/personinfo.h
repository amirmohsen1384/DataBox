#ifndef PERSONINFO_H
#define PERSONINFO_H

#include <QObject>
#include <QPixmap>
#include <QDateTime>

class PersonInfo : public QObject
{
    Q_OBJECT
public:
    typedef QList<PersonInfo> List;
    typedef QListIterator<PersonInfo> ListIterator;
    enum class GenderContainer {Male = 0x00, Female = 0x01}; Q_ENUM(GenderContainer)
private:
    QString firstName;
    QString lastName;
    QString fatherName;
    GenderContainer gender = GenderContainer::Male;
    QDate birthday = QDate::currentDate();
    QString nationality;
    QString bornProvince;
    QPixmap photo;
    QDateTime creation = QDateTime::currentDateTime();
    QDateTime lastModification = QDateTime::currentDateTime();
    friend class InfoModel;
public:
    explicit PersonInfo(QObject *parent = nullptr);
    PersonInfo(const PersonInfo &target, QObject *parent = nullptr);
    PersonInfo& operator=(const PersonInfo &dataItem);
    friend QDataStream& operator<<(QDataStream &stream, const PersonInfo &target);
    friend QDataStream& operator>>(QDataStream &stream, PersonInfo &target);
    friend bool operator==(const PersonInfo &one, const PersonInfo &two);
    friend bool operator!=(const PersonInfo &one, const PersonInfo &two);
    const QString& getFirstName() const;
    const QString& getLastName() const;
    const QString& getFatherName() const;
    const PersonInfo::GenderContainer &getGender() const;
    const QDate& getBirthday() const;
    const QString& getNationality() const;
    const QString& getBornProvince() const;
    const QPixmap& getPhoto() const;
    const QDateTime& getCreation() const;
    const QDateTime& getLastModification() const;
public slots:
    void setFirstName(const QString &value);
    void setLastName(const QString &value);
    void setFatherName(const QString &value);
    void setGender(const PersonInfo::GenderContainer &value);
    void setBirthday(const QDate &value);
    void setBornProvince(const QString &value);
    void setNationality(const QString &value);
    void setPhoto(const QPixmap &value);
};

QDataStream& operator<<(QDataStream &stream, const PersonInfo &target);
QDataStream& operator>>(QDataStream &stream, PersonInfo &target);
bool operator==(const PersonInfo &one, const PersonInfo &two);
bool operator!=(const PersonInfo &one, const PersonInfo &two);

Q_DECLARE_METATYPE(PersonInfo)

#endif // PERSONINFO_H
