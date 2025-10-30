#ifndef SELECTWAY_H
#define SELECTWAY_H

#include <QDialog>
#include <QWidget>
#include <QApplication>
#include <QTextCodec>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QTime>
#include <QtSql/QSqlError>
#include <QtDebug>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlRecord>
namespace Ui {
class SelectWay;
}

class SelectWay : public QDialog
{
    Q_OBJECT

public:
    explicit SelectWay(QString name1,QWidget *parent = nullptr);
    QString name;
    ~SelectWay();
 void paintEvent(QPaintEvent *);
    void set_job(QString);//设置进入此界面的员工岗位信息
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::SelectWay *ui;
    int job = 0;
};

#endif // SELECTWAY_H
