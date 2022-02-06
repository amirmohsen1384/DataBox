#ifndef INFOEDITOR_H
#define INFOEDITOR_H
#include <QDialog>
#include "personinfo.h"
#include "photoviewer.h"
namespace Ui { class InfoEditor; }
class InfoEditor : public QDialog
{
    Q_OBJECT
    PersonInfo defaultInfo;
    PersonInfo *currentInfo{};
    Ui::InfoEditor *ui{};
    PhotoViewer *photoViewer{};
private:
    void initializeInformation(const PersonInfo &infoItem);
    void setupUi();
protected:
    void accept() override;
private slots:
    void on_buttonBrowsePC_clicked();
    void on_buttonResetFirstName_clicked();

    void on_buttonResetLastName_clicked();

    void on_buttonResetFatherName_clicked();

    void on_buttonResetBirthday_clicked();

    void on_buttonResetNationality_clicked();

    void on_buttonResetBornProvince_clicked();

    void on_buttonResetGender_clicked();

    void on_buttonResetPhoto_clicked();

public:
    explicit InfoEditor(QWidget *parent = nullptr);
    explicit InfoEditor(PersonInfo &information, QWidget *parent = nullptr);
    const PersonInfo &retrieve() const;
    ~InfoEditor();
};
#endif // INFOEDITOR_H
