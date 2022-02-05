#include "include/infosheet.h"
#include "ui_infosheet.h"

const QString &InfoSheet::getRecentFileName() const
{
    return recentFileName;
}
void InfoSheet::setRecentFileName(const QString &value)
{
    recentFileName = value;
}
void InfoSheet::initializeProperties()
{
    ui = new Ui::InfoSheet;
    ui->setupUi(this);
    connect(ui->containerData, &QListWidget::itemActivated, this, &InfoSheet::itemActivated);
}
InfoSheet::InfoSheet(QWidget *parent) : QWidget(parent) { initializeProperties(); }
InfoSheet::InfoSheet(const QList<QListWidgetItem*> &list, QWidget *parent) : QWidget(parent)
{
    initializeProperties();
    add(list);
}
InfoSheet::~InfoSheet()
{
    delete ui;
}
void InfoSheet::add(QListWidgetItem *item)
{
    ui->containerData->addItem(item);
}
void InfoSheet::add(const QList<QListWidgetItem*> &items)
{
    QListIterator<QListWidgetItem*> iterator(items);
    while(iterator.hasNext())
        ui->containerData->addItem(iterator.next());
}
QListWidgetItem* InfoSheet::itemAt(int row)
{
    return ui->containerData->item(row);
}
int InfoSheet::itemRow(QListWidgetItem *item) const
{
    return ui->containerData->row(item);
}
QListWidgetItem* InfoSheet::currentItem()
{
    return ui->containerData->currentItem();
}
int InfoSheet::currentRow() const
{
    return ui->containerData->currentRow();
}
QList<QListWidgetItem*> InfoSheet::selectedItems()
{
    return ui->containerData->selectedItems();
}
void InfoSheet::remove(int row)
{
    delete ui->containerData->item(row);
}
void InfoSheet::removeSelectedItems()
{
    QListIterator<QListWidgetItem*> iterator(ui->containerData->selectedItems());
    while(iterator.hasNext())
        delete iterator.next();
}
void InfoSheet::wipe()
{
    ui->containerData->clear();
}
bool InfoSheet::isEmpty() const
{
    return ui->containerData->count() == 0;
}
int InfoSheet::count() const
{
    return ui->containerData->count();
}
