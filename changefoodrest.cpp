#include "changefoodrest.h"
#include "ui_changefoodrest.h"
#include "changefoodamount.h"
#include <QApplication>
#include <QTextCodec>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QTime>
#include <QtSql/QSqlError>
#include <QtDebug>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlRecord>
#include <QPainter>
#include <QMessageBox>
void changeFoodRest::paintEvent(QPaintEvent *)
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
changeFoodRest::changeFoodRest(QString name1,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changeFoodRest)
{
    name=name1;
    ui->setupUi(this);
      setFixedSize(360,250);
      setWindowTitle("修改食材");

      setWindowIcon(QIcon(":/icon.jpg"));
}

changeFoodRest::~changeFoodRest()
{
    delete ui;
}

void changeFoodRest::on_pushButton_2_clicked()
{
    changeFoodAmount change(name);
    this->hide();
    change.show();
}

void changeFoodRest::on_pushButton_clicked()
{

        QVariantMap stuInfo;

        QString rest=ui->lineEdit->text();
       QString  sel=ui->comboBox->currentText();

     stuInfo.insert("rest",rest);
      stuInfo.insert("sel",sel);

     emit signalStuInfo(stuInfo);
    close();


}
void changeFoodRest::clearData()
{

    ui->lineEdit->clear();

}

void changeFoodRest::closeEvent(QCloseEvent *event)
{
    clearData();
}
