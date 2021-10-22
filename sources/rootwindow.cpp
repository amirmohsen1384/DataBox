#include "../headers/rootwindow.h"
#include "ui_rootwindow.h"
#include <QMessageBox>
#include "../headers/infoeditor.h"
#include "../headers/infomonitor.h"

void showNoItemSelectedMessage(QWidget *parent = nullptr)
{
    QMessageBox::warning(parent, "No item selected", "You have not selected any item from the current sheet.");
}
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
        InfoEditor editor;
        editor.setWindowTitle("Create new information");
        if(editor.exec() == QDialog::Accepted)
            currentSheet->add(*editor.getInformation());
    }
}
void RootWindow::on_actionEdit_triggered()
{
    InfoSheet *currentSheet = getCurrentSheet();
    if(currentSheet != nullptr)
    {
        InfoItem *currentItem = currentSheet->getCurrentItem();
        if(currentItem != nullptr)
        {
            InfoEditor editor(currentItem);
            editor.setWindowTitle(currentItem->getItemText() + " - Edit the information");
            editor.exec();
        }
        else
            showNoItemSelectedMessage(this);
    }
}
bool confirmToDelete(int size, QWidget *parent = nullptr)
{
    QMessageBox confirmMessage;
    confirmMessage.setParent(parent);
    confirmMessage.setWindowTitle("Confirm");
    confirmMessage.setIcon(QMessageBox::Warning);
    confirmMessage.setText("Are you sure to delete " + QString::number(size) + " element(s) from the sheet?");
    confirmMessage.setInformativeText("Warning: This cannot be undone later.");
    confirmMessage.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    return confirmMessage.exec() == QMessageBox::Yes ? true : false;
}
void RootWindow::on_actionRemove_triggered()
{
    InfoSheet *currentSheet = getCurrentSheet();
    if(currentSheet != nullptr)
    {
        QList<int> itemRows = currentSheet->getSelectedRows();
        if(!itemRows.isEmpty())
        {
            if(confirmToDelete(itemRows.size()))
            {
                QListIterator<int> rowIterator(itemRows);
                rowIterator.toBack();
                while(rowIterator.hasPrevious())
                    currentSheet->remove(rowIterator.previous());
            }
        }
        else
            showNoItemSelectedMessage(this);
    }
}
void RootWindow::on_actionWipe_triggered()
{
    InfoSheet *currentSheet = getCurrentSheet();
    if(currentSheet != nullptr)
    {
        int size = currentSheet->getSize();
        if(size <= 0)
            QMessageBox::information(this, "This sheet is already empty.", "There's no item to delete from the sheet.");
        else if(confirmToDelete(currentSheet->getSize()))
            currentSheet->wipe();
    }
}
void RootWindow::showItem(const InfoItem *information)
{
    InfoMonitor monitor(*information);
    monitor.setFont(QFont("Segoe UI", 10, QFont::Bold));
    monitor.exec();
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
            showNoItemSelectedMessage(this);
    }
}
void RootWindow::on_sheetViewer_tabCloseRequested(int index)
{
    delete sheetContainer.takeAt(index);
}

