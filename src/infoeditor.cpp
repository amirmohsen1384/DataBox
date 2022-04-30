#include "include/infoeditor.h"
#include "include/photoview.h"
#include "ui_infoeditor.h"
#include <QFileDialog>

InfoEditor::InfoEditor(QWidget *parent) : QDialog(parent)
{
    setupEditor();
}
InfoEditor::InfoEditor(const InfoContainer &target, QWidget *parent) : QDialog(parent), data(target)
{
    setupEditor();
    resetEditor();
}
void InfoEditor::resetFirstName()
{
    ui->containerFirstName->setText(data.firstName);
}
void InfoEditor::resetLastName()
{
    ui->containerLastName->setText(data.lastName);
}
void InfoEditor::resetFatherName()
{
    ui->containerFatherName->setText(data.fatherName);
}
void InfoEditor::resetBirthday()
{
    ui->containerBirthday->setDate(data.birthday);
}
void InfoEditor::resetGender()
{
    using enum InfoContainer::GenderContainer;
    switch(data.gender)
    {
    case Male: {
       ui->radioButtonMale->setChecked(true);
       break;
    }
    case Female: {
        ui->radioButtonFemale->setChecked(true);
        break;
    }
    }
}
void InfoEditor::resetNationality()
{
    ui->containerNationality->setText(data.nationality);
}
void InfoEditor::resetBornProvince()
{
    ui->containerBornProvince->setText(data.bornProvince);
}
void InfoEditor::resetPhoto()
{
    containerPhoto->setCurrentPhoto(data.photo);
    resize(sizeHint());
}
void InfoEditor::resetEditor()
{
    resetFirstName();
    resetLastName();
    resetFatherName();
    resetBirthday();
    resetGender();
    resetNationality();
    resetBornProvince();
    resetPhoto();
}
void InfoEditor::setupEditor()
{
    ui = new Ui::InfoEditor;
    ui->setupUi(this);

    containerPhoto = new PhotoView(this);
    containerPhoto->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    ui->layoutPhoto->insertWidget(0, containerPhoto);

    ui->containerBirthday->setDate(QDate::currentDate());

#define INIT_RESET_PROPERTY(PROPERTY) \
    connect(ui->buttonReset##PROPERTY, &QPushButton::clicked, this, &InfoEditor::reset##PROPERTY);

    INIT_RESET_PROPERTY(FirstName)
    INIT_RESET_PROPERTY(LastName)
    INIT_RESET_PROPERTY(FatherName)
    INIT_RESET_PROPERTY(Gender)
    INIT_RESET_PROPERTY(Birthday)
    INIT_RESET_PROPERTY(BornProvince)
    INIT_RESET_PROPERTY(Nationality)
    INIT_RESET_PROPERTY(Photo)

#undef INIT_RESET_PROPERTY

    connect(ui->buttonResetAll, &QPushButton::clicked, this, &InfoEditor::resetEditor);
    connect(ui->buttonLocalBrowser, &QPushButton::clicked, this, [this]()
    {
        QDir homeDir = QDir::homePath();
        homeDir.cd("Pictures");

        QFileDialog fileBrowser(this, "Select a photo to continue");
        fileBrowser.setDirectory(homeDir);
        fileBrowser.setAcceptMode(QFileDialog::AcceptOpen);
        fileBrowser.setNameFilters({"JPG files (*.jpg *.jpeg)", "PNG files (*.png)", "BMP files (*.bmp)"});
        fileBrowser.setFileMode(QFileDialog::ExistingFile);

        if(fileBrowser.exec()) {
            containerPhoto->setCurrentPhoto(fileBrowser.selectedFiles().constFirst());
        }
    });
}
InfoEditor::~InfoEditor()
{
    delete ui;
}
const InfoContainer &InfoEditor::getData() const
{
    return data;
}
void InfoEditor::setData(const InfoContainer &target)
{
    data = target;
    resetEditor();
}
void InfoEditor::accept()
{ 
    {
        const QString error = "This has not been filled yet.";
#define VALIDATE_PROPERTY(PROPERTY) \
    if(ui->container##PROPERTY->text().isEmpty()) { \
        ui->container##PROPERTY->setPlaceholderText(error); \
        return; }

        VALIDATE_PROPERTY(FirstName)
        VALIDATE_PROPERTY(LastName)
        VALIDATE_PROPERTY(FatherName)
        VALIDATE_PROPERTY(BornProvince)
        VALIDATE_PROPERTY(Nationality)

#undef VALIDATE_PROPERTY
    }
    data.firstName = ui->containerFirstName->text();
    data.lastName = ui->containerLastName->text();
    data.fatherName = ui->containerFatherName->text();
    {
        using enum InfoContainer::GenderContainer;
        if(ui->radioButtonMale->isChecked()) {
            data.gender = Male;
        }
        else if(ui->radioButtonFemale->isChecked()) {
            data.gender = Female;
        }
    }
    data.birthday = ui->containerBirthday->date();
    data.bornProvince = ui->containerBornProvince->text();
    data.nationality = ui->containerNationality->text();
    data.photo = containerPhoto->currentPhoto();
    data.lastModification = QDateTime::currentDateTime();
    QDialog::accept();
}
