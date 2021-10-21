#include "../headers/rootwindow.h"
#include "ui_rootwindow.h"
#include <QMessageBox>
#include "../headers/infoeditor.h"
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
    delete ui;
}
void RootWindow::on_actionNew_triggered()
{
    if(sheetContainer.last()->isEmpty())
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
