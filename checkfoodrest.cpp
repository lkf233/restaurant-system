#include "checkfoodrest.h"
#include "ui_checkfoodrest.h"
#include "stockwidget.h"
#include <QPainter>
#include <QApplication>
#include <QTextCodec>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QTime>
#include <QtSql/QSqlError>
#include <QtDebug>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlRecord>
checkFoodRest::checkFoodRest(QString name1,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::checkFoodRest)
{
    name = name1;
    ui->setupUi(this);
    setFixedSize(750,427);

    setWindowTitle("查看食材");

    setWindowIcon(QIcon(":/icon.jpg"));
    onShowDb();
}

checkFoodRest::~checkFoodRest()
{
    delete ui;
}

void checkFoodRest::on_pushButton_2_clicked()
{
    Stockwidget *stock=new Stockwidget(name);
    this->hide();
    stock->show();
}
void checkFoodRest::paintEvent(QPaintEvent *)
{
    //创建画家，制定绘画设备
    QPainter painter(this);
    //创建QPixmap对象
    QPixmap pix;
    //加载图片
    pix.load(":/IMAGES/BACKGROUND");
    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);


}
void checkFoodRest::onShowDb()
{
    QSqlQuery query;
      int nColumn, nRow;
     query.prepare("select * from material");
     query.exec(); //显示数据
     query.last();//指向最后一条记录 打印行数等于总行数加一
     nRow = query.at() + 1;
     QSqlRecord rec = query.record();
     nColumn=rec.count();
     //qDebug()<<nColumn;
     ui->tableWidget->setRowCount(nRow-1);
     nColumn = ui->tableWidget->columnCount();//列数等于总列数
     ui->tableWidget->setColumnCount(3);
      query.first();//指向第一条记录

      //设置表头

      ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("食材"));
      ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("数目"));
      ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem("属性"));


    int j=0;
      while(j<nRow)
      {
      for (int i = 1;i<8; i++)
     if(i<=4) ui->tableWidget->setItem(j, i-1, new QTableWidgetItem(query.value(i).toString()));//把这条记录放在j行i列
      else ui->tableWidget->setItem(j, i-2, new QTableWidgetItem(query.value(i).toString()));//把这条记录放在j行i列
      j++;
      query.next();//指向下一条记录
      }
ui->tableWidget->show();
}
