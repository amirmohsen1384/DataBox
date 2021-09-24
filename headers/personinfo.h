#ifndef PERSONINFO_H
#define PERSONINFO_H
#include <QObject>
#include <QDate>
#include <QPixmap>
#include <QListWidgetItem>
#include <QDateTime>

class PersonInfo : public QObject
{
    Q_OBJECT
public:
    // "Gender" enum type describes the gender of the person.
    typedef enum {Male = 0x01, Female = 0x02} GenderType;
    /* "HiddenInfoFlag" describes a set of flags used to specify which kind of
     * information should not be shown when showing the user information */
    typedef enum {FirstName = 0x01,
                 LastName = 0x02,
                 FatherName = 0x04,
                 FirstNameAndLastName = FirstName | LastName,
                 Gender = 0x08,
                 Birthday = 0x10,
                 Nationality = 0x20,
                 BornProvince = 0x40,
                 Photo = 0x80,
                 Created = 0x100,
                 LastModified = 0x200} HiddenInfoFlag;
    Q_DECLARE_FLAGS(HiddenInfoFlags, HiddenInfoFlag)
private:
    // Personal information about the person stored by this class.
    QString firstName, lastName, fatherName;
    PersonInfo::GenderType gender = PersonInfo::Male;
    QDate birthday = QDate::currentDate();
    QString nationality, bornProvince;
    HiddenInfoFlags hiddenInfo;
    QPixmap photo;
    // Information about the date and time in which the class is constructed or modified.
    QDateTime createdDateTime = QDateTime::currentDateTime();
    QDateTime lastModifiedDateTime = QDateTime::currentDateTime();
public:
    // Const member functions to retrieve stored data
    QString getFirstName() const;
    QString getLastName() const;
    QString getFatherName() const;
    PersonInfo::GenderType getGender() const;
    QDate getBirthday() const;
    QString getNationality() const;
    QString getBornProvince() const;
    QPixmap getPhoto() const;
    HiddenInfoFlags getHiddenInfo() const;
    QDateTime getCreated() const;
    QDateTime getLastModified() const;
public slots:
    // Member functions to modify the value of information
    void setFirstName(const QString &value);
    void setLastName(const QString &value);
    void setFatherName(const QString &value);
    void setGender(const PersonInfo::GenderType &value);
    void setBirthday(const QDate &value);
    void setBornProvince(const QString &value);
    void setNationality(const QString &value);
    void setPhoto(const QPixmap &value);
    void setHiddenInfo(HiddenInfoFlag flag, bool active = true);
    void setHiddenInfo(HiddenInfoFlags flags);
signals:
    // Signals emitted whenever a group of data has been changed.
    void firstNameChanged(const QString &value);
    void lastNameChanged(const QString &value);
    void fatherNameChanged(const QString &value);
    void genderChanged(const PersonInfo::GenderType &value);
    void birthdayChanged(const QDate &value);
    void bornProvinceChanged(const QString &value);
    void nationalityChanged(const QString &value);
    void photoChanged(const QPixmap &value);
    void hiddenInfoChanged(const HiddenInfoFlags &value);
    void lastModifiedChanged(const QDateTime &value);
public:
    PersonInfo(QObject *parent = nullptr);
    PersonInfo(const PersonInfo &target, QObject *parent = nullptr);
    PersonInfo& operator=(const PersonInfo &dataItem);
    friend QDataStream& operator<<(QDataStream &stream, const PersonInfo &target);
    friend QDataStream& operator>>(QDataStream &stream, PersonInfo &target);
};
Q_DECLARE_OPERATORS_FOR_FLAGS(PersonInfo::HiddenInfoFlags);
QDataStream& operator<<(QDataStream &stream, const PersonInfo &target);
QDataStream& operator>>(QDataStream &stream, PersonInfo &target);

#endif // PERSONINFO_H
