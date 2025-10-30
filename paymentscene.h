#ifndef PAYMENTSCENE_H
#define PAYMENTSCENE_H

#include <QWidget>

#include <QApplication>
#include <QTextCodec>
#include<QAction>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QTime>
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
#include<QVariant>
#include<QPropertyAnimation>
#include<QTimer>
#include<QList>
#include<QLineEdit>
#include<QSqlRecord>
namespace Ui {
class PaymentScene;
}

class PaymentScene : public QWidget
{
    Q_OBJECT

public:

    explicit PaymentScene(int job1,QString name1,QWidget *parent = nullptr);
    ~PaymentScene();
  void paintEvent(QPaintEvent *);
  void setBtn();
  QString name;
  void set_job(int);

private:
    friend class MenuScene;
    Ui::PaymentScene *ui;
    int job = 0;

  private  slots:
   void decreaseMaterial(QList<bool>);
   void addSalesAmountInDay(QList<bool>);
   void addSalesAmountInMonth(QList<bool>);
   void printInfo(QList<bool>);
};

#endif // PAYMENTSCENE_H
