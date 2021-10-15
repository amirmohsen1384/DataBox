#ifndef INFOITEM_H
#define INFOITEM_H
#include <QObject>
#include <QListWidgetItem>
#include "personinfo.h"
class InfoItem : public QObject
{
    Q_OBJECT
    QListWidgetItem *item = new QListWidgetItem;
private:
    void setInitialItemProperties();
public:
    PersonInfo info;
    InfoItem(QObject *parent = nullptr);
    InfoItem(const PersonInfo &data, QObject *parent = nullptr);
    InfoItem(const InfoItem &another, QObject *parent = nullptr);
    ~InfoItem();
    QString getItemText() const;
    QColor getTextColor() const;
    QColor getBackgroundColor() const;
    bool isChecked() const;
    bool isHidden() const;
    friend QDataStream& operator<<(QDataStream &stream, const InfoItem &target);
    friend QDataStream& operator>>(QDataStream &stream, InfoItem &target);
    friend bool operator==(const InfoItem &one, const InfoItem &two);
    friend bool operator!=(const InfoItem &one, const InfoItem &two);
    InfoItem& operator=(const InfoItem &another);
    void addToQListWidget(QListWidget *parent) const;
    void insertToQListWidget(QListWidget *parent, int row) const;
public slots:
    void setItemText(const QString &newText);
    void setTextColor(const QColor &newColor);
    void setBackgroundColor(const QColor &newColor);
    void setChecked(const bool &newStatus);
    void setHidden(const bool &newStatus);
signals:
    void itemTextChanged(const QString &text);
    void textColorChanged(const QColor &color);
    void backgroundColorChanged(const QColor &color);
    void checkStatusChanged(const bool &status);
    void hiddenStatusChanged(const bool &status);
};
QDataStream& operator<<(QDataStream &stream, const InfoItem &target);
QDataStream& operator>>(QDataStream &stream, InfoItem &target);
bool operator==(const InfoItem &one, const InfoItem &two);
bool operator!=(const InfoItem &one, const InfoItem &two);
typedef QList<InfoItem> InfoItemList;
typedef QListIterator<InfoItem> InfoItemListIterator;
typedef QMutableListIterator<InfoItem> InfoItemMutableListIterator;
#endif // INFOITEM_H
