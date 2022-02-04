#include <QFileDialog>
#include "headers/infoeditor.h"
#include "headers/messages.h"
#include "ui_infoeditor.h"
void InfoEditor::initializeInformation(const PersonInfo &info)
{
#define ENTER_TEXTUAL_PROPERTY(PROPERTY) \
    ui->container##PROPERTY->setText(info.get##PROPERTY());

    ENTER_TEXTUAL_PROPERTY(FirstName)
    ENTER_TEXTUAL_PROPERTY(LastName)
    ENTER_TEXTUAL_PROPERTY(FatherName)
    ENTER_TEXTUAL_PROPERTY(Nationality)
    ENTER_TEXTUAL_PROPERTY(BornProvince)

    ui->containerGender->setCurrentText(info.getGender());
    ui->containerBirthday->setDate(info.getBirthday());
    photoViewer->setCurrentPhoto(info.getPhoto());

#undef ENTER_TEXTUAL_PROPERTY
}
void InfoEditor::setupUi()
{
    ui = new Ui::InfoEditor;
    photoViewer = new PhotoViewer;
    photoViewer->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
    ui->photoLayout->insertWidget(0, photoViewer);
    connect(ui->buttonOk, &QPushButton::clicked, this, &InfoEditor::accept);
    connect(ui->buttonCancel, &QPushButton::clicked, this, &InfoEditor::reject);
}
void InfoEditor::accept()
{
    if(ui->containerFirstName->text().isEmpty())
        ui->containerFirstName->setPlaceholderText("<p style=\"color:red;\"><b>This should be filled.</p></b>");

    else if(ui->containerLastName->text().isEmpty())
        ui->containerLastName->setPlaceholderText("<p style=\"color:red;\"><b>This should be filled.</p></b>");

#define APPLY_TEXTUAL_PROPERTY(PROPERTY) \
    currentInfo->set##PROPERTY(ui->container##PROPERTY->text());

    APPLY_TEXTUAL_PROPERTY(FirstName)
    APPLY_TEXTUAL_PROPERTY(LastName)
    APPLY_TEXTUAL_PROPERTY(FatherName)
    APPLY_TEXTUAL_PROPERTY(BornProvince)
    APPLY_TEXTUAL_PROPERTY(Nationality)

    currentInfo->setBirthday(ui->containerBirthday->date());
    currentInfo->setGender(ui->containerGender->currentText());
    currentInfo->setPhoto(photoViewer->getCurrentPhoto());

#undef APPLY_TEXTUAL_PROPERTY
}
InfoEditor::InfoEditor(PersonInfo &information, QWidget *parent) : QDialog(parent)
{
    setupUi();
    currentInfo = &information;
    defaultInfo = information;
    initializeInformation(information);
}
const PersonInfo &InfoEditor::retrieve() const { return *currentInfo; }
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
InfoEditor::InfoEditor(QWidget *parent) : QDialog(parent)
{
    setupUi();
    currentInfo = new PersonInfo;
    defaultInfo = *currentInfo;
}
