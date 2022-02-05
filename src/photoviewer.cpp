#include "include/photoviewer.h"
#include <QPainter>
#include <QPaintEvent>
#include <QImageReader>

void PhotoViewer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect area = event->rect();

    if(currentPhoto.isNull())
        painter.fillRect(area, Qt::black);
    else
        painter.drawPixmap(area, currentPhoto);
}
QSize PhotoViewer::minimumSizeHint() const
{
    return QSize(100, 100);
}
QSize PhotoViewer::sizeHint() const
{
    return QSize(220, 300);
}
PhotoViewer::PhotoViewer(QWidget *parent) : QWidget(parent)
{
}
PhotoViewer::PhotoViewer(const QString &filename, QWidget *parent) : QWidget(parent)
{
    setCurrentPhoto(filename);
}
PhotoViewer::PhotoViewer(const QPixmap &initialPhoto, QWidget *parent) : QWidget(parent)
{
    setCurrentPhoto(initialPhoto);
}
PhotoViewer::PhotoViewer(const QImage &initialImage, QWidget *parent) : QWidget(parent)
{
    setCurrentPhoto(initialImage);
}
PhotoViewer::PhotoViewer(const PhotoViewer &copyPhotoViewer, QWidget *parent) : QWidget(parent)
{
   currentPhoto = copyPhotoViewer.currentPhoto;
   minimumPhotoSize = copyPhotoViewer.minimumPhotoSize;
   maximumPhotoSize = copyPhotoViewer.maximumPhotoSize;
   update();
}
PhotoViewer::PhotoViewer(QIODevice *device, QWidget *parent) : QWidget(parent)
{
    setCurrentPhoto(device);
}
QPixmap PhotoViewer::getCurrentPhoto() const
{
    return currentPhoto;
}
void PhotoViewer::setCurrentPhoto(const QPixmap &newPhoto)
{
    if(newPhoto.isNull())
    {
        loadingError = LoadingStatus::TheDataIsInvalid;
        emit loadingStatusChanged(loadingError);
    }
    else if(newPhoto.width() >= minimumPhotoSize.width() && newPhoto.width() <= maximumPhotoSize.width())
    {
        if(newPhoto.height() >= minimumPhotoSize.height() && newPhoto.height() <= maximumPhotoSize.height())
        {
            currentPhoto = newPhoto;
            emit photoChanged(currentPhoto);
            update();
        }
        else
        {
            loadingError = LoadingStatus::SizeNotInRange;
            emit loadingStatusChanged(loadingError);
        }
    }
    else
    {
        loadingError = LoadingStatus::SizeNotInRange;
        emit loadingStatusChanged(loadingError);
    }
}
void PhotoViewer::setCurrentPhoto(const QImage &newPhoto)
{
    if(newPhoto.isNull())
    {
        loadingError = LoadingStatus::TheDataIsInvalid;
        emit loadingStatusChanged(loadingError);
    }
    else if(newPhoto.width() >= minimumPhotoSize.width() && newPhoto.width() <= maximumPhotoSize.width())
    {
        if(newPhoto.height() >= minimumPhotoSize.height() && newPhoto.height() <= maximumPhotoSize.height())
        {
            currentPhoto = QPixmap::fromImage(newPhoto);
            emit photoChanged(currentPhoto);
            update();
        }
        else
        {
            loadingError = LoadingStatus::SizeNotInRange;
            emit loadingStatusChanged(loadingError);
        }
    }
    else
    {
        loadingError = LoadingStatus::SizeNotInRange;
        emit loadingStatusChanged(loadingError);
    }
}
void PhotoViewer::setCurrentPhoto(const QString &newFileName)
{
    QImageReader reader(newFileName);
    QImage image = reader.read();
    if(image.isNull())
    {
        switch(reader.error())
        {
        case QImageReader::ImageReaderError::FileNotFoundError:
            loadingError = LoadingStatus::FileNotExist;
            break;
        case QImageReader::ImageReaderError::DeviceError:
            loadingError = LoadingStatus::DeviceIsNotGood;
            break;
        case QImageReader::ImageReaderError::InvalidDataError:
            loadingError = LoadingStatus::TheDataIsInvalid;
            break;
        case QImageReader::ImageReaderError::UnsupportedFormatError:
            loadingError = LoadingStatus::FormatNotSupported;
            break;
        case QImageReader::ImageReaderError::UnknownError:
            loadingError = LoadingStatus::UnknownError;
            break;
        }
        emit loadingStatusChanged(loadingError);
    }
    else if(image.width() >= minimumPhotoSize.width() && image.width() <= maximumPhotoSize.width())
    {
        if(image.height() >= minimumPhotoSize.height() && image.height() <= maximumPhotoSize.height())
        {
            currentPhoto = QPixmap::fromImage(image);
            emit photoChanged(currentPhoto);
            update();
        }
        else
        {
            loadingError = LoadingStatus::SizeNotInRange;
            emit loadingStatusChanged(loadingError);
        }
    }
    else
    {
        loadingError = LoadingStatus::SizeNotInRange;
        emit loadingStatusChanged(loadingError);
    }
}
void PhotoViewer::setCurrentPhoto(QIODevice *newDevice)
{
    QImageReader reader(newDevice);
    QImage image = reader.read();
    if(image.isNull())
    {
        switch(reader.error())
        {
        case QImageReader::ImageReaderError::FileNotFoundError:
            loadingError = LoadingStatus::FileNotExist;
            break;
        case QImageReader::ImageReaderError::DeviceError:
            loadingError = LoadingStatus::DeviceIsNotGood;
            break;
        case QImageReader::ImageReaderError::InvalidDataError:
            loadingError = LoadingStatus::TheDataIsInvalid;
            break;
        case QImageReader::ImageReaderError::UnsupportedFormatError:
            loadingError = LoadingStatus::FormatNotSupported;
            break;
        case QImageReader::ImageReaderError::UnknownError:
            loadingError = LoadingStatus::UnknownError;
            break;
        }
        emit loadingStatusChanged(loadingError);
    }
    else if(image.width() >= minimumPhotoSize.width() && image.width() <= maximumPhotoSize.width())
    {
        if(image.height() >= minimumPhotoSize.height() && image.height() <= maximumPhotoSize.height())
        {
            currentPhoto = QPixmap::fromImage(image);
            emit photoChanged(currentPhoto);
            update();
        }
        else
        {
            loadingError = LoadingStatus::SizeNotInRange;
            emit loadingStatusChanged(loadingError);
        }
    }
    else
    {
        loadingError = LoadingStatus::SizeNotInRange;
        emit loadingStatusChanged(loadingError);
    }
}
bool PhotoViewer::isEmpty() const
{
    return currentPhoto.isNull();
}
bool PhotoViewer::setMinimumPhotoSize(const QSize &size)
{
    if(size.width() > 0 && size.height() > 0)
    {
        if(maximumPhotoSize.width() >= size.width() && maximumPhotoSize.height() >= size.height())
        {
            minimumPhotoSize = size;
            emit minimumPhotoSizeChanged(size);
            return true;
        }
    }
    return false;
}
bool PhotoViewer::setMaximumPhotoSize(const QSize &size)
{
    if(size.width() > 0 && size.height() > 0)
    {
        if(minimumPhotoSize.height() <= size.height() && minimumPhotoSize.width() <= size.width())
        {
            maximumPhotoSize = size;
            emit maximumPhotoSizeChanged(size);
            return true;
        }
    }
    return false;
}
QSize PhotoViewer::getMinimumPhotoSize() const
{
    return minimumPhotoSize;
}
QSize PhotoViewer::getMaximumPhotoSize() const
{
    return maximumPhotoSize;
}
PhotoViewer::LoadingStatus PhotoViewer::getLoadingStatus() const
{
    return loadingError;
}
PhotoViewer &PhotoViewer::operator=(const PhotoViewer &copyPhotoViewer)
{
    currentPhoto = copyPhotoViewer.currentPhoto;
    minimumPhotoSize = copyPhotoViewer.minimumPhotoSize;
    maximumPhotoSize = copyPhotoViewer.maximumPhotoSize;
    update();

    return *this;
}
