#ifndef OPERATIONONDISHES_H
#define OPERATIONONDISHES_H

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
#include "widget1.h"
#include "add.h"
namespace Ui {
class OperationOnDishes;
}

class OperationOnDishes : public QWidget
{
    Q_OBJECT
    enum OperateType
       {
           Add ,
           Edit
       };

public:
    explicit OperationOnDishes(QString name1,QWidget *parent = nullptr);
    QString name;
    ~OperationOnDishes();
    void onShowDb();
    void paintEvent(QPaintEvent *);
    void setTabCornerBtn();
    void appendRowData(QStringList rowData);
    QString getCurrentID();
    QStringList getCurrentRowData();
     QList<QStringList> selectDataFromBase();

     void set_job(QString);//设置进入此界面的员工岗位信息
private slots:
    void onBtnAdd();
  void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();
    void clearTableData();
   void ExecDelSql(QString id);
   void ExecEditSql(QVariantMap stuInfo);
   void ExecAddsql(QVariantMap stuInfo);



   void on_pushButton_4_clicked();

private:
    Ui::OperationOnDishes *ui;
    int job = 0;
     class Add* m_pAddStuDlg;

   void initAddDlg();
    OperateType m_operateType;




};

#endif // OPERATIONONDISHES_H
