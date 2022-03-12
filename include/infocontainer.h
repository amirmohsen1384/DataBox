#ifndef INFOCONTAINER_H
#define INFOCONTAINER_H

#include <QObject>
#include <QPixmap>
#include <QDateTime>

class InfoContainer : public QObject
{
    Q_OBJECT
public:
    typedef QList<InfoContainer> List;
    typedef QListIterator<InfoContainer> ListIterator;
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
    explicit InfoContainer(QObject *parent = nullptr);
    InfoContainer(const InfoContainer &value, QObject *parent = nullptr);
    InfoContainer& operator=(const InfoContainer &dataItem);
    friend QDataStream& operator<<(QDataStream &stream, const InfoContainer &target);
    friend QDataStream& operator>>(QDataStream &stream, InfoContainer &target);
    friend bool operator==(const InfoContainer &one, const InfoContainer &two);
    friend bool operator!=(const InfoContainer &one, const InfoContainer &two);
    const QString& getFirstName() const;
    const QString& getLastName() const;
    const QString& getFatherName() const;
    const InfoContainer::GenderContainer &getGender() const;
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
    void setGender(const InfoContainer::GenderContainer &value);
    void setBirthday(const QDate &value);
    void setBornProvince(const QString &value);
    void setNationality(const QString &value);
    void setPhoto(const QPixmap &value);
};

QDataStream& operator<<(QDataStream &stream, const InfoContainer &target);
QDataStream& operator>>(QDataStream &stream, InfoContainer &target);
bool operator==(const InfoContainer &one, const InfoContainer &two);
bool operator!=(const InfoContainer &one, const InfoContainer &two);

Q_DECLARE_METATYPE(InfoContainer)

#endif // INFOCONTAINER_H
