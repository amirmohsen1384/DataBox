#include "include/namedphotoviewer.h"
#include <QPaintEvent>
#include <QPainter>

void NamedPhotoViewer::initSettings()
{
    m_indent = 10;
    m_backgroundColor = Qt::red;
    m_backgroundColor.setAlphaF(0.5);

    setMargins(QMarginsF(2,2,2,4));
    setFont(QFont("Segoe UI", 14, QFont::Bold), Title::MinorTitle);
    setBrush(Qt::gray, Title::MinorTitle);
    setText("Minor title", Title::MinorTitle);

    QLinearGradient gradient(QPointF(0, 0.5), QPointF(1, 0.5));
    gradient.setCoordinateMode(QGradient::ObjectMode);
    gradient.setStops({{0.4, Qt::blue}, {0.5, QColor(255, 0, 128)}});
    setFont(QFont("Segoe UI", 18, QFont::Bold), Title::MainTitle);
    setBrush(gradient, Title::MainTitle);
    setText("Main title", Title::MainTitle);

    setFont(QFont("Segoe UI", 10, QFont::Bold), Title::Subtitle);
    setBrush(Qt::black, Title::Subtitle);
    setText("Subtitle", Title::Subtitle);
}
void NamedPhotoViewer::drawTitle(QPainter *painter, const QPointF &point, Title title)
{
    const int index = static_cast<int>(title);
    painter->setFont(m_info[index].m_font);
    painter->setBrush(m_info[index].m_brush);
    painter->drawText(point, m_info[index].m_text);
}
void NamedPhotoViewer::paintEvent(QPaintEvent *event)
{
    PhotoViewer::paintEvent(event);
    const int minor = static_cast<int>(Title::MinorTitle);
    const int main = static_cast<int>(Title::MainTitle);
    const int subtitle = static_cast<int>(Title::Subtitle);

    QPainter painter(this);
    QRectF background;
    {
        qreal height = (m_margins.bottom() + m_margins.top()) * 2 + m_info[subtitle].m_metrics.height();
        height += qMax(m_info[minor].m_metrics.height(), m_info[main].m_metrics.height());

        QRectF base = event->rect();
        background.setWidth(base.width());
        background.setHeight(height);

        QPointF start = base.bottomLeft();
        start.setY(start.y() - m_indent - height);
        background.translate(start);

        painter.fillRect(background, m_backgroundColor);
    }
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
