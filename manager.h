#ifndef MANAGER_H
#define MANAGER_H
#include "employee.h"
#include <QString>
class manager:public Employee
{
public:
    manager();
    manager(QString);
    int getSeasonSalary() override;
    int getMonthlySalary() override;
private:
    QString name;
};

#endif // MANAGER_H
