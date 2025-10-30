#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>


class button : public QPushButton
{
    Q_OBJECT
public:
   // explicit ShoppingButton(QPushButton *parent = nullptr);
    button(QString, QString pressing="");
    //实现弹起特效
    void zoom1();
    void zoom2();

    //默认路径 按下后显示的路径
    QString normalImagePath;
    QString pressImagePath;

signals:

};

#endif // BUTTON_H
