#ifndef DATAVIEWER_H
#define DATAVIEWER_H

#include <QDialog>

namespace Ui { class DataViewer; }
class NamedPhotoViewer;

class DataViewer : public QDialog
{
    Q_OBJECT
    Ui::DataViewer *ui{};
    NamedPhotoViewer *w_photo{};
private:
    void setupViewer();
public:
    explicit DataViewer(QWidget *parent = nullptr);
    ~DataViewer();
};

#endif // DATAVIEWER_H
