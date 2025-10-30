#include "table.h"
#include <QTextCodec>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QTime>
#include <QtSql/QSqlError>
#include <QtDebug>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlRecord>

Table::Table()
{

}

Table::Table(QString name1,int id)
{
    name = name1;
    number = id;
}

void Table::setReservationStatus(bool a)
{
    reservation_status = a;
}
void Table::setUsageStatus(bool a)
{
    usage_status = a;
}
void Table::setReservationTime()
{
    reservation_time = QTime::currentTime();
}
QTime Table::getRestReservationTime()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
     QString dsn = QString::fromLocal8Bit("restaurant");//你配置的Data Source
     db.setHostName("192.168.56.102");//你的IP地址
     db.setDatabaseName(dsn);
     db.setUserName("my_root"); //用户名
     db.setPassword("my_root@123");//密码
     db.setPort(26000); //opengauss端口号为26000
    QTime now = QTime::currentTime();
    if( !db.open())
      {
          qDebug()<<"Connection fails.";
      }

    int ms = reservation_time.msecsTo(now);//获得差值毫秒数
    //将毫秒数转回QTime的计算基数
    int ss = 1000;
    int mi = ss * 60;
    int hh = mi * 60;
    int dd = hh * 24;

    //QTime所需参数
    long day,hour,minute,second,milliSecond;

    if(ms >= 3600000)//预约已超过一小时，即将解除预约
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
                 if(q.exec(QString("update tables set reservation_status=0 where number=%1;").arg(number)))
                 {
                     qDebug()<<"update reservation_status=0 success";
                 }
                 if(q.exec(QString("update tables set reservation_time='%1' where number=%2;").arg("0").arg(number)))//修改数据库中的预约开始时间
                 {
                     qDebug()<<"update reservation_time=0 success";
                 }
             }
        day = 0;
        hour = 0;
        minute = 0;
        second = 0;
        milliSecond = 0;
    }
    else
    {
        ms = 3600000 - ms;//ms为剩余的毫秒时间（相对于一小时）
        //将毫秒数转回QTime
            day = ms / dd;
            hour = (ms - day * dd) / hh;
            minute = (ms - day * dd - hour * hh) / mi;
            second = (ms - day * dd - hour * hh - minute * mi) / ss;
            milliSecond = ms - day * dd - hour * hh - minute * mi - second * ss;

            /*QString hou = QString::number(hour,10);
            QString min = QString::number(minute,10);
            QString sec = QString::number(second,10);
            QString msec = QString::number(milliSecond,10);*/

    }
    QTime time(hour,minute,second);
    return time;

}

bool Table::getReservationStatus()
{
    return reservation_status;
}
bool Table::getUsageStatus()
{
    return usage_status;
}

int Table::getNumber()
{
    return number;
}

void Table::setNumber(int i)
{
    number = i;
}

void Table::setReservationTimeFromDb(QTime time)
{
    reservation_time = time;
}
