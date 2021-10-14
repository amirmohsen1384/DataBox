#ifndef PERSONINFOWIDGET_H
#define PERSONINFOWIDGET_H
#include <QWidget>
class PhotoViewer;
class QLabel;
class QGridLayout;
class QHBoxLayout;
class PersonInfoWidget : public QWidget
{
    Q_OBJECT
    QHBoxLayout *mainLayout = nullptr;
    QGridLayout *infoLayout = nullptr;
    QLabel *nameLabel = nullptr, *nameText = nullptr;
    QLabel *fatherNameLabel = nullptr, *fatherNameText = nullptr;
    QLabel *genderLabel = nullptr, *genderText = nullptr;
    QLabel *birthdayLabel = nullptr, *birthdayText = nullptr;
    QLabel *bornProvinceLabel = nullptr, *bornProvinceText = nullptr;
    QLabel *nationalityLabel = nullptr, *nationalityText = nullptr;
    QLabel *createdDateTimeLabel = nullptr, *createdDateTimeText = nullptr;
    QLabel *lastModifiedDateTimeLabel = nullptr, *lastModifiedDateTimeText = nullptr;
    PhotoViewer *photoContainer = nullptr;
public:
    PersonInfoWidget(QWidget *parent = nullptr);
    ~PersonInfoWidget();

    void constructName();
    bool nameExists() const;
    void setName(const QString &newName);
    QString getName() const;
    void destructName();

    void constructFatherName();
    bool fatherNameExists() const;
    void setFatherName(const QString &newName);
    QString getFatherName() const;
    void destructFatherName();

    void constructGender();
    bool genderExists() const;
    void setGender(const QString &gender);
    QString getGender() const;
    void destructGender();

    void constructBirthday();
    bool birthdayExists() const;
    void setBirthday(const QString &birthday);
    QString getBirthday() const;
    void destructBirthday();

    void constructBornProvince();
    bool bornProvinceExists() const;
    void setBornProvince(const QString &newBornProvince);
    QString getBornProvince() const;
    void destructBornProvince();

    void constructNationality();
    bool nationalityExists() const;
    void setNationality(const QString &newNationality);
    QString getNationality() const;
    void destructNationality();

    void constructPhoto();
    bool photoExists() const;
    void setPhoto(const QPixmap &photo);
    QPixmap getPhoto() const;
    void destructPhoto();

    void constructCreatedDateTime();
    bool createdDateTimeExists() const;
    void setCreatedDateTime(const QString &dateTime);
    QString getCreatedDateTime() const;
    void destructCreatedDateTime();

    void constructLastModifiedDateTime();
    bool lastModifiedDateTimeExists() const;
    void setLastModifiedDateTime(const QString &dateTime);
    QString getLastModifiedDateTime() const;
    void destructLastModifiedDateTime();
signals:
    void nameConstructed();
    void nameChanged(const QString &newName);
    void nameDestructed();

    void fatherNameConstructed();
    void fatherNameChanged(const QString &newName);
    void fatherNameDestructed();

    void genderConstructed();
    void genderChanged(const QString &newName);
    void genderDestructed();

    void birthdayConstructed();
    void birthdayChanged(const QString &newName);
    void birthdayDestructed();

    void bornProvinceConstructed();
    void bornProvinceChanged(const QString &newName);
    void bornProvinceDestructed();

    void nationalityConstructed();
    void nationalityChanged(const QString &newName);
    void nationalityDestructed();

    void photoConstructed();
    void photoChanged(const QPixmap &newName);
    void photoDestructed();

    void createdDateTimeConstructed();
    void createdDateTimeChanged(const QString &date);
    void createdDateTimeDestructed();

    void lastModifiedDateTimeConstructed();
    void lastModifiedDateTimeChanged(const QString &date);
    void lastModifiedDateTimeDestructed();
};
#endif // PERSONINFOWIDGET_H
