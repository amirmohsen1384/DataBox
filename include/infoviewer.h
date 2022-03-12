#ifndef INFOVIEWER_H
#define INFOVIEWER_H

#include <QDialog>
#include "infocontainer.h"

namespace Ui { class InfoViewer; }
class PhotoViewer;

class InfoViewer : public QDialog
{
    Q_OBJECT
    Ui::InfoViewer *ui{};
    PhotoViewer *photoViewer{};
    Q_DISABLE_COPY_MOVE(InfoViewer)
private:
    void initViewer(const InfoContainer &information);
    void setupUi();
public:
    explicit InfoViewer(QWidget *parent = nullptr);
    InfoViewer(const InfoContainer &information, QWidget *parent = nullptr);
    ~InfoViewer();
public slots:
    void setFirstName(const QString &value);
    void setLastName(const QString &value);
    void setFatherName(const QString &value);
    void setBirthday(const QDate &value);
    void setBornProvince(const QString &value);
    void setGender(const InfoContainer::GenderContainer &value);
    void setNationality(const QString &value);
    void setPhoto(const QPixmap &value);
    void setCreation(const QDateTime &value);
    void setLastModification(const QDateTime &value);
};

#endif // INFOVIEWER_H
