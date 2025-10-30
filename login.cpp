#include "login.h"
#include "ui_login.h"
#include <QTimer>
#include "register.h"
#include "administratorhomepage.h"
#include "loginchooseidentity.h"
#include <QMessageBox>
#include <QIcon>
#include <QPainter>
#include "registerchooseidentity.h"


void Login::paintEvent(QPaintEvent *event)
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

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    //配置主场景

    //设置固定大小
    setFixedSize(750,427);

    //设置图标

    setWindowIcon(QIcon(":/icon.jpg"));
    //设置标题
    setWindowTitle("餐厅管理系统");

    set(ui->register_2);
    set(ui->login);

    //设置图片
    ui->picture->setIcon(QIcon(":/a.JPG"));
    ui->picture->setIconSize(this->size());

    connect(ui->picture,&QPushButton::clicked,[=](){

        QMessageBox::information(this,"Hi!","欢迎光临~");


    });


    connect(ui->register_2,&QPushButton::clicked,[=](){

        //延时进入注册界面
        QTimer::singleShot(100,this,[=](){
        //自身隐藏
        this->hide();
        //显示注册界面
        RegisterChooseIdentity *registerChooseIdentity = new RegisterChooseIdentity();
        registerChooseIdentity->show();
//            administratorHomePage *ahp = new administratorHomePage();
//            ahp->show();

        });

    });

    connect(ui->login,&QPushButton::clicked,[=](){

        //延时进入注册界面
        QTimer::singleShot(100,this,[=](){
        //自身隐藏
        this->hide();
        //显示注册界面
        LoginChooseIdentity *loginchooseidentity = new LoginChooseIdentity();
        loginchooseidentity->show();

        });

    });




}

Login::~Login()
{
    delete ui;
}

void Login::set(QPushButton* m)
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
