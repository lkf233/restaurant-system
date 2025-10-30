#ifndef SHOPPINGBUTTON_H
#define SHOPPINGBUTTON_H

#include<QPushButton>

class ShoppingButton : public QPushButton
{
    Q_OBJECT
public:
   // explicit ShoppingButton(QPushButton *parent = nullptr);
    ShoppingButton(QString, QString pressing="");
    //实现弹起特效
    void zoom1();
    void zoom2();

    //默认路径 按下后显示的路径
    QString normalImagePath;
    QString pressImagePath;

signals:

};

#endif // SHOPPINGBUTTON_H
