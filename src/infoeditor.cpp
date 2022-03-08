#include "include/photoviewer.h"
#include "include/infoeditor.h"
#include "ui_infoeditor.h"
#include <QFileDialog>
#define INIT_PROPERTY_FROM_CURRENT(PROPERTY) \
    ui->container##PROPERTY->setText(container.get##PROPERTY());

void InfoEditor::initGenderFromContainer()
{
    switch(container.getGender())
    {
    case PersonInfo::GenderContainer::Male: {
       ui->radioButtonMale->setEnabled(true);
       break;
    }
    case PersonInfo::GenderContainer::Female: {
        ui->radioButtonFemale->setEnabled(true);
        break;
    }
    }
}
void InfoEditor::setupUi()
{
    ui = new Ui::InfoEditor;
    ui->setupUi(this);

    ui->containerBirthday->setDate(QDate::currentDate());

    photoViewer = new PhotoViewer;
    photoViewer->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    ui->layoutPhoto->insertWidget(0, photoViewer);

    connect(ui->buttonResetFirstName, &QPushButton::clicked, this, [=]()
    {
        INIT_PROPERTY_FROM_CURRENT(FirstName)
    });
    connect(ui->buttonResetLastName, &QPushButton::clicked, this, [=]()
    {
        INIT_PROPERTY_FROM_CURRENT(LastName)
    });
    connect(ui->buttonResetFatherName, &QPushButton::clicked, this, [=]()
    {
        INIT_PROPERTY_FROM_CURRENT(FatherName)
    });
    connect(ui->buttonResetNationality, &QPushButton::clicked, this, [=]()
    {
        INIT_PROPERTY_FROM_CURRENT(Nationality)
    });
    connect(ui->buttonResetBornProvince, &QPushButton::clicked, this, [=]()
    {
        INIT_PROPERTY_FROM_CURRENT(BornProvince)
    });
    connect(ui->buttonResetGender, &QPushButton::clicked, this, &InfoEditor::initGenderFromContainer);
    connect(ui->buttonResetBirthday, &QPushButton::clicked, this, [=]()
    {
        ui->containerBirthday->setDate(container.getBirthday());
    });
    connect(ui->buttonResetPhoto, &QPushButton::clicked, this, [=]()
    {
        photoViewer->setCurrentPhoto(container.getPhoto());
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
#define DEFINE_RESET_ALL_CONNECTION(PROPERTY) \
    connect(ui->buttonResetAll, &QPushButton::clicked, ui->buttonReset##PROPERTY, &QPushButton::clicked);

    DEFINE_RESET_ALL_CONNECTION(FirstName)
    DEFINE_RESET_ALL_CONNECTION(LastName)
    DEFINE_RESET_ALL_CONNECTION(FatherName)
    DEFINE_RESET_ALL_CONNECTION(Nationality)
    DEFINE_RESET_ALL_CONNECTION(BornProvince)
    DEFINE_RESET_ALL_CONNECTION(Birthday)
    DEFINE_RESET_ALL_CONNECTION(Gender)
    DEFINE_RESET_ALL_CONNECTION(Photo)

#undef DEFINE_RESET_ALL_CONNECTION
}
InfoEditor::InfoEditor(PersonInfo &information, QWidget *parent) : QDialog(parent), container(information)
{
    setupUi();
    initEditor();
}
InfoEditor::~InfoEditor()
{
    delete photoViewer;
    delete ui;
}
void InfoEditor::initEditor()
{
    INIT_PROPERTY_FROM_CURRENT(FirstName)
    INIT_PROPERTY_FROM_CURRENT(LastName)
    INIT_PROPERTY_FROM_CURRENT(FatherName)
    INIT_PROPERTY_FROM_CURRENT(Nationality)
    INIT_PROPERTY_FROM_CURRENT(BornProvince)
    initGenderFromContainer();
    ui->containerBirthday->setDate(container.getBirthday());
    photoViewer->setCurrentPhoto(container.getPhoto());
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
#define APPLY_TEXTUAL_PROPERTY(PROPERTY) \
    container.set##PROPERTY(ui->container##PROPERTY->text());

    APPLY_TEXTUAL_PROPERTY(FirstName)
    APPLY_TEXTUAL_PROPERTY(LastName)
    APPLY_TEXTUAL_PROPERTY(FatherName)
    APPLY_TEXTUAL_PROPERTY(BornProvince)
    APPLY_TEXTUAL_PROPERTY(Nationality)

#undef APPLY_TEXTUAL_PROPERTY
    if(ui->radioButtonMale->isChecked()) {
        container.setGender(PersonInfo::GenderContainer::Male);
    }
    else if(ui->radioButtonFemale->isChecked()) {
        container.setGender(PersonInfo::GenderContainer::Female);
    }
    container.setBirthday(ui->containerBirthday->date());
    container.setPhoto(photoViewer->getCurrentPhoto());
    QDialog::accept();
}
