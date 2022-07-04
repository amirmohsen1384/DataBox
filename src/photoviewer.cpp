#include "include/photoviewer.h"
#include <QPaintEvent>
#include <QPainter>

void PhotoViewer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(QRect area = event->rect(); m_photo.isNull()) {
        painter.fillRect(area, Qt::black);
    } else {
        painter.drawPixmap(area, m_photo);
    }
}
QSize PhotoViewer::minimumSizeHint() const
{
    return QSize(100, 100);
}
QSize PhotoViewer::sizeHint() const
{
    return QSize(220, 300);
}
const QPixmap &PhotoViewer::photo() const
{
    return m_photo;
}
void PhotoViewer::setPhoto(const QPixmap &newPhoto)
{
    m_photo = newPhoto;
    update();
    emit photoChanged(m_photo);
}
