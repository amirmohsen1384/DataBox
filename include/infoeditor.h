#ifndef INFOEDITOR_H
#define INFOEDITOR_H

#include <QDialog>
#include "infocontainer.h"

namespace Ui { class InfoEditor; }

class InfoEditor : public QDialog
{
    Q_OBJECT
    InfoContainer &container;
    Ui::InfoEditor *ui{};
    class PhotoViewer *photoViewer{};
private:
    void setupUi();
    void initEditor();
    void initGenderFromContainer();
    Q_DISABLE_COPY_MOVE(InfoEditor)
protected:
    void accept() override;
public:
    explicit InfoEditor(InfoContainer &information, QWidget *parent = nullptr);
    ~InfoEditor();
};

#endif // INFOEDITOR_H
