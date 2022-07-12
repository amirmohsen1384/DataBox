#include "include/namedphotoviewer.h"
#include <QPaintEvent>
#include <QPainter>

void NamedPhotoViewer::initSettings()
{
    QColor background = Qt::black;
    background.setAlphaF(0.8);
    m_backgroundColor = background;

    primary.text = "Primary title";
    secondary.text = "Secondary title";
    m_margins = QMarginsF(10, 5, 10, 5);
    m_indent = 20;
    m_spacing = 5;
    m_settings = m_settings | SettingsFlag::AlignByDirection;
    m_betterViewTitle = false;

    QLinearGradient primaryBrush(QPointF(0, 0.5), QPointF(1, 0.5));
    primaryBrush.setCoordinateMode(QGradient::ObjectMode);
    primaryBrush.setColorAt(0, QColorConstants::Svg::blue);
    primaryBrush.setColorAt(1, QColorConstants::Svg::gold);
    primary.brush = primaryBrush;

    secondary.brush = Qt::white;
}
void NamedPhotoViewer::paintEvent(QPaintEvent *event)
{
    PhotoViewer::paintEvent(event);

    QPainter painter(this);
    const QRect mainRegion = event->rect();

    drawBetterViewTitle(&painter, QRectF(0, 0, mainRegion.width(), 0));
    if(m_settings.testFlag(SettingsFlag::BetterView)) {
        return;
    }

    const QRectF boundingPrimary = boundingPrimaryRect();
    const QRectF boundingSecondary = boundingSecondaryRect();

    QRectF background;
    {
        qreal height = boundingPrimary.height();
        height += boundingSecondary.height();
        height += m_margins.top() + m_margins.bottom() + m_spacing;
        background.setHeight(height);

        background.setWidth(mainRegion.width());

        QPointF startPoint;
        startPoint.setY(mainRegion.bottomLeft().ry() - m_indent - height);

        background.translate(startPoint);
        painter.fillRect(background, m_backgroundColor);
    }
    painter.translate(background.topLeft());

    QRectF primaryTitle;
    primaryTitle.setTopLeft(QPointF(m_margins.left(), m_margins.top()));
    primaryTitle.setWidth(background.width() - m_margins.left() - m_margins.right());
    primaryTitle.setHeight(boundingPrimary.height());
    drawTitle(&painter, primaryTitle, Title::Primary);

    QRectF secondaryTitle;
    {
        QPointF startPoint;
        startPoint.setX(primaryTitle.x());
        startPoint.setY(primaryTitle.height() + m_spacing);
        secondaryTitle.setTopLeft(startPoint);
    }
    secondaryTitle.setWidth(primaryTitle.width());
    secondaryTitle.setHeight(boundingSecondary.height());
    drawTitle(&painter, secondaryTitle, Title::Secondary);
}
void NamedPhotoViewer::drawTitle(QPainter *painter, const QRectF &rectangle, NamedPhotoViewer::Title title)
{
    const TitleInfo &info = title == Title::Primary ? primary : secondary;

    QPen initPen = painter->pen(), pen;
    pen.setBrush(info.brush);
    painter->setPen(pen);

    QFont initFont = painter->font();
    painter->setFont(info.font);

    if(!m_settings.testFlag(SettingsFlag::AlignByDirection)) {
        painter->drawText(rectangle, info.text, QTextOption(info.alignment));
    } else {
        Qt::LayoutDirection direction = painter->layoutDirection();
        Qt::Alignment alignment = info.alignment;
        if(info.text.isRightToLeft()) {
            painter->setLayoutDirection(Qt::RightToLeft);
            alignment.setFlag(Qt::AlignLeft, false);
            alignment.setFlag(Qt::AlignRight, true);
        } else {
            painter->setLayoutDirection(Qt::LeftToRight);
            alignment.setFlag(Qt::AlignLeft, true);
            alignment.setFlag(Qt::AlignRight, false);
        }
        painter->setLayoutDirection(direction);
        painter->drawText(rectangle, info.text, QTextOption(alignment));
    }
    painter->setPen(initPen);
    painter->setFont(initFont);
}
void NamedPhotoViewer::enterEvent(QEnterEvent *event)
{
    Q_UNUSED(event)
    m_betterViewTitle = true;
    update();
}
void NamedPhotoViewer::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    m_betterViewTitle = false;
    update();
}
void NamedPhotoViewer::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    m_settings.setFlag(SettingsFlag::BetterView, !m_settings.testFlag(SettingsFlag::BetterView));
    update();
}
QRectF NamedPhotoViewer::boundingPrimaryRect() const
{
    return primary.metrics.boundingRect(primary.text);
}
QRectF NamedPhotoViewer::boundingSecondaryRect() const
{
    return secondary.metrics.boundingRect(secondary.text);
}
void NamedPhotoViewer::drawBetterViewTitle(QPainter *painter, QRectF region)
{
    QColor color = Qt::black;
    color.setAlphaF(0.8);

    const QFont init_font = painter->font();
    const QPen init_pen = painter->pen();

    QPen current_pen = painter->pen();
    current_pen.setBrush(Qt::white);
    painter->setPen(current_pen);

    painter->setFont(QFont("Segoe UI", 9, QFont::Bold));
    qreal height = m_margins.top() + m_margins.bottom();
    QFontMetricsF metrics(painter->font());

    if(m_settings.testFlag(SettingsFlag::BetterView)) {
        const QString &text = "Double-click to go back.";

        height += metrics.boundingRect(text).height();
        region.setHeight(height);

        painter->fillRect(region, color);
        painter->drawText(region, text, QTextOption(Qt::AlignCenter));

    } else if(m_betterViewTitle) {
        const QString &text = "Double-click to view the photo better.";

        height += metrics.boundingRect(text).height();
        region.setHeight(height);

        painter->fillRect(region, color);
        painter->drawText(region, text, QTextOption(Qt::AlignCenter));
    }

    painter->setFont(init_font);
    painter->setPen(init_pen);
}
NamedPhotoViewer::NamedPhotoViewer(QWidget *parent) : PhotoViewer(parent)
{
    initSettings();
}
QFont NamedPhotoViewer::primaryFont() const
{
    return primary.font;
}
QFont NamedPhotoViewer::secondaryFont() const
{
    return secondary.font;
}
QBrush NamedPhotoViewer::primaryBrush() const
{
    return primary.brush;
}
QBrush NamedPhotoViewer::secondaryBrush() const
{
    return secondary.brush;
}
QString NamedPhotoViewer::primaryText() const
{
    return primary.text;
}
QString NamedPhotoViewer::secondaryText() const
{
    return secondary.text;
}
QFontMetricsF NamedPhotoViewer::primaryMetrics() const
{
    return primary.metrics;
}
QFontMetricsF NamedPhotoViewer::secondaryMetrics() const
{
    return secondary.metrics;
}
Qt::Alignment NamedPhotoViewer::primaryAlignment() const
{
    return primary.alignment;
}
Qt::Alignment NamedPhotoViewer::secondaryAlignment() const
{
    return secondary.alignment;
}
int NamedPhotoViewer::indent() const
{
    return m_indent;
}
int NamedPhotoViewer::spacing() const
{
    return m_spacing;
}
QMarginsF NamedPhotoViewer::margins() const
{
    return m_margins;
}
NamedPhotoViewer::SettingsFlags NamedPhotoViewer::settings() const
{
    return m_settings;
}
QColor NamedPhotoViewer::backgroundColor() const
{
    return m_backgroundColor;
}
void NamedPhotoViewer::setPrimaryFont(const QFont &font)
{
    primary.font = font;
    primary.metrics = QFontMetricsF(font);
    update();
    emit primaryFontChanged(font);
}
void NamedPhotoViewer::setSecondaryFont(const QFont &font)
{
    secondary.font = font;
    secondary.metrics = QFontMetricsF(font);
    update();
    emit secondaryFontChanged(font);
}
void NamedPhotoViewer::setPrimaryBrush(const QBrush &brush)
{
    primary.brush = brush;
    update();
    emit primaryBrushChanged(brush);
}
void NamedPhotoViewer::setSecondaryBrush(const QBrush &brush)
{
    secondary.brush = brush;
    update();
    emit secondaryBrushChanged(brush);
}
void NamedPhotoViewer::setPrimaryText(const QString &text)
{
    primary.text = text;
    update();
    emit primaryTextChanged(text);
}
void NamedPhotoViewer::setSecondaryText(const QString &text)
{
    secondary.text = text;
    update();
    emit secondaryTextChanged(text);
}
void NamedPhotoViewer::setPrimaryAlignment(Qt::Alignment alignment)
{
    primary.alignment = alignment;
    update();
    emit primaryAlignmentChanged(alignment);
}
void NamedPhotoViewer::setSecondaryAlignment(Qt::Alignment alignment)
{
    secondary.alignment = alignment;
    update();
    emit secondaryAlignmentChanged(alignment);
}
void NamedPhotoViewer::setIndent(int value)
{
    m_indent = value;
    update();
    emit indentChanged(value);
}
void NamedPhotoViewer::setSpacing(int value)
{
    m_spacing = value;
    update();
    emit spacingChanged(value);
}
void NamedPhotoViewer::setSettings(NamedPhotoViewer::SettingsFlags flags)
{
    m_settings = flags;
    update();
    emit settingsChanged(flags);
}
void NamedPhotoViewer::setMargins(const QMarginsF &value)
{
    m_margins = value;
    update();
    emit marginsChanged(value);
}
void NamedPhotoViewer::setBackgroundColor(const QColor &value)
{
    m_backgroundColor = value;
    update();
    emit backgroundColorChanged(value);
}
