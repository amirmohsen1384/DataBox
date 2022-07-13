#ifndef DATAEDITOR_H
#define DATAEDITOR_H

#include <QDialog>
#include "datacontainer.h"
#include "countrymodel.h"

namespace Ui { class DataEditor; }
class PhotoViewer;

class DataEditor : public QDialog
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(DataEditor)
    void setupEditor();
    Ui::DataEditor *ui{};
    PhotoViewer *w_photo{};
    CountryModel m_country;
    DataContainer m_container;
private:
    void fillBackground(QPainter *painter);
private slots:
    void openPhotoFileDialog();
protected:
    void paintEvent(QPaintEvent *event) override;
    virtual void updateData();
public:
    explicit DataEditor(QWidget *parent = nullptr);
    explicit DataEditor(const DataContainer &target, QWidget *parent = nullptr);
    ~DataEditor();

    const DataContainer& container() const;
    void setContainer(const DataContainer &target);
public slots:
    void accept() override;
    void resetFirstName();
    void resetLastName();
    void resetFatherName();
    void resetBirthday();
    void resetGender();
    void resetCountry();
    void resetPhoto();
    void resetEditor();
    void resetContainer();
};

#endif // DATAEDITOR_H
