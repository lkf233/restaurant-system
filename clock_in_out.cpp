#include "clock_in_out.h"
#include "ui_clock_in_out.h"
#include "widget1.h"
#include "administratorhomepage.h"
#include "servant_open.h"
#include <QTimer>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QTextCodec>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QTime>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlRecord>
#include <QPainter>

Clock_in_out::Clock_in_out(QString name1,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Clock_in_out)
{
    name=name1;
    ui->setupUi(this);
    today_time.setHMS(0,0,0);

    QFont ft;
    ft.setPointSize(14);//字号
    ft.setBold(75);//粗体
    ui->label_3->setFont(ft);//设置字体
    ui->label_3->setText("Welcome!"+name);

    getCheck_in_out();//获得上班状态
    onTimeOut();//刷新
    setBtn();
    setWindowTitle("上下班打卡");

    setWindowIcon(QIcon(":/icon.jpg"));

    /*QTimer *pTimer = new QTimer(this);
    // 设置定时间隔
    pTimer->setInterval(1000);//间隔1s
    connect(pTimer, SIGNAL(timeout()), this, SLOT(onTimeOut()));

    // 启动定时器
    pTimer->start();*/
}

Clock_in_out::~Clock_in_out()
{
    delete ui;
}

void Clock_in_out::paintEvent(QPaintEvent *)
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

void Clock_in_out::set_job(QString job1)
{
    //进入此页面的身份是服务员
    if(job1 == "servant")
    {
        job = 1;
    }
    //进入此页面的身份是厨师
    else if(job1 == "chef")
    {
        job = 2;
    }
    //进入此页面的身份是仓管
    else if(job1 == "warehouse")//查看一下仓管到底叫啥
    {
        job = 3;
    }
    //进入此页面的身份是管理员
    else if(job1 == "manager")
    {
        job = 4;
    }
    else
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::critical(this, tr("QMessageBox::critical()"),
                                            "无效的职位",
                                            QMessageBox::Abort | QMessageBox::Retry | QMessageBox::Ignore);

    }
}

void Clock_in_out::on_pushButton_2_clicked()
{
            //延时进入界面
            QTimer::singleShot(500,this,[=](){
            //自身隐藏
            this->hide();
            //返回原始界面
            //需要获得进入本界面时的员工岗位信息
                switch(job)
                {
                case 1 ://进入此页面的身份是服务员//返回服务员界面
                {Servant_open *servant = new Servant_open(name);
                    servant->show();
                    break;}
               case 2://进入此页面的身份是厨师
                   { Widget1 *chef = new Widget1(name);
                    chef->show();
                    break;}
                case 4 ://进入此页面的身份是管理员
                {
                    administratorHomePage *manager = new administratorHomePage(name);
                    manager->show();
                    break;
                }
                default:
                    qDebug()<<"wrong job!";
                    break;
                }

            });

}

//签到、签退按钮
void Clock_in_out::on_pushButton_clicked()
{
    QFont ft;
    ft.setPointSize(16);//字号
    ft.setBold(75);//粗体
    ui->label->setFont(ft);//设置字体
    if(check_in_out)//上班中，准备签退
    {
        check_in_out = false;//改为下班状态
        ui->pushButton->setText("签到");
        ui->label->setAlignment(Qt::AlignHCenter);
        ui->label->setText("下班中");
        ui->lcdNumber_2->display("0");

        //修改数据库中的本次上班开始时间为0
        QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
         QString dsn = QString::fromLocal8Bit("restaurant");//你配置的Data Source
         db.setHostName("192.168.56.102");//你的IP地址
         db.setDatabaseName(dsn);
         db.setUserName("my_root"); //用户名
         db.setPassword("my_root@123");//密码
         db.setPort(26000); //opengauss端口号为26000
            if( !db.open())
            {
              qDebug()<<"Connection fails.";
            }
             if( db.open())
             {
                 qDebug()<<"Connection success.";
                 QSqlQuery q;
                 q=QSqlQuery(db);
                 if(q.exec(QString("update workTimeTable set thisWorkStartTime='%1' where name='%2';").arg("0").arg(name)))
                 {
                     qDebug()<<"check out and set thisWorkStartTime=0 seccess";
                 }
                 if(q.exec(QString("update workTimeTable set check_in_out=%1 where name='%2';").arg(0).arg(name)))
                 {
                     qDebug()<<"set workBool to be false";
                 }
                 if(q.exec(QString("update workTimeTable set refreshTime='%1' where name='%2'").arg("00::00::00").arg(name)))
                 {
                     qDebug()<<"update refreshTime successfully";
                 }
             }
    }
    else//准备签到
    {
        check_in_out = true;
        in_time = QTime::currentTime();
        last_time = QTime::currentTime();
        ui->pushButton->setText("签退");
        ui->label->setAlignment(Qt::AlignHCenter);
        ui->label->setText("上班中");

        //设置数据库中的本次上班开始时间
        QString inTimestr = QTime::currentTime().toString("hh::mm::ss");
        QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
         QString dsn = QString::fromLocal8Bit("restaurant");//你配置的Data Source
         db.setHostName("192.168.56.102");//你的IP地址
         db.setDatabaseName(dsn);
         db.setUserName("my_root"); //用户名
         db.setPassword("my_root@123");//密码
         db.setPort(26000); //opengauss端口号为26000
            if( !db.open())
            {
              qDebug()<<"Connection fails.";
            }
             if( db.open())
             {
                 qDebug()<<"Connection success.";
                 QSqlQuery q;
                 q=QSqlQuery(db);
                 if(q.exec(QString("update workTimeTable set thisWorkStartTime='%1' where name='%2';").arg(inTimestr).arg(name)))
                 {
                     qDebug()<<"check in and set thisWorkStartTime seccess";
                 }
                 if(q.exec(QString("update workTimeTable set refreshTime='%1' where name='%2';").arg(inTimestr).arg(name)))
                 {
                     qDebug()<<"check in and set refreshTime seccess";
                 }
                 if(q.exec(QString("update workTimeTable set check_in_out=%1 where name='%2';").arg(1).arg(name)))
                 {
                     qDebug()<<"set workBool to be true";
                 }
             }

    }

}

void Clock_in_out::onTimeOut()
{
    QFont ft;
    ft.setPointSize(16);//字号
    ft.setBold(75);//粗体
    ui->label->setFont(ft);//设置字体

    if(check_in_out)//上班中//需要简化计算
    {
        ui->pushButton->setText("签退");
        ui->label->setAlignment(Qt::AlignHCenter);
        ui->label->setText("上班中");
        QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
         QString dsn = QString::fromLocal8Bit("restaurant");//你配置的Data Source
         db.setHostName("192.168.56.102");//你的IP地址
         db.setDatabaseName(dsn);
         db.setUserName("my_root"); //用户名
         db.setPassword("my_root@123");//密码
         db.setPort(26000); //opengauss端口号为26000
        //打开数据库获得本次上班的开始时间和本日工作总时长
        if( db.open())
             {
                 qDebug()<<"Connection success.";
                 QSqlQuery q;
                 q=QSqlQuery(db);
                 if(q.exec(QString("select thisWorkStartTime,todayWorkTime,refreshTime from workTimeTable where name='%1'").arg(name)))
                 {
                     if(q.next())//找到了
                     {
                         in_time = QTime::fromString(q.value(0).toString(),"hh::mm::ss");//获得当前这个人本次上班的开始时间
                         today_time = QTime::fromString(q.value(1).toString(),"hh::mm::ss");//获得当前这个人本日上班的时长
                         last_time = QTime::fromString(q.value(2).toString(),"hh::mm::ss");//获得上次刷新的时间
                         qDebug()<<"get thisWorkStartTime,todayWorkTime from workTimeTable successfully";
                     }

                 }
             }
        int ms = in_time.msecsTo(QTime::currentTime());//本次上班时间毫秒时间差
        qDebug()<<"ms:"<<ms<<endl;


        //将毫秒数转回QTime的计算基数
        int ss = 1000;
        int mi = ss * 60;
        int hh = mi * 60;
        int dd = hh * 24;
        //QTime所需参数
        long day,hour,minute,second,milliSecond;
        //将毫秒数转回QTime
            day = ms / dd;
            hour = (ms - day * dd) / hh;
            minute = (ms - day * dd - hour * hh) / mi;
            second = (ms - day * dd - hour * hh - minute * mi) / ss;
            milliSecond = ms - day * dd - hour * hh - minute * mi - second * ss;
        this_time.setHMS(hour,minute,second);//本次上班时长
        ui->lcdNumber_2->setDigitCount(10);//设置显示位数
        ui->lcdNumber_2->display(this_time.toString("HH:mm:ss"));

       // int refreshMs = last_time.msecsTo(this_time);//两次刷新的间隔时间
        //last_time = this_time;
        int refreshMs = last_time.msecsTo(QTime::currentTime());//两次刷新的间隔时间

        QTime zeroTime(0,0,0);
        int todayms = zeroTime.msecsTo(today_time);//获得本日已工作总时长毫秒数
        qDebug()<<"todayms:"<<todayms<<endl;
        todayms += refreshMs;//本日工作时间要加上本次刷新得到的本次工作时间
        qDebug()<<"todayms + ms:"<<todayms<<endl;
        long tdday,tdhour,tdminute,tdsecond,tdmilliSecond;
        tdday = todayms / dd;
        tdhour = (todayms - tdday * dd) / hh;
        tdminute = (todayms - tdday * dd - tdhour * hh) / mi;
        tdsecond = (todayms - tdday * dd - tdhour * hh - tdminute * mi) / ss;
        tdmilliSecond = todayms - tdday * dd - tdhour * hh - tdminute * mi - tdsecond * ss;
        today_time.setHMS(tdhour,tdminute,tdsecond);//本日上班时长

        last_time = QTime::currentTime();

        ui->lcdNumber->setDigitCount(10);//设置显示位数
        ui->lcdNumber->display(today_time.toString("HH:mm:ss"));
        if( db.open())
             {
                 qDebug()<<"Connection success.";
                 QSqlQuery q;
                 q=QSqlQuery(db);
                 QString todayStr = today_time.toString("hh::mm::ss");
                 QString refreshStr = last_time.toString("hh::mm::ss");
                 if(q.exec(QString("update workTimeTable set todayWorkTime='%1' where name='%2'").arg(todayStr).arg(name)))
                 {
                     qDebug()<<"update todayWorkTime successfully";
                 }
                 if(q.exec(QString("update workTimeTable set refreshTime='%1' where name='%2'").arg(refreshStr).arg(name)))
                 {
                     qDebug()<<"update refreshTime successfully";
                 }
             }

    }
    else//下班中
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
         QString dsn = QString::fromLocal8Bit("restaurant");//你配置的Data Source
         db.setHostName("192.168.56.102");//你的IP地址
         db.setDatabaseName(dsn);
         db.setUserName("my_root"); //用户名
         db.setPassword("my_root@123");//密码
         db.setPort(26000); //opengauss端口号为26000
        if( db.open())
             {
                 qDebug()<<"Connection success.";
                 QSqlQuery q;
                 q=QSqlQuery(db);
                 if(q.exec(QString("select todayWorkTime from workTimeTable where name='%1'").arg(name)))
                 {
                     if(q.next())//找到了
                     {

                         today_time = QTime::fromString(q.value(0).toString(),"hh::mm::ss");//获得当前这个人本日上班的时长
                     }

                 }
             }
        ui->lcdNumber->setDigitCount(10);//设置显示位数
        ui->lcdNumber->display(today_time.toString("hh:mm:ss"));

        ui->lcdNumber_2->setDigitCount(10);//设置显示位数
        ui->lcdNumber_2->display("0");

        ui->pushButton->setText("签到");
        ui->label->setAlignment(Qt::AlignHCenter);
        ui->label->setText("下班中");
    }

}

//刷新键
void Clock_in_out::on_pushButton_3_clicked()
{
    onTimeOut();
}

//从数据库中获得当前员工的上班状态并设置
void Clock_in_out::getCheck_in_out()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
     QString dsn = QString::fromLocal8Bit("restaurant");//你配置的Data Source
     db.setHostName("192.168.56.102");//你的IP地址
     db.setDatabaseName(dsn);
     db.setUserName("my_root"); //用户名
     db.setPassword("my_root@123");//密码
     db.setPort(26000); //opengauss端口号为26000

        if( !db.open())
        {
          qDebug()<<"Connection fails.";
        }
         if( db.open())
         {
             qDebug()<<"Connection success.";
             QSqlQuery q;
             q=QSqlQuery(db);
             if(q.exec(QString("select check_in_out from workTimeTable where name='%1'").arg(name)))
             {
                 if(q.next())//找到了当前员工的工作状态
                 {
                     QString check = q.value(0).toString();
                     if(check == "0")//下班状态，设为false
                     {
                        check_in_out = false;
                     }
                     else//上班中
                     {
                         check_in_out = true;
                     }
                 }
                 else//没找到该员工
                 {
                     QMessageBox::StandardButton reply;
                     reply = QMessageBox::critical(this, tr("QMessageBox::critical()"),
                                                         "错误：没从workTime表中找到对应员工的check_in_out",
                                                         QMessageBox::Abort | QMessageBox::Retry | QMessageBox::Ignore);

                 }
             }
         }
         db.close();
}


//设置员工名字
void Clock_in_out::setName(QString a)
{
    name = a;
}

//本日结束，处理相应时间的加和
void Clock_in_out::on_pushButton_4_clicked()
{
   if(check_in_out)//仍在上班中，不可以结束本日
   {
       QMessageBox::information(NULL, "提示", "当前仍在上班中，请先签退再结束今日上班！");
   }
   else
   {
       QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
        QString dsn = QString::fromLocal8Bit("restaurant");//你配置的Data Source
        db.setHostName("192.168.56.102");//你的IP地址
        db.setDatabaseName(dsn);
        db.setUserName("my_root"); //用户名
        db.setPassword("my_root@123");//密码
        db.setPort(26000); //opengauss端口号为26000
        if( !db.open())
        {
          qDebug()<<"Connection fails.";
        }
         if( db.open())
         {
             qDebug()<<"Connection success.";
             QSqlQuery q;
             q=QSqlQuery(db);
             qint64 monthMs = 0;
             if(q.exec(QString("select todayWorkTime,monthWorkTime from workTimeTable where name='%1'").arg(name)))
             {
                 if(q.next())//找到了
                 {
                     today_time = QTime::fromString(q.value(0).toString(),"hh::mm::ss");//获得当前这个人本日上班的时长
                     monthMs = q.value(1).toLongLong();//获得当前这个人本月已工作的时长(毫秒）
                     qDebug()<<"get todayWorkTime,monthWorkTime from workTimeTable successfully";
                 }

             }

             QTime zeroTime(0,0,0);
             int todayMs = zeroTime.msecsTo(today_time);//本日上班总时长
             qint64 ms = todayMs + monthMs;//本月中加上本日的时长
             QString monthStr = QString::number(ms);
             //更新数据库中本月工作时长
             if(q.exec(QString("update workTimeTable set monthWorkTime='%1' where name='%2';").arg(monthStr).arg(name)))
             {
                 qDebug()<<"check in and set monthWorkTime seccess";
             }
             //将数据库中今日工作时长恢复为0
             if(q.exec(QString("update workTimeTable set todayWorkTime='%1' where name='%2'").arg("0").arg(name)))
             {
                 qDebug()<<"update todayWorkTime = 0 successfully";
             }

         }
    ui->lcdNumber->display("--：--：--");
   }
}

void Clock_in_out::setBtn()
{
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



}
