#include "include/dataeditor.h"
#include "include/photoviewer.h"
#include "ui_dataeditor.h"
#include <QFileDialog>

DataEditor::DataEditor(QWidget *parent) : QDialog(parent)
{
    setupEditor();
}
DataEditor::DataEditor(const DataContainer &target, QWidget *parent) : QDialog(parent), m_container(target)
{
    setupEditor();
    resetEditor();
}
void DataEditor::resetFirstName()
{
    ui->containerFirstName->setText(m_container.m_firstName);
}
void DataEditor::resetLastName()
{
    ui->containerLastName->setText(m_container.m_lastName);
}
void DataEditor::resetFatherName()
{
    ui->containerFatherName->setText(m_container.m_fatherName);
}
void DataEditor::resetBirthday()
{
    ui->containerBirthday->setDate(m_container.m_birthday);
}
void DataEditor::resetGender()
{
    using enum DataContainer::GenderContainer;
    switch(m_container.m_gender)
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
void DataEditor::resetNationality()
{
    ui->containerNationality->setText(m_container.m_nationality);
}
void DataEditor::resetBornProvince()
{
    ui->containerBornProvince->setText(m_container.m_bornProvince);
}
void DataEditor::resetPhoto()
{
    w_photo->setPhoto(m_container.m_photo);
    resize(sizeHint());
}
void DataEditor::resetEditor()
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
void DataEditor::resetContainer()
{
    m_container = DataContainer();
    resetEditor();
}
void DataEditor::setupEditor()
{
    ui = new Ui::DataEditor;
    ui->setupUi(this);

    w_photo = new PhotoViewer(this);
    w_photo->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    ui->layoutPhoto->insertWidget(0, w_photo);

    ui->containerBirthday->setDate(QDate::currentDate());

#define INIT_RESET(PROPERTY) \
    connect(ui->buttonReset##PROPERTY, &QPushButton::clicked, this, &DataEditor::reset##PROPERTY);

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
            w_photo->setPhoto(fileName);
            mainDirectory = QFileInfo(fileName).dir();
        }
    });
}
DataEditor::~DataEditor()
{
    delete ui;
}
const DataContainer &DataEditor::container() const
{
    return m_container;
}
void DataEditor::setContainer(const DataContainer &target)
{
    m_container = target;
    resetEditor();
}
void DataEditor::accept()
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
    m_container.m_firstName = ui->containerFirstName->text();
    m_container.m_lastName = ui->containerLastName->text();
    m_container.m_fatherName = ui->containerFatherName->text();
    {
        using enum DataContainer::GenderContainer;
        if(ui->radioButtonMale->isChecked()) {
            m_container.m_gender = Male;
        }
        else if(ui->radioButtonFemale->isChecked()) {
            m_container.m_gender = Female;
        }
    }
    m_container.m_birthday = ui->containerBirthday->date();
    m_container.m_bornProvince = ui->containerBornProvince->text();
    m_container.m_nationality = ui->containerNationality->text();
    m_container.m_photo = w_photo->photo();
    m_container.m_lastModification = QDateTime::currentDateTime();
    QDialog::accept();
}
