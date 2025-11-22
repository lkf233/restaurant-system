#include "administratorhomepage.h"
#include "ui_administratorhomepage.h"
#include "operationondishes.h"
#include "menuscene.h"
#include "selectway.h"
#include "menuscene.h"
#include "stufflogin.h"
#include "customerlogin.h"
#include "checkleave.h"
#include "checkcomments_.h"
#include "check_salary.h"
#include "change_password.h"
#include "ask_for_leave.h"
#include "clock_in_out.h"
#include "check_table.h"
#include "changefoodamount.h"
#include <QIcon>
#include <QTimer>
#include <QPainter>
#include <QPushButton>
#include <QMessageBox>

void administratorHomePage::paintEvent(QPaintEvent *event)
{
    //创建画家，制定绘画设备
    QPainter painter(this);
    //创建QPixmap对象
    QPixmap pix;
    //加载图片
    pix.load(":/b.jpg");
    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

}

administratorHomePage::administratorHomePage(QString name1,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::administratorHomePage)
{
    ui->setupUi(this);

    name=name1;

    set(ui->pushButton);
    set(ui->pushButton_2);
    set(ui->pushButton_3);
    set(ui->pushButton_4);
    set(ui->pushButton_5);
    set(ui->pushButton_6);
    set(ui->pushButton_7);
    set(ui->pushButton_8);
    set(ui->pushButton_9);
    set(ui->pushButton_10);
    set(ui->pushButton_11);


    //配置主场景

    //设置固定大小
    setFixedSize(750,427);

    //设置图标  
    QIcon q1(":/icon.jpg");
    setWindowIcon(QIcon(":/icon.jpg"));

    //设置标题
    setWindowTitle("管理员主菜单页");

    qDebug()<<name;



    connect(ui->pushButton_4,&QPushButton::clicked,[=](){

        //延时进入请假界面
        QTimer::singleShot(100,this,[=](){
        //自身隐藏
        this->hide();
        //显示请假界面
        CheckLeave *checkleave = new CheckLeave(name);
        checkleave->show();

        });

    });


    connect(ui->pushButton_5,&QPushButton::clicked,[=](){

        //延时进入请假界面
        QTimer::singleShot(100,this,[=](){
        //自身隐藏
        this->hide();
        //显示查看销量界面
        SelectWay *checkleave = new SelectWay(name);
        checkleave->set_job("manager");
        checkleave->show();

        });

    });

    connect(ui->pushButton_7,&QPushButton::clicked,[=](){

        //延时进入请假界面
        QTimer::singleShot(100,this,[=](){
        //自身隐藏
        this->hide();
        //显示请假界面
        StuffLogin *checkleave = new StuffLogin();
        checkleave->show();

        });

    });
    connect(ui->pushButton_2,&QPushButton::clicked,[=](){

        //延时进入点菜界面
        QTimer::singleShot(100,this,[=](){
        //自身隐藏
        this->hide();
        //显示点菜界面
        OperationOnDishes *checkleave = new OperationOnDishes(name);
        checkleave->set_job("manager");
        checkleave->show();

        });

    });


    connect(ui->pushButton_8,&QPushButton::clicked,[=](){

        //延时进入评论界面
        QTimer::singleShot(100,this,[=](){
        //自身隐藏
        this->hide();
        //显示评论界面
        CheckComments_ *checkcomments_ = new CheckComments_(name);
        checkcomments_->show();

        });

    });

}

administratorHomePage::~administratorHomePage()
{
    delete ui;
}

void administratorHomePage::set(QPushButton* m)
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

//跳转查工资界面
void administratorHomePage::on_pushButton_3_clicked()
{
            //延时进入界面
            QTimer::singleShot(500,this,[=](){
            //自身隐藏
            this->hide();
            //显示查工资界面
            Check_Salary *checkSalary = new Check_Salary(name);
            checkSalary->set_job("manager");
            checkSalary->setName(name);
            checkSalary->show();

            });

}

//跳转改密码界面
void administratorHomePage::on_pushButton_6_clicked()
{
            //延时进入界面
            QTimer::singleShot(500,this,[=](){
            //自身隐藏
            this->hide();
            //显示改密码界面
            Change_Password *changePassword = new Change_Password(name);
            changePassword->set_job("manager");
            changePassword->show();

            });

}

//跳转签到/签退界面
void administratorHomePage::on_pushButton_9_clicked()
{
            //延时进入界面
            QTimer::singleShot(500,this,[=](){
            //自身隐藏
            this->hide();
            //显示签到/签退界面
            Clock_in_out *clockInOut = new Clock_in_out(name);
            clockInOut->set_job("manager");

            clockInOut->show();


            });

}

//跳转查桌界面
void administratorHomePage::on_pushButton_10_clicked()
{
            //延时进入界面
            QTimer::singleShot(200,this,[=](){
            //自身隐藏
            this->hide();
            //显示查桌界面
            check_table *checkTable = new check_table(name);
            checkTable->set_job("manager");
            checkTable->show();

            });

}

void administratorHomePage::setName(QString name1)
{
    name=name1;
}

//进入change food amount界面
void administratorHomePage::on_pushButton_11_clicked()
{
    //延时进入界面
    QTimer::singleShot(200,this,[=](){
    //自身隐藏
    this->hide();
    //显示change food amount界面
    changeFoodAmount *changeFood = new changeFoodAmount(name);
    changeFood->set_job("manager");
    changeFood->show();


    });
}

void administratorHomePage::on_pushButton_clicked()
{
    //延时进入点菜界面
    QTimer::singleShot(100,this,[=](){
    //自身隐藏
    this->hide();
    //显示点菜界面
    MenuScene *menu = new MenuScene(name);
    menu->set_job("manager");
    menu->show();
    });
}
