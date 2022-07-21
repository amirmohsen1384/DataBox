#include "include/dataeditor.h"

void DataEditor::initEditor()
{
    connect(this, &DataEditor::containerChanged, [this](DataContainer*){ resetEditor(); });
}
bool DataEditor::commitData()
{
    bool state = AbstractEditor::commitData();
    if(state) {
        m_container->updateModified();
    }
    return state;
}
DataEditor::DataEditor(QWidget *parent) : AbstractEditor(parent)
{
    initEditor();
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
    m_container = container;
    emit containerChanged(m_container);
}
