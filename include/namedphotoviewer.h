#ifndef NAMEDPHOTOVIEWER_H
#define NAMEDPHOTOVIEWER_H

#include "photoviewer.h"

class NamedPhotoViewer : public PhotoViewer
{
public:
    enum class SettingsFlag {
        NoFlag = 0x00,
        AlignByDirection = 0x01,
        BetterView = 0x02
    };
    Q_DECLARE_FLAGS(SettingsFlags, SettingsFlag);
private:
    Q_OBJECT
    class TitleInfo
    {
    public:
        QString text;
        QBrush brush = Qt::black;
        QFont font = QFont("Segoe UI", 10, QFont::Bold);
        QFontMetricsF metrics = QFontMetricsF(font);
        Qt::Alignment alignment = Qt::AlignLeft;
    };
    enum Title {Primary = 0, Secondary = 1};
    int m_indent;
    int m_spacing;
    TitleInfo primary;
    TitleInfo secondary;
    QMarginsF m_margins;
    bool m_betterViewTitle;
    QColor m_backgroundColor;
    SettingsFlags m_settings;
private:
    void initSettings();
    QRectF boundingPrimaryRect() const;
    QRectF boundingSecondaryRect() const;
    void drawBetterViewTitle(QPainter *painter, QRectF region);
    void drawTitle(QPainter *painter, const QRectF &rectangle, Title title);
protected:
    void leaveEvent(QEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
public:
    NamedPhotoViewer(QWidget *parent = nullptr);

    QFont primaryFont() const;
    QFont secondaryFont() const;

    QBrush primaryBrush() const;
    QBrush secondaryBrush() const;

    QString primaryText() const;
    QString secondaryText() const;

    QFontMetricsF primaryMetrics() const;
    QFontMetricsF secondaryMetrics() const;

    Qt::Alignment primaryAlignment() const;
    Qt::Alignment secondaryAlignment() const;

    int indent() const;
    int spacing() const;
    QMarginsF margins() const;
    QColor backgroundColor() const;
    NamedPhotoViewer::SettingsFlags settings() const;
public slots:
    void setPrimaryFont(const QFont &font);
    void setSecondaryFont(const QFont &font);

    void setPrimaryBrush(const QBrush &brush);
    void setSecondaryBrush(const QBrush &brush);

    void setPrimaryText(const QString &text);
    void setSecondaryText(const QString &text);

    void setPrimaryAlignment(Qt::Alignment alignment);
    void setSecondaryAlignment(Qt::Alignment alignment);

    void setIndent(int value);
    void setSpacing(int value);
    void setMargins(const QMarginsF &value);
    void setBackgroundColor(const QColor &value);
    void setSettings(NamedPhotoViewer::SettingsFlags flags);
signals:
    void primaryFontChanged(QFont font);
    void secondaryFontChanged(QFont font);

    void primaryBrushChanged(QBrush brush);
    void secondaryBrushChanged(QBrush brush);

    void primaryTextChanged(QString text);
    void secondaryTextChanged(QString text);

    void primaryAlignmentChanged(Qt::Alignment alignment);
    void secondaryAlignmentChanged(Qt::Alignment alignment);

    void indentChanged(int indent);
    void spacingChanged(int spacing);
    void marginsChanged(QMarginsF margins);
    void backgroundColorChanged(QColor color);
    void settingsChanged(NamedPhotoViewer::SettingsFlags flags);
};

Q_DECLARE_OPERATORS_FOR_FLAGS(NamedPhotoViewer::SettingsFlags)

#endif // NAMEDPHOTOVIEWER_H
