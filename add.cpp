#include "add.h"
#include "ui_add.h"
#include "operationondishes.h"
#include <QPainter>
/**调用构造函数，设置界面大小，实现继承*/
Add::Add(QString name1,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add)
{
    name=name1;
     setWindowTitle("增加菜品");

     setWindowIcon(QIcon(":/icon.jpg"));
    ui->setupUi(this);
     setFixedSize(600,500);
}

Add::~Add()/**调用析构函数 收回ui空间*/
{
    delete ui;
}
/**函数设计当按钮点击后，OperationOnDishes 的类的窗口打开，并且该窗口隐藏*/
/**需要创立OperationOnDishes 的实例对象*/
void Add::on_pushButton_2_clicked()
{
    OperationOnDishes *operation=new OperationOnDishes(name);
    this->close();
    operation->show();
}
/**函数创建一个QPanter 的对象,并调用load()函数，加载了背景图，调用drawPixmap函数，设置了背景图的布局，实现了背景图的设置*/
void Add::paintEvent(QPaintEvent *)
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
/**函数每一个控件设置了它的值，调用setText()函数或者是setCurrentText函数将传入的QstringList类型的数据写入当中*/
void Add::setEditData(QStringList rowData)
{
    ui->lineEdit_2->setText(rowData.at(0));
    ui->lineEdit_5->setText(rowData.at(1));
    ui->lineEdit->setText(rowData.at(2));;
    ui->lineEdit_3->setText(rowData.at(3));;
   ui->comboBox_2->setCurrentText(rowData.at(4));
    ui->comboBox->setCurrentText(rowData.at(5));
}
/**函数实现的对所有空间内容的清除操作，调用控件内部的clear()函数完成*/
void Add::clearData()
{
    ui->lineEdit_2->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit->clear();
    ui->lineEdit_3->clear();
    ui->comboBox_2->clear();
    ui->comboBox->clear();
}

void Add::on_pushButton_clicked()
{
    QVariantMap stuInfo;
    QString menuinChinese=ui->lineEdit_2->text();
    QString menuinEnglish=ui->lineEdit_5->text();
    QString material=ui->lineEdit->text();
    QString price=ui->lineEdit_3->text();
     QString style=ui->comboBox_2->currentText();
      QString spicy=ui->comboBox->currentText();
 stuInfo.insert("menuinChinese", menuinChinese);
 stuInfo.insert("menuinEnglish",menuinEnglish);
 stuInfo.insert("material",material);
 stuInfo.insert("price",price);
 stuInfo.insert("style",style);
 stuInfo.insert("spicy",spicy);
 emit signalStuInfo(stuInfo);
close();

}
