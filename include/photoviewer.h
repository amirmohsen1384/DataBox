#ifndef PHOTOVIEWER_H
#define PHOTOVIEWER_H

#include <QWidget>
#include <QPixmap>

class PhotoViewer : public QWidget
{
    Q_OBJECT
    QPixmap current;
    Q_DISABLE_COPY_MOVE(PhotoViewer)
protected:
    void paintEvent(QPaintEvent *event) override;
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
public:
    PhotoViewer(QWidget *parent = nullptr);
    PhotoViewer(const QPixmap &initial, QWidget *parent = nullptr);
    QPixmap getCurrentPhoto() const;
    bool isEmpty() const;
public slots:
    void setCurrentPhoto(const QPixmap &newPhoto);
signals:
    void photoChanged(const QPixmap &photo);
};

#endif // PHOTOVIEWER_H
