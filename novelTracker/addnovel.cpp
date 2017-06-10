#include "addnovel.h"
#include "ui_addnovel.h"
#include <QMap>
#include <QList>
#include <QDebug>

addNovel::addNovel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addNovel)
{
    ui->setupUi(this);
    QList<QString> list;
    list << "Ongoing" << "Hiatus" << "Ended";
    ui->statusBox->addItems(list);
}

addNovel::~addNovel()
{
    delete ui;
}

QMap<QString, QString> addNovel::returnMap(){
    return addMap;
}

bool addNovel::isAccepted(){
    return accepted;
}

void addNovel::addCollection(){
    addMap["title"] = ui->titleEdit->text();
    addMap["status"] = ui->statusBox->currentText();
    addMap["note"] = ui->noteEdit->toPlainText();
    addMap["site"] = ui->siteEdit->text();
    QString url = ui->urlEdit->text();
    qDebug()<<url.endsWith('/');
    if(url.endsWith('/')){
       qDebug()<<"now";
       url = url.remove(url.size() - 1, 1);
    }

    addMap["url"] = url;

    addMap["synopsis"] = ui->synopsisEdit->toPlainText();
    int i  = ui->chapterBox->value();
    QString j = QString::number(i);
    addMap["chapter"] = j;

    qDebug()<<url;
}

void addNovel::on_buttonBox_accepted(){
    this->addCollection();
    accepted = true;
}
