#ifndef INFOMONITOR_H
#define INFOMONITOR_H
#include <QDialog>
#include "infoitem.h"
#include "photoviewer.h"
#include "personinfowidget.h"

class QVBoxLayout;
class InfoMonitor : public QDialog
{
    Q_OBJECT
    PersonInfoWidget mainWidget;
    QVBoxLayout *mainLayout = nullptr;
public:
    InfoMonitor(const InfoItem &information, QWidget *parent = nullptr);
};

#endif // INFOMONITOR_H
