#include "../headers/messages.h"
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
void Messages::saveFailed(QWidget *parent)
{
    QMessageBox saveFailed(parent);
    saveFailed.setWindowTitle("Failed to save information");
    saveFailed.setIcon(QMessageBox::Warning);
    saveFailed.setText("An error occurred when saving information.");
    saveFailed.setInformativeText("Make sure the selected file is allowed to be saved to.");
    saveFailed.exec();
}
void Messages::openFailed(QWidget *parent)
{
    QMessageBox openFailed(parent);
    openFailed.setIcon(QMessageBox::Warning);
    openFailed.setWindowTitle("Failed to open file");
    openFailed.setText("The chosen filename is not available.");
    openFailed.setInformativeText("Check if the selected file is not moved, renamed or unavailable and then try again.");
    openFailed.exec();
}
void Messages::unsupportedFormat(QWidget *parent)
{
    QMessageBox wrongFormat(parent);
    wrongFormat.setIcon(QMessageBox::Critical);
    wrongFormat.setWindowTitle("Failed to open file");
    wrongFormat.setText("The selected file is unsupported.");
    wrongFormat.setInformativeText("Please select another one and try again.");
    wrongFormat.exec();
}
void Messages::corruptFile(QWidget *parent)
{
    QMessageBox message(parent);
    message.setIcon(QMessageBox::Critical);
    message.setWindowTitle("The file is corrupt");
    message.setText("The selected file is corrupt or damaged.");
    message.setInformativeText("Please select another one and try again.");
    message.exec();
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
