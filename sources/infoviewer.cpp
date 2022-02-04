#include "headers/infoviewer.h"
#include "ui_infoviewer.h"
#include "headers/photoviewer.h"
#include "headers/personinfo.h"

void InfoViewer::displayInfo(const PersonInfo &information)
{
#define DISPLAY_PROPERTY(PROPERTY) \
    set##PROPERTY(information.get##PROPERTY());

    DISPLAY_PROPERTY(FirstName)
    DISPLAY_PROPERTY(LastName)
    DISPLAY_PROPERTY(FatherName)
    DISPLAY_PROPERTY(Birthday)
    DISPLAY_PROPERTY(BornProvince)
    DISPLAY_PROPERTY(Gender)
    DISPLAY_PROPERTY(Nationality)
    DISPLAY_PROPERTY(Photo)
    DISPLAY_PROPERTY(Creation)
    DISPLAY_PROPERTY(LastModification)

#undef DISPLAY_PROPERTY
}
void InfoViewer::connectPropertiesToView(const PersonInfo *information)
{
#define CONNECT_PROPERTY_TO_VIEW(SIGNAL, SETTER) \
    connect(information, &PersonInfo::SIGNAL, this, &InfoViewer::SETTER);

    CONNECT_PROPERTY_TO_VIEW(firstNameChanged, setFirstName)
    CONNECT_PROPERTY_TO_VIEW(lastNameChanged, setLastName)
    CONNECT_PROPERTY_TO_VIEW(fatherNameChanged, setFatherName)
    CONNECT_PROPERTY_TO_VIEW(birthdayChanged, setBirthday)
    CONNECT_PROPERTY_TO_VIEW(bornProvinceChanged, setBornProvince)
    CONNECT_PROPERTY_TO_VIEW(genderChanged, setGender)
    CONNECT_PROPERTY_TO_VIEW(nationalityChanged, setNationality)
    CONNECT_PROPERTY_TO_VIEW(photoChanged, setPhoto)
    CONNECT_PROPERTY_TO_VIEW(lastModificationChanged, setLastModification)

#undef CONNECT_PROPERTY_TO_VIEW
}
InfoViewer::InfoViewer(QWidget *parent) : QDialog(parent)
{
    setupUi();
}
InfoViewer::InfoViewer(const PersonInfo &information, QWidget *parent) : QDialog(parent)
{
    setupUi();
    displayInfo(information);
    connectPropertiesToView(&information);
}
InfoViewer::~InfoViewer()
{
    delete ui;
}
void InfoViewer::setupUi()
{
    ui = new Ui::InfoViewer;
    ui->setupUi(this);
    photoViewer = new PhotoViewer;
    photoViewer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->mainLayout->addWidget(photoViewer);
}
void InfoViewer::setFirstName(const QString &value)
{
    ui->labelFirstName->setText(value);
}
void InfoViewer::setLastName(const QString &value)
{
    ui->labelLastName->setText(value);
}
void InfoViewer::setFatherName(const QString &value)
{
    ui->labelFatherName->setText(value);
}
void InfoViewer::setBirthday(const QDate &value)
{
    ui->labelBirthday->setText(value.toString());
}
void InfoViewer::setBornProvince(const QString &value)
{
    ui->labelBornProvince->setText(value);
}
void InfoViewer::setGender(const QString &value)
{
    ui->labelGender->setText(value);
}
void InfoViewer::setNationality(const QString &value)
{
    ui->labelNationality->setText(value);
}
void InfoViewer::setPhoto(const QPixmap &value)
{
    photoViewer->setCurrentPhoto(value);
}
void InfoViewer::setCreation(const QDateTime &value)
{
    ui->labelCreation->setText(value.toString());
}
void InfoViewer::setLastModification(const QDateTime &value)
{
    ui->labelLastModification->setText(value.toString());
}
