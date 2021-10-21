#ifndef ROOTWINDOW_H
#define ROOTWINDOW_H
#include <QMainWindow>
#include "infosheet.h"
QT_BEGIN_NAMESPACE
namespace Ui { class RootWindow; }
QT_END_NAMESPACE

class RootWindow : public QMainWindow
{
private:
    Q_OBJECT
    Ui::RootWindow *ui = nullptr;
    QList<InfoSheet*> sheetContainer;
    QString recentFileName;
private:
    bool checkInRange(int index) const;
    void createNewSheet(InfoSheet *initialSheet = nullptr);
    InfoSheet* getCurrentSheet();
    const InfoSheet* getCurrentSheet() const;
    int getCurrentIndex() const;
    bool removeSheet(int index);
public:
    RootWindow(QWidget *parent = nullptr);
    ~RootWindow();
private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSaveAs_triggered();
    void on_actionAdd_triggered();
};
#endif // ROOTWINDOW_H
