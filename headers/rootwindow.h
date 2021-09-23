#ifndef ROOTWINDOW_H
#define ROOTWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class RootWindow; }
QT_END_NAMESPACE

class RootWindow : public QMainWindow
{
    Q_OBJECT

public:
    RootWindow(QWidget *parent = nullptr);
    ~RootWindow();

private:
    Ui::RootWindow *ui;
};
#endif // ROOTWINDOW_H
