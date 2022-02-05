#ifndef INFOSHEET_H
#define INFOSHEET_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui { class InfoSheet; }
class InfoSheet : public QWidget
{
    Q_OBJECT
    QString recentFileName;
    Ui::InfoSheet *ui{};
private:
    void initializeProperties();
    Q_DISABLE_COPY_MOVE(InfoSheet)
public:
    explicit InfoSheet(QWidget *parent = nullptr);
    explicit InfoSheet(const QList<QListWidgetItem*> &items, QWidget *parent = nullptr);
    ~InfoSheet();

    void add(QListWidgetItem *item);
    void add(const QList<QListWidgetItem*> &items);

    QListWidgetItem* itemAt(int row);
    int itemRow(QListWidgetItem *item) const;

    QListWidgetItem* currentItem();
    int currentRow() const;

    QList<QListWidgetItem*> selectedItems();

    void remove(int row);
    void removeSelectedItems();
    void wipe();

    bool isEmpty() const;
    int count() const;

    const QString &getRecentFileName() const;
    void setRecentFileName(const QString &value);
signals:
    void itemActivated(QListWidgetItem *item);
};

#endif // INFOSHEET_H
