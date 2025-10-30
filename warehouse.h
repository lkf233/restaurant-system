#ifndef WAREHOUSE_H
#define WAREHOUSE_H
#include "employee.h"
#include <QString>

class warehouse:public Employee
{
public:
    warehouse();
    warehouse(QString);
    int getSeasonSalary() override;
    int getMonthlySalary() override;
private:
    QString name;
};

#endif // WAREHOUSE_H
