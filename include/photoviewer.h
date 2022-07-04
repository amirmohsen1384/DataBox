#ifndef PHOTOVIEWER_H
#define PHOTOVIEWER_H

#include <QWidget>
#include <QPixmap>

class PhotoViewer : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(PhotoViewer)
protected:
    QPixmap m_photo;
    virtual void paintEvent(QPaintEvent *event) override;
    virtual QSize minimumSizeHint() const override;
    virtual QSize sizeHint() const override;
public:
    PhotoViewer(QWidget *parent = nullptr) : QWidget(parent) {}
    PhotoViewer(const QPixmap &m_init, QWidget *parent = nullptr) : QWidget(parent), m_photo(m_init) {}
    const QPixmap &photo() const;
    inline bool isNull() const { return m_photo.isNull(); }
public slots:
    void setPhoto(const QPixmap &newPhoto);
signals:
    void photoChanged(const QPixmap &photo);
};

#endif // PHOTOVIEWER_H
