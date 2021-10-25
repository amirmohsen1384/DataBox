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
private:
    QString firstName, lastName, fatherName;
    PersonInfo::GenderType gender = PersonInfo::Male;
    QDate birthday = QDate::currentDate();
    QString nationality, bornProvince;
    QPixmap photo;
public:
    QString getFirstName() const;
    QString getLastName() const;
    QString getFatherName() const;
    PersonInfo::GenderType getGender() const;
    QDate getBirthday() const;
    QString getNationality() const;
    QString getBornProvince() const;
    QPixmap getPhoto() const;
public slots:
    void setFirstName(const QString &value);
    void setLastName(const QString &value);
    void setFatherName(const QString &value);
    void setGender(const PersonInfo::GenderType &value);
    void setBirthday(const QDate &value);
    void setBornProvince(const QString &value);
    void setNationality(const QString &value);
    void setPhoto(const QPixmap &value);
public:
    PersonInfo(QObject *parent = nullptr);
    PersonInfo(const PersonInfo &target, QObject *parent = nullptr);
    PersonInfo& operator=(const PersonInfo &dataItem);
    friend QDataStream& operator<<(QDataStream &stream, const PersonInfo &target);
    friend QDataStream& operator>>(QDataStream &stream, PersonInfo &target);
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
};
QDataStream& operator<<(QDataStream &stream, const PersonInfo &target);
QDataStream& operator>>(QDataStream &stream, PersonInfo &target);
bool operator==(const PersonInfo &one, const PersonInfo &two);
bool operator!=(const PersonInfo &one, const PersonInfo &two);
QString connectFirstAndLastName(const QString &firstName, const QString &lastName);
QString genderToString(const PersonInfo::GenderType &gender);
#endif // PERSONINFO_H
