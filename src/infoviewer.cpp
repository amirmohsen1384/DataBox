#include "include/infoviewer.h"
#include "include/photoviewer.h"
#include "ui_infoviewer.h"

void InfoViewer::initViewer(const PersonInfo &information)
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
    DISPLAY_PROPERTY(LastModification)

#undef DISPLAY_PROPERTY
}
InfoViewer::InfoViewer(QWidget *parent) : QDialog(parent)
{
    setupUi();
}
InfoViewer::InfoViewer(const PersonInfo &information, QWidget *parent) : QDialog(parent)
{
    setupUi();
    initViewer(information);
}
InfoViewer::~InfoViewer()
{
    delete photoViewer;
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
void InfoViewer::setGender(const PersonInfo::GenderContainer &value)
{
    switch(value)
    {
    case PersonInfo::GenderContainer::Male: {
        ui->labelGender->setText("Male");
        break;
    }
    case PersonInfo::GenderContainer::Female: {
        ui->labelGender->setText("Female");
        break;
    }
    }
}
void InfoViewer::setNationality(const QString &value)
{
    ui->labelNationality->setText(value);
}
void InfoViewer::setPhoto(const QPixmap &value)
{
    photoViewer->setCurrentPhoto(value);
}
void InfoViewer::setLastModification(const QDateTime &value)
{
    ui->labelLastModification->setText(value.toString());
}
