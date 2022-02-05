#ifndef PHOTOVIEWER_H
#define PHOTOVIEWER_H
#include <QWidget>
#include <QPixmap>
#include <cstdint>

class PhotoViewer : public QWidget
{
    Q_OBJECT
public:
// Errors which may happen when loading an image to show.
    typedef enum {NormalStatus,
                  FileNotExist,
                  SizeNotInRange,
                  FormatNotSupported,
                  DeviceIsNotGood,
                  TheDataIsInvalid,
                  UnknownError} LoadingStatus;
private:
    LoadingStatus loadingError = PhotoViewer::NormalStatus;
    QPixmap currentPhoto;
    QSize minimumPhotoSize = QSize(1, 1);
    QSize maximumPhotoSize = QSize(SHRT_MAX, SHRT_MAX);
protected:
    void paintEvent(QPaintEvent *event) override;
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
public:
    PhotoViewer(QWidget *parent = nullptr);
    PhotoViewer(const QString &filename, QWidget *parent = nullptr);
    PhotoViewer(const QPixmap &initialPhoto, QWidget *parent = nullptr);
    PhotoViewer(const QImage &initialImage, QWidget *parent = nullptr);
    PhotoViewer(const PhotoViewer &copyPhotoViewer, QWidget *parent = nullptr);
    PhotoViewer(QIODevice *device, QWidget *parent = nullptr);
// Member function to give read-only access to the current photo
    QPixmap getCurrentPhoto() const;
// Member function to give write-only access to the current photo
// The current photo can be changed using a filename, a loaded QPixmap or QImage
    void setCurrentPhoto(const QPixmap &newPhoto);
    void setCurrentPhoto(const QImage &newPhoto);
    void setCurrentPhoto(const QString &newFileName);
    void setCurrentPhoto(QIODevice *newDevice);
// Member function to check whether the current photo is empty
    bool isEmpty() const;
// Member functions to set a range size for photos
    bool setMinimumPhotoSize(const QSize &size);
    bool setMaximumPhotoSize(const QSize &size);
    void setPhotoSizeRange(const QSize &minimumSize, const QSize &maximumSize);
    QSize getMinimumPhotoSize() const;
    QSize getMaximumPhotoSize() const;
// Member function to return the current loading error
    LoadingStatus getLoadingStatus() const;
// Member function to assign a PhotoViewer using assignment operator
    PhotoViewer &operator=(const PhotoViewer &copyPhotoViewer);
signals:
// Signals emitted whenever a special event happens
    void photoChanged(const QPixmap &photo);
    void minimumPhotoSizeChanged(const QSize &size);
    void maximumPhotoSizeChanged(const QSize &size);
    void loadingStatusChanged(const LoadingStatus &loadingError);
};

#endif // PHOTOVIEWER_H
