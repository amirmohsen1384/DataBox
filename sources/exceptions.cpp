#include "../headers/exceptions.h"
#include <QMessageBox>
#define SAVE_FAILED -1
#define CORRUPT_FILE -2
#define OPEN_FAILED -3
#define UNSUPPORTED_FORMAT -4
void WriteFailedException::showMessage() const
{
    QMessageBox message;
    message.setWindowTitle("Failed to save information");
    message.setIcon(QMessageBox::Critical);
    message.setText("An error occurred when saving information.");
    message.setInformativeText("Make sure the selected file is allowed to be saved to.");
    message.exec();
}
void OpenFailedException::showMessage() const
{
    QMessageBox message;
    message.setIcon(QMessageBox::Critical);
    message.setWindowTitle("Failed to open file");
    message.setText("The chosen filename is not available.");
    message.setInformativeText("Check if the selected file is not moved, renamed or unavailable and then try again.");
    message.exec();
}
void UnsupportedFormatException::showMessage() const
{
    QMessageBox message;
    message.setIcon(QMessageBox::Critical);
    message.setWindowTitle("Failed to open file");
    message.setText("The selected file is unsupported.");
    message.setInformativeText("Please select another one and try again.");
    message.exec();
}
void CorruptFileException::showMessage() const
{
    QMessageBox message;
    message.setIcon(QMessageBox::Critical);
    message.setWindowTitle("The file is corrupt");
    message.setText("The selected file is corrupt or damaged.");
    message.setInformativeText("Please select another one and try again.");
    message.exec();
}
void AbstractException::showMessage() const {}
