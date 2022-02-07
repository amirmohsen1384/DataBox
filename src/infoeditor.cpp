#include <QFileDialog>
#include "include/infoeditor.h"
#include "include/messages.h"
#include "ui_infoeditor.h"
#include "photoviewer.h"
void InfoEditor::initializeInformation(const PersonInfo &info)
{
#define ENTER_TEXTUAL_PROPERTY(PROPERTY) \
    ui->container##PROPERTY->setText(info.get##PROPERTY());

    ENTER_TEXTUAL_PROPERTY(FirstName)
    ENTER_TEXTUAL_PROPERTY(LastName)
    ENTER_TEXTUAL_PROPERTY(FatherName)
    ENTER_TEXTUAL_PROPERTY(Nationality)
    ENTER_TEXTUAL_PROPERTY(BornProvince)

    QString gender = info.getGender();
    if(gender == "Male")
        ui->radioButtonMale->setChecked(true);
    else if(gender == "Female")
        ui->radioButtonFemale->setChecked(true);

    ui->containerBirthday->setDate(info.getBirthday());
    photoViewer->setCurrentPhoto(info.getPhoto());

#undef ENTER_TEXTUAL_PROPERTY
}
void InfoEditor::setupUi()
{
    ui = new Ui::InfoEditor;
    ui->setupUi(this);

    photoViewer = new PhotoViewer;
    photoViewer->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    ui->photoLayout->insertWidget(0, photoViewer);

    connect(ui->buttonOk, &QPushButton::clicked, this, &InfoEditor::accept);
    connect(ui->buttonCancel, &QPushButton::clicked, this, &InfoEditor::reject);
}
void InfoEditor::accept()
{ 
    if(ui->containerFirstName->text().isEmpty())
    {
        const QString errorString = "This should be filled.";

        ui->containerFirstName->setPlaceholderText(errorString);
        if(ui->containerLastName->text().isEmpty())
            ui->containerLastName->setPlaceholderText(errorString);

        return;
    }

#define APPLY_TEXTUAL_PROPERTY(PROPERTY) \
    currentInfo.set##PROPERTY(ui->container##PROPERTY->text());

    APPLY_TEXTUAL_PROPERTY(FirstName)
    APPLY_TEXTUAL_PROPERTY(LastName)
    APPLY_TEXTUAL_PROPERTY(FatherName)
    APPLY_TEXTUAL_PROPERTY(BornProvince)
    APPLY_TEXTUAL_PROPERTY(Nationality)

    if(ui->radioButtonMale->isChecked())
        currentInfo.setGender("Male");

    else if(ui->radioButtonFemale->isChecked())
        currentInfo.setGender("Female");

    currentInfo.setBirthday(ui->containerBirthday->date());
    currentInfo.setPhoto(photoViewer->getCurrentPhoto());

#undef APPLY_TEXTUAL_PROPERTY
    QDialog::accept();
}
InfoEditor::InfoEditor(const PersonInfo &information, QWidget *parent) : QDialog(parent)
{
    setupUi();
    currentInfo = information;
    defaultInfo = information;
    initializeInformation(information);
}
const PersonInfo &InfoEditor::retrieve() const { return currentInfo; }
InfoEditor::~InfoEditor() { delete ui; }
void InfoEditor::on_buttonBrowsePC_clicked()
{
    QFileDialog dialog;
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setNameFilters({"JPG files (*.jpg *.jpeg)", "PNG files (*.png)", "BMP files (*.bmp)"});
    dialog.setFileMode(QFileDialog::ExistingFile);
    if(dialog.exec() == QDialog::Accepted)
        photoViewer->setCurrentPhoto(dialog.selectedFiles().constFirst());
}
InfoEditor::InfoEditor(QWidget *parent) : QDialog(parent) { setupUi(); }

#define RESET_TEXTUAL_PROPERTY(PROPERTY) \
    ui->container##PROPERTY->setText(defaultInfo.get##PROPERTY());

void InfoEditor::on_buttonResetFirstName_clicked()
{
    RESET_TEXTUAL_PROPERTY(FirstName)
}
void InfoEditor::on_buttonResetLastName_clicked()
{
    RESET_TEXTUAL_PROPERTY(LastName)
}
void InfoEditor::on_buttonResetFatherName_clicked()
{
    RESET_TEXTUAL_PROPERTY(FatherName)
}
void InfoEditor::on_buttonResetBirthday_clicked()
{
    ui->containerBirthday->setDate(defaultInfo.getBirthday());
}
void InfoEditor::on_buttonResetNationality_clicked()
{
    RESET_TEXTUAL_PROPERTY(Nationality)
}
void InfoEditor::on_buttonResetBornProvince_clicked()
{
    RESET_TEXTUAL_PROPERTY(BornProvince)
}
void InfoEditor::on_buttonResetGender_clicked()
{
    QString gender = defaultInfo.getGender();
    if(gender == "Male")
    {
        ui->radioButtonMale->setChecked(true);
    }
    else if(gender == "Female")
    {
        ui->radioButtonFemale->setChecked(true);
    }
}
void InfoEditor::on_buttonResetPhoto_clicked()
{
    photoViewer->setCurrentPhoto(defaultInfo.getPhoto());
}

