#include "include/datacreator.h"

bool DataCreator::commitData()
{
    if(DataEditor::commitData() != true) {
        return false;
    } else {
        m_data->m_created = QDateTime::currentDateTime();
        return true;
    }
}
DataCreator::DataCreator(QWidget *parent) : DataEditor(parent)
{
    setWindowTitle("Creator");
}
void DataCreator::setContainer(DataContainer *container)
{
    Q_UNUSED(container)
}
DataContainer *DataCreator::container() const
{
    return m_data.data();
}
int DataCreator::exec()
{
    m_data.reset(new DataContainer);
    return DataEditor::exec();
}
