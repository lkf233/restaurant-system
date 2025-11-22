#include "admitleave.h"
#include "ui_admitleave.h"
#include "query.h"
#include "QString"
#include "QDebug"
#include "QMessageBox"
#include "QFile"
#include <QDebug>
#include <QTimer>
#include "checkleave.h"
#include <QPainter>
#include <QIcon>

void AdmitLeave::paintEvent(QPaintEvent *event)
{
    //创建画家，制定绘画设备
    QPainter painter(this);
    //创建QPixmap对象
    QPixmap pix;
    //加载图片
    pix.load(":/b.jpg");
    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

}

AdmitLeave::AdmitLeave(QString name1,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdmitLeave)
{
    ui->setupUi(this);
name =name1;

    //配置主场景

    //设置固定大小
    setFixedSize(750,427);

    //设置图标
    setWindowIcon(QIcon(":/t.jpg"));

    //设置标题
    setWindowTitle("休假许可");

    set(ui->confirm);
    set(ui->return_2);

     setWindowTitle("休假许可");

     setWindowIcon(QIcon(":/icon.jpg"));

    connect(ui->confirm,&QPushButton::clicked,[=](){

        on_btn_changedata_del_clicked();


        });
    connect(ui->return_2,&QPushButton::clicked,[=](){

        //延时进入评论界面
        QTimer::singleShot(100,this,[=](){

        //自身隐藏
        this->hide();

        //显示评论界面
        CheckLeave *checkleave = new CheckLeave(name);
        checkleave->show();

        });

        });
}

AdmitLeave::~AdmitLeave()
{
    delete ui;
    if(readfile()==-1)
        {
            this->close();
            QMessageBox::critical(this,"错误","文件读取失败!","确认");
        }
}


int AdmitLeave::readfile()
{
    stuff_line.clear();
    QFile file("D:/Qt profile/new/leave.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return -1;
    }
    QTextStream in(&file);
    while (!in.atEnd())
    {
       QString line=in.readLine();
       stuff_line.append(line);
    }
    file.close();
    return 0;
}

void AdmitLeave::writeIn(QString information)
{
    this->ui->name->clear();

    this->ui->name->setFocus();

    QFile mFile("/Users/jessicawen/Desktop/leave.txt");
    if(!mFile.open(QIODevice::Append|QIODevice::Text))
    {
        QMessageBox::critical(this,"错误","文件打开失败，信息没有写入","确认");
        return;
    }
    QTextStream out(&mFile);
    out<<information<<"\n";
    mFile.flush();
    mFile.close();
}

void AdmitLeave::on_btn_changedata_del_clicked()
{
    if(ui->name->isModified()==false)
        QMessageBox::critical(this,"Error","请输入一个有效的账号ID");
    else{
    int flag = 0;
    QString strAll;
    QStringList strList;
    QFile readFile("D:/Qt profile/new/leave.txt");		//PATH是自定义读取文件的地址
    if(readFile.open((QIODevice::ReadOnly|QIODevice::Text)))
             {
                 //把文件所有信息读出来
                 QTextStream stream(&readFile);
                 strAll=stream.readAll();
             }
             readFile.close();

             QFile writeFile("D:/Qt profile/new/leave.txt");	//PATH是自定义写文件的地址
             if(writeFile.open(QIODevice::WriteOnly|QIODevice::Text))
             {
                     QTextStream stream(&writeFile);
                     strList=strAll.split("\n");           //以换行符为基准分割文本
                     for(int i=0;i<strList.count();i++)    //遍历每一行
                     {

                         if(strList.at(i).contains(ui->name->text()))
                         {
                             while(flag!=1){
                             QString tempStr=strList.at(0);
                             tempStr.replace(0,tempStr.length(),"");
//                             stream<<tempStr<<'\n';
                             QMessageBox::information(this,"通知","销假成功！","确认");
                             flag = 1;
                             }
                         }

                         //如果没有找到要替换的内容，照常写入
                         else
                         {
                             if(i==strList.count()-1)
                             {
                                stream<<strList.at(i);
                             }
                             else
                             {
                                stream<<strList.at(i)<<'\n';
                             }

                         }
                     }
                     if(flag == 0) QMessageBox::critical(this,"错误","无该请假信息，请重试！","确认");
             }
             writeFile.close();
    }
}

void AdmitLeave::on_pushButton_clicked()
{
    this->ui->name->setText(name1);

}

void AdmitLeave::set(QPushButton* m)
{
    m->setStyleSheet(
                        //正常状态样式
                        "QPushButton{"
                        "background-color:rgba(100,225,100,30);"//背景色（也可以设置图片）
                        "border-style:outset;"                  //边框样式（inset/outset）
                        "border-width:4px;"                     //边框宽度像素
                        "border-radius:10px;"                   //边框圆角半径像素
                        "border-color:rgba(255,255,255,30);"    //边框颜色
                        "padding:6px;"                          //填衬
                        "}"
                        //鼠标按下样式
                        "QPushButton:pressed{"
                        "background-color:rgba(100,255,100,200);"
                        "border-color:rgba(255,255,255,30);"
                        "border-style:inset;"
                        "color:rgba(0,0,0,100);"
                        "}"
                        //鼠标悬停样式
                        "QPushButton:hover{"
                        "background-color:rgba(100,255,100,100);"
                        "border-color:rgba(255,255,255,200);"
                        "color:rgba(0,0,0,200);"
                        "}");
}
