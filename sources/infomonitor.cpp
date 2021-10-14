#include "../headers/infomonitor.h"
#include <QVBoxLayout>

InfoMonitor::InfoMonitor(const InfoItem &information, QWidget *parent) : QDialog(parent)
{
    mainLayout = new QVBoxLayout;

    const PersonInfo &data = information.info;
    PersonInfo::HiddenInfoFlags hiddenInfo = data.getHiddenInfo();

    if(!hiddenInfo.testFlag(PersonInfo::FirstName) && !hiddenInfo.testFlag(PersonInfo::LastName))
    {
        mainWidget.constructName();
        mainWidget.setName(connectFirstAndLastName(data.getFirstName(), data.getLastName()));
    }
    else if(!hiddenInfo.testFlag(PersonInfo::FirstName))
    {
        mainWidget.constructName();
        mainWidget.setName(data.getFirstName());
    }
    else if(!hiddenInfo.testFlag(PersonInfo::LastName))
    {
        mainWidget.constructName();
        mainWidget.setName(data.getLastName());
    }

    if(!hiddenInfo.testFlag(PersonInfo::FatherName))
    {
        mainWidget.constructFatherName();
        mainWidget.setFatherName(data.getFatherName());
    }
    if(!hiddenInfo.testFlag(PersonInfo::Birthday))
    {
        mainWidget.constructBirthday();
        mainWidget.setBirthday(data.getBirthday().toString());
    }
    if(!hiddenInfo.testFlag(PersonInfo::BornProvince))
    {
        mainWidget.constructBornProvince();
        mainWidget.setBornProvince(data.getBornProvince());
    }
    if(!hiddenInfo.testFlag(PersonInfo::HiddenInfoFlag::Gender))
    {
        mainWidget.constructGender();
        mainWidget.setGender(genderToString(data.getGender()));
    }
    if(!hiddenInfo.testFlag(PersonInfo::HiddenInfoFlag::Nationality))
    {
        mainWidget.constructNationality();
        mainWidget.setNationality(data.getNationality());
    }
    if(!hiddenInfo.testFlag(PersonInfo::HiddenInfoFlag::Photo))
    {
        mainWidget.constructPhoto();
        mainWidget.setPhoto(data.getPhoto());
    }
    if(!hiddenInfo.testFlag(PersonInfo::HiddenInfoFlag::CreatedDateTime))
    {
        mainWidget.constructCreatedDateTime();
        mainWidget.setCreatedDateTime(data.getCreatedDateTime().toString());
    }
    if(!hiddenInfo.testFlag(PersonInfo::HiddenInfoFlag::LastModifiedDateTime))
    {
        mainWidget.constructLastModifiedDateTime();
        mainWidget.setLastModifiedDateTime(data.getLastModifiedDateTime().toString());
    }

    mainLayout->addWidget(&mainWidget);
    setLayout(mainLayout);
}
