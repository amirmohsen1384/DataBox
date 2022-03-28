#include "include/infoeditor.h"
#include "include/photoview.h"
#include "ui_infoeditor.h"
#include <QFileDialog>

InfoEditor::InfoEditor(QWidget *parent) : QDialog(parent)
{
    setupEditor();
}
InfoEditor::InfoEditor(const InfoContainer &initContainer, QWidget *parent) : QDialog(parent), resetContainer(initContainer)
{
    setupEditor();
    resetEditor();
}
void InfoEditor::resetFirstName()
{
    ui->containerFirstName->setText(resetContainer.firstName);
}
void InfoEditor::resetLastName()
{
    ui->containerLastName->setText(resetContainer.lastName);
}
void InfoEditor::resetFatherName()
{
    ui->containerFatherName->setText(resetContainer.fatherName);
}
void InfoEditor::resetBirthday()
{
    ui->containerBirthday->setDate(resetContainer.birthday);
}
void InfoEditor::resetGender()
{
    switch(resetContainer.gender)
    {
    case InfoContainer::GenderContainer::Male: {
       ui->radioButtonMale->setChecked(true);
       break;
    }
    case InfoContainer::GenderContainer::Female: {
        ui->radioButtonFemale->setChecked(true);
        break;
    }
    }
}
void InfoEditor::resetNationality()
{
    ui->containerNationality->setText(resetContainer.nationality);
}
void InfoEditor::resetBornProvince()
{
    ui->containerBornProvince->setText(resetContainer.bornProvince);
}
void InfoEditor::resetPhoto()
{
    containerPhoto->setCurrentPhoto(resetContainer.photo);
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
    connect(ui->buttonResetFirstName, &QPushButton::clicked, this, &InfoEditor::resetFirstName);
    connect(ui->buttonResetLastName, &QPushButton::clicked, this, &InfoEditor::resetLastName);
    connect(ui->buttonResetFatherName, &QPushButton::clicked, this, &InfoEditor::resetFatherName);
    connect(ui->buttonResetGender, &QPushButton::clicked, this, &InfoEditor::resetGender);
    connect(ui->buttonResetBirthday, &QPushButton::clicked, this, &InfoEditor::resetBirthday);
    connect(ui->buttonResetNationality, &QPushButton::clicked, this, &InfoEditor::resetNationality);
    connect(ui->buttonResetBornProvince, &QPushButton::clicked, this, &InfoEditor::resetBornProvince);
    connect(ui->buttonResetPhoto, &QPushButton::clicked, this, &InfoEditor::resetPhoto);
    connect(ui->buttonResetAll, &QPushButton::clicked, this, &InfoEditor::resetEditor);
    connect(ui->buttonLocalBrowser, &QPushButton::clicked, this, [=]()
    {
        QFileDialog fileBrowser(this, "Select a photo to continue", QDir::homePath());
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
const InfoContainer &InfoEditor::infoContainer() const
{
    return resultContainer;
}
void InfoEditor::setInfoContainer(const InfoContainer &tempContainer)
{
    resetContainer = tempContainer;
    resultContainer = InfoContainer();
    resetEditor();
}
void InfoEditor::accept()
{ 
    {
        const QString errorString = "This should be filled.";
        if(ui->containerFirstName->text().isEmpty()) {
            ui->containerFirstName->setPlaceholderText(errorString);
            return;
        }
        else if(ui->containerLastName->text().isEmpty()) {
            ui->containerLastName->setPlaceholderText(errorString);
            return;
        }
    }
    resultContainer.firstName = ui->containerFirstName->text();
    resultContainer.lastName = ui->containerLastName->text();
    resultContainer.fatherName = ui->containerFatherName->text();
    if(ui->radioButtonMale->isChecked()) {
        resultContainer.gender = InfoContainer::GenderContainer::Male;
    }
    else if(ui->radioButtonFemale->isChecked()) {
        resultContainer.gender = InfoContainer::GenderContainer::Female;
    }
    resultContainer.birthday = ui->containerBirthday->date();
    resultContainer.bornProvince = ui->containerBornProvince->text();
    resultContainer.nationality = ui->containerNationality->text();
    resultContainer.photo = containerPhoto->currentPhoto();
    resultContainer.lastModification = QDateTime::currentDateTime();
    QDialog::accept();
}
