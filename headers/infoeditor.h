#ifndef INFOEDITOR_H
#define INFOEDITOR_H
#include <QDialog>
#include "infoitem.h"
#include "photoviewer.h"
namespace Ui { class InfoEditor; }
class InfoEditor : public QDialog
{
    Q_OBJECT
    InfoItem defaultInformation, *currentInformation = nullptr;
    Ui::InfoEditor *ui = nullptr;
    PhotoViewer *containerPhoto = nullptr;
private:
    void initializeInformation(const InfoItem *infoItem);
    void setInitialProperties();
    bool isInfoEnough();
private slots:
    bool applyInformation();
    void applyInformationAndClose();
    void updateInfoTitle();
    void on_buttonBrowsePC_clicked();
    void on_resetFirstNameButton_clicked();
    void on_resetLastNameButton_clicked();
    void on_resetFatherNameButton_clicked();
    void on_resetBirthdayButton_clicked();
    void on_resetGenderButton_clicked();
    void on_resetNationalityButton_clicked();
    void on_resetBornProvinceButton_clicked();
    void on_resetPhotoButton_clicked();
    void on_resetTitleButton_clicked();
    void on_buttonResetAll_clicked();
public:
    InfoEditor(QWidget *parent = nullptr);
    InfoEditor(InfoItem &information, QWidget *parent = nullptr);
    InfoItem* getInformation();
    ~InfoEditor();
};
#endif // INFOEDITOR_H
