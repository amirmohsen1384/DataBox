#ifndef INFOMONITOR_H
#define INFOMONITOR_H
#include <QDialog>
#include "personinfowidget.h"
class QVBoxLayout;
class PersonInfo;
class InfoMonitor : public QDialog
{
    Q_OBJECT
    PersonInfoWidget mainWidget;
    QVBoxLayout *mainLayout = nullptr;
public:
    InfoMonitor(const PersonInfo &data, QWidget *parent = nullptr);
};

#endif // INFOMONITOR_H
