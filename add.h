#ifndef ADD_H
#define ADD_H
#include <QVariantMap>
#include <QDialog>
#include "operationondishes.h"
namespace Ui {
class Add;
}

class Add : public QDialog
{
    Q_OBJECT

public:
    /**构造器用于初始化*/

    explicit Add(QString name1,QWidget *parent = nullptr);
    QString name;
    /**调用析构函数可以收回空间*/
    ~Add();

  void paintEvent(QPaintEvent *);
 void setEditData(QStringList rowData);
signals:
    void signalStuInfo(QVariantMap stuInfo);
private slots:
    void on_pushButton_2_clicked();
  void on_pushButton_clicked();


private:
    Ui::Add *ui;
    /**用于清除dialog内所有的数据*/
    void clearData();


};

#endif // ADD_H
