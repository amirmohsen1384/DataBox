#ifndef DATAEDITOR_H
#define DATAEDITOR_H

#include "abstracteditor.h"
#include "datacontainer.h"
#include <QPointer>

class DataEditor : public AbstractEditor
{
    Q_OBJECT
    QPointer<DataContainer> m_container{};
private:
    void initEditor();
    void updateWindowTitle();
protected:
    bool commitData() override;
public:
    DataEditor(QWidget *parent = nullptr);
    DataEditor(DataContainer *container, QWidget *parent = nullptr);
    DataContainer* container() const override;
public slots:
    void setContainer(DataContainer *container);
signals:
    void containerChanged(DataContainer *container);
};

#endif // DATAEDITOR_H
