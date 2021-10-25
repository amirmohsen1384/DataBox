#ifndef INFOITEM_H
#define INFOITEM_H
#include <QObject>
#include <QListWidgetItem>
#include "personinfo.h"
class InfoItem : public QObject
{
public:
    typedef enum {HideFirstName = 0x01,
                 HideLastName = 0x02,
                 HideFatherName = 0x04,
                 HideFirstNameAndLastName = HideFirstName | HideLastName,
                 HideGender = 0x08,
                 HideBirthday = 0x10,
                 HideNationality = 0x20,
                 HideBornProvince = 0x40,
                 HidePhoto = 0x80,
                 HideCreatedDateTime = 0x100,
                 HideLastModifiedDateTime = 0x200,
                 HideEverything = 0x3FF} HiddenInfoFlag;
    Q_DECLARE_FLAGS(HiddenInfoFlags, HiddenInfoFlag);
private:
    Q_OBJECT
    QListWidgetItem *item = new QListWidgetItem;
    QDateTime createdDateTime = QDateTime::currentDateTime();
    QDateTime lastModifiedDateTime = QDateTime::currentDateTime();
    HiddenInfoFlags hiddenInfo;
    void setInitialProperties();
    void setCreatedDateTime(const QDateTime &date);
    void setLastModifiedDateTime(const QDateTime &date);
    void updateLastModifiedDateTime();
public:
    PersonInfo info;
    InfoItem(QObject *parent = nullptr);
    InfoItem(const PersonInfo &data, QObject *parent = nullptr);
    InfoItem(const InfoItem &another, QObject *parent = nullptr);
    ~InfoItem();
    QString getItemText() const;
    QColor getTextColor() const;
    QColor getBackgroundColor() const;
    InfoItem::HiddenInfoFlags getHiddenInfo() const;
    bool isChecked() const;
    bool isHidden() const;
    QDateTime getCreatedDateTime() const;
    QDateTime getLastModifiedDateTime() const;
    friend QDataStream& operator<<(QDataStream &stream, const InfoItem &target);
    friend QDataStream& operator>>(QDataStream &stream, InfoItem &target);
    friend QDataStream& operator<<(QDataStream &stream, const InfoItem::HiddenInfoFlags &hiddenInfo);
    friend QDataStream& operator>>(QDataStream &stream, InfoItem::HiddenInfoFlags &hiddenInfo);
    friend bool operator==(const InfoItem &one, const InfoItem &two);
    friend bool operator!=(const InfoItem &one, const InfoItem &two);
    InfoItem& operator=(const InfoItem &another);
    void addToQListWidget(QListWidget *parent) const;
    void insertToQListWidget(QListWidget *parent, int row) const;
    bool isPrivate() const;
public slots:
    void setItemText(const QString &newText);
    void setTextColor(const QColor &newColor);
    void setBackgroundColor(const QColor &newColor);
    void setChecked(const bool &newStatus);
    void setHidden(const bool &newStatus);
    void setHiddenInfo(const HiddenInfoFlags &hiddenInfo);
    void setHiddenInfo(const HiddenInfoFlag &hidden, bool toggle = true);
signals:
    void itemTextChanged(const QString &text);
    void textColorChanged(const QColor &color);
    void backgroundColorChanged(const QColor &color);
    void checkStatusChanged(const bool &status);
    void hiddenStatusChanged(const bool &status);
    void createdDateTimeChanged(const QDateTime &date);
    void lastModifiedDateTimeChanged(const QDateTime &date);
    void hiddenInfoChanged(const HiddenInfoFlags &hiddenInfo);
};
QDataStream& operator<<(QDataStream &stream, const InfoItem &target);
QDataStream& operator>>(QDataStream &stream, InfoItem &target);
bool operator==(const InfoItem &one, const InfoItem &two);
bool operator!=(const InfoItem &one, const InfoItem &two);
typedef QList<InfoItem> InfoItemList;
typedef QListIterator<InfoItem> InfoItemListIterator;
typedef QMutableListIterator<InfoItem> InfoItemMutableListIterator;
QDataStream& operator<<(QDataStream &stream, const InfoItem::HiddenInfoFlags &hiddenInfo);
QDataStream& operator>>(QDataStream &stream, InfoItem::HiddenInfoFlags &hiddenInfo);
#endif // INFOITEM_H
