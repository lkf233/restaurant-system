#ifndef SHOPPINGSCENE_H
#define SHOPPINGSCENE_H

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

//#include "menuscene.h"
namespace Ui {
class ShoppingScene;
}

class ShoppingScene : public QWidget
{
    Q_OBJECT

public:
    explicit ShoppingScene(QString name1,QWidget *parent = nullptr);
    ~ShoppingScene();
     void paintEvent(QPaintEvent *);
    void setBtn();
     void connectDB();

     QString name;
     //MenuScene *menuscene();

private slots:
     void on_pushButton_clicked();

     void printDishes(QList<bool>);
     void printSum(QList<bool>);
private:
    Ui::ShoppingScene *ui;
};

#endif // SHOPPINGSCENE_H
