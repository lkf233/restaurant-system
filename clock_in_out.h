#ifndef CLOCK_IN_OUT_H
#define CLOCK_IN_OUT_H

#include <QWidget>
#include <QTime>
#include <QPainter>

namespace Ui {
class Clock_in_out;
}

class Clock_in_out : public QWidget
{
    Q_OBJECT

public:
    explicit Clock_in_out(QString name1,QWidget *parent = nullptr);
    QString name;
    ~Clock_in_out();
    void paintEvent(QPaintEvent *);
    void set_job(QString);//设置进入此界面的员工岗位信息
    void show_led(QTime);
    void getCheck_in_out();//从数据库中获得当前员工的上班状态
    //void endOfDay();//判断今天是否结束，并处理相应时间的加和
    void setName(QString);
    void setBtn();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();
    void onTimeOut();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Clock_in_out *ui;
    int job = 0;
    bool check_in_out = false;
    QTime out_time ;
    QTime in_time ;
    QTime this_time;
    QTime last_time;
    QTime today_time;

    int this_timeMs = 0;
};

#endif // CLOCK_IN_OUT_H
