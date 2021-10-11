#ifndef PERSONINFO_H
#define PERSONINFO_H
#include <QObject>
#include <QPixmap>
#include <QDateTime>
class PersonInfo : public QObject
{
    Q_OBJECT
public:
    typedef enum {Male = 0x00, Female = 0x01} GenderType;
    typedef enum {FirstName = 0x01,
                 LastName = 0x02,
                 FatherName = 0x04,
                 FirstNameAndLastName = FirstName | LastName,
                 Gender = 0x08,
                 Birthday = 0x10,
                 Nationality = 0x20,
                 BornProvince = 0x40,
                 Photo = 0x80,
                 CreatedDateTime = 0x100,
                 LastModifiedDateTime = 0x200} HiddenInfoFlag;
    Q_DECLARE_FLAGS(HiddenInfoFlags, HiddenInfoFlag)
private:
    QString firstName, lastName, fatherName;
    PersonInfo::GenderType gender = PersonInfo::Male;
    QDate birthday = QDate::currentDate();
    QString nationality, bornProvince;
    HiddenInfoFlags hiddenInfo;
    QPixmap photo;
    QDateTime createdDateTime = QDateTime::currentDateTime();
    QDateTime lastModifiedDateTime = QDateTime::currentDateTime();
private:
    void updateLastModifiedDateTime();
public:
    QString getFirstName() const;
    QString getLastName() const;
    QString getFatherName() const;
    PersonInfo::GenderType getGender() const;
    QDate getBirthday() const;
    QString getNationality() const;
    QString getBornProvince() const;
    QPixmap getPhoto() const;
    HiddenInfoFlags getHiddenInfo() const;
    QDateTime getCreatedDateTime() const;
    QDateTime getLastModifiedDateTime() const;
public slots:
    void setFirstName(const QString &value);
    void setLastName(const QString &value);
    void setFatherName(const QString &value);
    void setGender(const PersonInfo::GenderType &value);
    void setBirthday(const QDate &value);
    void setBornProvince(const QString &value);
    void setNationality(const QString &value);
    void setPhoto(const QPixmap &value);
    void setHiddenInfo(const HiddenInfoFlag &flag, bool active = true);
    void setHiddenInfo(const HiddenInfoFlags &flags);
public:
    PersonInfo(QObject *parent = nullptr);
    PersonInfo(const PersonInfo &target, QObject *parent = nullptr);
    PersonInfo& operator=(const PersonInfo &dataItem);
    friend QDataStream& operator<<(QDataStream &stream, const PersonInfo &target);
    friend QDataStream& operator>>(QDataStream &stream, PersonInfo &target);
    friend QDataStream& operator<<(QDataStream &stream, const HiddenInfoFlags &hiddenInfo);
    friend QDataStream& operator>>(QDataStream &stream, HiddenInfoFlags &hiddenInfo);
    friend bool operator==(const PersonInfo &one, const PersonInfo &two);
    friend bool operator!=(const PersonInfo &one, const PersonInfo &two);
signals:
    void firstNameChanged(const QString &value);
    void lastNameChanged(const QString &value);
    void fatherNameChanged(const QString &value);
    void genderChanged(const PersonInfo::GenderType &value);
    void birthdayChanged(const QDate &value);
    void bornProvinceChanged(const QString &value);
    void nationalityChanged(const QString &value);
    void photoChanged(const QPixmap &value);
    void hiddenInfoChanged(const HiddenInfoFlags &value);
    void createdDateTimeChanged(const QDateTime &value);
    void lastModifiedDateTimeChanged(const QDateTime &value);
};
Q_DECLARE_OPERATORS_FOR_FLAGS(PersonInfo::HiddenInfoFlags);
QDataStream& operator<<(QDataStream &stream, const PersonInfo &target);
QDataStream& operator>>(QDataStream &stream, PersonInfo &target);
bool operator==(const PersonInfo &one, const PersonInfo &two);
bool operator!=(const PersonInfo &one, const PersonInfo &two);
QString connectFirstAndLastName(const QString &firstName, const QString &lastName);
#endif // PERSONINFO_H
