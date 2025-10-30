#include "loginchooseidentity.h"
#include "ui_loginchooseidentity.h"
#include <QPainter>
#include <QIcon>
#include "customerlogin.h"
#include "stufflogin.h"
#include <QTimer>
#include "login.h"
#include "button.h"

LoginChooseIdentity::LoginChooseIdentity(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginChooseIdentity)
{
    ui->setupUi(this);
    //配置主场景

    set(ui->return_2);

    //设置固定大小
    setFixedSize(750,427);

    //设置图标

    setWindowIcon(QIcon(":/icon.jpg"));
    //设置标题
    setWindowTitle("身份识别");

    shoppingBtn();
    shoppingBtn2();




    connect(ui->return_2,&QPushButton::clicked,[=](){

        //延时进入注册界面
        QTimer::singleShot(100,this,[=](){
        //自身隐藏
        this->hide();
        //显示注册界面
        Login *login = new Login();
        login->show();

        });

    });
}

LoginChooseIdentity::~LoginChooseIdentity()
{
    delete ui;
}

void LoginChooseIdentity::paintEvent(QPaintEvent *event)
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

void LoginChooseIdentity::set(QPushButton* m)
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

void LoginChooseIdentity::shoppingBtn()
{
    button *shoppingButton=new button(":/s.JPG");

    shoppingButton->setParent(this);
    shoppingButton->move(460,100);

    connect(shoppingButton,&button::clicked,[=](){
        //弹起特效
        shoppingButton->zoom1();
        shoppingButton->zoom2();
        //进入购物车场景
        //延时进入注册界面
        QTimer::singleShot(100,this,[=](){
        //自身隐藏
        this->hide();
        //显示注册界面
        StuffLogin *stuffLogin = new StuffLogin();
        stuffLogin->show();

        });

        });


}

void LoginChooseIdentity::shoppingBtn2()
{
    button *shoppingButton=new button(":/c.JPG");
    shoppingButton->setParent(this);
    shoppingButton->move(160,100);


    connect(shoppingButton,&button::clicked,[=](){
        //弹起特效
        shoppingButton->zoom1();
        shoppingButton->zoom2();
        //进入购物车场景
        //延时进入注册界面
        QTimer::singleShot(100,this,[=](){
        //自身隐藏
        this->hide();
        //显示注册界面
            CustomerLogin *stuffLogin = new CustomerLogin();
            stuffLogin->show();

        });

        });


}
