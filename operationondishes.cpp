#include "operationondishes.h"
#include "ui_operationondishes.h"
#include "add.h"
#include "widget1.h"
#include "modifymenu.h"
#include "widget1.h"
#include "stockwidget.h"
#include "administratorhomepage.h"
#include "servant_open.h"
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
#include <QPainter>
#include <QMessageBox>
OperationOnDishes::OperationOnDishes(QString name1,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OperationOnDishes)
{
    name = name1;
    ui->setupUi(this);
    onShowDb();
    initAddDlg();
  on_pushButton_6_clicked();
  setFixedSize(800,427);

     m_operateType = Add;
     setWindowTitle("菜品操作");

     setWindowIcon(QIcon(":/icon.jpg"));
connect(ui->lineEdit,&QLineEdit::returnPressed,[this](){on_pushButton_4_clicked();});
}

OperationOnDishes::~OperationOnDishes()
{
    delete ui;
}

void OperationOnDishes::onShowDb()
{
    QSqlQuery query;
      int nColumn, nRow;
     query.prepare("select * from menu");
     query.exec(); //显示数据
     query.last();//指向最后一条记录 打印行数等于总行数加一
     nRow = query.at() + 1;
     QSqlRecord rec = query.record();
     nColumn=rec.count();
     //qDebug()<<nColumn;
     ui->tableWidget->setRowCount(nRow-1);
     nColumn = ui->tableWidget->columnCount();//列数等于总列数
     ui->tableWidget->setColumnCount(6);
      query.first();//指向第一条记录

      //设置表头
      ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("菜品名(英文)"));
      ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("菜品名(中文)"));
      ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem("食材"));
      ui->tableWidget->setHorizontalHeaderItem(3,new QTableWidgetItem("价格"));
      ui->tableWidget->setHorizontalHeaderItem(4,new QTableWidgetItem("风格"));
      ui->tableWidget->setHorizontalHeaderItem(5,new QTableWidgetItem("辣度"));


    int j=0;
      while(j<nRow)
      {
      for (int i = 1;i<8; i++)
     if(i<=3) ui->tableWidget->setItem(j, i-1, new QTableWidgetItem(query.value(i).toString()));//把这条记录放在j行i列
      else ui->tableWidget->setItem(j, i-2, new QTableWidgetItem(query.value(i).toString()));//把这条记录放在j行i列
      j++;
      query.next();//指向下一条记录
      }
ui->tableWidget->show();
}

//返回原岗位界面
void OperationOnDishes::on_pushButton_3_clicked()
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
void OperationOnDishes::onBtnAdd()
{
    qDebug()<<"onBtnAdd";
    m_operateType = Add;
    if(m_pAddStuDlg)
    {
        m_pAddStuDlg->activateWindow();
        m_pAddStuDlg->setWindowTitle(tr("添加: 新的菜品"));
        m_pAddStuDlg->exec();
    }
}
void OperationOnDishes::on_pushButton_clicked()//增加菜品
{
    onBtnAdd();

}

void OperationOnDishes::paintEvent(QPaintEvent *)
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
void OperationOnDishes::on_pushButton_5_clicked()//修改菜品
{
    qDebug()<<"onBtnEdit";

       m_operateType = Edit;

       QStringList rowData ;
       rowData = this->getCurrentRowData();
       if(rowData.isEmpty())
       {
           QMessageBox::information(this, tr("提示") , tr("请选中需要编辑的数据!"));
           return ;
       }
       else
       {
           m_pAddStuDlg->setEditData(rowData);
       }

       m_pAddStuDlg->activateWindow();
       m_pAddStuDlg->setWindowTitle(tr("修改: 菜品信息"));
       m_pAddStuDlg->exec();
}
void OperationOnDishes::ExecEditSql(QVariantMap stuInfo)
{
    if(m_operateType == Edit)
    {
        QString  menuInChinese= stuInfo.value("menuinChinese").toString();
        QString menuInEnglish = stuInfo.value("menuinEnglish").toString();
        QString material = stuInfo.value("material").toString();
        QString price = stuInfo.value("price").toString();
        QString style = stuInfo.value("style").toString();
        QString spicy  = stuInfo.value("spicy").toString();
qDebug()<<menuInEnglish;
qDebug()<<menuInChinese;
        QString sql;
        sql = QString("UPDATE menu "
                      "set  menuInEnglish = '%2' ,material= '%3',"
                      "price = '%4',style= '%5',spicy = '%6'"
                      " where menuInChinese= '%9' ")
                .arg(menuInEnglish).arg(material).arg(price).arg(style).arg(spicy).arg(menuInChinese);
qDebug()<<sql;
        QSqlQuery query;
        bool ok = query.exec(sql);
        if(ok)
        {

           on_pushButton_6_clicked();//重新加载数据

            QMessageBox::information(this ,tr("提示") , tr("修改成功!"));
        }
        else
        {
            QMessageBox::information(this ,tr("提示") , tr("修改失败!"));
        }

    }
}

QStringList OperationOnDishes::getCurrentRowData()
{
    QStringList rowData;
    int row = ui->tableWidget->currentRow();
    if(row != -1)
    {
        rowData << ui->tableWidget->item(row , 0)->text();
        rowData << ui->tableWidget->item(row , 1)->text();
        rowData << ui->tableWidget->item(row , 2)->text();
        rowData << ui->tableWidget->item(row , 3)->text();
        rowData << ui->tableWidget->item(row , 4)->text();
        rowData << ui->tableWidget->item(row , 5)->text();

    }
    return rowData;
}
void OperationOnDishes::ExecAddsql(QVariantMap stuInfo)
{

    if(m_operateType == Add)
        {

    QString nameInChinese=stuInfo.value("menuinChinese").toString();
    QString nameInEnglish=stuInfo.value("menuinEnglish").toString();
    QString material=stuInfo.value("material").toString();
   QString price=stuInfo.value("price").toString();
     QString style=stuInfo.value("style").toString();
      QString spicy=stuInfo.value("spicy").toString();
      QString sql;

      sql=QString("insert into menu(menuInChinese,menuInEnglish,material,price,style,spicy)"
                  "VALUES ('%1','%2','%3','%4','%5','%6')").arg(nameInChinese).arg(nameInEnglish).arg(material).arg(price).arg(style).arg(spicy);
  QSqlQuery query;
qDebug()<<sql<<endl;
      bool ok=query.exec(sql);

      if(ok)
      {
          QStringList rowData;
          rowData<< nameInChinese<<nameInEnglish <<material<<price<<style<<spicy;
           this->appendRowData(rowData);
          QMessageBox::information(this, tr("提示"),tr("添加成功！"));
      }
      else
             {query.lastError();
                 QMessageBox::information(this ,tr("提示") , tr("修改失败!"));
             }

}}
void OperationOnDishes::appendRowData(QStringList rowData)
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
void OperationOnDishes::initAddDlg()//连接
{
   m_pAddStuDlg = new class Add(name);
    connect(m_pAddStuDlg , SIGNAL(signalStuInfo(QVariantMap)) , this ,SLOT(ExecAddsql(QVariantMap)));
   connect(m_pAddStuDlg , SIGNAL(signalStuInfo(QVariantMap)) , this ,SLOT(ExecEditSql(QVariantMap)));
}

void OperationOnDishes::on_pushButton_2_clicked()//删除菜品
{
   qDebug()<<"onBtnDel";
       QString ID = this->getCurrentID();
       if(ID.isEmpty())
       {
           QMessageBox::information(this , tr("提示") , tr("请选中一条记录！"));
           return ;
       }

       QMessageBox::StandardButton button = QMessageBox::question(this , tr("提示") ,tr("确定删除这一条记录？"));
       if(button == QMessageBox::Yes)
       {
           //删除操作
           ExecDelSql(ID);
       }
}
void OperationOnDishes::ExecDelSql(QString id)
{
    QString sql;
    sql = QString("DELETE FROM menu "
                  " where menuInChinese = '%9' ").arg(id);

    QSqlQuery query;
    bool ok = query.exec(sql);
    if(ok)
    {
       on_pushButton_6_clicked();//重新加载数据
        QMessageBox::information(this ,tr("提示") , tr("删除成功!"));
    }
    else
    {
        QMessageBox::information(this ,tr("提示") , tr("删除失败!"));
    }

}
void OperationOnDishes::on_pushButton_6_clicked()//刷新数据
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
void OperationOnDishes::clearTableData()//清除
{
    //清除表格
    int rowCount = ui->tableWidget->rowCount();
    for(int r = rowCount-1 ; r >=0 ; r--)
    {
        ui->tableWidget->removeRow(r);
    }
}
 QList<QStringList> OperationOnDishes::selectDataFromBase()
{
    QSqlQuery query("SELECT * FROM menu");

    QList<QStringList> stuInfo;

    while (query.next())
    {
        QStringList rowData ;

        rowData <<query.value(1).toString();
        rowData <<query.value(2).toString();
        rowData <<query.value(4).toString();
        rowData <<query.value(5).toString();
        rowData <<query.value(6).toString();
        rowData <<query.value(7).toString();

        stuInfo.append(rowData);
    }
    return stuInfo;
}
 QString OperationOnDishes::getCurrentID()
 {
     QString ID ;
     int row = ui->tableWidget->currentRow();
     if(row != -1)
     {
         ID =  ui->tableWidget->item(row , 0)->text();
     }
     return ID;
 }

void OperationOnDishes::on_pushButton_4_clicked()//实现模糊查询
{
    QString text =ui->lineEdit->text();
    QString text2=ui->comboBox->currentText();

    QString sql; int nColumn, nRow;
    sql=QString("select * FROM menu WHERE menuInChinese LIKE '%8' AND style='%6'"
                ).arg(text2).arg(text);
QSqlQuery query;
    bool ok=query.exec(sql);
    qDebug()<<sql;
    if(ok)
    {clearTableData();
             if(text2!="默认")
      {  query.exec(QString("select * FROM menu WHERE menuInChinese LIKE '%8%' AND style='%6'"
                           ).arg(text2).arg(text));}
             else query.exec(QString("select * FROM menu WHERE menuInChinese LIKE '%8%'"
                                     ).arg(text));
        query.last();//指向最后一条记录 打印行数等于总行数加一
        nRow = query.at() + 1;
        QSqlRecord rec = query.record();
        nColumn=rec.count();
        //qDebug()<<nColumn;
        ui->tableWidget->setRowCount(nRow-1);
        nColumn = ui->tableWidget->columnCount();//列数等于总列数
        ui->tableWidget->setColumnCount(6);
         query.first();//指向第一条记录

         //设置表头
         ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("菜品名(英文)"));
         ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("菜品名(中文)"));
         ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem("食材"));
         ui->tableWidget->setHorizontalHeaderItem(3,new QTableWidgetItem("价格"));
         ui->tableWidget->setHorizontalHeaderItem(4,new QTableWidgetItem("风格"));
         ui->tableWidget->setHorizontalHeaderItem(5,new QTableWidgetItem("辣度"));

       int j=0;
         while(j<nRow)
         {
         for (int i = 1;i<8; i++)
        if(i<=3) ui->tableWidget->setItem(j, i-1, new QTableWidgetItem(query.value(i).toString()));//把这条记录放在j行i列
         else ui->tableWidget->setItem(j, i-2, new QTableWidgetItem(query.value(i).toString()));//把这条记录放在j行i列
         j++;
         query.next();//指向下一条记录

    }}
    else
           {
               QMessageBox::information(this ,tr("提示") , tr("查询失败!"));
           }

}

void OperationOnDishes::set_job(QString job1)
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
