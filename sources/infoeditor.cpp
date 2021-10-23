#include "headers/infoeditor.h"
#include "ui_infoeditor.h"
#include <QDebug>
#include <QFileDialog>

void InfoEditor::initializeInformation(const InfoItem *infoItem)
{
    // Initialize widgets to the currentInformation of "infoItem"
    ui->containerFirstName->setText(infoItem->info.getFirstName());
    ui->containerLastName->setText(infoItem->info.getLastName());
    ui->containerFatherName->setText(infoItem->info.getFatherName());
    ui->containerGender->setCurrentIndex(infoItem->info.getGender());
    ui->containerBirthday->setDate(infoItem->info.getBirthday());
    ui->containerNationality->setText(infoItem->info.getNationality());
    ui->containerBornProvince->setText(infoItem->info.getBornProvince());
    containerPhoto->setCurrentPhoto(infoItem->info.getPhoto());
    ui->containerInfoTitle->setText(infoItem->getItemText());
    // Initialize disapperance flag widgets
    PersonInfo::HiddenInfoFlags hiddenFlags = infoItem->info.getHiddenInfo();
    ui->hideFirstName->setChecked(hiddenFlags.testFlag(PersonInfo::FirstName));
    ui->hideLastName->setChecked(hiddenFlags.testFlag(PersonInfo::LastName));
    ui->hideFatherName->setChecked(hiddenFlags.testFlag(PersonInfo::FatherName));
    ui->hideGender->setChecked(hiddenFlags.testFlag(PersonInfo::Gender));
    ui->hideBirthday->setChecked(hiddenFlags.testFlag(PersonInfo::Birthday));
    ui->hideNationality->setChecked(hiddenFlags.testFlag(PersonInfo::Nationality));
    ui->hideBornProvince->setChecked(hiddenFlags.testFlag(PersonInfo::BornProvince));
    ui->hidePhoto->setChecked(hiddenFlags.testFlag(PersonInfo::Photo));
    ui->hideCreation->setChecked(hiddenFlags.testFlag(PersonInfo::CreatedDateTime));
    ui->hideLastModified->setChecked(hiddenFlags.testFlag(PersonInfo::LastModifiedDateTime));
}
void InfoEditor::setInitialProperties()
{
    // Construct a photo viewer to show photos
    containerPhoto = new PhotoViewer;
    containerPhoto->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
    ui->photoLayout->insertWidget(0, containerPhoto);
    // Set data to the combobox containing gender
    ui->containerGender->setItemData(0, PersonInfo::Male);
    ui->containerGender->setItemData(1, PersonInfo::Female);
    // Connect signals to related slots
    connect(ui->containerFirstName, &QLineEdit::textChanged, this, &InfoEditor::updateInfoTitle);
    connect(ui->containerLastName, &QLineEdit::textChanged, this, &InfoEditor::updateInfoTitle);
    connect(ui->buttonOk, &QPushButton::clicked, this, &InfoEditor::applyInformationAndClose);
    connect(ui->buttonApply, &QPushButton::clicked, this, &InfoEditor::applyInformation);
    connect(ui->buttonCancel, &QPushButton::clicked, this, &InfoEditor::reject);
}
void InfoEditor::applyInformation()
{
    // Update currentInformation stored in the main object of "InfoItem"
    currentInformation->info.setFirstName(ui->containerFirstName->text());
    currentInformation->info.setLastName(ui->containerLastName->text());
    currentInformation->info.setFatherName(ui->containerFatherName->text());
    currentInformation->info.setBirthday(ui->containerBirthday->date());
    currentInformation->info.setBornProvince(ui->containerBornProvince->text());
    currentInformation->info.setGender(static_cast<PersonInfo::GenderType>(ui->containerGender->currentData().toInt()));
    currentInformation->info.setNationality(ui->containerNationality->text());
    currentInformation->info.setPhoto(containerPhoto->getCurrentPhoto());
    currentInformation->info.setHiddenInfo(PersonInfo::FirstName, ui->hideFirstName->isChecked());
    currentInformation->info.setHiddenInfo(PersonInfo::LastName, ui->hideLastName->isChecked());
    currentInformation->info.setHiddenInfo(PersonInfo::FatherName, ui->hideFatherName->isChecked());
    currentInformation->info.setHiddenInfo(PersonInfo::Birthday, ui->hideBirthday->isChecked());
    currentInformation->info.setHiddenInfo(PersonInfo::BornProvince, ui->hideBornProvince->isChecked());
    currentInformation->info.setHiddenInfo(PersonInfo::Gender, ui->hideGender->isChecked());
    currentInformation->info.setHiddenInfo(PersonInfo::Nationality, ui->hideNationality->isChecked());
    currentInformation->info.setHiddenInfo(PersonInfo::Photo, ui->hidePhoto->isChecked());
    currentInformation->info.setHiddenInfo(PersonInfo::CreatedDateTime, ui->hideCreation->isChecked());
    currentInformation->info.setHiddenInfo(PersonInfo::LastModifiedDateTime, ui->hideLastModified->isChecked());
    currentInformation->setItemText(ui->containerInfoTitle->text());
}
void InfoEditor::applyInformationAndClose()
{
    applyInformation();
    accept();
}
void InfoEditor::updateInfoTitle()
{
    QString name = connectFirstAndLastName(ui->containerFirstName->text(), ui->containerLastName->text());
    ui->containerInfoTitle->setText(name);
}
InfoEditor::InfoEditor(InfoItem &initialInformation, QWidget *parent) : QDialog(parent), ui(new Ui::InfoEditor)
{
    ui->setupUi(this);
    setInitialProperties();
    this->currentInformation = &initialInformation;
    this->defaultInformation = initialInformation;
    initializeInformation(this->currentInformation);
}
InfoItem *InfoEditor::getInformation() { return currentInformation; }
InfoEditor::~InfoEditor() { delete ui; }
void InfoEditor::on_buttonBrowsePC_clicked()
{
    QFileDialog fileDialog;
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setNameFilters({"JPG files (*.jpg *.jpeg)", "PNG files (*.png)", "BMP files (*.bmp)"});
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    if(fileDialog.exec() == QDialog::Accepted)
        containerPhoto->setCurrentPhoto(fileDialog.selectedFiles().at(0));
}
void InfoEditor::on_resetFirstNameButton_clicked()
{
    ui->containerFirstName->setText(defaultInformation.info.getFirstName());
    ui->hideFirstName->setChecked(defaultInformation.info.getHiddenInfo().testFlag(PersonInfo::FirstName));
}
void InfoEditor::on_resetLastNameButton_clicked()
{
    ui->containerLastName->setText(defaultInformation.info.getLastName());
    ui->hideLastName->setChecked(defaultInformation.info.getHiddenInfo().testFlag(PersonInfo::LastName));
}
void InfoEditor::on_resetFatherNameButton_clicked()
{
    ui->containerFatherName->setText(defaultInformation.info.getFatherName());
    ui->hideFatherName->setChecked(defaultInformation.info.getHiddenInfo().testFlag(PersonInfo::FatherName));
}
void InfoEditor::on_resetBirthdayButton_clicked()
{
    ui->containerBirthday->setDate(defaultInformation.info.getBirthday());
    ui->hideBirthday->setChecked(defaultInformation.info.getHiddenInfo().testFlag(PersonInfo::Birthday));
}
void InfoEditor::on_resetGenderButton_clicked()
{
    ui->containerGender->setCurrentIndex(defaultInformation.info.getGender() == PersonInfo::Male ? 0 : 1);
    ui->hideGender->setChecked(defaultInformation.info.getHiddenInfo().testFlag(PersonInfo::Gender));
}
void InfoEditor::on_resetNationalityButton_clicked()
{
    ui->containerNationality->setText(defaultInformation.info.getNationality());
    ui->hideNationality->setChecked(defaultInformation.info.getHiddenInfo().testFlag(PersonInfo::Nationality));
}
void InfoEditor::on_resetBornProvinceButton_clicked()
{
    ui->containerBornProvince->setText(defaultInformation.info.getBornProvince());
    ui->hideBornProvince->setChecked(defaultInformation.info.getHiddenInfo().testFlag(PersonInfo::BornProvince));
}
void InfoEditor::on_resetPhotoButton_clicked()
{
    containerPhoto->setCurrentPhoto(defaultInformation.info.getPhoto());
    ui->hidePhoto->setChecked(defaultInformation.info.getHiddenInfo().testFlag(PersonInfo::Photo));
}
void InfoEditor::on_resetTitleButton_clicked()
{
    ui->containerInfoTitle->setText(defaultInformation.getItemText());
}
void InfoEditor::on_buttonResetAll_clicked()
{
    initializeInformation(&defaultInformation);
}
InfoEditor::InfoEditor(QWidget *parent) : QDialog(parent), ui(new Ui::InfoEditor)
{
    ui->setupUi(this);
    setInitialProperties();
    currentInformation = new InfoItem;
    defaultInformation = *currentInformation;
    initializeInformation(currentInformation);
}
