#include "include/dataviewer.h"
#include "ui_dataviewer.h"

DataViewer::DataViewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataViewer)
{
    ui->setupUi(this);
}

DataViewer::~DataViewer()
{
    delete ui;
}
