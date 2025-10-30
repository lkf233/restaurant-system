#include "button.h"
#include<QPushButton>
#include<QDebug>
#include<QSize>
#include<QPropertyAnimation>

/*shoppingButton::ShoppingButton(QPushButton *parent) : QPushButton(parent)
{

}*/

button::button(QString normalImg, QString pressImg)
{
    this->normalImagePath=normalImg;
    this->pressImagePath=pressImg;

    QPixmap pix;
    bool ret= pix.load(normalImg);
    if(!ret)
    {
        qDebug()<<"Errors in loading.";
        return;
    }

    //设置图片固定大小
    this->setFixedSize(150,300);
    //样式
    this->setStyleSheet("QPushButton{border:0px;}");
    //图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(150,300));
}


void button::zoom1()
{
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    //开始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //弹跳效果
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

void button::zoom2()
{
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    //开始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //弹跳效果
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}
