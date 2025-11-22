#include "check_table.h"
#include "ui_check_table.h"
#include "servant_open.h"
#include "widget1.h"
#include "administratorhomepage.h"
#include "stockwidget.h"
#include <QTimer>
#include <QString>
#include <QMessageBox>
#include "table.h"
#include <QTextCodec>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QTime>
#include <QtSql/QSqlError>
#include <QtDebug>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlRecord>
#include <QPainter>

check_table::check_table(QString name1,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::check_table)
{
    name = name1;
    ui->setupUi(this);
    setBtn();
    for(int i = 0;i<20;i++)
    {
        tables[i].setNumber(i+1);
    }
    refresh();

    setWindowTitle("查看桌位");

    setWindowIcon(QIcon(":/icon.jpg"));

}

check_table::~check_table()
{
    delete ui;
}

void check_table::paintEvent(QPaintEvent *)
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

void check_table::set_job(QString job1)
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

void check_table::on_pushButton_21_clicked()
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

               case 3 ://进入此页面的身份是仓管
                {
                    administratorHomePage *manager = new administratorHomePage(name);
                    manager->show();
                    break;
                }
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

void check_table::setTablet(Table table)
{
    QString str = QString::number(table.getNumber());
    QFont ft;
    ft.setPointSize(16);
    ft.setBold(75);//粗体
    ui->label_5->setFont(ft);//设置字体
    ui->label_5->setText(str);//显示桌号
    if(table.getReservationStatus())//在预约状态
    {
        ft.setPointSize(14);//字号
        ft.setBold(75);//粗体
        ui->label_3->setFont(ft);//设置字体
        ui->label_3->setText("已预约");
        QTime time = table.getRestReservationTime();
        ui->lcdNumber->setDigitCount(10);//设置显示位数
        ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);
        ui->lcdNumber->setStyleSheet("color:black;");
        ui->lcdNumber->display(time.toString("HH:mm:ss"));
        ui->pushButton_22->setText("取消预约");

    }
    else
    {
        ft.setPointSize(14);//字号
        ft.setBold(75);//粗体
        ui->label_3->setFont(ft);//设置字体
        ui->label_3->setText("未预约");
        ui->lcdNumber->setDigitCount(10);//设置显示位数
        ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);
        ui->lcdNumber->setStyleSheet("color:black;");
        ui->lcdNumber->display("0");
        ui->pushButton_22->setText("预约");
    }
    if(table.getUsageStatus())
    {
        ft.setPointSize(14);//字号
        ft.setBold(75);//粗体
        ui->label_7->setFont(ft);//设置字体
        ui->label_7->setText("已落座");
        ui->pushButton_23->setText("离座");
    }
    else
    {
        ft.setPointSize(14);//字号
        ft.setBold(75);//粗体
        ui->label_7->setFont(ft);//设置字体
        ui->label_7->setText("未落座");
        ui->pushButton_23->setText("落座");
    }
}

void check_table::setTable(int num)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("table.db");
        if( !db.open())
        {
          qDebug()<<"Connection fails.";
        }
         if( db.open())
         {
             qDebug()<<"Connection success.";
             QSqlQuery q;
             q=QSqlQuery(db);
             if(q.exec(QString("select * from tables where number=%1").arg(num)))
             {
                 if(q.next())//找到了对应的桌子
                 {
                     QString reservationBool = q.value(1).toString();
                     if(reservationBool == "0")//不在预约状态 没有预约开始时间
                     {
                         tables[num-1].setReservationStatus(false);
                     }
                     else//预约状态中，有预约开始时间
                     {
                         tables[num-1].setReservationStatus(true);

                         //获取数据库中的预约开始时间放到table成员内
                         QTime reservationTime;
                         QString timestr = q.value(3).toString();
                         if(timestr == "0")//说明未设置预约开始时间
                         {
                             QMessageBox::StandardButton reply;
                             reply = QMessageBox::critical(this, tr("QMessageBox::critical()"),
                                                                 "错误：是预约状态却没有设置预约开始时间",
                                                                 QMessageBox::Abort | QMessageBox::Retry | QMessageBox::Ignore);
                         }
                         else
                         {
                             reservationTime = QTime::fromString(timestr,"hh::mm::ss");//获取预约的开始时间
                             tables[num-1].setReservationTimeFromDb(reservationTime);
                         }
                     }
                     QString usageBool = q.value(2).toString();
                     if(usageBool == "0")//不在落座状态
                     {
                         tables[num-1].setUsageStatus(false);
                     }
                     else
                     {
                         tables[num-1].setUsageStatus(true);
                     }
                 }
             }
         }
         db.close();
         setTablet(tables[num-1]);//转去显示
}


void check_table::on_pushButton_clicked()//01
{
    setTable(1);
    QPalette pal = ui->pushButton->palette();
    if(tables[0].getUsageStatus())//在使用状态，显示红色 在使用状态时不可能预约状态为true
    {
        pal.setColor(QPalette::Button,Qt::red);
    }
    else if(tables[0].getReservationStatus())//在预约状态，显示蓝色
    {
        pal.setColor(QPalette::Button,Qt::blue);
    }
    else//非使用非预约状态， 显示绿色
    {
        pal.setColor(QPalette::Button,Qt::green);
    }
    ui->pushButton->setPalette(pal);
    ui->pushButton->setAutoFillBackground(true);
    ui->pushButton->setFlat(true);
}

void check_table::on_pushButton_2_clicked()//02
{
    setTable(2);
    QPalette pal = ui->pushButton_2->palette();
    if(tables[1].getUsageStatus())//在使用状态，显示红色 在使用状态时不可能预约状态为true
    {
        pal.setColor(QPalette::Button,Qt::red);
    }
    else if(tables[1].getReservationStatus())//在预约状态，显示蓝色
    {
        pal.setColor(QPalette::Button,Qt::blue);
    }
    else//非使用非预约状态， 显示绿色
    {
        pal.setColor(QPalette::Button,Qt::green);
    }
    ui->pushButton_2->setPalette(pal);
    ui->pushButton_2->setAutoFillBackground(true);
    ui->pushButton_2->setFlat(true);
}

void check_table::on_pushButton_20_clicked()//是03号桌
{
    setTable(3);
    QPalette pal = ui->pushButton_20->palette();
    if(tables[2].getUsageStatus())//在使用状态，显示红色 在使用状态时不可能预约状态为true
    {
        pal.setColor(QPalette::Button,Qt::red);
    }
    else if(tables[2].getReservationStatus())//在预约状态，显示蓝色
    {
           pal.setColor(QPalette::Button,Qt::blue);
    }
    else//非使用非预约状态， 显示绿色
    {
        pal.setColor(QPalette::Button,Qt::green);
    }
    ui->pushButton_20->setPalette(pal);
    ui->pushButton_20->setAutoFillBackground(true);
    ui->pushButton_20->setFlat(true);
}


void check_table::on_pushButton_3_clicked()//04
{
    setTable(4);
    QPalette pal = ui->pushButton_3->palette();
    if(tables[3].getUsageStatus())//在使用状态，显示红色 在使用状态时不可能预约状态为true
    {
        pal.setColor(QPalette::Button,Qt::red);
    }
    else if(tables[3].getReservationStatus())//在预约状态，显示蓝色
    {
        pal.setColor(QPalette::Button,Qt::blue);

    }
    else//非使用非预约状态， 显示绿色
    {
        pal.setColor(QPalette::Button,Qt::green);
    }
    ui->pushButton_3->setPalette(pal);
    ui->pushButton_3->setAutoFillBackground(true);
    ui->pushButton_3->setFlat(true);
}


void check_table::on_pushButton_4_clicked()//05
{
    setTable(5);
    QPalette pal = ui->pushButton_4->palette();
    if(tables[4].getUsageStatus())//在使用状态，显示红色 在使用状态时不可能预约状态为true
    {
        pal.setColor(QPalette::Button,Qt::red);
    }
    else if(tables[4].getReservationStatus())//在预约状态，显示蓝色
    {
        pal.setColor(QPalette::Button,Qt::blue);
    }
    else//非使用非预约状态， 显示绿色
    {
        pal.setColor(QPalette::Button,Qt::green);
    }
    ui->pushButton_4->setPalette(pal);
    ui->pushButton_4->setAutoFillBackground(true);
    ui->pushButton_4->setFlat(true);
}

void check_table::on_pushButton_5_clicked()//06
{
    setTable(6);
    QPalette pal = ui->pushButton_5->palette();
    if(tables[5].getUsageStatus())//在使用状态，显示红色 在使用状态时不可能预约状态为true
    {
        pal.setColor(QPalette::Button,Qt::red);
    }
    else if(tables[5].getReservationStatus())//在预约状态，显示蓝色
    {
        pal.setColor(QPalette::Button,Qt::blue);
    }
    else//非使用非预约状态， 显示绿色
    {
        pal.setColor(QPalette::Button,Qt::green);
    }
    ui->pushButton_5->setPalette(pal);
    ui->pushButton_5->setAutoFillBackground(true);
    ui->pushButton_5->setFlat(true);
}

void check_table::on_pushButton_6_clicked()//07
{
    setTable(7);
    QPalette pal = ui->pushButton_6->palette();
    if(tables[6].getUsageStatus())//在使用状态，显示红色 在使用状态时不可能预约状态为true
    {
          pal.setColor(QPalette::Button,Qt::red);
    }
    else if(tables[6].getReservationStatus())//在预约状态，显示蓝色
    {
           pal.setColor(QPalette::Button,Qt::blue);
    }
    else//非使用非预约状态， 显示绿色
    {
        pal.setColor(QPalette::Button,Qt::green);
    }
    ui->pushButton_6->setPalette(pal);
    ui->pushButton_6->setAutoFillBackground(true);
    ui->pushButton_6->setFlat(true);
}

void check_table::on_pushButton_7_clicked()//08
{
     QPalette pal = ui->pushButton_7->palette();
     setTable(8);
    if(tables[7].getUsageStatus())//在使用状态，显示红色 在使用状态时不可能预约状态为true
    {
        pal.setColor(QPalette::Button,Qt::red);
    }
    else if(tables[7].getReservationStatus())//在预约状态，显示蓝色
    {
           pal.setColor(QPalette::Button,Qt::blue);
    }
    else//非使用非预约状态， 显示绿色
    {
        pal.setColor(QPalette::Button,Qt::green);
    }
    ui->pushButton_7->setPalette(pal);
    ui->pushButton_7->setAutoFillBackground(true);
    ui->pushButton_7->setFlat(true);
}

void check_table::on_pushButton_8_clicked()//09
{
    setTable(9);
    QPalette pal = ui->pushButton_8->palette();
    if(tables[8].getUsageStatus())//在使用状态，显示红色 在使用状态时不可能预约状态为true
    {
           pal.setColor(QPalette::Button,Qt::red);

    }
    else if(tables[8].getReservationStatus())//在预约状态，显示蓝色
    {
           pal.setColor(QPalette::Button,Qt::blue);
    }
    else//非使用非预约状态， 显示绿色
    {
           pal.setColor(QPalette::Button,Qt::green);
    }
    ui->pushButton_8->setPalette(pal);
    ui->pushButton_8->setAutoFillBackground(true);
    ui->pushButton_8->setFlat(true);
}

void check_table::on_pushButton_9_clicked()//10
{
    setTable(10);
    QPalette pal = ui->pushButton_9->palette();
    if(tables[9].getUsageStatus())//在使用状态，显示红色 在使用状态时不可能预约状态为true
    {
           pal.setColor(QPalette::Button,Qt::red);

    }
    else if(tables[9].getReservationStatus())//在预约状态，显示蓝色
    {
           pal.setColor(QPalette::Button,Qt::blue);
    }
    else//非使用非预约状态， 显示绿色
    {
           pal.setColor(QPalette::Button,Qt::green);
    }
    ui->pushButton_9->setPalette(pal);
    ui->pushButton_9->setAutoFillBackground(true);
    ui->pushButton_9->setFlat(true);
}

void check_table::on_pushButton_10_clicked()//11
{
    setTable(11);
    QPalette pal = ui->pushButton_10->palette();
    if(tables[10].getUsageStatus())//在使用状态，显示红色 在使用状态时不可能预约状态为true
    {
           pal.setColor(QPalette::Button,Qt::red);

    }
    else if(tables[10].getReservationStatus())//在预约状态，显示蓝色
    {
           pal.setColor(QPalette::Button,Qt::blue);
    }
    else//非使用非预约状态， 显示绿色
    {
           pal.setColor(QPalette::Button,Qt::green);
    }
    ui->pushButton_10->setPalette(pal);
    ui->pushButton_10->setAutoFillBackground(true);
    ui->pushButton_10->setFlat(true);
}

void check_table::on_pushButton_11_clicked()//12
{
    setTable(12);
    QPalette pal = ui->pushButton_11->palette();
    if(tables[11].getUsageStatus())//在使用状态，显示红色 在使用状态时不可能预约状态为true
    {
           pal.setColor(QPalette::Button,Qt::red);

    }
    else if(tables[11].getReservationStatus())//在预约状态，显示蓝色
    {
           pal.setColor(QPalette::Button,Qt::blue);
    }
    else//非使用非预约状态， 显示绿色
    {
           pal.setColor(QPalette::Button,Qt::green);
    }
    ui->pushButton_11->setPalette(pal);
    ui->pushButton_11->setAutoFillBackground(true);
    ui->pushButton_11->setFlat(true);
}

void check_table::on_pushButton_12_clicked()//13
{
    setTable(13);
    QPalette pal = ui->pushButton_12->palette();
    if(tables[12].getUsageStatus())//在使用状态，显示红色 在使用状态时不可能预约状态为true
    {
           pal.setColor(QPalette::Button,Qt::red);

    }
    else if(tables[12].getReservationStatus())//在预约状态，显示蓝色
    {
           pal.setColor(QPalette::Button,Qt::blue);
    }
    else//非使用非预约状态， 显示绿色
    {
           pal.setColor(QPalette::Button,Qt::green);
    }
    ui->pushButton_12->setPalette(pal);
    ui->pushButton_12->setAutoFillBackground(true);
    ui->pushButton_12->setFlat(true);
}

void check_table::on_pushButton_14_clicked()//14
{
    setTable(14);
    QPalette pal = ui->pushButton_14->palette();
    if(tables[13].getUsageStatus())//在使用状态，显示红色 在使用状态时不可能预约状态为true
    {
           pal.setColor(QPalette::Button,Qt::red);
    }
    else if(tables[13].getReservationStatus())//在预约状态，显示蓝色
    {
        pal.setColor(QPalette::Button,Qt::blue);
    }
    else//非使用非预约状态， 显示绿色
    {
        pal.setColor(QPalette::Button,Qt::green);
    }
    ui->pushButton_14->setPalette(pal);
    ui->pushButton_14->setAutoFillBackground(true);
    ui->pushButton_14->setFlat(true);
}

void check_table::on_pushButton_15_clicked()//15
{
    setTable(15);
    QPalette pal = ui->pushButton_15->palette();
    if(tables[14].getUsageStatus())//在使用状态，显示红色 在使用状态时不可能预约状态为true
    {
           pal.setColor(QPalette::Button,Qt::red);

    }
    else if(tables[14].getReservationStatus())//在预约状态，显示蓝色
    {
        pal.setColor(QPalette::Button,Qt::blue);

    }
    else//非使用非预约状态， 显示绿色
    {
        pal.setColor(QPalette::Button,Qt::green);
    }
    ui->pushButton_15->setPalette(pal);
    ui->pushButton_15->setAutoFillBackground(true);
    ui->pushButton_15->setFlat(true);
}

void check_table::on_pushButton_16_clicked()//16
{
    setTable(16);
    QPalette pal = ui->pushButton_16->palette();
    if(tables[15].getUsageStatus())//在使用状态，显示红色 在使用状态时不可能预约状态为true
    {
           pal.setColor(QPalette::Button,Qt::red);
    }
    else if(tables[15].getReservationStatus())//在预约状态，显示蓝色
    {
        pal.setColor(QPalette::Button,Qt::blue);
    }
    else//非使用非预约状态， 显示绿色
    {
        pal.setColor(QPalette::Button,Qt::green);
    }
    ui->pushButton_16->setPalette(pal);
    ui->pushButton_16->setAutoFillBackground(true);
    ui->pushButton_16->setFlat(true);
}

void check_table::on_pushButton_13_clicked()//17
{
    setTable(17);
    QPalette pal = ui->pushButton_13->palette();
    if(tables[16].getUsageStatus())//在使用状态，显示红色 在使用状态时不可能预约状态为true
    {
           pal.setColor(QPalette::Button,Qt::red);
    }
    else if(tables[16].getReservationStatus())//在预约状态，显示蓝色
    {
        pal.setColor(QPalette::Button,Qt::blue);
    }
    else//非使用非预约状态， 显示绿色
    {
        pal.setColor(QPalette::Button,Qt::green);
    }
    ui->pushButton_13->setPalette(pal);
    ui->pushButton_13->setAutoFillBackground(true);
    ui->pushButton_13->setFlat(true);
}

void check_table::on_pushButton_17_clicked()//18
{
    setTable(18);
    QPalette pal = ui->pushButton_17->palette();
    if(tables[17].getUsageStatus())//在使用状态，显示红色 在使用状态时不可能预约状态为true
    {
           pal.setColor(QPalette::Button,Qt::red);
    }
    else if(tables[17].getReservationStatus())//在预约状态，显示蓝色
    {
        pal.setColor(QPalette::Button,Qt::blue);
    }
    else//非使用非预约状态， 显示绿色
    {
        pal.setColor(QPalette::Button,Qt::green);
    }
    ui->pushButton_17->setPalette(pal);
    ui->pushButton_17->setAutoFillBackground(true);
    ui->pushButton_17->setFlat(true);
}

void check_table::on_pushButton_18_clicked()//19
{
    setTable(19);
    QPalette pal = ui->pushButton_18->palette();
    if(tables[18].getUsageStatus())//在使用状态，显示红色 在使用状态时不可能预约状态为true
    {
           pal.setColor(QPalette::Button,Qt::red);
    }
    else if(tables[18].getReservationStatus())//在预约状态，显示蓝色
    {
        pal.setColor(QPalette::Button,Qt::blue);
    }
    else//非使用非预约状态， 显示绿色
    {
        pal.setColor(QPalette::Button,Qt::green);
    }
    ui->pushButton_18->setPalette(pal);
    ui->pushButton_18->setAutoFillBackground(true);
    ui->pushButton_18->setFlat(true);
}

void check_table::on_pushButton_19_clicked()//20
{
    setTable(20);
    QPalette pal = ui->pushButton_19->palette();
    if(tables[19].getUsageStatus())//在使用状态，显示红色 在使用状态时不可能预约状态为true
    {
           pal.setColor(QPalette::Button,Qt::red);
    }
    else if(tables[19].getReservationStatus())//在预约状态，显示蓝色
    {
        pal.setColor(QPalette::Button,Qt::blue);
    }
    else//非使用非预约状态， 显示绿色
    {
        pal.setColor(QPalette::Button,Qt::green);
    }
    ui->pushButton_19->setPalette(pal);
    ui->pushButton_19->setAutoFillBackground(true);
    ui->pushButton_19->setFlat(true);
}

//预约、取消预约按钮
void check_table::on_pushButton_22_clicked()
{
    QString str = ui->label_5->text();
    QFont ft;
    int number = str.toInt();//获得当前桌号
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("table.db");
        if( !db.open())
        {
          qDebug()<<"Connection fails.";
        }


    if(tables[number-1].getReservationStatus())//预约状态中,转成取消预约
    {
        if( db.open())
         {
             qDebug()<<"Connection success.";
             QSqlQuery q;
             q=QSqlQuery(db);
             if(q.exec(QString("update tables set reservation_status=0 where number=%1;").arg(number)))//修改数据库中的预约状态
             {
                 qDebug()<<"update reservation_status=0 success";
             }
             if(q.exec(QString("update tables set reservation_time='%1' where number=%2;").arg("0").arg(number)))//修改数据库中的预约开始时间
             {
                 qDebug()<<"update reservation_time=0 success";
             }
        }
        tables[number-1].setReservationStatus(false);
        ui->pushButton_22->setText("预约");

        ft.setPointSize(14);//字号
        ft.setBold(75);//粗体
        ui->label_3->setFont(ft);//设置字体
        ui->label_3->setText("未预约");
        ui->lcdNumber->setDigitCount(10);//设置显示位数
        ui->lcdNumber->display("0");
    }
    else//未预约状态中，要转成预约状态
    {
        if(tables[number-1].getUsageStatus())//已落座，不可预约
        {
            QMessageBox::information(NULL, "提示", "该桌子已落座，不可预约！");
        }
        else//未落座，可预约
        {
            if( db.open())
             {
                 qDebug()<<"Connection success.";
                 QSqlQuery q;
                 q=QSqlQuery(db);
                 if(q.exec(QString("update tables set reservation_status=1 where number=%1;").arg(number)))//修改数据库中的预约状态
                 {
                     qDebug()<<"update reservation_status=1 success";
                 }
                 QString reservationTimestr = QTime::currentTime().toString("hh::mm::ss");
                 if(q.exec(QString("update tables set reservation_time='%1' where number=%2;").arg(reservationTimestr).arg(number)))//修改数据库中的预约开始时间
                 {
                     qDebug()<<"update reservation_time success";
                 }
            }
            tables[number-1].setReservationStatus(true);
            ui->pushButton_22->setText("取消预约");
            ft.setPointSize(14);//字号
            ft.setBold(75);//粗体
            ui->label_3->setFont(ft);//设置字体
            ui->label_3->setText("已预约");
            tables[number-1].setReservationTime();
            QTime time = tables[number-1].getRestReservationTime();
            ui->lcdNumber->setDigitCount(10);//设置显示位数
            ui->lcdNumber->display(time.toString("HH:mm:ss"));

        }

    }
    db.close();
}

//落座、离座按钮
void check_table::on_pushButton_23_clicked()
{
    QFont ft;
    QString str = ui->label_5->text();
    int number = str.toInt();//获得当前桌号

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("table.db");
        if( !db.open())
        {
          qDebug()<<"Connection fails.";
        }

    if(tables[number-1].getUsageStatus())//已落座，准备离座
    {
        if( db.open())
         {
             qDebug()<<"Connection success.";
             QSqlQuery q;
             q=QSqlQuery(db);
             if(q.exec(QString("update tables set usage_status=0 where number=%1;").arg(number)))//修改数据库中的使用状态
             {
                 qDebug()<<"update usage_status=0 success";
             }
        }
        tables[number-1].setUsageStatus(false);
        ft.setPointSize(14);//字号
        ft.setBold(75);//粗体
        ui->label_7->setFont(ft);//设置字体
        ui->label_7->setText("未落座");
        ui->pushButton_23->setText("落座");
    }
    else//可落座，准备落座
    {
        if( db.open())
         {
             qDebug()<<"Connection success.";
             QSqlQuery q;
             q=QSqlQuery(db);
             if(q.exec(QString("update tables set usage_status=1 where number=%1;").arg(number)))//修改数据库中的使用状态
             {
                 qDebug()<<"update usage_status=1 success";
             }
        }
        tables[number-1].setUsageStatus(true);
        ft.setPointSize(14);//字号
        ft.setBold(75);//粗体
        ui->label_7->setFont(ft);//设置字体
        ui->label_7->setText("已落座");
        ui->pushButton_23->setText("离座");
        tables[number-1].setReservationStatus(false);
        ui->pushButton_22->setText("预约");
        ft.setPointSize(14);//字号
        ft.setBold(75);//粗体
        ui->label_3->setFont(ft);//设置字体
        ui->label_3->setText("未预约");
        ui->lcdNumber->display("0");
    }
    db.close();
}

//刷新
void check_table::refresh()
{

    ui->pushButton_2->click();
    ui->pushButton_3->click();
    ui->pushButton_4->click();
    ui->pushButton_5->click();
    ui->pushButton_6->click();
    ui->pushButton_7->click();
    ui->pushButton_8->click();
    ui->pushButton_9->click();
    ui->pushButton_10->click();
    ui->pushButton_11->click();
    ui->pushButton_12->click();
    ui->pushButton_13->click();
    ui->pushButton_14->click();
    ui->pushButton_15->click();
    ui->pushButton_16->click();
    ui->pushButton_17->click();
    ui->pushButton_18->click();
    ui->pushButton_19->click();
    ui->pushButton_20->click();
    ui->pushButton->click();
}

void check_table::on_pushButton_24_clicked()
{
    refresh();
}

void check_table::setBtn()
{
    ui->pushButton_21->setStyleSheet(
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
    ui->pushButton_22->setStyleSheet(
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
    ui->pushButton_23->setStyleSheet(
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
    ui->pushButton_24->setStyleSheet(
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
