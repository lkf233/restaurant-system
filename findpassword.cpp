#include "findpassword.h"
#include "ui_findpassword.h"
#include <QIcon>
#include <QTimer>
#include <QPainter>
#include "customerlogin.h"
#include <QPushButton>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

void FindPassword::paintEvent(QPaintEvent *event)
{
    //创建画家，制定绘画设备
    QPainter painter(this);
    //创建QPixmap对象
    QPixmap pix;
    //加载图片
    setWindowTitle("找回密码");

    setWindowIcon(QIcon(":/icon.jpg"));
    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);


}

FindPassword::FindPassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindPassword)
{
    ui->setupUi(this);
    //配置主场景

    //设置固定大小
    setFixedSize(750,427);

    //设置图标
    setWindowIcon(QIcon(":/t.jpg"));

    //设置标题
    setWindowTitle("Find Password");

    set(ui->confirm);
    set(ui->return_2);

    connect(ui->return_2,&QPushButton::clicked,[=](){

        //延时进入注册界面
        QTimer::singleShot(100,this,[=](){
        //自身隐藏
        this->hide();
        //显示注册界面
        CustomerLogin *customerLogin = new CustomerLogin();
        customerLogin->show();

        });

    });


    connect(ui->confirm,&QPushButton::clicked,[=](){
        bool AccountIsFind = false;
                bool PasswordIsFind = false;
                QString password;
        //检测是否输入id
        if(ui->cinaccount_id->isModified()==false)
            QMessageBox::critical(this,"错误","请输入一个有效的账号ID");
        else
        {

        //检测账号是否有被注册

        //如果账户未被创建
        //消息对话框 错误对话框
        //QMessageBox::critical(this,"Error","Your Account hasn't been Register");


        //如果账户被创建

        //检查生日是否输入
            if(ui->cinbirthday->isModified()==false)
            {
                QTimer::singleShot(100,this,[=](){
                QMessageBox::critical(this,"错误","请输入你的生日");
                });
            }

        //检测生日是否正确
            else{
                //检测账号是否有被注册
                            QSqlDatabase vip;
                            if(QSqlDatabase::contains("qt_sql_default_connection"))
                                vip = QSqlDatabase::database("qt_sql_default_connection");
                            else
                                vip = QSqlDatabase::addDatabase("QSQLITE");
                            vip.setDatabaseName("test.db");
                            if(vip.open()){
                                QSqlQuery sql_query(vip);
                                QString ID = ui->cinaccount_id->text();
                                QString birthday = ui->cinbirthday->text();

                                \
                                sql_query.exec("select * from vip");
                                while(sql_query.next())
                                {
                                    QString x = sql_query.value(0).toString();
                                    QString y = sql_query.value(4).toString();
                                    if(x==ID)
                                    {
                                        AccountIsFind = true;
                                        if(y==birthday)
                                        {PasswordIsFind = true;
                                         password = sql_query.value(3).toString();
                                        break;


                                    }
                                }
                            }
                                vip.close();
                                //如果账户未被创建
                                        //消息对话框 错误对话框
                                        if(AccountIsFind==false) QMessageBox::critical(this,"错误","你的账号尚未注册");

                                        //如果账户被创建
                                        if(AccountIsFind==true){

                                        if(PasswordIsFind==false)
                                        {
                                            QTimer::singleShot(100,this,[=](){
                                            QMessageBox::critical(this,"错误","错误的生日");
                                            });
                                        }

                                            else
                                            {

                                            //跳转窗口
                                            QMessageBox::information(this,"密码","你的密码是: "+password);

                                        }

                                            }
                                        }
                                            }
                                        }

});
}

FindPassword::~FindPassword()
{
    delete ui;


}

void FindPassword::set(QPushButton* m)
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
