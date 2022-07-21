#ifndef DATAVIEWER_H
#define DATAVIEWER_H

#include <QDialog>
#include "include/datacontainer.h"

namespace Ui { class DataViewer; }
class NamedPhotoViewer;

class DataViewer : public QDialog
{
    Q_OBJECT
    Ui::DataViewer *ui{};
    DataContainer m_container{};
    NamedPhotoViewer *w_photo{};
private:
    void setupViewer();
    void fillBackground(QPainter *painter);
protected:
    virtual void paintEvent(QPaintEvent *event);
public:
    explicit DataViewer(QWidget *parent = nullptr);
    explicit DataViewer(const DataContainer &target, QWidget *parent = nullptr);
    ~DataViewer();

    const DataContainer& container() const;
    void setContainer(const DataContainer &container);
public slots:
    void resetFullName();
    void resetFatherName();
    void resetBirthday();
    void resetGender();
    void resetCountry();
    void resetPhoto();
    void resetViewer();
};

#endif // DATAVIEWER_H
