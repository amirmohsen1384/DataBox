#include "include/countrymodel.h"
#include <QPixmap>
#include <QDir>

CountryModel::CountryModel(QObject *parent) : QAbstractListModel(parent),
    m_container(QDir(":/icons/country").entryInfoList()) {}

QVariant CountryModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) {
        return QVariant();
    }
    int row = index.row();
    if(row < 0 || row >= m_container.size()) {
        return QVariant();
    }
    switch(role) {
    case Qt::DisplayRole: {
        return m_container.at(row).baseName();
    }
    case Qt::DecorationRole: {
        QString filePath = m_container.at(row).absoluteFilePath();
        return QPixmap(filePath);
    }
    default: {
        return QVariant();
    }
    }
}
int CountryModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_container.size();
}

