#include "../headers/personinfowidget.h"
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include "../headers/photoviewer.h"
// Define constructor and destructor
PersonInfoWidget::PersonInfoWidget(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QHBoxLayout(this);
    infoLayout = new QGridLayout;
    mainLayout->addLayout(infoLayout);
}
PersonInfoWidget::~PersonInfoWidget()
{
    destructName();
    destructFatherName();
    destructBirthday();
    destructBornProvince();
    destructGender();
    destructNationality();
    destructCreatedDateTime();
    destructLastModifiedDateTime();
    delete infoLayout;

    destructPhoto();
    delete mainLayout;
}
// Show first name and last name
void PersonInfoWidget::constructName()
{
    if(!nameExists())
    {
        nameLabel = new QLabel("Name: ");
        nameText = new QLabel;
        infoLayout->addWidget(nameLabel, 0, 0, Qt::AlignLeft);
        infoLayout->addWidget(nameText, 0, 1, Qt::AlignLeft);
        emit nameConstructed();
    }
}
bool PersonInfoWidget::nameExists() const
{
    return nameLabel != nullptr && nameText != nullptr;
}
void PersonInfoWidget::setName(const QString &newName)
{
    if(nameExists())
    {
        nameText->setText(newName);
        emit nameChanged(newName);
    }
}
QString PersonInfoWidget::getName() const
{
    if(!nameExists())
        return QString();

    return nameText->text();
}
void PersonInfoWidget::destructName()
{
    delete nameLabel;
    delete nameText;
    nameLabel = nameText = nullptr;
    emit nameDestructed();
}
// Show father's name
void PersonInfoWidget::constructFatherName()
{
    if(!fatherNameExists())
    {
        fatherNameLabel = new QLabel("Father's name: ");
        fatherNameText = new QLabel;
        infoLayout->addWidget(fatherNameLabel, 1, 0, Qt::AlignLeft);
        infoLayout->addWidget(fatherNameText, 1, 1, Qt::AlignLeft);
        emit fatherNameConstructed();
    }
}
void PersonInfoWidget::setFatherName(const QString &newFatherName)
{
    if(fatherNameExists())
    {
        fatherNameText->setText(newFatherName);
        emit fatherNameChanged(newFatherName);
    }
}
QString PersonInfoWidget::getFatherName() const
{
    if(!fatherNameExists())
        return QString();

    return fatherNameText->text();
}
bool PersonInfoWidget::fatherNameExists() const
{
    return fatherNameLabel != nullptr && fatherNameText != nullptr;
}
void PersonInfoWidget::destructFatherName()
{
    delete fatherNameLabel;
    delete fatherNameText;
    fatherNameLabel = fatherNameText = nullptr;
    emit fatherNameDestructed();
}
// Show birthday
void PersonInfoWidget::constructBirthday()
{
    if(!birthdayExists())
    {
        birthdayLabel = new QLabel("Birthday: ");
        birthdayText = new QLabel;
        infoLayout->addWidget(birthdayLabel, 2, 0, Qt::AlignLeft);
        infoLayout->addWidget(birthdayText, 2, 1, Qt::AlignLeft);
        emit birthdayConstructed();
    }
}
void PersonInfoWidget::setBirthday(const QString &birthday)
{
    if(birthdayExists())
    {
        birthdayText->setText(birthday);
        emit birthdayChanged(birthday);
    }
}
QString PersonInfoWidget::getBirthday() const
{
    if(!birthdayExists())
        return QString();

    return birthdayText->text();
}
void PersonInfoWidget::destructBirthday()
{
    delete birthdayLabel;
    delete birthdayText;
    birthdayLabel = birthdayText = nullptr;
    emit birthdayDestructed();
}
bool PersonInfoWidget::birthdayExists() const
{
    return birthdayLabel != nullptr && birthdayText != nullptr;
}
// Born province
void PersonInfoWidget::constructBornProvince()
{
    if(!bornProvinceExists())
    {
        bornProvinceLabel = new QLabel("Born province: ");
        bornProvinceText = new QLabel;
        infoLayout->addWidget(bornProvinceLabel, 3, 0, Qt::AlignLeft);
        infoLayout->addWidget(bornProvinceText, 3, 1, Qt::AlignLeft);
        emit bornProvinceConstructed();
    }
}
bool PersonInfoWidget::bornProvinceExists() const
{
    return bornProvinceLabel != nullptr && bornProvinceText != nullptr;
}
QString PersonInfoWidget::getBornProvince() const
{
    if(!bornProvinceExists())
        return QString();

    return bornProvinceText->text();
}
void PersonInfoWidget::setBornProvince(const QString &newBornProvince)
{
    if(bornProvinceExists())
    {
        bornProvinceText->setText(newBornProvince);
        emit bornProvinceChanged(newBornProvince);
    }
}
void PersonInfoWidget::destructBornProvince()
{
    delete bornProvinceLabel;
    delete bornProvinceText;
    bornProvinceLabel = bornProvinceText = nullptr;
    emit bornProvinceDestructed();
}
// Show gender
void PersonInfoWidget::constructGender()
{
    if(!genderExists())
    {
        genderLabel = new QLabel("Gender: ");
        genderText = new QLabel;
        infoLayout->addWidget(genderLabel, 4, 0, Qt::AlignLeft);
        infoLayout->addWidget(genderText, 4, 1, Qt::AlignLeft);
        emit genderConstructed();
    }
}
void PersonInfoWidget::setGender(const QString &newGender)
{
    if(genderExists())
    {
        genderText->setText(newGender);
        emit genderChanged(newGender);
    }
}
QString PersonInfoWidget::getGender() const
{
    if(!genderExists())
        return QString();

    return genderText->text();
}
void PersonInfoWidget::destructGender()
{
    delete genderLabel;
    delete genderText;
    genderLabel = genderText = nullptr;
    emit genderDestructed();
}
bool PersonInfoWidget::genderExists() const
{
    return genderText != nullptr && genderLabel != nullptr;
}
// Show nationality
void PersonInfoWidget::constructNationality()
{
    if(!nationalityExists())
    {
        nationalityLabel = new QLabel("Nationality: ");
        nationalityText = new QLabel;
        infoLayout->addWidget(nationalityLabel, 5, 0, Qt::AlignLeft);
        infoLayout->addWidget(nationalityText, 5, 1, Qt::AlignLeft);
        emit nationalityConstructed();
    }
}
bool PersonInfoWidget::nationalityExists() const
{
    return nationalityLabel != nullptr && nationalityText != nullptr;
}
void PersonInfoWidget::setNationality(const QString &newNationality)
{
    if(nationalityExists())
    {
        nationalityText->setText(newNationality);
        emit nationalityChanged(newNationality);
    }
}
QString PersonInfoWidget::getNationality() const
{
    if(!nationalityExists())
        return QString();

    return nationalityText->text();
}
void PersonInfoWidget::destructNationality()
{
    delete nationalityLabel;
    delete nationalityText;
    nationalityLabel = nationalityText = nullptr;
    emit nationalityDestructed();
}
// Show created date and time
void PersonInfoWidget::constructCreatedDateTime()
{
    if(!createdDateTimeExists())
    {
        createdDateTimeLabel = new QLabel("Created in: ");
        createdDateTimeText = new QLabel;
        infoLayout->addWidget(createdDateTimeLabel, 6, 0, Qt::AlignLeft);
        infoLayout->addWidget(createdDateTimeText, 6, 1, Qt::AlignLeft);
        emit createdDateTimeConstructed();
    }
}
bool PersonInfoWidget::createdDateTimeExists() const
{
    return createdDateTimeLabel != nullptr && createdDateTimeText != nullptr;
}
void PersonInfoWidget::destructCreatedDateTime()
{
    delete createdDateTimeLabel;
    delete createdDateTimeText;
    createdDateTimeLabel = createdDateTimeText = nullptr;
    emit createdDateTimeDestructed();
}
void PersonInfoWidget::setCreatedDateTime(const QString &dateTime)
{
    if(createdDateTimeExists())
    {
        createdDateTimeText->setText(dateTime);
        emit createdDateTimeChanged(dateTime);
    }
}
QString PersonInfoWidget::getCreatedDateTime() const
{
    if(!createdDateTimeExists())
            return QString();

    return createdDateTimeText->text();
}
// Show last modified date and time
void PersonInfoWidget::destructLastModifiedDateTime()
{
    delete lastModifiedDateTimeLabel;
    delete lastModifiedDateTimeText;
    lastModifiedDateTimeLabel = lastModifiedDateTimeText = nullptr;
    emit lastModifiedDateTimeDestructed();
}
void PersonInfoWidget::constructLastModifiedDateTime()
{
    if(!lastModifiedDateTimeExists())
    {
        lastModifiedDateTimeLabel = new QLabel("Last modified in: ");
        lastModifiedDateTimeText = new QLabel;
        infoLayout->addWidget(lastModifiedDateTimeLabel, 7, 0, Qt::AlignLeft);
        infoLayout->addWidget(lastModifiedDateTimeText, 7, 1, Qt::AlignLeft);
        emit lastModifiedDateTimeConstructed();
    }
}
bool PersonInfoWidget::lastModifiedDateTimeExists() const
{
    return lastModifiedDateTimeLabel != nullptr && lastModifiedDateTimeText != nullptr;
}
void PersonInfoWidget::setLastModifiedDateTime(const QString &dateTime)
{
    if(lastModifiedDateTimeExists())
    {
        lastModifiedDateTimeText->setText(dateTime);
        emit lastModifiedDateTimeChanged(dateTime);
    }
}
QString PersonInfoWidget::getLastModifiedDateTime() const
{
    if(!lastModifiedDateTimeExists())
            return QString();

    return lastModifiedDateTimeText->text();
}
// Show photo
void PersonInfoWidget::constructPhoto()
{
    if(!photoExists())
    {
        photoContainer = new PhotoViewer;
        photoContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        mainLayout->addWidget(photoContainer);
        emit photoConstructed();
    }
}
void PersonInfoWidget::destructPhoto()
{
    delete photoContainer;
    photoContainer = nullptr;
    emit photoDestructed();
}
QPixmap PersonInfoWidget::getPhoto() const
{
    if(!photoExists())
        return QPixmap();

    return photoContainer->getCurrentPhoto();
}
void PersonInfoWidget::setPhoto(const QPixmap &photo)
{
    if(photoExists())
    {
        photoContainer->setCurrentPhoto(photo);
        emit photoChanged(photo);
    }
}
bool PersonInfoWidget::photoExists() const
{
    return photoContainer != nullptr;
}
