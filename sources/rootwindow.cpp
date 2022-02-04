#include "../headers/rootwindow.h"
#include "ui_rootwindow.h"
#include <QMessageBox>
#include "../headers/infoeditor.h"
#include "headers/infoviewer.h"
#include "../headers/messages.h"

bool RootWindow::checkInRange(int index) const
{
    return (index >= 0 && index < sheetContainer.size());
}
void RootWindow::createNewSheet(InfoSheet *initialSheet)
{
    InfoSheet *newSheet = initialSheet;
    if(newSheet != nullptr)
    {
        sheetContainer.append(newSheet);
        ui->sheetViewer->addTab(newSheet, newSheet->windowTitle());
    }
    else
    {
        newSheet = new InfoSheet;
        sheetContainer.append(newSheet);
        ui->sheetViewer->addTab(newSheet, newSheet->windowTitle());
    }
    connect(newSheet, &InfoSheet::itemActivated, this, &RootWindow::showItem);
}
InfoSheet *RootWindow::getCurrentSheet()
{
    if(sheetContainer.isEmpty() || ui->sheetViewer->currentIndex() == -1)
        return nullptr;

    return sheetContainer[ui->sheetViewer->currentIndex()];
}
const InfoSheet *RootWindow::getCurrentSheet() const
{
    if(sheetContainer.isEmpty() || ui->sheetViewer->currentIndex() == -1)
        return nullptr;

    return sheetContainer.at(ui->sheetViewer->currentIndex());
}
int RootWindow::getCurrentIndex() const
{
    return ui->sheetViewer->currentIndex();
}
bool RootWindow::removeSheet(int index)
{
    if(!checkInRange(index))
        return false;

    sheetContainer.removeAt(index);
    return true;
}
RootWindow::RootWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::RootWindow)
{
    ui->setupUi(this);
    createNewSheet();
}
RootWindow::~RootWindow()
{
    for(int i = sheetContainer.size() - 1; i >= 0; --i)
        delete sheetContainer.takeAt(i);

    delete ui;
}
void RootWindow::on_actionNew_triggered()
{
    if(!sheetContainer.isEmpty() && sheetContainer.last()->isEmpty())
    {
        QMessageBox::warning(this, "The last sheet is still empty", "A new sheet cannot be created if the last one is empty.");
        return;
    }
    createNewSheet();
}
void RootWindow::on_actionAdd_triggered()
{
    InfoSheet *currentSheet = getCurrentSheet();
    if(currentSheet != nullptr)
    {
        InfoEditor editor(this);
        editor.setWindowTitle("Create new information");
        if(editor.exec() == QDialog::Accepted)
            currentSheet->add(*editor.getInformation());
    }
    else
        Messages::noSheetFound(this);
}
void RootWindow::on_actionEdit_triggered()
{
    InfoSheet *currentSheet = getCurrentSheet();
    if(currentSheet != nullptr)
    {
        InfoItem *currentItem = currentSheet->getCurrentItem();
        if(currentItem != nullptr)
        {
            InfoEditor editor(*currentItem, this);
            editor.setWindowTitle(currentItem->getItemText() + " - Edit the information");
            editor.exec();
        }
        else
            Messages::noItemSelected(this);
    }
    else
        Messages::noSheetFound(this);
}
void RootWindow::on_actionRemove_triggered()
{
    InfoSheet *currentSheet = getCurrentSheet();
    if(currentSheet != nullptr)
    {
        QList<int> itemRows = currentSheet->getSelectedRows();
        if(!itemRows.isEmpty())
        {
            if(Messages::confirmToDelete(itemRows.size(), this))
            {
                QListIterator<int> rowIterator(itemRows);
                rowIterator.toBack();
                while(rowIterator.hasPrevious())
                    currentSheet->remove(rowIterator.previous());
            }
        }
        else if(currentSheet->getCurrentRow() != -1)
        {
            if(Messages::confirmToDelete(1, this))
                currentSheet->remove(currentSheet->getCurrentRow());
        }
        else
            Messages::noItemSelected(this);
    }
    else
        Messages::noSheetFound(this);
}
void RootWindow::on_actionWipe_triggered()
{
    InfoSheet *currentSheet = getCurrentSheet();
    if(currentSheet != nullptr)
    {
        int size = currentSheet->getSize();
        if(size <= 0)
            QMessageBox::information(this, "This sheet is already empty.", "There's no item to delete from the sheet.");
        else if(Messages::confirmToDelete(size, this))
            currentSheet->wipe();
    }
    else
        Messages::noSheetFound(this);
}
void RootWindow::showItem(const InfoItem *information)
{
    if(!information->isPrivate())
    {
        InfoViewer monitor(information->info, this);
        monitor.exec();
    }
    else
        Messages::cannotShowItem(this);
}
void RootWindow::on_actionShow_triggered()
{
    InfoSheet *currentSheet = getCurrentSheet();
    if(currentSheet != nullptr)
    {
        InfoItem *current = currentSheet->getCurrentItem();
        if(current != nullptr)
            showItem(current);
        else
            Messages::noItemSelected(this);
    }
    else
        Messages::noSheetFound(this);
}
void RootWindow::on_sheetViewer_tabCloseRequested(int index)
{
    delete sheetContainer.takeAt(index);
}
void RootWindow::on_actionSelectAll_triggered()
{
    InfoSheet *currentSheet = getCurrentSheet();
    if(currentSheet != nullptr)
    {
        for(int i = 0; i < currentSheet->getSize(); ++i)
            currentSheet->getItemAt(i)->setChecked(true);
    }
    else
        Messages::noSheetFound(this);
}
void RootWindow::on_actionUnselectAll_triggered()
{
    InfoSheet *currentSheet = getCurrentSheet();
    if(currentSheet != nullptr)
    {
        for(int i = 0; i < currentSheet->getSize(); ++i)
            currentSheet->getItemAt(i)->setChecked(false);
    }
    else
        Messages::noSheetFound(this);
}

