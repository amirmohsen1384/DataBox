#include "../headers/infomonitor.h"
#include "../headers/infoitem.h"
#include <QVBoxLayout>

InfoMonitor::InfoMonitor(const InfoItem &information, QWidget *parent) : QDialog(parent)
{
    mainLayout = new QVBoxLayout;
    const InfoItem::HiddenInfoFlags &hiddenInfo = information.getHiddenInfo();
    const PersonInfo &data = information.info;
    if(!hiddenInfo.testFlag(InfoItem::HideFirstName) && !hiddenInfo.testFlag(InfoItem::HideLastName))
    {
        mainWidget.constructName();
        mainWidget.setName(connectFirstAndLastName(data.getFirstName(), data.getLastName()));
    }
    else if(!hiddenInfo.testFlag(InfoItem::HideFirstName))
    {
        mainWidget.constructName();
        mainWidget.setName(data.getFirstName());
    }
    else if(!hiddenInfo.testFlag(InfoItem::HideLastName))
    {
        mainWidget.constructName();
        mainWidget.setName(data.getLastName());
    }

    if(!hiddenInfo.testFlag(InfoItem::HideFatherName))
    {
        mainWidget.constructFatherName();
        mainWidget.setFatherName(data.getFatherName());
    }
    if(!hiddenInfo.testFlag(InfoItem::HideBirthday))
    {
        mainWidget.constructBirthday();
        mainWidget.setBirthday(data.getBirthday().toString());
    }
    if(!hiddenInfo.testFlag(InfoItem::HideBornProvince))
    {
        mainWidget.constructBornProvince();
        mainWidget.setBornProvince(data.getBornProvince());
    }
    if(!hiddenInfo.testFlag(InfoItem::HiddenInfoFlag::HideGender))
    {
        mainWidget.constructGender();
        mainWidget.setGender(genderToString(data.getGender()));
    }
    if(!hiddenInfo.testFlag(InfoItem::HiddenInfoFlag::HideNationality))
    {
        mainWidget.constructNationality();
        mainWidget.setNationality(data.getNationality());
    }
    if(!hiddenInfo.testFlag(InfoItem::HiddenInfoFlag::HidePhoto))
    {
        mainWidget.constructPhoto();
        mainWidget.setPhoto(data.getPhoto());
    }
    if(!hiddenInfo.testFlag(InfoItem::HideCreatedDateTime))
    {
        mainWidget.constructCreatedDateTime();
        mainWidget.setCreatedDateTime(information.getCreatedDateTime().toString());
    }
    if(!hiddenInfo.testFlag(InfoItem::HideLastModifiedDateTime))
    {
        mainWidget.constructLastModifiedDateTime();
        mainWidget.setLastModifiedDateTime(information.getLastModifiedDateTime().toString());
    }
    mainLayout->addWidget(&mainWidget);
    setLayout(mainLayout);
    setWindowTitle(information.getItemText() + " - Show information");
}
