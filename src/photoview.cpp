#include "include/photoview.h"
#include <QPainter>
#include <QPaintEvent>

void PhotoView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect area = event->rect();

    if(photo.isNull())
        painter.fillRect(area, Qt::black);
    else
        painter.drawPixmap(area, photo);
}
QSize PhotoView::minimumSizeHint() const
{
    return QSize(100, 100);
}
QSize PhotoView::sizeHint() const
{
    return QSize(220, 300);
}
PhotoView::PhotoView(QWidget *parent) : QWidget(parent) {}
PhotoView::PhotoView(const QPixmap &photo, QWidget *parent) : QWidget(parent)
{
    setCurrentPhoto(photo);
}
QPixmap PhotoView::currentPhoto() const
{
    return photo;
}
bool PhotoView::isEmpty() const
{
    return photo.isNull();
}
void PhotoView::setCurrentPhoto(const QPixmap &newPhoto)
{
    photo = newPhoto;
    update();
    emit currentPhotoChanged(photo);
}
