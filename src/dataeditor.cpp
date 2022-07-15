#include "include/dataeditor.h"
#include "include/photoviewer.h"
#include "ui_dataeditor.h"

DataEditor::DataEditor(QWidget *parent) : QDialog(parent)
{
    setupEditor();
}
DataEditor::DataEditor(const DataContainer &target, QWidget *parent) : QDialog(parent)
{
    setupEditor();
    setContainer(target);
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
void DataEditor::resetCountry()
{
    if(m_container.m_country.isEmpty()) {
        ui->containerCountry->setCurrentIndex(0);
    } else {
        ui->containerCountry->setCurrentText(m_container.m_country);
    }
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
    resetCountry();
    resetPhoto();
}
void DataEditor::resetContainer()
{
    m_container = DataContainer();
    resetEditor();
}

#include <QFileDialog>
void DataEditor::setupEditor()
{
    ui = new Ui::DataEditor;
    ui->setupUi(this);

    w_photo = new PhotoViewer(this);
    ui->layoutPhoto->insertWidget(0, w_photo);
    w_photo->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    ui->containerBirthday->setDate(QDate::currentDate());
    ui->containerCountry->setModel(&m_country);

    connect(ui->radioButtonMale, &QRadioButton::toggled, [this](bool) { this->update(); });
    connect(ui->radioButtonFemale, &QRadioButton::toggled, [this](bool) { this->update(); });
    connect(ui->buttonLocalBrowser, &QPushButton::clicked, this, &DataEditor::openPhotoFileDialog);

#define INIT_RESET(PROPERTY) \
    connect(ui->buttonReset##PROPERTY, &QPushButton::clicked, this, &DataEditor::reset##PROPERTY);

    INIT_RESET(FirstName)
    INIT_RESET(LastName)
    INIT_RESET(FatherName)
    INIT_RESET(Gender)
    INIT_RESET(Birthday)
    INIT_RESET(Country)
    INIT_RESET(Photo)
    INIT_RESET(Editor)

#undef INIT_RESET
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
    updateData();
    QDialog::accept();
}
void DataEditor::updateData()
{
    bool one = ui->containerFirstName->text().isEmpty();
    bool two = ui->containerLastName->text().isEmpty();
    bool three = ui->containerFatherName->text().isEmpty();
    if(one || two || three)
    {
        const QString errorString = "This has not been filled yet.";
        if(one) {
            ui->containerFirstName->setPlaceholderText(errorString);
        }
        if(two) {
            ui->containerLastName->setPlaceholderText(errorString);
        }
        if(three) {
            ui->containerFatherName->setPlaceholderText(errorString);
        }
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
    m_container.m_country = ui->containerCountry->currentText();
    m_container.m_photo = w_photo->photo();
    m_container.updateModified();
}

#include <QPainter>
void DataEditor::fillBackground(QPainter *painter)
{
    const qreal start = 0.1;

    QLinearGradient gradient(QPointF(0, 0), QPointF(1, 1));
    gradient.setCoordinateMode(QGradient::ObjectMode);
    if(ui->radioButtonMale->isChecked()) {
        gradient.setColorAt(start, QColorConstants::Svg::lightblue);

    } else if(ui->radioButtonFemale->isChecked()) {
        gradient.setColorAt(start, QColorConstants::Svg::lightpink);

    }
    gradient.setColorAt(0.4, Qt::white);
    painter->fillRect(rect(), gradient);
}
void DataEditor::openPhotoFileDialog()
{
    QDir tempPicture = QDir::home();
    tempPicture.cd("Pictures");

    static QDir mainDirectory = tempPicture;

    QFileDialog photoBrowser;
    photoBrowser.setDirectory(mainDirectory);
    photoBrowser.setWindowTitle("Select a photo to continue.");
    photoBrowser.setAcceptMode(QFileDialog::AcceptOpen);
    photoBrowser.setNameFilters({"JPG files (*.jpg *.jpeg)", "PNG files (*.png)", "BMP files (*.bmp)"});
    photoBrowser.setFileMode(QFileDialog::ExistingFile);

    if(photoBrowser.exec()) {
        QString fileName = photoBrowser.selectedFiles().constFirst();
        w_photo->setPhoto(fileName);
        mainDirectory = QFileInfo(fileName).dir();
    }
}
void DataEditor::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    fillBackground(&painter);
    QWidget::paintEvent(event);
}