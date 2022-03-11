#ifndef INFOMODEL_H
#define INFOMODEL_H

#include <QStandardItemModel>
#include "include/personinfo.h"

class InfoModel : public QStandardItemModel
{
    Q_OBJECT
    void initModel();
public:
    enum class InfoColumn
    {
      FirstName = 0,
      LastName = 1,
      Gender = 2,
      Birthday = 3,
      Creation = 4,
      LastModification = 5
    }; Q_ENUM(InfoColumn)
    enum class BackgroundInfoRole
    {
        Gender = Qt::UserRole,
        Birthday = Qt::UserRole,
        Creation = Qt::UserRole,
        LastModification = Qt::UserRole,
        FatherName = Qt::UserRole,
        Nationality = Qt::UserRole,
        BornProvince = Gender + 1,
        Photo = Birthday + 1
    }; Q_ENUM(BackgroundInfoRole)

    explicit InfoModel(QObject *parent = nullptr);

    using QStandardItemModel::index;
    QModelIndex index(int row, const InfoColumn &column) const;

    void setInformation(int row, const PersonInfo &info);
    PersonInfo information(int row) const;
};

#endif // INFOMODEL_H
