#include "include/namedphotoviewer.h"
#include "include/dataviewer.h"
#include "ui_dataviewer.h"

void DataViewer::setupViewer()
{
    ui = new Ui::DataViewer;
    ui->setupUi(this);

    w_photo = new NamedPhotoViewer(this);
    w_photo->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    ui->layoutPhoto->addWidget(w_photo);

    w_photo->setPrimaryText(QString());
    w_photo->setSecondaryText("No photo has been set.");

    w_photo->setPrimaryFont(QFont("Segoe Print", 20, QFont::Bold));
    w_photo->setSecondaryFont(QFont("Segoe UI", 10, QFont::Bold));
}
DataViewer::DataViewer(QWidget *parent) : QDialog(parent)
{
    setupViewer();
}
DataViewer::DataViewer(const DataContainer &target, QWidget *parent) : QDialog(parent)
{
    setupViewer();
    setContainer(target);
}
DataViewer::~DataViewer()
{
    delete ui;
}
const DataContainer &DataViewer::container() const
{
    return m_container;
}
void DataViewer::setContainer(const DataContainer &container)
{
    m_container = container;
    resetViewer();
}

void DataViewer::resetFullName()
{
    w_photo->setPrimaryText(m_container.fullName());
}
void DataViewer::resetFatherName()
{
    ui->containerFatherName->setText(m_container.fatherName());
}
void DataViewer::resetBirthday()
{
    ui->containerBirthday->setText(m_container.birthday().toString());
}
void DataViewer::resetGender()
{
    using enum DataContainer::GenderContainer;
    switch(m_container.gender()) {
    case Male: {
        ui->containerGender->setText("Male");
        break;
    }
    case Female: {
        ui->containerGender->setText("Female");
        break;
    }
    }
}
void DataViewer::resetCountry()
{
    ui->containerCountry->setText(m_container.country());
}
void DataViewer::resetPhoto()
{
    w_photo->setPhoto(m_container.photo());
}
void DataViewer::resetViewer()
{
    resetFullName();
    resetFatherName();
    resetBirthday();
    resetGender();
    resetCountry();
    resetPhoto();
    w_photo->setSecondaryText("Date modified on " + m_container.modified().toString());
    ui->labelDateCreated->setText("Date created: " + m_container.created().toString());
}

#include <QPainter>
void DataViewer::fillBackground(QPainter *painter)
{
    const qreal start = 0.1;

    QLinearGradient gradient(QPointF(0, 0), QPointF(1, 1));
    gradient.setCoordinateMode(QGradient::ObjectMode);

    using enum DataContainer::GenderContainer;
    switch(m_container.gender()) {
    case Male: {
        gradient.setColorAt(start, QColorConstants::Svg::lightblue);
        break;
    }
    case Female: {
        gradient.setColorAt(start, QColorConstants::Svg::lightpink);
        break;
    }
    }
    gradient.setColorAt(0.4, Qt::white);
    painter->fillRect(rect(), gradient);
}
void DataViewer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    fillBackground(&painter);
    QWidget::paintEvent(event);
}