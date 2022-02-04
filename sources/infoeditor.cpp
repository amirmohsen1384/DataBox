#include "headers/infoeditor.h"
#include "ui_infoeditor.h"
#include <QDebug>
#include <QFileDialog>
#include "headers/messages.h"

void InfoEditor::initializeInformation(const InfoItem *infoItem)
{
    // Initialize widgets to the currentInformation of "infoItem"
    const PersonInfo &information = infoItem->info;
    ui->containerFirstName->setText(information.getFirstName());
    ui->containerLastName->setText(information.getLastName());
    ui->containerFatherName->setText(information.getFatherName());
    ui->containerGender->setCurrentText(information.getGender());
    ui->containerBirthday->setDate(information.getBirthday());
    ui->containerNationality->setText(information.getNationality());
    ui->containerBornProvince->setText(information.getBornProvince());
    containerPhoto->setCurrentPhoto(information.getPhoto());
    ui->containerInfoTitle->setText(infoItem->getItemText());
    // Initialize hide flag widgets
    InfoItem::HiddenInfoFlags hiddenFlags = infoItem->getHiddenInfo();
    ui->hideFirstName->setChecked(hiddenFlags.testFlag(InfoItem::HideFirstName));
    ui->hideLastName->setChecked(hiddenFlags.testFlag(InfoItem::HideLastName));
    ui->hideFatherName->setChecked(hiddenFlags.testFlag(InfoItem::HideFatherName));
    ui->hideGender->setChecked(hiddenFlags.testFlag(InfoItem::HideGender));
    ui->hideBirthday->setChecked(hiddenFlags.testFlag(InfoItem::HideBirthday));
    ui->hideNationality->setChecked(hiddenFlags.testFlag(InfoItem::HideNationality));
    ui->hideBornProvince->setChecked(hiddenFlags.testFlag(InfoItem::HideBornProvince));
    ui->hidePhoto->setChecked(hiddenFlags.testFlag(InfoItem::HidePhoto));
    ui->hideCreation->setChecked(hiddenFlags.testFlag(InfoItem::HideCreatedDateTime));
    ui->hideLastModified->setChecked(hiddenFlags.testFlag(InfoItem::HideLastModifiedDateTime));
}
void InfoEditor::setInitialProperties()
{
    // Construct a photo viewer to show photos
    containerPhoto = new PhotoViewer;
    containerPhoto->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
    ui->photoLayout->insertWidget(0, containerPhoto);
    // Connect signals to related slots
    connect(ui->containerFirstName, &QLineEdit::textChanged, this, &InfoEditor::updateInfoTitle);
    connect(ui->containerLastName, &QLineEdit::textChanged, this, &InfoEditor::updateInfoTitle);
    connect(ui->buttonOk, &QPushButton::clicked, this, &InfoEditor::applyInformationAndClose);
    connect(ui->buttonApply, &QPushButton::clicked, this, &InfoEditor::applyInformation);
    connect(ui->buttonCancel, &QPushButton::clicked, this, &InfoEditor::reject);
}

bool InfoEditor::isInfoEnough()
{
    QString firstName = ui->containerFirstName->text();
    QString lastName = ui->containerLastName->text();
    QString infoTitle = ui->containerInfoTitle->text();
    if(firstName.isEmpty() || lastName.isEmpty() || infoTitle.isEmpty())
        return false;
    else
        return true;
}
bool InfoEditor::applyInformation()
{
    if(!isInfoEnough())
    {
        Messages::notEnoughInformation(this);
        return false;
    }
    // Update currentInformation stored in the main object of "InfoItem"
    currentInformation->info.setFirstName(ui->containerFirstName->text());
    currentInformation->info.setLastName(ui->containerLastName->text());
    currentInformation->info.setFatherName(ui->containerFatherName->text());
    currentInformation->info.setBirthday(ui->containerBirthday->date());
    currentInformation->info.setBornProvince(ui->containerBornProvince->text());
    currentInformation->info.setGender(ui->containerGender->currentText());
    currentInformation->info.setNationality(ui->containerNationality->text());
    currentInformation->info.setPhoto(containerPhoto->getCurrentPhoto());
    currentInformation->setHiddenInfo(InfoItem::HideFirstName, ui->hideFirstName->isChecked());
    currentInformation->setHiddenInfo(InfoItem::HideLastName, ui->hideLastName->isChecked());
    currentInformation->setHiddenInfo(InfoItem::HideFatherName, ui->hideFatherName->isChecked());
    currentInformation->setHiddenInfo(InfoItem::HideBirthday, ui->hideBirthday->isChecked());
    currentInformation->setHiddenInfo(InfoItem::HideBornProvince, ui->hideBornProvince->isChecked());
    currentInformation->setHiddenInfo(InfoItem::HideGender, ui->hideGender->isChecked());
    currentInformation->setHiddenInfo(InfoItem::HideNationality, ui->hideNationality->isChecked());
    currentInformation->setHiddenInfo(InfoItem::HidePhoto, ui->hidePhoto->isChecked());
    currentInformation->setHiddenInfo(InfoItem::HideCreatedDateTime, ui->hideCreation->isChecked());
    currentInformation->setHiddenInfo(InfoItem::HideLastModifiedDateTime, ui->hideLastModified->isChecked());
    currentInformation->setItemText(ui->containerInfoTitle->text());
    return true;
}
void InfoEditor::applyInformationAndClose()
{
    if(applyInformation() != true)
        return;
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
    ui->hideFirstName->setChecked(defaultInformation.getHiddenInfo().testFlag(InfoItem::HideFirstName));
}
void InfoEditor::on_resetLastNameButton_clicked()
{
    ui->containerLastName->setText(defaultInformation.info.getLastName());
    ui->hideLastName->setChecked(defaultInformation.getHiddenInfo().testFlag(InfoItem::HideLastName));
}
void InfoEditor::on_resetFatherNameButton_clicked()
{
    ui->containerFatherName->setText(defaultInformation.info.getFatherName());
    ui->hideFatherName->setChecked(defaultInformation.getHiddenInfo().testFlag(InfoItem::HideFatherName));
}
void InfoEditor::on_resetBirthdayButton_clicked()
{
    ui->containerBirthday->setDate(defaultInformation.info.getBirthday());
    ui->hideBirthday->setChecked(defaultInformation.getHiddenInfo().testFlag(InfoItem::HideBirthday));
}
void InfoEditor::on_resetGenderButton_clicked()
{
    ui->containerGender->setCurrentText(defaultInformation.info.getGender());
    ui->hideGender->setChecked(defaultInformation.getHiddenInfo().testFlag(InfoItem::HideGender));
}
void InfoEditor::on_resetNationalityButton_clicked()
{
    ui->containerNationality->setText(defaultInformation.info.getNationality());
    ui->hideNationality->setChecked(defaultInformation.getHiddenInfo().testFlag(InfoItem::HideNationality));
}
void InfoEditor::on_resetBornProvinceButton_clicked()
{
    ui->containerBornProvince->setText(defaultInformation.info.getBornProvince());
    ui->hideBornProvince->setChecked(defaultInformation.getHiddenInfo().testFlag(InfoItem::HideBornProvince));
}
void InfoEditor::on_resetPhotoButton_clicked()
{
    containerPhoto->setCurrentPhoto(defaultInformation.info.getPhoto());
    ui->hidePhoto->setChecked(defaultInformation.getHiddenInfo().testFlag(InfoItem::HidePhoto));
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
