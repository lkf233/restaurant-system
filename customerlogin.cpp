#include "customerlogin.h"
#include "ui_customerlogin.h"
#include "menuscene.h"
#include "commentscene.h"
#include"commentscene.h"
#include <QIcon>
#include <QTimer>
#include "loginchooseidentity.h"
#include <QPainter>
#include "findpassword.h"
#include <QMessageBox>
#include <QVector>
#include <QtWidgets/QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>


void CustomerLogin::paintEvent(QPaintEvent *event)
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

CustomerLogin::CustomerLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomerLogin)
{
    ui->setupUi(this);
    //配置主场景

    set(ui->confirm);
    set(ui->return_2);
    set(ui->findPassword);

    //设置固定大小
    setFixedSize(750,427);

    //设置图标

    setWindowIcon(QIcon(":/icon.jpg"));

    //设置标题
    setWindowTitle("顾客登录");


//    connect(this,SIGNAL(signalString(QString),cs,SLOT(setComment(QString))));
    connect(ui->return_2,&QPushButton::clicked,[=](){

        //延时进入身份选择界面
        QTimer::singleShot(100,this,[=](){
        //自身隐藏
        this->hide();
        //显示身份选择界面
        LoginChooseIdentity *loginChooseIdentity = new LoginChooseIdentity();
        loginChooseIdentity->show();

        });
    });

    connect(ui->findPassword,&QPushButton::clicked,[=](){

        //延时进入找回密码界面
        QTimer::singleShot(100,this,[=](){
        //自身隐藏
        this->hide();
        //显示找回密码界面
        FindPassword *findpassword = new FindPassword();
        findpassword->show();

        });
    });

    connect(ui->confirm,&QPushButton::clicked,[=](){

        QString all;
        //检测是否输入id
        bool AccountIsFind = false;
        bool PasswordIsFind = false;
        if(ui->cinaccount_id->isModified()==false)
            QMessageBox::critical(this,"Error","Please enter a valid Account ID");
        else
        {

        //检测账号是否有被注册
            QSqlDatabase vip = QSqlDatabase::addDatabase("QODBC");
                  QString dsn = QString::fromLocal8Bit("restaurant");//你配置的Data Source
                  vip.setHostName("192.168.56.102");//你的IP地址
                  vip.setDatabaseName(dsn);
                  vip.setUserName("my_root"); //用户名
                  vip.setPassword("my_root@123");//密码
                  vip.setPort(26000); //opengauss端口号为26000

            if(vip.open()){
                QSqlQuery sql_query(vip);
                QString ID = ui->cinaccount_id->text();
                QString password = ui->cinpassword->text();

                \
                sql_query.exec("select * from vip");
                while(sql_query.next())
                {
                    QString x = sql_query.value(0).toString();
                    QString y = sql_query.value(3).toString();
                    if(x==ID)
                    {
                        AccountIsFind = true;
                        if(y==password)
                        {PasswordIsFind = true;
                            QString fn = sql_query.value(1).toString();

                            all = fn;
//                            qDebug()<<all;

                       //   connect(this,SIGNAL(sendName(QString)),cm,SLOT(getName(QString)));
                         // emit sendName(all);
                            break;


                    }
                }
            }
                vip.close();


        //如果账户未被创建
        //消息对话框 错误对话框
        if(AccountIsFind==false) QMessageBox::critical(this,"Error","Your Account hasn't been Register");

        //如果账户被创建
        if(AccountIsFind==true){

        //检查密码输否输入
            if(ui->cinpassword->isModified()==false)
            {
                QTimer::singleShot(100,this,[=](){
                QMessageBox::critical(this,"Error","Please enter your password");
                });
            }

        //检测密码是否正确
            else{
        if(PasswordIsFind==false)
        {
            QTimer::singleShot(100,this,[=](){
            QMessageBox::critical(this,"Error","Wrong password");
            });
        }

            else
            {

            //延时进入注册界面
            QTimer::singleShot(100,this,[=](){
            //自身隐藏
            this->hide();
            //显示注册界面
            MenuScene *aph = new MenuScene(all);
            aph->set_job("customer");
            aph->show();

            });

        }

            }
        }
            }
        }



});



}

    CustomerLogin::~CustomerLogin()
    {
        delete ui;
    }

    void CustomerLogin::set(QPushButton* m)
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

