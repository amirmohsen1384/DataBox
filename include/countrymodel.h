#ifndef COUNTRYMODEL_H
#define COUNTRYMODEL_H

#include <QAbstractListModel>
#include <QFileInfoList>

class CountryModel : public QAbstractListModel
{
    Q_OBJECT
    QFileInfoList m_container;
public:
    CountryModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &parent) const override;
};

#endif // COUNTRYMODEL_H
