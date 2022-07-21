#include "include/dataeditor.h"
#include "include/photoviewer.h"
#include "ui_dataeditor.h"

DataEditor::DataEditor(QWidget *parent) : QDialog(parent)
{
    setupEditor();
}
void DataEditor::setContainer(DataContainer *container)
{
    if(container != nullptr) {
        m_container = container;
        setWindowTitle(m_container->fullName() + " - " + "Editor");
        resetEditor();
    }
}
DataContainer *DataEditor::container() const
{
    return m_container;
}
void DataEditor::resetFirstName()
{
    DataContainer *target = this->container();
    if(target == nullptr) {
        return;
    }
    ui->containerFirstName->setText(target->m_firstName);
}
void DataEditor::resetLastName()
{
    DataContainer *target = this->container();
    if(target == nullptr) {
        return;
    }
    ui->containerLastName->setText(target->m_lastName);
}
void DataEditor::resetFatherName()
{
    DataContainer *target = this->container();
    if(target == nullptr) {
        return;
    }
    ui->containerFatherName->setText(target->m_fatherName);
}
void DataEditor::resetBirthday()
{
    DataContainer *target = this->container();
    if(target == nullptr) {
        return;
    }
    ui->containerBirthday->setDate(target->m_birthday);
}
void DataEditor::resetGender()
{
    DataContainer *target = this->container();
    if(target == nullptr) {
        return;
    }
    using enum DataContainer::GenderContainer;
    switch(target->m_gender)
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
    DataContainer *target = this->container();
    if(target == nullptr) {
        return;
    }
    const QString &country = target->m_country;
    if(m_container->m_country.isEmpty()) {
        ui->containerCountry->setCurrentIndex(0);
    } else {
        ui->containerCountry->setCurrentText(country);
    }
}
void DataEditor::resetPhoto()
{
    DataContainer *target = this->container();
    if(target == nullptr) {
        return;
    }
    w_photo->setPhoto(target->m_photo);
    resize(sizeHint());
}
void DataEditor::resetEditor()
{
    if(this->container() == nullptr) {
        return;
    }
    resetFirstName();
    resetLastName();
    resetFatherName();
    resetBirthday();
    resetGender();
    resetCountry();
    resetPhoto();
}

#include <QFileDialog>
void DataEditor::setupEditor()
{
    ui = new Ui::DataEditor;
    ui->setupUi(this);

    w_photo = new PhotoViewer(this);
    ui->layoutPhoto->insertWidget(0, w_photo);
    w_photo->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    ui->containerCountry->setModel(&m_country);
    ui->containerBirthday->setDate(QDate::currentDate());

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
void DataEditor::accept()
{
    this->commitData();
    QDialog::accept();
}
bool DataEditor::commitData()
{
    DataContainer *target = this->container();
    if(target == nullptr) {
        return false;
    }
    bool one = ui->containerFirstName->text().isEmpty();
    bool two = ui->containerLastName->text().isEmpty();
    bool three = ui->containerFatherName->text().isEmpty();
    if(one || two || three)
    {
        const QString errorString = "REQUIRED";
        if(one) {
            ui->containerFirstName->setPlaceholderText(errorString);
        }
        if(two) {
            ui->containerLastName->setPlaceholderText(errorString);
        }
        if(three) {
            ui->containerFatherName->setPlaceholderText(errorString);
        }
        return false;
    }
    target->m_firstName = ui->containerFirstName->text();
    target->m_lastName = ui->containerLastName->text();
    target->m_fatherName = ui->containerFatherName->text();
    {
        using enum DataContainer::GenderContainer;
        if(ui->radioButtonMale->isChecked()) {
            target->m_gender = Male;
        }
        else if(ui->radioButtonFemale->isChecked()) {
            target->m_gender = Female;
        }
    }
    target->m_birthday = ui->containerBirthday->date();
    target->m_country = ui->containerCountry->currentText();
    target->m_photo = w_photo->photo();
    target->updateModified();
    return true;
}
int DataEditor::exec()
{
    if(this->container() == nullptr) {
        qCritical() << "No data container is provided to the editor.";
        qCritical() << "Most of functionality will not work.";
    }
    return QDialog::exec();
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