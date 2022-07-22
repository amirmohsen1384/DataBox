#ifndef DATACREATOR_H
#define DATACREATOR_H

#include "abstracteditor.h"
#include "datacontainer.h"
#include <QScopedPointer>

class DataCreator : public AbstractEditor
{
    Q_OBJECT
    QScopedPointer<DataContainer> m_container;
private:
    void initCreator();
protected:
    virtual bool commitData() override;
public:
    DataCreator(QWidget *parent);
    DataContainer* container() const override;
public slots:
    int exec() override;
};

#endif // DATACREATOR_H
