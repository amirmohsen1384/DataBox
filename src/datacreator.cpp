#include "include/datacreator.h"

bool DataCreator::commitData()
{
    bool state = AbstractEditor::commitData();
    if(state) {
        m_container.data()->m_created = QDateTime::currentDateTime();
    }
    return state;
}
void DataCreator::initCreator()
{
    setWindowTitle("Creator");
}
DataCreator::DataCreator(QWidget *parent) : AbstractEditor(parent)
{
    initCreator();
}
DataContainer *DataCreator::container() const
{
    return m_container.data();
}
int DataCreator::exec()
{
    m_container.reset(new DataContainer);
    return AbstractEditor::exec();
}
