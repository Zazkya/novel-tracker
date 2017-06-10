#ifndef ADDNOVEL_H
#define ADDNOVEL_H

#include <QDialog>
#include <QMap>

namespace Ui {
class addNovel;
}

class addNovel : public QDialog
{
    Q_OBJECT

public:
    explicit addNovel(QWidget *parent = 0);
    ~addNovel();
    QMap<QString, QString> returnMap();
    bool isAccepted();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::addNovel *ui;
    QMap<QString, QString> addMap;
    void addCollection();
    bool accepted = false;
};

#endif // ADDNOVEL_H
