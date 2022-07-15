#ifndef DATACREATOR_H
#define DATACREATOR_H

#include "include/dataeditor.h"

class DataCreator : public DataEditor
{
    Q_OBJECT
    QScopedPointer<DataContainer> m_data;
protected:
    virtual bool commitData() override;
public:
    DataCreator(QWidget *parent = nullptr);
    virtual void setContainer(DataContainer *container) override;
    virtual DataContainer* container() const override;
public slots:
    virtual int exec() override;
};

#endif // DATACREATOR_H
