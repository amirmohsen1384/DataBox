#include "include/dataeditor.h"

void DataEditor::initEditor()
{
    connect(this, &DataEditor::containerChanged, this, &DataEditor::updateEditor);
}
bool DataEditor::commitData()
{
    bool state = AbstractEditor::commitData();
    if(state) {
        m_container->m_modified = QDateTime::currentDateTime();
    }
    return state;
}
DataEditor::DataEditor(QWidget *parent) : AbstractEditor(parent)
{
    initEditor();
    updateAcceptState();
}
DataEditor::DataEditor(DataContainer *container, QWidget *parent) : AbstractEditor(parent)
{
    initEditor();
    setContainer(container);
}
DataContainer *DataEditor::container() const
{
    return m_container;
}
void DataEditor::setContainer(DataContainer *container)
{
    m_container = qobject_cast<DataContainer*>(container);
    emit containerChanged(m_container);
}
void DataEditor::updateEditor()
{
    if(m_container == nullptr) {
        return;
    }
    resetEditor();
    setWindowTitle(m_container->fullName() + " - Editor");
    updateAcceptState();
}
