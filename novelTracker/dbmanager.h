#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlQuery>
#include <QString>
#include <QSqlDatabase>
#include <QMap>

class dbManager
{
public:
    dbManager();
    ~dbManager();
    bool dbOpen();
    bool isOpen();
    bool createTable();
    bool addEntry(QMap<QString, QString> map);
    bool updateChapter(QString name, int chapter);
    bool incChapter(QString name);
    bool decChapter(QString name);
    bool editUpdate(QMap<QString, QString> map, QString name);
    QSqlQuery queryAll();
    QSqlQuery queryStatus(QString status);
    QString getSynopsis();
    QMap<QString, QString> editQuery(QString name);
    QMap<QString, QString> panelQuery(QString name);


private:
    QSqlDatabase m_db;
    QString currentTime();
};

#endif // DBMANAGER_H
