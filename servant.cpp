#include "servant.h"
#include <QDate>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>

servant::servant()
{

}

servant::servant(QString a)
{
    name = a;
}

int servant::getSeasonSalary()
{
    int a = 200;
    return a;
}

int servant::getMonthlySalary()
{
    int saleSalary = 0;//servant没有月销量奖金
     return saleSalary;
}
