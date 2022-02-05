#include "include/messages.h"
#include <QWidget>
#include <QMessageBox>
void Messages::noSheetFound(QWidget *parent)
{
    QMessageBox noSheet(parent);
    noSheet.setWindowTitle("No sheet found.");
    noSheet.setIcon(QMessageBox::Warning);
    noSheet.setText("You have not created a sheet to work on.");
    noSheet.setInformativeText("Please open a file or click <b>New sheet<\b>");
    noSheet.exec();
}
void Messages::noItemSelected(QWidget *parent)
{
    QMessageBox message(parent);
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("No item selected");
    message.setText("You have not selected any item from the current sheet.");
    message.setInformativeText("You can select an item by clicking on it or check it.");
    message.exec();
}
bool Messages::confirmToDelete(int size, QWidget *parent)
{
    QMessageBox confirmMessage(parent);
    confirmMessage.setWindowTitle("Confirm");
    confirmMessage.setIcon(QMessageBox::Warning);
    confirmMessage.setText("Are you sure to delete " + QString::number(size) + " element(s) from the sheet?");
    confirmMessage.setInformativeText("Warning: This cannot be undone later.");
    confirmMessage.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    return confirmMessage.exec() == QMessageBox::Yes ? true : false;
}
void Messages::cannotShowItem(QWidget *parent)
{
    QMessageBox message(parent);
    message.setWindowTitle("Cannot show this item.");
    message.setIcon(QMessageBox::Information);
    message.setText("The selected information is completely private.");
    message.setInformativeText("Please select another item or make some information public.");
    message.exec();
}
void Messages::unknownError(QWidget *parent)
{
    QMessageBox message(parent);
    message.setWindowTitle("Unknown error");
    message.setIcon(QMessageBox::Critical);
    message.setText("An unexpected error has happened.");
    message.exec();
}

void Messages::notEnoughInformation(QWidget *parent)
{
    QMessageBox message(parent);
    message.setWindowTitle("Cannot apply changes.");
    message.setIcon(QMessageBox::Warning);
    message.setText("You have not entered required information.");
    message.setInformativeText("It's important to fill the first name, last name and info text.");
    message.exec();
}
