#include "gotocomment.h"
#include "ui_gotocomment.h"
#include "customerlogin.h"
#include "menuscene.h"
#include <commentscene.h>

GoToComment::GoToComment(int job1,QString name1,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GoToComment)
{
    ui->setupUi(this);
    name=name1;
    job = job1;

//    qDebug()<<name;
    qDebug()<<"gotocommentjob:"<<job;
    setWindowTitle("点单");
    setWindowIcon(QIcon(":/image/shopping.png"));
    connect(ui->goto_2,&QPushButton::clicked,[this]()
    {
       if(job != 5)//不是顾客
       {
           QMessageBox::information(NULL, "提示", "非顾客，不可评论");
       }
       else{
        CommentScene *commentScene=new CommentScene(name);
    QTimer::singleShot(400,this,[=](){
      this->hide();
     commentScene->show();
      });
       }

 });
    //残忍拒绝，回到下单界面
    connect(ui->back,&QPushButton::clicked,[this](){
    MenuScene *menu = new MenuScene(name);
    QTimer::singleShot(400,this,[=](){
        QString jobStr;
        if(job == 1)
            jobStr = "servant";
        else if(job == 2)
            jobStr = "chef";
        else if(job == 3)
            jobStr = "warehouse";
        else if(job == 4)
            jobStr = "manager";
        else if(job == 5)
            jobStr = "customer";
       menu->set_job(jobStr);
      this->hide();
     menu->show();
      });

 });


    setBtn();
}

GoToComment::~GoToComment()
{
    delete ui;
}

void GoToComment::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void GoToComment::setBtn()
{
    ui->back->setStyleSheet(
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

    ui->goto_2->setStyleSheet(
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
