#ifndef DIALOGS_H
#define DIALOGS_H

#include <QStringList>
#include <QWidget>

namespace Dialogs
{
    QStringList Open(QWidget *parent = nullptr);
    QString Save(QWidget *parent = nullptr);
}
#endif // DIALOGS_H
