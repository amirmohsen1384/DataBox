#ifndef ABSTRACTEDITOR_H
#define ABSTRACTEDITOR_H

#include <QDialog>
#include "countrymodel.h"

namespace Ui { class AbstractEditor; }
class PhotoViewer;
class DataContainer;

class AbstractEditor : public QDialog
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(AbstractEditor)
    Ui::AbstractEditor *ui{};
    PhotoViewer *w_photo{};
    CountryModel m_country;
private:
    void fillBackground(QPainter *painter);
private slots:
    void openPhotoFileDialog();
    void containerFirstName(const QString &text);
    void containerLastName(const QString &text);
    void containerFatherName(const QString &text);
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual bool commitData();
public:
    explicit AbstractEditor(QWidget *parent = nullptr);
    virtual DataContainer* container() const = 0;
    ~AbstractEditor();
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
    virtual int exec() override;
};

#endif // ABSTRACTEDITOR_H
