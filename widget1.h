#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "operationondishes.h"
#include <QPushButton>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget1; }
QT_END_NAMESPACE

class Widget1 : public QWidget
{
    Q_OBJECT

public:


    Widget1(QString name1,QWidget *parent = nullptr);
    ~Widget1();

    void paintEvent(QPaintEvent *event);

     void setName(QString name1);
     void set(QPushButton* m);

private slots:

    void on_pushButton_pressed();


    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();



    void on_pushButton_5_clicked();

private:
    Ui::Widget1 *ui;
    QString name;

};
#endif // WIDGET_H
