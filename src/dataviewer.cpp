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
DataViewer::~DataViewer()
{
    delete ui;
}
