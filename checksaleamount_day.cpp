#include "checksaleamount_day.h"
#include "ui_checksaleamount_day.h"
#include "selectway.h"
#include "widget1.h"
#include "administratorhomepage.h"
#include "servant_open.h"
#include <QApplication>
#include <QTextCodec>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QTime>
#include <QtSql/QSqlError>
#include <QtDebug>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlRecord>
#include <QPainter>
#include <QMessageBox>
#include <QSpinBox>
checkSaleAmount_day::checkSaleAmount_day(QString name1,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::checkSaleAmount_day)
{
    name=name1;
    ui->setupUi(this);
    setFixedSize(750,427);

    setWindowTitle("按日查看销售额");

    setWindowIcon(QIcon(":/icon.jpg"));
    onShowDb();

}
void checkSaleAmount_day::paintEvent(QPaintEvent *)
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
checkSaleAmount_day::~checkSaleAmount_day()
{
    delete ui;
}

void checkSaleAmount_day::on_pushButton_2_clicked()
{
    SelectWay *select=new SelectWay(name);
    QString jobStr;
    if(job == 1)
        jobStr = "servant";
    else if(job == 2)
        jobStr = "chef";
    else if(job == 4)
        jobStr = "manager";
    else if(job == 5)
        jobStr = "customer";
    select->set_job(jobStr);
    this->hide();
    select->show();
}
void checkSaleAmount_day::onShowDb()
{
    QSqlQuery query;
      int nColumn, nRow;
     query.prepare("select * from saleAmount_day");
     query.exec(); //显示数据
     query.last();//指向最后一条记录 打印行数等于总行数加一
     nRow = query.at() + 1;
     QSqlRecord rec = query.record();
     nColumn=rec.count();
     //qDebug()<<nColumn;
     ui->tableWidget->setRowCount(nRow-1);
     nColumn = ui->tableWidget->columnCount();//列数等于总列数
     ui->tableWidget->setColumnCount(4);
      query.first();//指向第一条记录

      //设置表头
       ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("月份"));
      ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("天"));
      ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem("菜品名(中文)"));
      ui->tableWidget->setHorizontalHeaderItem(3,new QTableWidgetItem("菜品名(英文)"));
      ui->tableWidget->setHorizontalHeaderItem(4,new QTableWidgetItem("销售额"));


    int j=0;
      while(j<nRow)//需修改
      {
      for (int i = 0;i<8; i++)
     if(i<=5) ui->tableWidget->setItem(j, i, new QTableWidgetItem(query.value(i).toString()));//把这条记录放在j行i列
      else ui->tableWidget->setItem(j, i-1, new QTableWidgetItem(query.value(i).toString()));//把这条记录放在j行i列
      j++;
      query.next();//指向下一条记录
      }
ui->tableWidget->show();
}
void checkSaleAmount_day::clearTableData()//清除
{
    //清除表格
    int rowCount = ui->tableWidget->rowCount();
    for(int r = rowCount-1 ; r >=0 ; r--)
    {
        ui->tableWidget->removeRow(r);
    }
}
void checkSaleAmount_day::on_pushButton_clicked()
{
    QString text =ui->lineEdit->text();
  QString day = ui->comboBox->currentText();
    QString sql; int nColumn, nRow;
    sql=QString("select * FROM SaleAmount_day WHERE dishNameInEnglish LIKE '%8' AND date = '%4' order by saleAmount  desc")
            .arg(day).arg(text);
     qDebug()<<sql;
QSqlQuery query;
    bool ok=query.exec(sql);
    if(ok)
    {    clearTableData();

        query.exec(QString("select * FROM SaleAmount_day WHERE dishNameInEnglish LIKE '%8%' AND date = '%4' order by saleAmount  desc")
                        .arg(day).arg(text));

        query.last();//指向最后一条记录 打印行数等于总行数加一
        nRow = query.at() + 1;
        QSqlRecord rec = query.record();
        nColumn=rec.count();
        //qDebug()<<nColumn;
        ui->tableWidget->setRowCount(nRow-1);
        nColumn = ui->tableWidget->columnCount();//列数等于总列数
        ui->tableWidget->setColumnCount(4);
         query.first();//指向第一条记录

         //设置表头
          ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("月份"));
         ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("天"));
         ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem("菜品名(中文)"));
         ui->tableWidget->setHorizontalHeaderItem(3,new QTableWidgetItem("菜品名(英文)"));
         ui->tableWidget->setHorizontalHeaderItem(4,new QTableWidgetItem("销售额"));


       int j=0;
         while(j<nRow)//需修改
         {
         for (int i = 0;i<8; i++)
             if(i<=5) ui->tableWidget->setItem(j, i, new QTableWidgetItem(query.value(i).toString()));//把这条记录放在j行i列
              else ui->tableWidget->setItem(j, i-1, new QTableWidgetItem(query.value(i).toString()));//把这条记录放在j行i列
         j++;
         query.next();//指向下一条记录

    }}
    else
           {
               QMessageBox::information(this ,tr("提示") , tr("查询失败!"));
           }

}
void checkSaleAmount_day::appendRowData(QStringList rowData)
{
    int row = ui->tableWidget->rowCount();

    ui->tableWidget->insertRow(row);

    for(int i  = 0 ; i < rowData.size() ; i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(rowData.at(i));
        ui->tableWidget->setItem(row , i , item);
    }
}
QList<QStringList> checkSaleAmount_day::selectDataFromBase()
{
   QSqlQuery query("SELECT * FROM saleAmount_day");

   QList<QStringList> stuInfo;

   while (query.next())
   {
       QStringList rowData ;

       rowData <<query.value(0).toString();
       rowData <<query.value(1).toString();
       rowData <<query.value(2).toString();
       rowData <<query.value(3).toString();
       rowData <<query.value(4).toString();

       stuInfo.append(rowData);
   }
   return stuInfo;
}

void checkSaleAmount_day::on_pushButton_3_clicked()//刷新
{
    qDebug()<<"onBtnRefresh";
        QList<QStringList> tableData;

        tableData = this->selectDataFromBase();
        if(!tableData.isEmpty())
        {
           this->clearTableData();
            QListIterator<QStringList> itr(tableData);
            while(itr.hasNext())
            {
               this->appendRowData(itr.next());
            }
        }
}

void checkSaleAmount_day::set_job(QString job1)
{
    //进入此页面的身份是服务员
    if(job1 == "servant")
    {
        job = 1;
    }
    //进入此页面的身份是厨师
    else if(job1 == "chef")
    {
        job = 2;
    }
    //进入此页面的身份是管理员
    else if(job1 == "manager")
    {
        job = 4;
    }
    else
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::critical(this, tr("QMessageBox::critical()"),
                                            "无效的职位",
                                            QMessageBox::Abort | QMessageBox::Retry | QMessageBox::Ignore);

    }
}
