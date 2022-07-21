#ifndef ABSTRACTEDITOR_H
#define ABSTRACTEDITOR_H

#include <QDialog>
class DataContainer;

class AbstractEditor : public QDialog
{
    Q_OBJECT
protected:
    virtual bool commitData();
public:
    explicit AbstractEditor(QWidget *parent = nullptr);
    virtual DataContainer* container() const = 0;
public slots:
    void accept() override;
    int exec() override;
    void resetFatherName();
    void resetFirstName();
    void resetLastName();
    void resetBirthday();
    void resetCountry();
    void resetGender();
    void resetEditor();
    void resetPhoto();
};

#endif // ABSTRACTEDITOR_H
