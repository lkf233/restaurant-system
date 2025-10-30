#include "modifymenu.h"
#include "ui_modifymenu.h"
#include "operationondishes.h"
#include <QPainter>
Modifymenu::Modifymenu(QString name1,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Modifymenu)
{
    name = name1;
    ui->setupUi(this);
    setWindowTitle("修改菜单");

    setWindowIcon(QIcon(":/icon.jpg"));
    setFixedSize(1200,700);
}

Modifymenu::~Modifymenu()
{
    delete ui;
}

void Modifymenu::on_pushButton_2_clicked()
{
    OperationOnDishes *operation=new OperationOnDishes(name);
    this->hide();
    operation->show();
}
void Modifymenu::paintEvent(QPaintEvent *)
{
    //创建画家，制定绘画设备
    QPainter painter(this);
    //创建QPixmap对象
    QPixmap pix;
    //加载图片
    pix.load(":/IMAGES/BACKGROUND");
    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);


}
