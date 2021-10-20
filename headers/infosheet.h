#ifndef INFOSHEET_H
#define INFOSHEET_H
#include <QWidget>
#include "infoitem.h"
typedef QList<InfoItem> InfoItemList;
typedef QListIterator<InfoItem> InfoItemListIterator;
namespace Ui { class InfoSheet; }
class InfoSheet : public QWidget
{
    Q_OBJECT
    InfoItemList mainContainer;
    Ui::InfoSheet *ui = nullptr;
private:
    bool checkInRange(int row) const;
public:
    InfoSheet(QWidget *parent = nullptr);
    InfoSheet(const InfoItemList &initalList, QWidget *parent = nullptr);
    InfoSheet(const InfoSheet &initalSheet, QWidget *parent = nullptr);
    InfoSheet& operator=(const InfoSheet &other);
    ~InfoSheet();
    void add(const InfoItem &information);
    void add(const InfoItemList &infoList);
    const InfoItem* getItemAt(int row) const;
    InfoItem* getItemAt(int row);
    const InfoItem* getCurrentItem() const;
    InfoItem* getCurrentItem();
    int getCurrentRow() const;
    QList<int> getSelectedRows() const;
    QList<InfoItem*> getSelectedItems();
};

#endif // INFOSHEET_H
