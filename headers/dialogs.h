#ifndef DIALOGS_H
#define DIALOGS_H
class QWidget;
class QString;
class QStringList;
namespace Dialogs
{
    QStringList Open(QWidget *parent = nullptr);
    QString Save(QWidget *parent = nullptr);
}
#endif // DIALOGS_H
