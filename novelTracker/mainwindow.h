#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include "dbmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_statusBox_currentIndexChanged(const QString &arg1);

    void on_searchBar_textChanged(const QString &arg1);

    void on_viewButton_clicked();

    void on_addButton_clicked();

    void on_editButton_clicked();

    void on_incBurtton_clicked();

    void on_decButton_clicked();

    void on_recentButton_clicked();

private:
    Ui::MainWindow *ui;
    QString currentTitle;
    QString currentStatus;
    QString searchText;
    dbManager db;
    void tableSetup();
    void panelSetup();
    QSqlQueryModel *tableQuery();
    QMap<QString, QString> currentData;
};

#endif // MAINWINDOW_H
