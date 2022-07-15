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
    DataContainer *m_container = nullptr;
private:
    void fillBackground(QPainter *painter);
private slots:
    void openPhotoFileDialog();
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual bool commitData();
public:
    explicit DataEditor(QWidget *parent = nullptr);
    virtual void setContainer(DataContainer *container);
    virtual DataContainer* container() const;
    ~DataEditor();
public slots:
    void resetFirstName();
    void resetLastName();
    void resetFatherName();
    void resetBirthday();
    void resetGender();
    void resetCountry();
    void resetPhoto();
    void resetEditor();
    void accept() override;
    virtual int exec() override;
};

#endif // DATAEDITOR_H
