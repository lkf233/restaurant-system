#include "widget1.h"
#include "operationondishes.h"
#include "ui_widget1.h"
#include <QPainter>
#include "viewcomment.h"
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
#include "checksaleamount.h"
#include "selectway.h"
#include "check_salary.h"
#include "change_password.h"
#include "clock_in_out.h"
#include "stufflogin.h"

Widget1::Widget1(QString name1,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget1)
{
    ui->setupUi(this);
    //设置固定大小
    setFixedSize(750,450);
    set(ui->pushButton);
    set(ui->pushButton_2);
    set(ui->pushButton_3);
    set(ui->pushButton_4);
    set(ui->pushButton_5);
    set(ui->pushButton_6);
    set(ui->pushButton_7);



        name=name1;

        //设置图标

        setWindowIcon(QIcon(":/icon.jpg"));
        //设置标题
        setWindowTitle("厨师主菜单页");

}

void Widget1::set(QPushButton* m)
{
    m->setStyleSheet(
                        //正常状态样式
                        "QPushButton{"
                        "background-color:rgba(100,225,100,30);"//背景色（也可以设置图片）
                        "border-style:outset;"                  //边框样式（inset/outset）
                        "border-width:4px;"                     //边框宽度像素
                        "border-radius:10px;"                   //边框圆角半径像素
                        "border-color:rgba(255,255,255,30);"    //边框颜色
                        "padding:6px;"                          //填衬
                        "}"
                        //鼠标按下样式
                        "QPushButton:pressed{"
                        "background-color:rgba(100,255,100,200);"
                        "border-color:rgba(255,255,255,30);"
                        "border-style:inset;"
                        "color:rgba(0,0,0,100);"
                        "}"
                        //鼠标悬停样式
                        "QPushButton:hover{"
                        "background-color:rgba(100,255,100,100);"
                        "border-color:rgba(255,255,255,200);"
                        "color:rgba(0,0,0,200);"
                        "}");
}

void Widget1::paintEvent(QPaintEvent *)
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

Widget1::~Widget1()
{
    delete ui;
}



void Widget1::on_pushButton_pressed()
{
   OperationOnDishes *Operation=new OperationOnDishes(name);
  this->hide();
   Operation->set_job("chef");
  Operation->show();//operation is a object of the operationondishes.

}

void Widget1::on_pushButton_3_clicked()
{
SelectWay *select=new SelectWay(name);
this->hide();
select->set_job("chef");
select->show();
}

//跳转到查工资界面
void Widget1::on_pushButton_2_clicked()
{
            //延时进入界面
            QTimer::singleShot(500,this,[=](){
            //自身隐藏
            this->hide();
            //显示查工资界面
            Check_Salary *checkSalary = new Check_Salary(name);
            checkSalary->set_job("chef");
            checkSalary->setName(name);
            checkSalary->show();

            });

}

//跳转改密码界面
void Widget1::on_pushButton_4_clicked()
{
            //延时进入界面
            QTimer::singleShot(500,this,[=](){
            //自身隐藏
            this->hide();
            //显示改密码界面
            Change_Password *changePassword = new Change_Password(name);
            changePassword->set_job("chef");
            changePassword->show();

            });

}

//跳转签到/签退界面
void Widget1::on_pushButton_6_clicked()
{
            //延时进入界面
            QTimer::singleShot(500,this,[=](){
            //自身隐藏
            this->hide();
            //显示签到/签退界面
            Clock_in_out *clockInOut = new Clock_in_out(name);
            clockInOut->set_job("chef");
            clockInOut->setName(name);
            clockInOut->show();
            });

}

void Widget1::on_pushButton_7_clicked()
{
    StuffLogin *stuff=new StuffLogin;
    this->close();
    stuff->show();
}

void Widget1::setName(QString name1)
{
    name=name1;
}

//查看评论
void Widget1::on_pushButton_5_clicked()
{
    //延时进入注册界面
    QTimer::singleShot(100,this,[=](){
    //自身隐藏
    this->hide();
    //显示查看评论界面
    ViewComment *view = new ViewComment(name);
    view->set_job("chef");
    view->show();
    });

}
