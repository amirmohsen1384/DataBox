#ifndef MESSAGES_H
#define MESSAGES_H
class QWidget;
namespace Messages
{
    void noItemSelected(QWidget *parent = nullptr);
    void noSheetFound(QWidget *parent = nullptr);
    bool confirmToDelete(int size, QWidget *parent = nullptr);
    void unknownError(QWidget *parent = nullptr);
    void cannotShowItem(QWidget *parent = nullptr);
    void notEnoughInformation(QWidget *parent = nullptr);
}
#endif // MESSAGES_H
