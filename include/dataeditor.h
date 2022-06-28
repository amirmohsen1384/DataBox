#ifndef INFOEDITOR_H
#define INFOEDITOR_H

#include <QDialog>
#include "infocontainer.h"

namespace Ui { class InfoEditor; }
class PhotoView;

class InfoEditor : public QDialog
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(InfoEditor)
    void setupEditor();
    InfoContainer m_container;
    Ui::InfoEditor *ui{};
    PhotoView *w_photo{};
protected:
    void accept() override;
public:
    explicit InfoEditor(QWidget *parent = nullptr);
    explicit InfoEditor(const InfoContainer &target, QWidget *parent = nullptr);
    ~InfoEditor();

    const InfoContainer& container() const;
    void setContainer(const InfoContainer &target);
public slots:
    void resetFirstName();
    void resetLastName();
    void resetFatherName();
    void resetBirthday();
    void resetGender();
    void resetNationality();
    void resetBornProvince();
    void resetPhoto();
    void resetEditor();
    void resetContainer();
};

#endif // INFOEDITOR_H
