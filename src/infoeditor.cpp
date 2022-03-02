#include "include/photoviewer.h"
#include "include/infoeditor.h"
#include "ui_infoeditor.h"
#include <QFileDialog>

void InfoEditor::setupUi()
{
    ui = new Ui::InfoEditor;
    ui->setupUi(this);

    photoViewer = new PhotoViewer;
    photoViewer->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    ui->photoLayout->insertWidget(0, photoViewer);

#define RESET_TEXTUAL_PROPERTY(PROPERTY) \
    ui->container##PROPERTY->setText(current.get##PROPERTY());

    connect(ui->buttonResetFirstName, &QPushButton::clicked, this, [=]()
    {
        RESET_TEXTUAL_PROPERTY(FirstName)
    });
    connect(ui->buttonResetLastName, &QPushButton::clicked, this, [=]()
    {
        RESET_TEXTUAL_PROPERTY(LastName)
    });
    connect(ui->buttonResetFatherName, &QPushButton::clicked, this, [=]()
    {
        RESET_TEXTUAL_PROPERTY(FatherName)
    });
    connect(ui->buttonResetNationality, &QPushButton::clicked, this, [=]()
    {
        RESET_TEXTUAL_PROPERTY(Nationality)
    });
    connect(ui->buttonResetBornProvince, &QPushButton::clicked, this, [=]()
    {
        RESET_TEXTUAL_PROPERTY(BornProvince)
    });

#undef RESET_TEXTUAL_PROPERTY

    connect(ui->buttonResetBirthday, &QPushButton::clicked, this, [=]()
    {
        ui->containerBirthday->setDate(current.getBirthday());
    });
    connect(ui->buttonResetGender, &QPushButton::clicked, this, [=]()
    {
        PersonInfo::GenderContainer data = current.getGender();
        if(data == PersonInfo::GenderContainer::Male) {
            ui->radioButtonMale->setChecked(true);
        } else {
            ui->radioButtonFemale->setEnabled(true);
        }
    });
    connect(ui->buttonResetPhoto, &QPushButton::clicked, this, [=]()
    {
        photoViewer->setCurrentPhoto(current.getPhoto());
    });
    connect(ui->buttonBrowsePC, &QPushButton::clicked, this, [=]()
    {
        QFileDialog dialog;
        dialog.setAcceptMode(QFileDialog::AcceptOpen);
        dialog.setNameFilters({"JPG files (*.jpg *.jpeg)", "PNG files (*.png)", "BMP files (*.bmp)"});
        dialog.setFileMode(QFileDialog::ExistingFile);
        if(dialog.exec()) {
            photoViewer->setCurrentPhoto(dialog.selectedFiles().constFirst());
        }
    });
    connect(ui->buttonOk, &QPushButton::clicked, this, &InfoEditor::accept);
    connect(ui->buttonCancel, &QPushButton::clicked, this, &InfoEditor::reject);
}
InfoEditor::InfoEditor(QWidget *parent) : QDialog(parent) { setupUi(); }
InfoEditor::InfoEditor(const PersonInfo &information, QWidget *parent) : QDialog(parent)
{
    setupUi();
    current = information;
    initEditor(information);
}
InfoEditor::~InfoEditor() { delete ui; }
void InfoEditor::initEditor(const PersonInfo &info)
{
#define ENTER_TEXTUAL_PROPERTY(PROPERTY) \
    ui->container##PROPERTY->setText(info.get##PROPERTY());

    ENTER_TEXTUAL_PROPERTY(FirstName)
    ENTER_TEXTUAL_PROPERTY(LastName)
    ENTER_TEXTUAL_PROPERTY(FatherName)
    ENTER_TEXTUAL_PROPERTY(Nationality)
    ENTER_TEXTUAL_PROPERTY(BornProvince)

    if(info.getGender() == PersonInfo::GenderContainer::Male) {
        ui->radioButtonMale->setChecked(true);
    } else {
        ui->radioButtonFemale->setChecked(true);
    }

    ui->containerBirthday->setDate(info.getBirthday());
    photoViewer->setCurrentPhoto(info.getPhoto());

#undef ENTER_TEXTUAL_PROPERTY
}
void InfoEditor::accept()
{ 
    const QString errorString = "This should be filled.";
    if(ui->containerFirstName->text().isEmpty())
    {
        ui->containerFirstName->setPlaceholderText(errorString);
        return;
    }
    if(ui->containerLastName->text().isEmpty())
    {
        ui->containerLastName->setPlaceholderText(errorString);
        return;
    }

#define APPLY_TEXTUAL_PROPERTY(PROPERTY) \
    current.set##PROPERTY(ui->container##PROPERTY->text());

    APPLY_TEXTUAL_PROPERTY(FirstName)
    APPLY_TEXTUAL_PROPERTY(LastName)
    APPLY_TEXTUAL_PROPERTY(FatherName)
    APPLY_TEXTUAL_PROPERTY(BornProvince)
    APPLY_TEXTUAL_PROPERTY(Nationality)
    if(ui->radioButtonMale->isChecked()) {
        current.setGender(PersonInfo::GenderContainer::Male);
    }
    else if(ui->radioButtonFemale->isChecked()) {
        current.setGender(PersonInfo::GenderContainer::Female);
    }

#undef APPLY_TEXTUAL_PROPERTY

    current.setBirthday(ui->containerBirthday->date());
    current.setPhoto(photoViewer->getCurrentPhoto());
    QDialog::accept();
}
const PersonInfo &InfoEditor::retrieve() const { return current; }
