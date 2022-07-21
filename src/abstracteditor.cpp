#include "datacontainer.h"
#include "abstracteditor.h"

bool AbstractEditor::commitData()
{
    DataContainer *container = this->container();
    Q_UNUSED(container);
    return true;
}
AbstractEditor::AbstractEditor(QWidget *parent) : QDialog(parent)
{
}
void AbstractEditor::accept()
{
    if(commitData()) {
        QDialog::accept();
    } else {
        QDialog::reject();
    }
}
int AbstractEditor::exec()
{
    if(this->container() == nullptr) {
        qCritical() << "Error: No data container has been sent.";
        setResult(QDialog::Rejected);
        return result();
    } else {
        return QDialog::exec();
    }
}
