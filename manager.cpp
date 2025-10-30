#include "manager.h"
#include "employee.h"
#include <QDate>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>

manager::manager()
{

}

manager::manager(QString a)
{
    name = a;
}

int manager::getSeasonSalary()
{
    int a = 400;//manager的季度奖金比其他人高，
    return a;
}

int manager::getMonthlySalary()
{
    int saleSalary = 0;//manager没有月销量奖金
     return saleSalary;
}
