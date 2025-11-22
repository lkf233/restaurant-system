#include "registerstuff.h"
#include "ui_registerstuff.h"
#include "registerchooseidentity.h"
#include <QPainter>
#include <QIcon>
#include <QMessageBox>
#include <QTimer>
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
#include <QDateEdit>
#include <QComboBox>

void RegisterStuff::paintEvent(QPaintEvent *event)
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

RegisterStuff::RegisterStuff(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterStuff)
{
    ui->setupUi(this);

    //配置主场景

    set(ui->confirm);
    set(ui->return_2);

    //设置固定大小
    setFixedSize(750,427);

    //设置图标

    setWindowIcon(QIcon(":/icon.jpg"));
    //设置标题
    setWindowTitle("注册你的账号");

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
        QString first_name1;
        QString job;
        if(ui->firstName->isModified()==false)
            QMessageBox::critical(this,"错误","请输入你的姓");
        //检查密码输否输入
            else if(ui->lastName->isModified()==false)
            {
                QTimer::singleShot(100,this,[=](){
                QMessageBox::critical(this,"错误","请输入你的名");
                });
            }
        //检查生日是否输入
        else if(ui->phoneNumber->isModified()==false)
        {
            QTimer::singleShot(100,this,[=](){
            QMessageBox::critical(this,"错误","请输入你的电话号号码");
            });
        }
        //检查首名字是否输入
        else if(ui->City->isModified()==false)
        {
            QTimer::singleShot(100,this,[=](){
            QMessageBox::critical(this,"错误","请输入你的城市");
            });
        }
        //检查尾名字是否输入
        else if(ui->iD->isModified()==false)
        {
            QTimer::singleShot(100,this,[=](){
            QMessageBox::critical(this,"错误","请输入你的ID");
            });
        }
        else if(ui->password->isModified()==false)
        {
            QTimer::singleShot(100,this,[=](){
            QMessageBox::critical(this,"错误","请输入你的密码");
            });
        }
        else if(ui->job->currentIndex()==0)
        {
            QTimer::singleShot(100,this,[=](){
            QMessageBox::critical(this,"错误","请选择你的职位");
            });
        }
        else
        {

        //检测账号是否有被注册
            QSqlDatabase employee;
            if(QSqlDatabase::contains("qt_sql_default_connection"))
                employee = QSqlDatabase::database("qt_sql_default_connection");
            else
                employee = QSqlDatabase::addDatabase("QSQLITE");

            employee.setDatabaseName("test.db");
            if(employee.open()){
                QSqlQuery sql_query(employee);

                QString ID1 = ui->iD->text();
                QString password1 = ui->password->text();
                 first_name1 = ui->firstName->text();
                QString last_name1 = ui->lastName->text();
                QString phone_numebr = ui->phoneNumber->text();
                QString city = ui->City->text();
                QDate hire_daate = ui->dateEdit->date();
                QString job_ = ui->job->currentText();
                int number = 0;
                sql_query.exec("select * from employee");
                while(sql_query.next())
                {
                    QString x = sql_query.value(10).toString();

                    if(x==ID1)
                    {
                        AccountIsFind = true;

                    }
                    number++;
                }

                //如果账户已被创建
                //消息对话框 错误对话框
                if(AccountIsFind==true) QMessageBox::critical(this,"错误","你的ID已被注册！");

                //如果账户未被创建
                else{
                    int salary1;
                    double cp;
                    int mc;

                    if(job_=="Manager")
                    {salary1=8500;
                        cp=0.01;
                        mc=500;}

                    if(job_=="chef")
                    {salary1=5000;
                        cp=0.008;
                        mc=200;}

                    if(job_=="servant")
                    {salary1=4500;
                        cp=0.008;
                        mc=200;}

                    if(job_=="warehouse stuff")
                    {salary1=3500;
                        cp=0.008;
                        mc=200;}



                    sql_query.clear();
                    sql_query.prepare("INSERT INTO employee (employee_id,first_name,last_name,phone_number,city,job,salary,commission_pct,monthly_commission,hiredate,id,password) "
                                          "VALUES (? ,? ,? ,? ,? ,? ,? ,? ,? ,? ,? ,? )");
                            sql_query.addBindValue(number+1);
                            sql_query.addBindValue(first_name1);
                            sql_query.addBindValue(last_name1);
                            sql_query.addBindValue(phone_numebr);
                            sql_query.addBindValue(city);
                            sql_query.addBindValue(job_);
                            sql_query.addBindValue(salary1);
                            sql_query.addBindValue(cp);
                            sql_query.addBindValue(mc);
                            sql_query.addBindValue(hire_daate);
                            sql_query.addBindValue(ID1.toInt());

                            sql_query.addBindValue(password1);





//                            sql_query.exec();
                            if(!sql_query.exec())
                            {
                                QMessageBox::critical(0, QObject::tr("Database Error"),
                                                      sql_query.lastError().text());
                                return false;
                            }




                }

                    }
            QSqlDatabase employeewt;
            if(QSqlDatabase::contains("qt_sql_default_connection"))
                employeewt = QSqlDatabase::database("qt_sql_default_connection");
            else
                employeewt = QSqlDatabase::addDatabase("QSQLITE");

            employeewt.setDatabaseName("workTime.db");


                if(employeewt.open()){
                    qDebug()<<111;
                    QSqlQuery sql_querywt(employeewt);
                    sql_querywt.exec("select * from workTimeTable");
                    QString q1="0";
                    int aaa=0;
                    sql_querywt.clear();
                    sql_querywt.prepare("INSERT INTO workTimeTable (name,monthWorkTime,check_in_out,thisWorkStartTime,todayWorkTime,refreshTime) "
                                          "VALUES (? ,? ,? ,? ,? ,? )");
                    sql_querywt.addBindValue(first_name1);
                    sql_querywt.addBindValue(q1);
                    sql_querywt.addBindValue(aaa);
                    sql_querywt.addBindValue(q1);
                    sql_querywt.addBindValue(q1);
                    sql_querywt.addBindValue(q1);

                    if(!sql_querywt.exec())
                    {
                        QMessageBox::critical(0, QObject::tr("Database Errorwt"),
                                              sql_querywt.lastError().text());
                        return false;
                    }
                    else QMessageBox::information(this,"ok","你的账号已被成功创建!");


            }
        }



        });

}

RegisterStuff::~RegisterStuff()
{
    delete ui;
}

void RegisterStuff::set(QPushButton* m)
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
