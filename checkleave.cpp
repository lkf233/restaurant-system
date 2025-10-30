#include "checkleave.h"
#include "administratorhomepage.h"
#include "ui_checkleave.h"
#include "query.h"
#include "admitleave.h"
#include <QIcon>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <QTimer>
#include <QPainter>
#include <QPushButton>
#include <QMessageBox>

void CheckLeave::paintEvent(QPaintEvent *event)
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
CheckLeave::CheckLeave(QString name1,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CheckLeave)
{
    ui->setupUi(this);
    //配置主场景
    name = name1;



    set(ui->return_2);
    set(ui->query);

    //设置固定大小
    setFixedSize(750,427);

    //设置图标

    setWindowIcon(QIcon(":/icon.jpg"));
    //设置标题
    setWindowTitle("查看休假审批情况");

    this->model = new QStandardItemModel;

    this->model->setHorizontalHeaderItem(0,new QStandardItem("姓名"));
    this->model->setHorizontalHeaderItem(1,new QStandardItem("离开时间"));
    this->model->setHorizontalHeaderItem(2,new QStandardItem("返回时间"));
    this->model->setHorizontalHeaderItem(3,new QStandardItem("原因"));

    this->ui->tableView->setModel(model);
    this->ui->tableView->setColumnWidth(0,100);
    this->ui->tableView->setColumnWidth(1,200);
    this->ui->tableView->setColumnWidth(2,200);
    this->ui->tableView->setColumnWidth(3,300);

    if(readfile()==-1)
    {
        this->close();
        QMessageBox::critical(this,"错误","文件读取失败","确认");
    }

    connect(ui->query,&QPushButton::clicked,[=](){

        //自身隐藏
        this->hide();
        Query *query = new Query(name);
        query->show();

        });

    connect(ui->admit,&QPushButton::clicked,[=](){

        //延时进入评论界面
        QTimer::singleShot(100,this,[=](){

        //自身隐藏
        this->hide();

        //显示评论界面
        AdmitLeave *admitleave = new AdmitLeave(name);
        admitleave->show();

        });

        });

    connect(ui->return_2,&QPushButton::clicked,[=](){

        //延时进入评论界面
        QTimer::singleShot(100,this,[=](){

        //自身隐藏
        this->hide();

        //显示评论界面
        administratorHomePage *administratorhomepage = new administratorHomePage(name);
        administratorhomepage->show();

        });

        });

}


CheckLeave::~CheckLeave()
{
    delete ui;
}

void CheckLeave::reset()
{
    this->model->setHorizontalHeaderItem(0,new QStandardItem("姓名"));
    this->model->setHorizontalHeaderItem(1,new QStandardItem("离开时间"));
    this->model->setHorizontalHeaderItem(2,new QStandardItem("返回时间"));
    this->model->setHorizontalHeaderItem(3,new QStandardItem("原因"));

    this->ui->tableView->setColumnWidth(0,100);
    this->ui->tableView->setColumnWidth(1,200);
    this->ui->tableView->setColumnWidth(2,200);
    this->ui->tableView->setColumnWidth(3,300);
}

int CheckLeave::readfile()
{
    stuff_line.clear();
    QFile file("C:/Users/HUAWEI/Desktop/new/new/leave.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return -1;
    }
    QTextStream in(&file);
    int row = -1;
    while(!in.atEnd())
    {
        QString line = in.readLine();
        stuff_line.append(line);
        QStringList subs=line.split(" ");
                for(int i=0;i<subs.length();i++)
                {
                   this->model->setItem(row,i,new QStandardItem(subs.at(i)));
                }
                row++;
    }
    file.close();
        return 0;
}

void CheckLeave::display(int row, QStringList score_line)
{
    int i=0;
    for (i=0;i<score_line.length();i++)
    {
        this->model->setItem(row,i,new QStandardItem(score_line.at(i)));
    }
}


void CheckLeave::set(QPushButton* m)
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

