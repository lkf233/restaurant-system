#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <string>

class Employee
{
public:
    Employee();
    virtual int getSeasonSalary() = 0;
    virtual int getMonthlySalary() = 0;
};

#endif // EMPLOYEE_H
