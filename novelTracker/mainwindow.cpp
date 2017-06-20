#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFile"
#include "QTextStream"
#include "QSqlQueryModel"
#include "dbmanager.h"
#include <QSortFilterProxyModel>
#include <QList>
#include "addnovel.h"
#include "editnovel.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile f(":qdarkstyle/style.qss");
    if (!f.exists())
    {
        printf("Unable to set stylesheet, file not found\n");
    }
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
    }

    db.dbOpen();
    db.createTable();

    QList<QString> statusList;
    statusList << "Recent" << "All" << "Ongoing" << "Hiatus" << "Ended" ;
    ui->statusBox->addItems(statusList);
    this->tableSetup();
    on_viewButton_clicked();

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::tableSetup(){
    QSqlQueryModel *model = new QSqlQueryModel();
    model = this->tableQuery();

    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    QSortFilterProxyModel *sort_filter = new QSortFilterProxyModel(this);
    sort_filter->setDynamicSortFilter(true);
    sort_filter->setSourceModel(model);
    sort_filter->setFilterWildcard(QRegExp(searchText,Qt::CaseInsensitive,QRegExp::Wildcard).pattern());

    sort_filter->setFilterCaseSensitivity(Qt::CaseInsensitive);

    ui->tableView->setModel(sort_filter);
    ui->tableView->setSortingEnabled(true);

    ui->tableView->horizontalHeader()->setDragEnabled(true);
    ui->tableView->setColumnWidth(0,195);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    QItemSelectionModel *select = ui->tableView->selectionModel();
    QObject::connect(select,SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(on_tableView_clicked(QModelIndex)));
}

void MainWindow::panelSetup(){

}

QSqlQueryModel *MainWindow::tableQuery(){
   QSqlQueryModel *model = new QSqlQueryModel();
   model->setQuery(db.queryStatus(currentStatus));
   model->setHeaderData(0, Qt::Horizontal, "Title");
   model->setHeaderData(1, Qt::Horizontal, "Status");
   model->setHeaderData(2, Qt::Horizontal, "Chapter");
   model->setHeaderData(3, Qt::Horizontal, "Date Added");
   model->setHeaderData(4, Qt::Horizontal, "Date Modified");
   model->setHeaderData(5, Qt::Horizontal, "Site");
   model->setHeaderData(6, Qt::Horizontal, "Note");
   return model;
}


void MainWindow::on_tableView_clicked(const QModelIndex &index){
    const QAbstractItemModel *model = index.model();

    QString name = model->data(model->index(index.row(), 0), 0).toString();
    currentTitle = name;

    currentData = db.panelQuery(currentTitle);
    ui->titleLabel->setText(currentTitle);
    ui->synopsisLabel->setText(currentData["synopsis"]);
    QString htmlUrl = "<a href=" + currentData["url"] + ">LINK</a>";
    ui->urlLabel->setOpenExternalLinks(true);
    ui->urlLabel->setText(htmlUrl);
    qDebug()<<htmlUrl;
    qDebug()<<currentData["url"];
}


void MainWindow::on_statusBox_currentIndexChanged(const QString &arg1){
    currentStatus = arg1;
    this->tableSetup();
}




void MainWindow::on_searchBar_textChanged(const QString &arg1){
    searchText = arg1;
    this->tableSetup();
}

void MainWindow::on_viewButton_clicked(){
    if(ui->scrollArea->isHidden()){
        ui->scrollArea->show();
        ui->verticalLayout->addWidget(ui->scrollArea);
        ui->verticalLayout->update();
    }else{
        ui->scrollArea->hide();
        ui->verticalLayout->removeWidget(ui->scrollArea);
        ui->verticalLayout->update();
        ui->tableView->adjustSize();
    }
}

void MainWindow::on_addButton_clicked(){
    addNovel addWindow;
    addWindow.setModal(true);
    addWindow.exec();
    if(addWindow.isAccepted()){
        db.addEntry(addWindow.returnMap());
        this->tableSetup();
    }

}

void MainWindow::on_editButton_clicked(){
    qDebug()<<currentTitle;
    editNovel editWindow;
    QMap<QString, QString> map;
    map = db.editQuery(currentTitle);
    editWindow.setName(currentTitle);
    editWindow.setMap(map);
    editWindow.setModal(true);
    editWindow.exec();
    map = editWindow.returnMap();
    db.editUpdate(map, currentTitle);
    this->tableSetup();
}

void MainWindow::on_incBurtton_clicked(){
    db.incChapter(currentTitle);
    this->tableSetup();
}

void MainWindow::on_decButton_clicked(){
    db.decChapter(currentTitle);
    this->tableSetup();
}

void MainWindow::on_recentButton_clicked(){

}
