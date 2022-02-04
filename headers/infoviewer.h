#ifndef INFOVIEWER_H
#define INFOVIEWER_H

#include <QDialog>

namespace Ui { class InfoViewer; }
class PhotoViewer;
class PersonInfo;

class InfoViewer : public QDialog
{
    Q_OBJECT
    Ui::InfoViewer *ui{};
    PhotoViewer *photoViewer{};
    Q_DISABLE_COPY_MOVE(InfoViewer)
private:
    void displayInfo(const PersonInfo &information);
    void connectSignals(const PersonInfo *information);
    void setupUi();
public:
    explicit InfoViewer(QWidget *parent = nullptr);
    explicit InfoViewer(const PersonInfo &information, QWidget *parent = nullptr);
    ~InfoViewer();
public slots:
    void setFirstName(const QString &value);
    void setLastName(const QString &value);
    void setFatherName(const QString &value);
    void setBirthday(const QDate &value);
    void setBornProvince(const QString &value);
    void setGender(const QString &value);
    void setNationality(const QString &value);
    void setPhoto(const QPixmap &value);
    void setCreation(const QDateTime &value);
    void setLastModification(const QDateTime &value);
};

#endif // INFOVIEWER_H
