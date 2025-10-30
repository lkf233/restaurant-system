#include "chef.h"
#include "employee.h"
#include <QDate>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>

chef::chef()
{

}

chef::chef(QString a)
{
    name = a;
}

int chef::getSeasonSalary()
{
    int a = 200;
    return a;
}

int chef::getMonthlySalary()
{
    QDate date = QDate::currentDate();
    int month = date.month();
    int sales = 0;
    QString basic_salary;
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
             if(q.exec(QString("select saleAmount from SaleAmount_month where month=%1").arg(month)))
             {
                 q.last();//指向最后一条记录 打印行数等于总行数加一
                int nRow = q.at() + 1;
                q.first();
               for(int i=0;i<nRow;i++)//找到了对应月份的相关销量
                 {
                     sales += q.value(0).toInt();
                     q.next();//不同菜品的月销量相加
                 }

             }
         }
     double rate = 0.1;//厨师的月销量奖金率
     int saleSalary = rate * sales;
     return saleSalary;
}
