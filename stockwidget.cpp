#include "stockwidget.h"
#include "ui_stockwidget.h"
#include "checkfoodrest.h"
#include "changefoodamount.h"
#include "check_salary.h"
#include "change_password.h"
#include "ask_for_leave.h"
#include "viewcomment.h"
#include "clock_in_out.h"
#include <QPainter>
#include <QWidget>
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
#include "stufflogin.h"


Stockwidget::Stockwidget(QString name1,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Stockwidget)
{
    ui->setupUi(this);

    name = name1;
    setWindowTitle("仓库管理员主菜单页");

    setWindowIcon(QIcon(":/icon.jpg"));
    setFixedSize(750,427);

}

Stockwidget::~Stockwidget()
{
    delete ui;
}



void Stockwidget::on_pushButton_2_clicked()
{
    changeFoodAmount *change=new changeFoodAmount(name);
    change->set_job("warehouse");
    this->hide();
    change->show();
}
void Stockwidget::paintEvent(QPaintEvent *)
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

//跳转签到/签退界面
void Stockwidget::on_pushButton_6_clicked()
{
            //延时进入界面
            QTimer::singleShot(500,this,[=](){
            //自身隐藏
            this->hide();
            //显示签到/签退界面
            Clock_in_out *clockInOut = new Clock_in_out(name);
            clockInOut->set_job("warehouse");
            clockInOut->setName(name);
            clockInOut->show();


            });

}

//跳转查工资界面
void Stockwidget::on_pushButton_3_clicked()
{
            //延时进入界面
            QTimer::singleShot(500,this,[=](){
            //自身隐藏
            this->hide();
            //显示查工资界面
            Check_Salary *checkSalary = new Check_Salary(name);
            checkSalary->set_job("warehouse");
            checkSalary->setName(name);
            checkSalary->show();

            });

}

//跳转改密码界面
void Stockwidget::on_pushButton_4_clicked()
{
            //延时进入界面
            QTimer::singleShot(500,this,[=](){
            //自身隐藏
            this->hide();
            //显示改密码界面
            Change_Password *changePassword = new Change_Password(name);
            changePassword->set_job("warehouse");
            changePassword->show();

            });

}


//跳转请假界面
void Stockwidget::on_pushButton_clicked()
{
            //延时进入界面
            QTimer::singleShot(500,this,[=](){
            //自身隐藏
            this->hide();
            //显示请假界面
            Ask_for_leave *askForLeave = new Ask_for_leave(name);
            askForLeave->set_job("warehouse");
            askForLeave->setName(name);
            askForLeave->show();

            });

}

void Stockwidget::on_pushButton_7_clicked()
{
    StuffLogin *stuff=new StuffLogin;
    this->hide();
    stuff->show();
}

void Stockwidget::setName(QString name1)
{
    name=name1;
}

//查看评价界面
void Stockwidget::on_pushButton_5_clicked()
{
    //延时进入注册界面
    QTimer::singleShot(100,this,[=](){
    //自身隐藏
    this->hide();
    //显示查看评价界面
    ViewComment *view = new ViewComment(name);
    view->set_job("warehouse");
    view->show();
    });
}
