#include "stufflogin.h"
#include "ui_stufflogin.h"
#include "servant_open.h"
#include "widget1.h"
#include "administratorhomepage.h"
#include <QIcon>
#include "loginchooseidentity.h"
#include <QPainter>
#include <QPushButton>
#include <QTimer>
#include <QMessageBox>
#include <QVector>
#include <QtWidgets/QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>




void StuffLogin::paintEvent(QPaintEvent *event)
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

typedef struct _testInfo //假定数据库存储内容
{
    QString employee_id;
    QString first_name;
    QString last_name;
    QString phone_number;
    QString city;
    QString job_id;
    QString salary;
    QString commission_pct;
    QString monthly_commission_pct;
    QString hiredate;
    QString ID;
    QString password;

}testInfo;

StuffLogin::StuffLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StuffLogin)
{
    ui->setupUi(this);
    //配置主场景

    //设置固定大小
    setFixedSize(750,427);

    //设置图标

    setWindowIcon(QIcon(":/icon.jpg"));
    //设置标题
    setWindowTitle("员工登录");

    set(ui->confirm);
    set(ui->return_2);




    connect(ui->return_2,&QPushButton::clicked,[=](){

        //延时进入注册界面
        QTimer::singleShot(100,this,[=](){
        //自身隐藏
        this->hide();
        //显示注册界面
        LoginChooseIdentity *loginChooseIdentity = new LoginChooseIdentity();
        loginChooseIdentity->show();

        });
    });

    connect(ui->confirm,&QPushButton::clicked,[=](){
        //检测是否输入id
        bool AccountIsFind = false;
        bool PasswordIsFind = false;
        QString job;
        QString fn;
        if(ui->cinAccount_id->isModified()==false)
            QMessageBox::critical(this,"错误","请输入你的账号 ID");
        //检查密码输否输入
            else if(ui->cinPassword->isModified()==false)
            {
                QTimer::singleShot(100,this,[=](){
                QMessageBox::critical(this,"错误","请输入你的密码");
                });
            }
        else
        {

        //检测账号是否有被注册
            QSqlDatabase employee = QSqlDatabase::addDatabase("QODBC");
                QString dsn = QString::fromLocal8Bit("restaurant");//你配置的Data Source
                employee.setHostName("192.168.56.102");//你的IP地址
                employee.setDatabaseName(dsn);
                employee.setUserName("my_root"); //用户名
                employee.setPassword("my_root@123");//密码
                employee.setPort(26000); //opengauss端口号为26000

            if(!employee.open()) qDebug()<<"hello";
            if(employee.open()){
                QSqlQuery sql_query(employee);
                QString ID = ui->cinAccount_id->text();
                QString password = ui->cinPassword->text();

                \
                sql_query.exec("select * from employee");
                while(sql_query.next())
                {
                    QString x = sql_query.value(10).toString();
                    QString y = sql_query.value(11).toString();
                    if(x==ID)
                    {
                        AccountIsFind = true;
                        if(y==password)
                        {PasswordIsFind = true;
                            job = sql_query.value(5).toString();
                            fn = sql_query.value(1).toString();
//                            qDebug()<<fn;
                        break;


                    }
                }
            }


        //如果账户未被创建
        //消息对话框 错误对话框
        if(AccountIsFind==false) QMessageBox::critical(this,"错误","你的账号尚未注册");

        //如果账户被创建
        if(AccountIsFind==true){

        //检测密码是否正确

        if(PasswordIsFind==false)
        {
            QTimer::singleShot(100,this,[=](){
            QMessageBox::critical(this,"错误","错误的密码");
            });
        }

            else
            {

            //跳转窗口
//            QMessageBox::information(this,"Welcome to work",job);
            if(job=="Manager")
            {
                //延时进入注册界面
                QTimer::singleShot(100,this,[=](){
                //自身隐藏
                this->hide();
                //显示注册界面
                administratorHomePage *aph = new administratorHomePage(fn);

                aph->show();

                });

            }

            if(job=="servant")
            {
                //延时进入注册界面
                QTimer::singleShot(100,this,[=](){
                //自身隐藏
                this->hide();
                //显示注册界面
                Servant_open *aph = new Servant_open(fn);

                aph->show();

                });
            }

            if(job=="chef")
            {
                //延时进入注册界面
                QTimer::singleShot(100,this,[=](){
                //自身隐藏
                this->hide();
                //显示注册界面
                Widget1 *aph = new Widget1(fn);

                aph->show();

                });
            }

        }

            }
        }
            }
        });
}


StuffLogin::~StuffLogin()
{
    delete ui;
}

void StuffLogin::set(QPushButton* m)
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
