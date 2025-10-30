#ifndef VIEWCOMMENT_H
#define VIEWCOMMENT_H

#include <QWidget>
#include<QVector>
#include "shoppingscene.h"

#include<QComboBox>
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
class ViewComment;
}

class ViewComment : public QWidget
{
    Q_OBJECT

public:
    explicit ViewComment(QString name1,QWidget *parent = nullptr);
    QString name;
    ~ViewComment();
    void paintEvent(QPaintEvent *);
    void setBtn();
    void printComment();
    void printAverage();
    void set_job(QString);//设置进入此界面的员工岗位信息
private slots:
    void on_pushButton_clicked();

private:
    Ui::ViewComment *ui;
    int job = 0;
};

#endif // VIEWCOMMENT_H
