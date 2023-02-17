#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("StuInfoSys");
    db = QSqlDatabase::addDatabase("QODBC");
    bool ret=db.isValid();
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("xfblackzero20012");
    db.setDatabaseName("test");
    bool ret2=db.open();
    if(ret2) qDebug()<<"数据库登录成功"<<endl;

    //===============================
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "学号" << "姓名" << "学科" << "GPA");
    connect(ui->addButton,&QPushButton::clicked,this,[=](){
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        QString no=ui->timeEdit->text();
        QString name=ui->reasonEdit->text();
        QString major=ui->recordEdit->text();
        QString GPA=ui->personEdit->text();
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(no));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(name));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(major));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(GPA));
        qDebug()<<tr("insert into stuinfo(no,name,major,GPA)values(%1,'%2','%3',%4)").arg(no,name,major,GPA);
        QSqlQuery query(db);
        int flag=query.exec(tr("insert into stuinfo(no,name,major,GPA)values(%1,'%2','%3',%4)").arg(no,name,major,GPA));
        qDebug()<<"insert success\n";
    });
    connect(ui->removeButton,&QPushButton::clicked,this,[=](){
        this->selectedList=ui->tableWidget->selectedRanges();
//              ui->tableWidget->removeRow(0);
        for(QTableWidgetSelectionRange it:this->selectedList){
//            qDebug()<<"row:"+QString::number(it.bottomRow())+"-"+QString::number(it.topRow())+"deleted"<<endl;
            int i=it.topRow();
            int j=it.bottomRow();
            for(;i<=j;i++){
                ui->tableWidget->removeRow(i);
            }
            QSqlQuery query(db);
            QString no=ui->timeEdit->text();
            int flag=query.exec(tr("delete from stuinfo where no='%1'").arg(no));
        }

    });
    connect(ui->loadButton,&QPushButton::clicked,this,[=](){
        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(0);
        ui->tableWidget->clearContents();
        QSqlQuery query(db);
        int flag=query.exec(tr("select * from stuinfo"));
        while (query.next()) {
            QString no=query.value(0).toString();
            QString name=query.value(1).toString();
            QString major=query.value(2).toString();
            QString GPA=query.value(3).toString();
            int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(no));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(name));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(major));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(GPA));
        }
    });

    connect(ui->searchBtn,&QPushButton::clicked,this,[=](){
       ui->tableWidget->clearContents();
       ui->tableWidget->setRowCount(0);
       QString no=ui->searchEdit->text();
       QSqlQuery query(db);
       int flag=query.exec(tr("select * from stuinfo where no='%1'").arg(no));
       query.next();
       if(flag){
       QString no=query.value(0).toString();
       QString name=query.value(1).toString();
       QString major=query.value(2).toString();
       QString GPA=query.value(3).toString();
       int row = ui->tableWidget->rowCount();
       ui->tableWidget->insertRow(row);
       ui->tableWidget->setItem(row, 0, new QTableWidgetItem(no));
       ui->tableWidget->setItem(row, 1, new QTableWidgetItem(name));
       ui->tableWidget->setItem(row, 2, new QTableWidgetItem(major));
       ui->tableWidget->setItem(row, 3, new QTableWidgetItem(GPA));
       }
    });

}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}
