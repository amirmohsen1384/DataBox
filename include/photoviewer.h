#ifndef PHOTOVIEW_H
#define PHOTOVIEW_H

#include <QWidget>
#include <QPixmap>

class PhotoView : public QWidget
{
    Q_OBJECT
    QPixmap photo;
    Q_DISABLE_COPY_MOVE(PhotoView)
protected:
    void paintEvent(QPaintEvent *event) override;
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
public:
    PhotoView(QWidget *parent = nullptr);
    PhotoView(const QPixmap &initial, QWidget *parent = nullptr);
    QPixmap currentPhoto() const;
    bool isEmpty() const;
public slots:
    void setCurrentPhoto(const QPixmap &newPhoto);
signals:
    void currentPhotoChanged(const QPixmap &photo);
};

#endif // PHOTOVIEW_H
