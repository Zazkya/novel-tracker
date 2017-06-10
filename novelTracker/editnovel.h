#ifndef EDITNOVEL_H
#define EDITNOVEL_H

#include <QDialog>
#include <QMap>

namespace Ui {
class editNovel;
}

class editNovel : public QDialog
{
    Q_OBJECT

public:
    explicit editNovel(QWidget *parent = 0);
    ~editNovel();
    void setName(QString name);
    QMap<QString, QString> returnMap();
    void setMap(QMap<QString, QString> map);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::editNovel *ui;
    QString currentName;
    QMap<QString, QString> newMap;
    void panelSetup(QMap<QString, QString> map);
    void setMap();
};

#endif // EDITNOVEL_H
