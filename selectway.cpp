#include "selectway.h"
#include "ui_selectway.h"
#include "checksaleamount.h"
#include "checksaleamount_day.h"
#include "widget1.h"
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
SelectWay::SelectWay(QString name1,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectWay)
{
    name = name1;
    ui->setupUi(this);
    setWindowTitle("选择职位");

    setWindowIcon(QIcon(":/icon.jpg"));
      setFixedSize(400,300);
}

SelectWay::~SelectWay()
{
    delete ui;
}
void SelectWay::paintEvent(QPaintEvent *)
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

void SelectWay::set_job(QString job1)
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

}

void SelectWay::on_pushButton_clicked()//按月查询
{
    checkSaleAmount *check=new checkSaleAmount(name);
    this->hide();
    QString jobStr;
    if(job == 1)
        jobStr = "servant";
    else if(job == 2)
        jobStr = "chef";
    else if(job == 4)
        jobStr = "manager";
    else if(job == 5)
        jobStr = "customer";
    check->set_job(jobStr);
    check->show();
}

void SelectWay::on_pushButton_2_clicked()//按日查询
{
    checkSaleAmount_day *check=new checkSaleAmount_day(name);
    QString jobStr;
    if(job == 1)
        jobStr = "servant";
    else if(job == 2)
        jobStr = "chef";
    else if(job == 3)
        jobStr = "warehouse";
    else if(job == 4)
        jobStr = "manager";
    else if(job == 5)
        jobStr = "customer";
    check->set_job(jobStr);
    this->hide();
    check->show();
}

//返回原岗位界面
void SelectWay::on_pushButton_3_clicked()
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
