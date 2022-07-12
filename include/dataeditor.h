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
    DataContainer m_container;
    Ui::DataEditor *ui{};
    PhotoViewer *w_photo{};
    CountryModel m_country;
private:
    void fillBackground(QPainter *painter);
protected:
    void paintEvent(QPaintEvent *event) override;
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
