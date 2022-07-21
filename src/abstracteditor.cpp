#include "include/abstracteditor.h"
#include "include/photoviewer.h"
#include "ui_abstracteditor.h"
#include "datacontainer.h"

AbstractEditor::AbstractEditor(QWidget *parent) : QDialog(parent), ui(new Ui::AbstractEditor)
{
    ui->setupUi(this);
    w_photo = new PhotoViewer(this);
    ui->containerPhoto->addWidget(w_photo);
    w_photo->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    ui->containerCountry->setModel(&m_country);
    ui->containerBirthday->setDate(QDate::currentDate());
    connect(ui->buttonLocalBrowser, &QPushButton::clicked, this, &AbstractEditor::openPhotoFileDialog);
    connect(ui->buttonResetFirstName, &QPushButton::clicked, this, &AbstractEditor::resetFirstName);
    connect(ui->buttonResetLastName, &QPushButton::clicked, this, &AbstractEditor::resetLastName);
    connect(ui->buttonResetFatherName, &QPushButton::clicked, this, &AbstractEditor::resetFatherName);
    connect(ui->buttonResetGender, &QPushButton::clicked, this, &AbstractEditor::resetGender);
    connect(ui->buttonResetBirthday, &QPushButton::clicked, this, &AbstractEditor::resetBirthday);
    connect(ui->buttonResetCountry, &QPushButton::clicked, this, &AbstractEditor::resetCountry);
    connect(ui->buttonResetPhoto, &QPushButton::clicked, this, &AbstractEditor::resetPhoto);
    connect(ui->buttonResetEditor, &QPushButton::clicked, this, &AbstractEditor::resetEditor);
}
void AbstractEditor::resetFirstName()
{
    DataContainer *target = this->container();
    if(target == nullptr) {
        return;
    }
    ui->containerFirstName->setText(target->m_firstName);
}
void AbstractEditor::resetLastName()
{
    DataContainer *target = this->container();
    if(target == nullptr) {
        return;
    }
    ui->containerLastName->setText(target->m_lastName);
}
void AbstractEditor::resetFatherName()
{
    DataContainer *target = this->container();
    if(target == nullptr) {
        return;
    }
    ui->containerFatherName->setText(target->m_fatherName);
}
void AbstractEditor::resetBirthday()
{
    DataContainer *target = this->container();
    if(target == nullptr) {
        return;
    }
    ui->containerBirthday->setDate(target->m_birthday);
}
void AbstractEditor::resetGender()
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
void AbstractEditor::resetCountry()
{
    DataContainer *target = this->container();
    if(target == nullptr) {
        return;

    } else if(!target->m_country.isEmpty()) {
        ui->containerCountry->setCurrentText(target->m_country);

    }
}
void AbstractEditor::resetPhoto()
{
    DataContainer *target = this->container();
    if(target == nullptr) {
        return;
    }
    w_photo->setPhoto(target->m_photo);
    resize(sizeHint());
}
void AbstractEditor::resetEditor()
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
AbstractEditor::~AbstractEditor()
{
    delete ui;
}
void AbstractEditor::accept()
{
    if(commitData()) {
        QDialog::accept();
    } else {
        QDialog::reject();
    }
}
bool AbstractEditor::commitData()
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
    return true;
}
int AbstractEditor::exec()
{
    if(this->container() == nullptr) {
        qCritical() << "Error: No data container has been sent.";
        setResult(QDialog::Rejected);
        return result();
    } else {
        return QDialog::exec();
    }
}

#include <QPainter>
void AbstractEditor::fillBackground(QPainter *painter)
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
#include <QFileDialog>
void AbstractEditor::openPhotoFileDialog()
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
void AbstractEditor::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    fillBackground(&painter);
    QWidget::paintEvent(event);
}