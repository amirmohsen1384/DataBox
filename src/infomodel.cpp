#include "include/infomodel.h"

void InfoModel::initModel()
{
    QStringList headerLabels;
    headerLabels.append("First name");
    headerLabels.append("Last name");
    headerLabels.append("Gender");
    headerLabels.append("Birthday");
    headerLabels.append("Creation");
    headerLabels.append("Last modification");
    setHorizontalHeaderLabels(headerLabels);
}
InfoModel::InfoModel(QObject *parent) : QStandardItemModel(parent)
{
    initModel();
}
QModelIndex InfoModel::index(int row, const InfoColumn &column) const
{
    return QStandardItemModel::index(row, static_cast<int>(column));
}
void InfoModel::setInformation(int row, const InfoContainer &info)
{
    typedef QStandardItemModel Base;
    QStandardItem *item{};
    {
        item = new QStandardItem(info.firstName);
        item->setData(info.fatherName, static_cast<int>(BackgroundInfoRole::FatherName));
        Base::setItem(row, static_cast<int>(InfoColumn::FirstName), item);
    }
    {
        item = new QStandardItem(info.lastName);
        item->setData(info.nationality, static_cast<int>(BackgroundInfoRole::Nationality));
        Base::setItem(row, static_cast<int>(InfoColumn::LastName), item);
    }
    {
        QVariant genderBinary;
        QString genderText;
        genderBinary.setValue(info.gender);
        switch(info.gender)
        {
        case InfoContainer::GenderContainer::Male:
            genderText = "Male";
            break;
        case InfoContainer::GenderContainer::Female:
            genderText = "Female";
            break;
        }
        item = new QStandardItem(genderText);
        item->setData(genderBinary, static_cast<int>(BackgroundInfoRole::Gender));
        item->setData(info.bornProvince, static_cast<int>(BackgroundInfoRole::BornProvince));
        Base::setItem(row, static_cast<int>(InfoColumn::Gender), item);
    }
    {
        item = new QStandardItem(info.birthday.toString());
        item->setData(info.birthday, static_cast<int>(BackgroundInfoRole::Birthday));
        item->setData(info.photo, static_cast<int>(BackgroundInfoRole::Photo));
        Base::setItem(row, static_cast<int>(InfoColumn::Birthday), item);
    }
    {
        item = new QStandardItem(info.creation.toString());
        item->setData(info.creation, static_cast<int>(BackgroundInfoRole::Creation));
        Base::setItem(row, static_cast<int>(InfoColumn::Creation), item);
    }
    {
        item = new QStandardItem(info.lastModification.toString());
        item->setData(info.lastModification, static_cast<int>(BackgroundInfoRole::LastModification));
        Base::setItem(row, static_cast<int>(InfoColumn::LastModification), item);
    }
}
InfoContainer InfoModel::information(int row) const
{
    typedef QStandardItemModel Base;
    InfoContainer information;
    QStandardItem *item{};
    {
        item = Base::item(row, static_cast<int>(InfoColumn::FirstName));
        information.firstName = item->text();
        information.fatherName = item->data(static_cast<int>(BackgroundInfoRole::FatherName)).toString();
    }
    {
        item = Base::item(row, static_cast<int>(InfoColumn::LastName));
        information.lastName = item->text();
        information.nationality = item->data(static_cast<int>(BackgroundInfoRole::Nationality)).toString();
    }
    {
        item = Base::item(row, static_cast<int>(InfoColumn::Gender));
        information.gender = item->data(static_cast<int>(BackgroundInfoRole::Gender)).value<InfoContainer::GenderContainer>();
        information.bornProvince = item->data(static_cast<int>(BackgroundInfoRole::BornProvince)).toString();
    }
    {
        item = Base::item(row, static_cast<int>(InfoColumn::Birthday));
        information.birthday = item->data(static_cast<int>(BackgroundInfoRole::Birthday)).toDate();
        information.photo = item->data(static_cast<int>(BackgroundInfoRole::Photo)).value<QPixmap>();
    }
    {
        item = Base::item(row, static_cast<int>(InfoColumn::Creation));
        information.creation = item->data(static_cast<int>(BackgroundInfoRole::Creation)).toDateTime();
    }
    {
        item = Base::item(row, static_cast<int>(InfoColumn::LastModification));
        information.lastModification = item->data(static_cast<int>(BackgroundInfoRole::LastModification)).toDateTime();
    }
    return information;
}
