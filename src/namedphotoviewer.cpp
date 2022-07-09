#include "include/namedphotoviewer.h"
#include <QPaintEvent>
#include <QPainter>

void NamedPhotoViewer::initSettings()
{
    m_indent = 10;
    m_backgroundColor = Qt::white;
    m_backgroundColor.setAlphaF(0.8);

    m_margins = QMarginsF(5,5,5,5);
    setFont(QFont("Segoe UI", 18, QFont::Bold), Title::MinorTitle);
    setBrush(Qt::gray, Title::MinorTitle);
    setText("Minor", Title::MinorTitle);

    QLinearGradient gradient(QPointF(0, 0.5), QPointF(1, 0.5));
    gradient.setCoordinateMode(QGradient::ObjectMode);
    gradient.setStops({{0.4, Qt::blue}, {0.5, QColor(255, 0, 128)}});
    setFont(QFont("Segoe UI", 20, QFont::Bold), Title::MainTitle);
    setBrush(gradient, Title::MainTitle);
    setText("Main title", Title::MainTitle);

    setFont(QFont("Segoe UI", 10, QFont::Bold), Title::Subtitle);
    setBrush(Qt::white, Title::Subtitle);
    setText("Subtitle", Title::Subtitle);
}
void NamedPhotoViewer::drawTitle(QPainter *painter, const QPointF &point, Title title)
{
    const int index = static_cast<int>(title);
    painter->setFont(m_info[index].m_font);

    QPen target_pen, init_pen = painter->pen();
    target_pen.setBrush(m_info[index].m_brush);
    painter->setPen(target_pen);

    painter->drawText(point, m_info[index].m_text);
    painter->setPen(init_pen);
}
void NamedPhotoViewer::paintEvent(QPaintEvent *event)
{
    PhotoViewer::paintEvent(event);
    const int minor = static_cast<int>(Title::MinorTitle);
    const int main = static_cast<int>(Title::MainTitle);
    const int subtitle = static_cast<int>(Title::Subtitle);

    const QRectF rectangle[3] = {m_info[minor].m_metrics.boundingRect(m_info[minor].m_text),
                                 m_info[main].m_metrics.boundingRect(m_info[main].m_text),
                                 m_info[subtitle].m_metrics.boundingRect(m_info[subtitle].m_text)};
    QPainter painter(this);
    QRectF background;
    {
        qreal height = rectangle[subtitle].height();
        height += qMax(rectangle[minor].height(), rectangle[main].height());

        QRectF base = event->rect();
        background.setWidth(base.width());
        background.setHeight(height);

        QPointF start = base.bottomLeft();
        start.setY(start.y() - m_indent - height);
        background.translate(start);

        painter.fillRect(background, m_backgroundColor);
    }

    painter.translate(background.bottomLeft());
    painter.translate(QPointF(m_margins.left(), -1 * m_margins.bottom()));
    drawTitle(&painter, QPointF(), Title::Subtitle);

    painter.translate(QPointF(0, -1 * rectangle[subtitle].height() - m_margins.top()));
    drawTitle(&painter, QPointF(), Title::MinorTitle);

    drawTitle(&painter,
              QPointF(rectangle[minor].width() + m_info[minor].m_metrics.size(0, QChar(' ')).width(), 0),
              Title::MainTitle);
}
NamedPhotoViewer::NamedPhotoViewer(QWidget *parent) : PhotoViewer(parent)
{
    initSettings();
}
QFont NamedPhotoViewer::font(Title title) const
{
    return m_info[static_cast<int>(title)].m_font;
}
QBrush NamedPhotoViewer::brush(Title title) const
{
    return m_info[static_cast<int>(title)].m_brush;
}
QString NamedPhotoViewer::text(Title title) const
{
    return m_info[static_cast<int>(title)].m_text;
}
QFontMetricsF NamedPhotoViewer::metrics(Title title) const
{
    return m_info[static_cast<int>(title)].m_metrics;
}
QColor NamedPhotoViewer::backgroundColor() const
{
    return m_backgroundColor;
}
QMarginsF NamedPhotoViewer::margins() const
{
    return m_margins;
}
int NamedPhotoViewer::indent() const
{
    return m_indent;
}
bool NamedPhotoViewer::fullscreenMode() const
{
    return m_fullscreen;
}
void NamedPhotoViewer::setFont(const QFont &font, Title title)
{
    m_info[static_cast<int>(title)].m_font = font;
    m_info[static_cast<int>(title)].m_metrics = QFontMetricsF(font);
    update();
    emit fontChanged(font, title);
}
void NamedPhotoViewer::setBrush(const QBrush &brush, Title title)
{
    m_info[static_cast<int>(title)].m_brush = brush;
    update();
    emit brushChanged(brush, title);
}
void NamedPhotoViewer::setText(const QString &text, Title title)
{
    m_info[static_cast<int>(title)].m_text = text;
    update();
    emit textChanged(text, title);
}
void NamedPhotoViewer::setBackgroundColor(const QColor &color)
{
    m_backgroundColor = color;
    update();
    emit backgroundColorChanged(color);
}
void NamedPhotoViewer::setMargins(const QMarginsF &margins)
{
    m_margins = margins;
    update();
    emit marginsChanged(margins);
}
void NamedPhotoViewer::setIndent(int value)
{
    m_indent = value;
    update();
    emit indentChanged(value);
}

void NamedPhotoViewer::setFullscreenMode(bool value)
{
    m_fullscreen = value;
    update();
    emit fullscreenModeChanged(value);
}
