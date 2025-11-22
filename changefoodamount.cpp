#include "changefoodamount.h"
#include "ui_changefoodamount.h"
#include "stockwidget.h"
#include "widget1.h"
#include "stockwidget.h"
#include "administratorhomepage.h"
#include "servant_open.h"
#include <QPainter>
#include <QPainter>
#include <QApplication>
#include <QTextCodec>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QTime>
#include <QTimer>
#include <QtSql/QSqlError>
#include <QtDebug>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlRecord>
#include <QMessageBox>
#include "changefoodrest.h"
changeFoodAmount::changeFoodAmount(QString name1,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changeFoodAmount)
{
    name=name1;
    ui->setupUi(this);
    initchangeDlg();
    setFixedSize(750,427);

    on_pushButton_4_clicked();
    setWindowTitle("修改食材数目");

    setWindowIcon(QIcon(":/icon.jpg"));
       m_operateType = Edit;
    onShowDb();
}

changeFoodAmount::~changeFoodAmount()
{
    delete ui;
}

void changeFoodAmount::on_pushButton_2_clicked()
{
            //延时进入界面
            QTimer::singleShot(500,this,[=](){
            //自身隐藏
            this->hide();
            //返回原始界面
            //需要获得进入本界面时的员工岗位信息
            switch(job)
            {
            case 1 ://进入此页面的身份是服务员//返回服务员界面
            {Servant_open *servant = new Servant_open(name);
                servant->show();
                break;}
           case 2://进入此页面的身份是厨师
               { Widget1 *chef = new Widget1(name);
                chef->show();
                break;}

           case 3 ://进入此页面的身份是仓管
            {
                Stockwidget *stock=new Stockwidget(name);
                stock->show();
                 this->hide();
                break;
            }
            case 4 ://进入此页面的身份是管理员
            {
                administratorHomePage *manager = new administratorHomePage(name);
                manager->show();
                break;
            }
            default:
                qDebug()<<"wrong job!";
                break;
            }

            });


}
void changeFoodAmount::paintEvent(QPaintEvent *)
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
void changeFoodAmount::onShowDb()
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

      ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("MATERIAL"));
      ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("AMOUNT"));
      ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem("TYPE"));


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


void changeFoodAmount::on_pushButton_5_clicked()//编辑数据
{
    qDebug()<<"onBtnEdit";


       QStringList rowData ;
       rowData = this->getCurrentRowData();
       if(rowData.isEmpty())
       {
           QMessageBox::information(this, tr("提示") , tr("请选中需要编辑的数据!"));
           return ;
       }
       else
       {
           //m_pAddStuDlg->setEditData(rowData);
       }

       m_pAddStuDlg->activateWindow();
       m_pAddStuDlg->setWindowTitle(tr("修改: 菜品信息"));
       m_pAddStuDlg->exec();


}
QStringList changeFoodAmount::getCurrentRowData()
{
    QStringList rowData;
    int row = ui->tableWidget->currentRow();
    if(row != -1)
    {
        rowData << ui->tableWidget->item(row , 0)->text();
        rowData << ui->tableWidget->item(row , 1)->text();
        rowData << ui->tableWidget->item(row , 2)->text();

    }
    return rowData;
}

void changeFoodAmount::ExecEditSql(QVariantMap stuInfo)
{

    if(m_operateType == Edit)
    {

        QString rest  = stuInfo.value("rest").toString();
           QString sel=stuInfo.value("sel").toString();
       QString material_name =this->getCurrentID();
        QString sql;
        if(sel=="ADD")
        sql = QString("UPDATE material "
                      "set rest=rest+'%2'"

                      " where material_name= '%9' ")
               .arg(rest).arg(material_name);
        else
            sql = QString("UPDATE material "
                          "set rest=rest-'%2'"

                          " where material_name= '%9' ")
                   .arg(rest).arg(material_name);
qDebug()<<sql;
        QSqlQuery query;
        bool ok = query.exec(sql);
        if(ok)
        {
           on_pushButton_4_clicked();//重新加载数据
            QMessageBox::information(this ,tr("提示") , tr("修改成功!"));
        }
        else
        {
            QMessageBox::information(this ,tr("提示") , tr("修改失败!"));
        }

    }


}
void changeFoodAmount::on_pushButton_4_clicked()
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
void changeFoodAmount::appendRowData(QStringList rowData)
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
void changeFoodAmount::clearTableData()//清除
{
    //清除表格
    int rowCount = ui->tableWidget->rowCount();
    for(int r = rowCount-1 ; r >=0 ; r--)
    {
        ui->tableWidget->removeRow(r);
    }
}
 QList<QStringList> changeFoodAmount::selectDataFromBase()
{
    QSqlQuery query("SELECT * FROM material");

    QList<QStringList> stuInfo;

    while (query.next())
    {
        QStringList rowData ;

        rowData <<query.value(1).toString();
        rowData <<query.value(2).toString();
        rowData <<query.value(3).toString();

        stuInfo.append(rowData);
    }
    return stuInfo;
}

 QString changeFoodAmount::getCurrentID()
 {
     QString ID ;
     int row = ui->tableWidget->currentRow();
     if(row != -1)
     {
         ID =  ui->tableWidget->item(row , 0)->text();
     }
     return ID;
 }


void changeFoodAmount::initchangeDlg()//连接
{
   m_pAddStuDlg = new class changeFoodRest(name);

   connect(m_pAddStuDlg , SIGNAL(signalStuInfo(QVariantMap)) , this ,SLOT(ExecEditSql(QVariantMap)));
}

void changeFoodAmount::on_pushButton_3_clicked()
{
    QString text =ui->lineEdit_2->text();
    QString sql; int nColumn, nRow;
    sql=QString("select * FROM material WHERE material_name LIKE '%8%'"
               ).arg(text);
QSqlQuery query;
qDebug()<<sql;
    bool ok=query.exec(sql);
    if(ok)
    {clearTableData();

        query.exec(QString("select * FROM material WHERE material_name LIKE '%8%'")
                       .arg(text));
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
         ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("数量"));
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
   ui->tableWidget->show();}
    else
           {
               QMessageBox::information(this ,tr("提示") , tr("查询失败!"));
           }
}

void changeFoodAmount::set_job(QString job1)
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
    //进入此页面的身份是仓管
    else if(job1 == "warehouse")//查看一下仓管到底叫啥
    {
        job = 3;
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

