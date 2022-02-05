#include "include/infosheet.h"
#include "ui_infosheet.h"

bool InfoSheet::checkInRange(int row) const
{
    return (row >= 0 && row < mainContainer.size());
}
void InfoSheet::updateVisualList()
{
    ui->infoList->clear();
    InfoItemListIterator iterator(mainContainer);
    while(iterator.hasNext())
        iterator.next().addToQListWidget(ui->infoList);
}
void InfoSheet::setInitalProperties()
{
    connect(ui->infoList, &QListWidget::itemActivated, this, &InfoSheet::activateItem);
}
void InfoSheet::activateItem(QListWidgetItem *item)
{
    emit itemActivated(getItemAt(ui->infoList->row(item)));
}
InfoSheet::InfoSheet(QWidget *parent) : QWidget(parent), ui(new Ui::InfoSheet)
{
    ui->setupUi(this);
    setInitalProperties();
}
InfoSheet::InfoSheet(const InfoItemList &initalList, QWidget *parent) : QWidget(parent), ui(new Ui::InfoSheet)
{
    ui->setupUi(this);
    setInitalProperties();
    add(initalList);
}
InfoSheet::InfoSheet(const InfoSheet &initalSheet, QWidget *parent) : QWidget(parent), ui(new Ui::InfoSheet)
{
    ui->setupUi(this);
    setInitalProperties();
    add(initalSheet.mainContainer);
}
InfoSheet &InfoSheet::operator=(const InfoSheet &other)
{
    add(other.mainContainer);
    return *this;
}
InfoSheet::~InfoSheet()
{
    delete ui;
}
void InfoSheet::add(const InfoItem &information)
{
    int position = mainContainer.size() - 1;
    while(position >= 0 && information.getItemText() < mainContainer.at(position).getItemText())
        --position;

    mainContainer.insert(position + 1, information);
    mainContainer.at(position + 1).insertToQListWidget(ui->infoList, position + 1);
}
void InfoSheet::add(const InfoItemList &infoList)
{
    InfoItemListIterator iterator(infoList);
    while(iterator.hasNext())
        add(iterator.next());
}
const InfoItem *InfoSheet::getItemAt(int row) const
{
    if(!checkInRange(row))
        return nullptr;

    return &mainContainer.at(row);
}

InfoItem *InfoSheet::getItemAt(int row)
{
    if(!checkInRange(row))
        return nullptr;

    return &mainContainer[row];
}
const InfoItem *InfoSheet::getCurrentItem() const
{
    if(mainContainer.isEmpty())
        return nullptr;

    int row = ui->infoList->currentRow();
    if(row == -1)
        return nullptr;

    return &mainContainer.at(row);

}
InfoItem *InfoSheet::getCurrentItem()
{
    if(mainContainer.isEmpty())
        return nullptr;

    int row = ui->infoList->currentRow();
    if(row == -1)
        return nullptr;

    return &mainContainer[row];
}
int InfoSheet::getCurrentRow() const
{
    if(mainContainer.isEmpty())
        return -1;

    return ui->infoList->currentRow();
}
QList<int> InfoSheet::getSelectedRows() const
{
    QList<int> result;
    InfoItemListIterator iterator(mainContainer);
    for(int row = 0; iterator.hasNext(); ++row, iterator.next())
    {
        if(iterator.peekNext().isChecked())
            result.push_back(row);
    }
    return result;
}
QList<InfoItem*> InfoSheet::getSelectedItems()
{
    QList<InfoItem*> result;
    QMutableListIterator<InfoItem> iterator(mainContainer);
    while(iterator.hasNext())
    {
        if(iterator.peekNext().isChecked())
            result.push_back(&iterator.peekNext());
        iterator.next();
    }
    return result;
}
bool InfoSheet::remove(int row)
{
    if(!checkInRange(row))
        return false;

    mainContainer.removeAt(row);
    return true;
}
void InfoSheet::wipe()
{
    mainContainer.clear();
}
bool InfoSheet::isEmpty() const
{
    return mainContainer.isEmpty();
}
int InfoSheet::getSize() const
{
    return mainContainer.size();
}
QDataStream& operator<<(QDataStream &stream, const InfoSheet &sheet)
{
    stream << sheet.mainContainer;
    return stream;
}
QDataStream& operator>>(QDataStream &stream, InfoSheet &sheet)
{
    sheet.mainContainer.clear();
    stream >> sheet.mainContainer;
    sheet.updateVisualList();
    return stream;
}
