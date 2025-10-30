#ifndef SERVANT_H
#define SERVANT_H
#include "employee.h"
#include <QString>

class servant:public Employee
{
public:
    servant();
    servant(QString);
    int getSeasonSalary() override;
    int getMonthlySalary() override;
private:
    QString name;
};

#endif // SERVANT_H
