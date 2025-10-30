#ifndef CHEF_H
#define CHEF_H
#include "employee.h"
#include <QString>

class chef:public Employee
{
public:
    chef();
    chef(QString);
    int getSeasonSalary() override;
    int getMonthlySalary() override;
private:
    QString name;
};

#endif // CHEF_H
