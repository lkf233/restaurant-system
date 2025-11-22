#include "viewcomment.h"
#include "ui_viewcomment.h"
#include "widget1.h"
#include "stockwidget.h"
#include "administratorhomepage.h"
#include "servant_open.h"
#include "menuscene.h"

ViewComment::ViewComment(QString name1,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewComment)
{
    name = name1;
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,[this](){
        QTimer::singleShot(400,this,[=](){
          this->hide();
          });
     });
    setWindowTitle("评论");

    setWindowIcon(QIcon(":/icon.jpg"));
    setBtn();
    printComment();
    printAverage();
}

ViewComment::~ViewComment()
{
    delete ui;
}

void ViewComment::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void ViewComment::setBtn()
{
    ui->pushButton->setStyleSheet(
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
                "}" );

}

void ViewComment::printComment()
{

    int nRow=0;

           QString sql;
            sql = QString("select time,id,comments from  comments " );
            QSqlQuery query;
            bool ok= query.exec(sql);
            query.last();//指向最后一条记录 打印行数等于总行数加一
            nRow = query.at() + 1;

              if(ok){
                  query.first();
                  for(int i=0;i<nRow;i++){

          ui->listWidget->addItem(query.value(0).toString()+
                                  "     "+
                                  query.value(1).toString()+
                                  "     "+
                                  query.value(2).toString());
  query.next();
              }
              }


}

void ViewComment::printAverage()
{
    QString s;
    int nRow=0;
    double total=0;
   double service=0;
    double environment=0;
    double taste=0;
    double cost=0;


           QString sql;
            sql = QString("select total from  comments " );
            QSqlQuery query;
            bool ok= query.exec(sql);
            query.last();//指向最后一条记录 打印行数等于总行数加一
            nRow = query.at() + 1;
              if(ok){
                  query.first();
                  for(int i=0;i<nRow;i++){
                      total+=query.value(0).toDouble();
                   }
               }

             sql = QString("select cost from  comments " );
             ok= query.exec(sql);

               if(ok){
                   query.first();
                   for(int i=0;i<nRow;i++){
                      cost+=query.value(0).toDouble();
                    }
               }

                   sql = QString("select taste from  comments " );
                   ok= query.exec(sql);

                     if(ok){
                         query.first();
                         for(int i=0;i<nRow;i++){
                             taste+=query.value(0).toDouble();
                          }
                     }

                         sql = QString("select environment from  comments " );
                         ok= query.exec(sql);

                           if(ok){
                               query.first();
                               for(int i=0;i<nRow;i++){
                                   environment+=query.value(0).toDouble();
                                }
                           }

                               sql = QString("select service from  comments " );
                               ok= query.exec(sql);

                                 if(ok){
                                     query.first();
                                     for(int i=0;i<nRow;i++){
                                         service+=query.value(0).toDouble();
                                      }

                                 }

                               s=QString("AVERAGE :    TOTAL : "+QString::number(total/nRow)
                                         +"    TASTE : "+QString::number(taste/nRow)
                                         +"    SERVICE : "+QString::number(service/nRow)
                                         +"    ENVIRONMENT : "+QString::number(environment/nRow)
                                         +"    COST : "+QString::number(cost/nRow));
                    ui->average->setText(s);
}

void ViewComment::set_job(QString job1)
{
    //进入此页面的身份是服务员
    if(job1 == "servant")
    {
        job = 1;
        qDebug()<<job;
    }
    //进入此页面的身份是厨师
    else if(job1 == "chef")
    {
        job = 2;
    }
    //进入此页面的身份是仓管
    else if(job1 == "warehouse")//查看一下仓管到底叫啥
    {
        job = 3;
    }
    //进入此页面的身份是管理员
    else if(job1 == "manager")
    {
        job = 4;
    }
    //进入此页面的身份是顾客
    else if(job1 == "customer")
    {
        job = 5;
    }
    else
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::critical(this, tr("QMessageBox::critical()"),
                                            "无效的职位",
                                            QMessageBox::Abort | QMessageBox::Retry | QMessageBox::Ignore);

    }
}

//返回原岗位界面
void ViewComment::on_pushButton_clicked()
{
            //延时进入界面
            QTimer::singleShot(500,this,[=](){
            //自身隐藏
            this->hide();
            //返回原始界面
            //需要获得进入本界面时的员工岗位信息
                qDebug()<<job;
            switch(job)
            {
            case 1 ://进入此页面的身份是服务员//返回服务员界面
            {Servant_open *servant = new Servant_open(name);
                servant->show();
                break;}
           case 2://进入此页面的身份是厨师
               { Widget1 *chef = new Widget1(name);
                chef->show();
                break;}

           case 3 ://进入此页面的身份是仓管
            {
                Stockwidget *stock=new Stockwidget(name);
                stock->show();
                 this->hide();
                break;
            }
            case 4 ://进入此页面的身份是管理员
            {
                administratorHomePage *manager = new administratorHomePage(name);
                manager->show();
                break;
            }
            case 5 ://进入此页面是顾客
            {
                MenuScene *customer = new MenuScene(name);
                customer->show();
                break;
            }
            default:
                qDebug()<<"wrong job!";
                break;
            }

            });

}
