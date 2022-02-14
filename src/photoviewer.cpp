#include "include/photoviewer.h"
#include <QPainter>
#include <QPaintEvent>

void PhotoViewer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect area = event->rect();

    if(current.isNull())
        painter.fillRect(area, Qt::black);
    else
        painter.drawPixmap(area, current);
}
QSize PhotoViewer::minimumSizeHint() const
{
    return QSize(100, 100);
}
QSize PhotoViewer::sizeHint() const
{
    return QSize(220, 300);
}
PhotoViewer::PhotoViewer(QWidget *parent) : QWidget(parent) {}
PhotoViewer::PhotoViewer(const QPixmap &photo, QWidget *parent) : QWidget(parent)
{
    setCurrentPhoto(photo);
}
QPixmap PhotoViewer::getCurrentPhoto() const
{
    return current;
}
bool PhotoViewer::isEmpty() const
{
    return current.isNull();
}
void PhotoViewer::setCurrentPhoto(const QPixmap &newPhoto)
{
    current = newPhoto;
    emit photoChanged(current);
    update();
}
