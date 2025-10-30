#ifndef MENUSCENE_H
#define MENUSCENE_H
#include <QWidget>
#include<QVector>
#include "shoppingscene.h"

#include<QComboBox>
#include<QRadioButton>
#include <QApplication>
#include <QTextCodec>
#include<QAction>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QTime>
#include<QVector>
#include <QtSql/QSqlError>
#include <QtDebug>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlRecord>
#include <QSqlTableModel>
#include<QPainter>
#include<QPixmap>
#include <QIcon>
#include<QTableWidget>
#include <QMessageBox>
#include<QCheckBox>
#include<QPropertyAnimation>
#include<QTimer>
#include<QVariant>
#include<QList>

namespace Ui {
class MenuScene;
}

class MenuScene : public QWidget
{
    Q_OBJECT

public:

    explicit MenuScene(QString name1,QWidget *parent = nullptr);
    ~MenuScene();
    void paintEvent(QPaintEvent *);
    void connectDB();
    void showMenu();
    void setCheckbox(int row, int col);
    void set_CheckBox();
    void setBtn();
    void setComboBox();
    void shoppingBtn();
    void connections();
    void set_job(QString);//设置进入此界面的员工岗位信息

   static  int getNumberOfDishes();
   QString name;
  ShoppingScene* shoppingScene=NULL;

private:
    friend class ShoppingScene;
    friend class PaymentScene;
    Ui::MenuScene *ui;
    int job = 0;

private slots:
    void search();
 //   void chooseOrder();
    void on_pushButton_clicked();

    //void on_comment_clicked();

    void on_pay_clicked();

signals:
    void sendName();
    void signalInfo(QList<bool>);
};

#endif // MENUSCENE_H
