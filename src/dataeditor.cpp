#include "include/infoeditor.h"
#include "include/photoview.h"
#include "ui_infoeditor.h"
#include <QFileDialog>

InfoEditor::InfoEditor(QWidget *parent) : QDialog(parent)
{
    setupEditor();
}
InfoEditor::InfoEditor(const InfoContainer &target, QWidget *parent) : QDialog(parent), m_container(target)
{
    setupEditor();
    resetEditor();
}
void InfoEditor::resetFirstName()
{
    ui->containerFirstName->setText(m_container.firstName);
}
void InfoEditor::resetLastName()
{
    ui->containerLastName->setText(m_container.lastName);
}
void InfoEditor::resetFatherName()
{
    ui->containerFatherName->setText(m_container.fatherName);
}
void InfoEditor::resetBirthday()
{
    ui->containerBirthday->setDate(m_container.birthday);
}
void InfoEditor::resetGender()
{
    using enum InfoContainer::GenderContainer;
    switch(m_container.gender)
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
    ui->containerNationality->setText(m_container.nationality);
}
void InfoEditor::resetBornProvince()
{
    ui->containerBornProvince->setText(m_container.bornProvince);
}
void InfoEditor::resetPhoto()
{
    w_photo->setCurrentPhoto(m_container.photo);
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
void InfoEditor::resetContainer()
{
    m_container = InfoContainer();
    resetEditor();
}
void InfoEditor::setupEditor()
{
    ui = new Ui::InfoEditor;
    ui->setupUi(this);

    w_photo = new PhotoView(this);
    w_photo->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    ui->layoutPhoto->insertWidget(0, w_photo);

    ui->containerBirthday->setDate(QDate::currentDate());

#define INIT_RESET(PROPERTY) \
    connect(ui->buttonReset##PROPERTY, &QPushButton::clicked, this, &InfoEditor::reset##PROPERTY);

    INIT_RESET(FirstName)
    INIT_RESET(LastName)
    INIT_RESET(FatherName)
    INIT_RESET(Gender)
    INIT_RESET(Birthday)
    INIT_RESET(BornProvince)
    INIT_RESET(Nationality)
    INIT_RESET(Photo)
    INIT_RESET(Editor)

#undef INIT_RESET

    connect(ui->buttonLocalBrowser, &QPushButton::clicked, this, [this]()
    {
        QDir tempPicture = QDir::home();
        tempPicture.cd("Pictures");

        static QDir mainDirectory = tempPicture;

        QFileDialog photoBrowser;
        photoBrowser.setWindowTitle("Select a photo to continue.");
        photoBrowser.setDirectory(mainDirectory);
        photoBrowser.setAcceptMode(QFileDialog::AcceptOpen);
        photoBrowser.setNameFilters({"JPG files (*.jpg *.jpeg)", "PNG files (*.png)", "BMP files (*.bmp)"});
        photoBrowser.setFileMode(QFileDialog::ExistingFile);

        if(photoBrowser.exec()) {
            QString fileName = photoBrowser.selectedFiles().constFirst();
            w_photo->setCurrentPhoto(fileName);
            mainDirectory = QFileInfo(fileName).dir();
        }
    });
}
InfoEditor::~InfoEditor()
{
    delete ui;
}
const InfoContainer &InfoEditor::container() const
{
    return m_container;
}
void InfoEditor::setContainer(const InfoContainer &target)
{
    m_container = target;
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

    m_container.firstName = ui->containerFirstName->text();
    m_container.lastName = ui->containerLastName->text();
    m_container.fatherName = ui->containerFatherName->text();
    {
        using enum InfoContainer::GenderContainer;
        if(ui->radioButtonMale->isChecked()) {
            m_container.gender = Male;
        }
        else if(ui->radioButtonFemale->isChecked()) {
            m_container.gender = Female;
        }
    }
    m_container.birthday = ui->containerBirthday->date();
    m_container.bornProvince = ui->containerBornProvince->text();
    m_container.nationality = ui->containerNationality->text();
    m_container.photo = w_photo->currentPhoto();
    m_container.lastModification = QDateTime::currentDateTime();
    QDialog::accept();
}
