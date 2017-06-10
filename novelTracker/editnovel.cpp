#include "editnovel.h"
#include "ui_editnovel.h"

editNovel::editNovel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editNovel)
{
    ui->setupUi(this);

}

editNovel::~editNovel()
{
    delete ui;
}

void editNovel::setName(QString name){
    currentName = name;
}

QMap<QString, QString> editNovel::returnMap(){
    return newMap;
}

void editNovel::setMap(QMap<QString, QString> map){
    this->panelSetup(map);
}

void editNovel::on_buttonBox_accepted(){
    this->setMap();
}

void editNovel::panelSetup(QMap<QString, QString> map){
    ui->titelEdit->setText(map["title"]);
    ui->chapterBox->setValue(map["chapter"].toInt());
    ui->noteEdit->setText(map["note"]);
    ui->urlEdit->setText(map["url"]);

    QList<QString> list;
    if(map["status"] == "Ongoing"){
        list << "Ongoing" << "Hiatus" << "Ended";
    }
    if(map["status"] == "Hiatus"){
        list  << "Hiatus" << "Ongoing" << "Ended";
    }
    if(map["status"] == "Ended"){
        list << "Ended" << "Ongoing" << "Hiatus";
    }
    ui->statusBox->addItems(list);
}

void editNovel::setMap(){
    newMap["title"] = currentName;
    newMap["status"] = ui->statusBox->currentText();
    newMap["note"] = ui->noteEdit->toPlainText();
    newMap["url"] = ui->urlEdit->text();
    int i = ui->chapterBox->value();
    newMap["chapter"] = QString::number(i);
}













