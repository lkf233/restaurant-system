#include "widget1.h"
#include "login.h"
#include "servant_open.h"

#include <QApplication>

int main(int argc, char *argv[])
{
     QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
     QString dsn = QString::fromLocal8Bit("restaurant");//你配置的Data Source
     db.setHostName("192.168.56.102");//你的IP地址
     db.setDatabaseName(dsn);
     db.setUserName("my_root"); //用户名
     db.setPassword("my_root@123");//密码
     db.setPort(26000); //opengauss端口号为26000
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    Login w;
    w.show();
    return a.exec();
}
