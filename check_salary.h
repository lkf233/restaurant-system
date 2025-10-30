#ifndef CHECK_SALARY_H
#define CHECK_SALARY_H
#include <QTime>
#include <QWidget>
#include <QPainter>

namespace Ui {
class Check_Salary;
}

class Check_Salary : public QWidget
{
    Q_OBJECT

public:

    explicit Check_Salary(QString name1,QWidget *parent = nullptr);
    ~Check_Salary();
    void paintEvent(QPaintEvent *);
    void set_job(QString);//设置进入此界面的员工岗位信息
    void show_salary();
    QString getBasicSalary();//获得基础工资
    //int getMonthlySaleSalary();//获得月销量相关奖金
    QTime getMonthWorkTime();//获得月工作时间
    qint64 getMonthWorkSalary();//获得月工作时长奖金
    void setName(QString);
    void setBtn();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Check_Salary *ui;
    int job = 0;
    QString name ;//测试用，是个chef
};

#endif // CHECK_SALARY_H
