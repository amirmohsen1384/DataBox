#ifndef INFOEDITOR_H
#define INFOEDITOR_H

#include <QDialog>
#include "personinfo.h"

namespace Ui { class InfoEditor; }

class InfoEditor : public QDialog
{
    Q_OBJECT
    PersonInfo &container;
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
    explicit InfoEditor(PersonInfo &information, QWidget *parent = nullptr);
    ~InfoEditor();
};

#endif // INFOEDITOR_H
