#ifndef CHECKSALEAMOUNT_H
#define CHECKSALEAMOUNT_H

#include <QDialog>

namespace Ui {
class checkSaleAmount;
}

class checkSaleAmount : public QDialog
{
    Q_OBJECT

public:
    explicit checkSaleAmount(QString name1,QWidget *parent = nullptr);
    QString name;
    ~checkSaleAmount();
 void paintEvent(QPaintEvent *);
 void onShowDb();
 void clearTableData();//清除
 QList<QStringList>selectDataFromBase();
 void appendRowData(QStringList rowData);
 void set_job(QString);//设置进入此界面的员工岗位信息
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::checkSaleAmount *ui;
    int job = 0;
};

#endif // CHECKSALEAMOUNT_H
