#include "servant_open.h"
#include "ui_servant_open.h"
#include "check_table.h"
#include "check_salary.h"
#include "change_password.h"
#include "ask_for_leave.h"
#include "menuscene.h"
#include "viewcomment.h"
#include "clock_in_out.h"
#include "stufflogin.h"
#include <QPainter>
#include <QWidget>
#include <QApplication>
#include <QTimer>
#include <QMessageBox>

Servant_open::Servant_open(QString name1,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Servant_open)
{
    ui->setupUi(this);
    QFont ft;
    name = name1;
    ft.setPointSize(12);//字号
    setBtn();
    ui->pushButton->setFont(ft);
    ui->pushButton_2->setFont(ft);
    ui->pushButton_3->setFont(ft);
    ui->pushButton_4->setFont(ft);
    ui->pushButton_5->setFont(ft);
    ui->pushButton_6->setFont(ft);
    ui->pushButton_7->setFont(ft);
    ui->pushButton_8->setFont(ft);

    setWindowTitle("服务员主菜单页");

    setWindowIcon(QIcon(":/icon.jpg"));

    connect(ui->pushButton,&QPushButton::clicked,[=](){

        //延时进入注册界面
        QTimer::singleShot(100,this,[=](){
        //自身隐藏
        this->hide();
        //显示点菜界面
        MenuScene *menu = new MenuScene(name);
        menu->set_job("servant");
        menu->show();

        });

    });

}

Servant_open::~Servant_open()
{
    delete ui;
}

void Servant_open::paintEvent(QPaintEvent *)
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

//跳转查桌界面
void Servant_open::on_pushButton_2_clicked()
{
            //延时进入界面
            QTimer::singleShot(200,this,[=](){
            //自身隐藏
            this->hide();
            //显示查桌界面
            check_table *checkTable = new check_table(name);
            checkTable->set_job("servant");
            checkTable->show();

            });

}

//跳转查看评价界面
void Servant_open::on_pushButton_3_clicked()
{

            //延时进入界面
            QTimer::singleShot(200,this,[=](){
            //自身隐藏
            this->hide();
            //显示查看评价界面
            ViewComment *registerChooseIdentity = new ViewComment(name);
            registerChooseIdentity->set_job("servant");
            registerChooseIdentity->show();
            });

}

//跳转查工资界面
void Servant_open::on_pushButton_4_clicked()
{
            //延时进入界面
            QTimer::singleShot(500,this,[=](){
            //自身隐藏
            this->hide();
            //显示查工资界面
            Check_Salary *checkSalary = new Check_Salary(name);
            checkSalary->set_job("servant");
            checkSalary->setName(name);
            checkSalary->show();

            });

}

//跳转请假界面
void Servant_open::on_pushButton_5_clicked()
{
            //延时进入界面
            QTimer::singleShot(500,this,[=](){
            //自身隐藏
            this->hide();
            //显示请假界面
            Ask_for_leave *askForLeave = new Ask_for_leave(name);
            askForLeave->set_job("servant");
            //askForLeave->setName(name);
            askForLeave->show();

            });

}

//跳转改密码界面
void Servant_open::on_pushButton_6_clicked()
{

            //延时进入界面
            QTimer::singleShot(500,this,[=](){
            //自身隐藏
            this->hide();
            //显示改密码界面
            Change_Password *changePassword = new Change_Password(name);
            changePassword->set_job("servant");
            changePassword->show();

            });

}

//跳转签到/签退界面
void Servant_open::on_pushButton_7_clicked()
{
            //延时进入界面
            QTimer::singleShot(500,this,[=](){
            //自身隐藏
            this->hide();
            //显示签到/签退界面
            Clock_in_out *clockInOut = new Clock_in_out(name);
            clockInOut->set_job("servant");
            clockInOut->setName(name);
            clockInOut->show();


            });

}

//回到员工登录界面
void Servant_open::on_pushButton_8_clicked()
{

            //延时进入界面
            QTimer::singleShot(500,this,[=](){
            //自身隐藏
            this->hide();
            //回到员工登录界面
            StuffLogin *stuffLogin = new StuffLogin();
            stuffLogin->show();

            });

}

//接收名字
void Servant_open::setName(QString a)
{
    name = a;
}
void Servant_open::setBtn(){

    ui->pushButton->setStyleSheet(
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
ui->pushButton_2->setStyleSheet(
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
ui->pushButton_3->setStyleSheet(
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
ui->pushButton_4->setStyleSheet(
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
ui->pushButton_5->setStyleSheet(
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
ui->pushButton_6->setStyleSheet(
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
ui->pushButton_7->setStyleSheet(
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
ui->pushButton_8->setStyleSheet(
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
