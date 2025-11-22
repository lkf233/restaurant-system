#include "register.h"
#include "ui_register.h"
#include <QPainter>
#include <QIcon>
#include <QMessageBox>
#include <QTimer>
#include "login.h"
#include <QPushButton>
#include <QVector>
#include <QtWidgets/QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include "registerchooseidentity.h"
#include <QSqlError>

void Register::paintEvent(QPaintEvent *event)
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

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);

    set(ui->confirm);
    set(ui->return_2);

    //配置主场景

    //设置固定大小
    setFixedSize(750,427);

    //设置图标

    setWindowIcon(QIcon(":/icon.jpg"));
    //设置标题
    setWindowTitle("注册你的账户");



    connect(ui->return_2,&QPushButton::clicked,[=](){

        //延时进入注册界面
        QTimer::singleShot(100,this,[=](){
        //自身隐藏
        this->hide();
        //显示注册界面
        RegisterChooseIdentity *registerChooseIdentity = new RegisterChooseIdentity();
        registerChooseIdentity->show();



        });

    });

    connect(ui->confirm,&QPushButton::clicked,[=](){
        //检测是否输入id
        bool AccountIsFind = false;
        QString job;
        if(ui->cinaccount_id->isModified()==false)
            QMessageBox::critical(this,"错误","请输入一个有效的账号ID");
        //检查密码输否输入
            else if(ui->cinpassword->isModified()==false)
            {
                QTimer::singleShot(100,this,[=](){
                QMessageBox::critical(this,"错误","请输入你的密码");
                });
            }
        //检查生日是否输入
        else if(ui->cinBirthday->isModified()==false)
        {
            QTimer::singleShot(100,this,[=](){
            QMessageBox::critical(this,"错误","请输入你的生日");
            });
        }
        //检查首名字是否输入
        else if(ui->cinFirstName->isModified()==false)
        {
            QTimer::singleShot(100,this,[=](){
            QMessageBox::critical(this,"错误","请输入你的姓");
            });
        }
        //检查尾名字是否输入
        else if(ui->cinLastName->isModified()==false)
        {
            QTimer::singleShot(100,this,[=](){
            QMessageBox::critical(this,"错误","请输入你的名");
            });
        }
        else
        {

        //检测账号是否有被注册
            QSqlDatabase vip;
            if(QSqlDatabase::contains("qt_sql_default_connection"))
                vip = QSqlDatabase::database("qt_sql_default_connection");
            else
                vip = QSqlDatabase::addDatabase("QSQLITE");

            vip.setDatabaseName("test.db");
            if(vip.open()){
                QSqlQuery sql_query(vip);
                QString ID1 = ui->cinaccount_id->text();
                QString password1 = ui->cinpassword->text();
                QString first_name1 = ui->cinFirstName->text();
                QString last_name1 = ui->cinLastName->text();
                QString birthday1 = ui->cinBirthday->text();

                sql_query.exec("select * from vip");
                while(sql_query.next())
                {
                    QString x = sql_query.value(0).toString();

                    if(x==ID1)
                    {
                        AccountIsFind = true;
                        break;


                    }
                }

                //如果账户已被创建
                //消息对话框 错误对话框
                if(AccountIsFind==true) QMessageBox::critical(this,"错误","你的账号已经被注册");

                //如果账户未被创建
                else{
                    sql_query.clear();
                    sql_query.prepare("INSERT INTO vip (vip_id,first_name,last_name,password,birthday) "
                                          "VALUES (? ,? ,? ,? ,? )");
                            sql_query.addBindValue(ID1);
                            sql_query.addBindValue(first_name1);
                            sql_query.addBindValue(last_name1);
                            sql_query.addBindValue(password1);
                            sql_query.addBindValue(birthday1);
                            sql_query.exec();

                    QMessageBox::information(this,"ok","你的账号已被成功创建！");

                }

                    }


            }



        });




}

Register::~Register()
{
    delete ui;
}

void Register::set(QPushButton* m)
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
