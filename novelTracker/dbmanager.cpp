#include "dbmanager.h"
#include <QString>
#include <QCoreApplication>
#include <QSqlQuery>
#include <QMap>
#include <QDate>
#include <QVariant>
#include <QDebug>

dbManager::dbManager(){

}

dbManager::~dbManager(){
    if (m_db.isOpen()){
        m_db.close();
    }
}

bool dbManager::dbOpen(){
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    QString myPath = QCoreApplication::applicationDirPath();
    QString path = myPath + "/novel.db";
    m_db.setDatabaseName(path);
    m_db.open();
    return m_db.isOpen();
}

bool dbManager::isOpen(){
    return m_db.isOpen();
}

bool dbManager::createTable(){
    bool success = false;
    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT EXISTS novelTable(id INTEGER PRIMARY KEY, title TEXT NOT NULL, status TEXT NOT NULL, note TEXT, dateAdded TEXT NOT NULL, dateModified TEXT NOT NULL, site TEXT, url TEXT, chapter INTEGER, synopsis CLOB, UNIQUE(title))");
    if(query.exec()) success = true;
    return success;
}

bool dbManager::addEntry(QMap<QString, QString> map){
    bool success = false;
    QSqlQuery query;
    query.prepare("INSERT OR IGNORE INTO novelTable(id, title, status, note, dateAdded, dateModified, site, url, chapter, synopsis) VALUES (:id, :title, :status, :note, :dateAdded, :dateModified, :site, :url, :chapter, :synopsis)");
    query.bindValue(":title", map["title"]);
    query.bindValue(":status", map["status"]);
    query.bindValue(":note", map["note"]);
    query.bindValue(":dateAdded", this->currentTime());
    query.bindValue(":dateModified", this->currentTime());
    query.bindValue(":site", map["site"]);
    query.bindValue(":url", map["url"]);
    query.bindValue(":chapter", map["chapter"].toInt());
    query.bindValue(":synopsis", map["synopsis"]);
    if(query.exec()) success = true;
    return success;

}



bool dbManager::updateChapter(QString name, int chapter){
    bool success = false;
    QSqlQuery query;
    query.prepare("UPDATE novelTable SET chapter = (:chapter) WHERE title = (:title)");
    query.bindValue(":title", name);
    query.bindValue(":chapter", chapter);
    if(query.exec()) success = true;
    return success;
}

bool dbManager::incChapter(QString name){
    bool success = false;
    QSqlQuery query;
    query.prepare("UPDATE novelTable SET chapter = chapter + 1, dateModified = (:dateModified) WHERE title = (:title)");
    query.bindValue(":title", name);
    query.bindValue(":dateModified", this->currentTime());
    if(query.exec()) success = true;
    return success;
}

bool dbManager::decChapter(QString name){
    bool success = false;
    QSqlQuery query;
    query.prepare("UPDATE novelTable SET chapter = chapter - 1, dateModified = (:dateModified) WHERE title = (:title)");
    query.bindValue(":title", name);
    query.bindValue(":dateModified", this->currentTime());
    if(query.exec()) success = true;
    return success;
}

bool dbManager::editUpdate(QMap<QString, QString> map, QString name){
    bool success = false;
    QSqlQuery query;
    query.prepare("UPDATE novelTable SET chapter = (:chapter), note = (:note), status = (:status), dateModified = (:dateModified) WHERE title = (:title)");
    query.bindValue(":chapter", map["chapter"].toInt());
    query.bindValue(":note", map["note"]);
    query.bindValue(":status", map["status"]);
    query.bindValue(":dateModified", this->currentTime());
    query.bindValue(":title", name);
    if(query.exec()) success = true;
    return success;
}

QSqlQuery dbManager::queryAll(){

    QSqlQuery query;
    query.prepare("SELECT title, status, chapter, dateAdded, dateModified, site, note FROM novelTable");
    query.exec();
    return query;
}

QSqlQuery dbManager::queryStatus(QString status){
   if(status == "All"){
       qDebug()<<"all";
       return this->queryAll();
   }
   else{
       QSqlQuery query;
       query.prepare("SELECT title, status, chapter, dateAdded, dateModified, site, note FROM novelTable WHERE status = (:status)");
       query.bindValue(":status", status);
       query.exec();
       return query;
   }
}

QMap<QString, QString> dbManager::editQuery(QString name){
    QSqlQuery query;
    query.prepare("SELECT status, note, chapter, url FROM novelTable WHERE title = (:title)");
    query.bindValue(":title", name);
    query.exec();
    query.next();
    QMap<QString, QString> map;
    map["title"] = name;
    map["status"] = query.value(0).toString();
    map["note"] = query.value(1).toString();
    map["chapter"] = query.value(2).toString();
    map["url"] = query.value(3).toString();
    return map;
}

QMap<QString, QString> dbManager::panelQuery(QString name){
    QSqlQuery query;
    query.prepare("SELECT synopsis, url FROM novelTable WHERE title = (:title)");
    query.bindValue(":title", name);
    query.exec();
    query.next();
    QMap<QString, QString> map;
    map["synopsis"] = query.value(0).toString();
    map["url"] = query.value(1).toString();
    qDebug()<<map["url"];
    return map;
}

QString dbManager::currentTime(){
    QDate date;
    date = QDate::currentDate();
    QString date_string;
    date_string = date.toString("dd/MM/yyyy");
    return date_string;
}


