#ifndef DATAVIEWER_H
#define DATAVIEWER_H

#include <QDialog>

namespace Ui {
class DataViewer;
}

class DataViewer : public QDialog
{
    Q_OBJECT

public:
    explicit DataViewer(QWidget *parent = nullptr);
    ~DataViewer();

private:
    Ui::DataViewer *ui;
};

#endif // DATAVIEWER_H
