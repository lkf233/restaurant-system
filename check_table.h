#ifndef CHECK_TABLE_H
#define CHECK_TABLE_H
#include "table.h"
#include <QWidget>
#include <QPainter>

namespace Ui {
class check_table;
}

class check_table : public QWidget
{
    Q_OBJECT

public:
    explicit check_table(QString name1,QWidget *parent = nullptr);
    QString name;
    ~check_table();
    void paintEvent(QPaintEvent *);
    void set_job(QString);//设置进入此界面的员工岗位信息

    void setTablet(Table);
    void setTable(int);
    void setButtonColor(Table);
    void refresh();//刷新

    void setBtn();
private slots:
    void on_pushButton_21_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_24_clicked();

private:
    Ui::check_table *ui;
    int job = 0;
    Table tables[20];



};

#endif // CHECK_TABLE_H
