#ifndef INFOEDITOR_H
#define INFOEDITOR_H
#include <QDialog>
#include "personinfo.h"
namespace Ui { class InfoEditor; }
class InfoEditor : public QDialog
{
    Q_OBJECT
    PersonInfo current;
    Ui::InfoEditor *ui{};
    class PhotoViewer *photoViewer{};
    Q_DISABLE_COPY_MOVE(InfoEditor)
private:
    void enableResetFeature();
    void initializeInformation(const PersonInfo &infoItem);
    void setupUi();
protected:
    void accept() override;
public:
    explicit InfoEditor(QWidget *parent = nullptr);
    InfoEditor(const PersonInfo &information, QWidget *parent = nullptr);
    const PersonInfo &retrieve() const;
    ~InfoEditor();
};
#endif // INFOEDITOR_H
