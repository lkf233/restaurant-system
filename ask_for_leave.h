#ifndef ASK_FOR_LEAVE_H
#define ASK_FOR_LEAVE_H
#include <QString>
#include <QWidget>
#include <QDateTime>
#include <QFile>
#include <QPainter>
namespace Ui {
class Ask_for_leave;
}

class Ask_for_leave : public QWidget
{
    Q_OBJECT

public:
    Ask_for_leave(QString name1,QWidget *parent = nullptr);
    ~Ask_for_leave();
    void paintEvent(QPaintEvent *);
    void set_job(QString);//设置进入此界面的员工岗位信息
    void check_leaveStatus();//查看进入此页面的员工的请假状态

    void setName(QString);//设置员工名字
    void setBtn();//按钮样式


private slots:
    void on_pushButton_clicked();

    void on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

    void on_dateTimeEdit_2_dateTimeChanged(const QDateTime &dateTime);

    void on_textBrowser_textChanged();

    void on_pushButton_2_clicked();

    void on_plainTextEdit_textChanged();

private:
    Ui::Ask_for_leave *ui;
    int job = 0;
    QDateTime leavetime;
    QDateTime backtime;
    QString leavetext ;
    QString name;

    //QFile file("D:/test.txt");
};

#endif // ASK_FOR_LEAVE_H
