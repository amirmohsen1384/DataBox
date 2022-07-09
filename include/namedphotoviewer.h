#ifndef NAMEDPHOTOVIEWER_H
#define NAMEDPHOTOVIEWER_H

#include "photoviewer.h"

class NamedPhotoViewer : public PhotoViewer
{
    Q_OBJECT
    struct {
      QFont m_font;
      QBrush m_brush;
      QString m_text;
      QFontMetricsF m_metrics = QFontMetricsF(m_font);
    } m_info[3];
    QColor m_backgroundColor;
    QMarginsF m_margins;
    int m_indent;
    bool m_fullscreen;
protected:
    virtual void paintEvent(QPaintEvent *event) override;
public:
    enum class Title {MinorTitle = 0, MainTitle = 1, Subtitle = 2};
    NamedPhotoViewer(QWidget *parent = nullptr);
private:
    void initSettings();
    void drawTitle(QPainter *painter, const QPointF &point, Title title);
public:
    QFont font(Title title) const;
    QBrush brush(Title title) const;
    QString text(Title title) const;
    QFontMetricsF metrics(Title title) const;
    QColor backgroundColor() const;
    QMarginsF margins() const;
    int indent() const;
    bool fullscreenMode() const;

    void setFont(const QFont &font, NamedPhotoViewer::Title title);
    void setBrush(const QBrush &brush, NamedPhotoViewer::Title title);
    void setText(const QString &text, NamedPhotoViewer::Title title);
    void setBackgroundColor(const QColor &color);
    void setMargins(const QMarginsF &margins);
    void setIndent(int value);
    void setFullscreenMode(bool value);
signals:
    void fontChanged(QFont font, NamedPhotoViewer::Title title);
    void brushChanged(QBrush brush, NamedPhotoViewer::Title title);
    void textChanged(QString text, NamedPhotoViewer::Title title);
    void backgroundColorChanged(QColor color);
    void marginsChanged(QMarginsF margins);
    void indentChanged(int indent);
    void fullscreenModeChanged(bool value);
};

#endif // NAMEDPHOTOVIEWER_H
