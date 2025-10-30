#ifndef CHANGE_PASSWORD_H
#define CHANGE_PASSWORD_H

#include <QWidget>
#include <QPainter>

namespace Ui {
class Change_Password;
}

class Change_Password : public QWidget
{
    Q_OBJECT

public:
    explicit Change_Password(QString name1,QWidget *parent = nullptr);
    QString name;
    ~Change_Password();
    void paintEvent(QPaintEvent *);
    void set_job(QString);//设置进入此界面的员工岗位信息
    void setBtn();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    //void on_pushButton_4_clicked();

    void on_pushButton_clicked();

private:
    Ui::Change_Password *ui;
    int job = 0;
    QString id = "";
    QString password = "";
    bool canChange = false;
};

#endif // CHANGE_PASSWORD_H
