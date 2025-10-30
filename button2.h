#ifndef BUTTON2_H
#define BUTTON2_H

#include <QPushButton>

class button2 : public QPushButton
{
    Q_OBJECT
public:
   // explicit ShoppingButton(QPushButton *parent = nullptr);
   button2(QString, QString pressing="");
    //实现弹起特效
    void zoom1();
    void zoom2();

    //默认路径 按下后显示的路径
    QString normalImagePath;
    QString pressImagePath;

signals:

};

#endif // BUTTON2_H
