#ifndef MESSAGES_H
#define MESSAGES_H
class QWidget;
namespace Messages
{
    void noItemSelected(QWidget *parent = nullptr);
    void noSheetFound(QWidget *parent = nullptr);
    void saveFailed(QWidget *parent = nullptr);
    void openFailed(QWidget *parent = nullptr);
    void unsupportedFormat(QWidget *parent = nullptr);
    void corruptFile(QWidget *parent = nullptr);
    bool confirmToDelete(int size, QWidget *parent = nullptr);
    void unknownError(QWidget *parent = nullptr);
    void cannotShowItem(QWidget *parent = nullptr);
}
#endif // MESSAGES_H
