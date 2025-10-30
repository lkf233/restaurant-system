#include "paymentscene.h"
#include "shoppingscene.h"
#include "menuscene.h"
#include "ui_paymentscene.h"
#include "gotocomment.h"

PaymentScene::PaymentScene(int job1,QString name1,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PaymentScene)
{
    ui->setupUi(this);
   // ui->setupUi(this);
    name=name1;
    job = job1;
    qDebug()<<"paymantjob:"<<job;
  setWindowTitle("餐厅管理系统");
    setWindowIcon(QIcon(":/image/shopping.png"));
  ui->listWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
   connect(ui->back,&QPushButton::clicked,[this](){
       MenuScene *ms=new MenuScene(name);
       QString jobName;
       if(job == 1)
       {
           jobName = "servant";
       }
       else if (job == 2) {
           jobName = "chef";
       }
       else if(job ==3)
       {
           jobName = "warehouse";
       }
       else if(job == 4)
       {
           jobName = "manager";
       }
       else if(job == 5)
       {
           jobName = "customer";
       }
       ms->set_job(jobName);
       ms->show();
        this->hide();
  });


   connect(ui->ok,&QPushButton::clicked,[this](){
       //decreaseMaterial();
       GoToComment *dialog=new GoToComment(job,name);
   QTimer::singleShot(400,this,[=](){
       this->hide();
      dialog->show();
     });

});

   setBtn();

}
void PaymentScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}



PaymentScene::~PaymentScene()
{
    delete ui;
}

void PaymentScene::printInfo(QList<bool>list)
{
    ui->listWidget->clear();
    int n=MenuScene::getNumberOfDishes();
    int sum=0;
    double discount=0.88;
     int count=0;
   for(int i=0;i<n;i++){
       if(list[i]){
            QString sql;
            sql = QString("select * from  menu "
                          " where number = '%0' ").arg(i+1);
            QSqlQuery query;
            query.exec(sql);

              query.first();
            sum+=query.value(5).toString().toInt();

     }
    }
     // ui->listWidget->clear();

      ui->listWidget->addItem("总价 : "+QString::number(sum));

      ui->listWidget->addItem(" ");
      ui->listWidget->addItem("折扣 : ");
       for(int i=0;i<n;i++){
           if(list[i]){
               count++;
                QString sql;
                sql = QString("select * from  menu "
                              " where number = '%0' ").arg(i+1);
                QSqlQuery query;
                query.exec(sql);

                query.first();
                 ui->listWidget->addItem("("+QString::number(count)+")"+query.value(1).toString());
                  ui->listWidget->addItem("最初价格 : "+query.value(5).toString()+"       折扣价格 : "+QString::number(query.value(5).toInt()*discount));

         }
        }
       ui->listWidget->addItem(" ");

       ui->listWidget->addItem("FINAL SUM : "+QString::number(sum*discount));
}

void PaymentScene::setBtn()
{

        ui->ok->setStyleSheet(
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


        ui->listWidget->setStyleSheet("QListWidget{border:1px solid gray; color:black; }"
                                    "QListWidget::Item{padding-top:20px; padding-bottom:4px; }"
                                    "QListWidget::Item:hover{background:skyblue; }"
                                    "QListWidget::item:selected{background:lightgray; color:red; }"
                                    "QListWidget::item:selected:!active{border-width:0px; background:lightgreen; }"
                                    );


}

void PaymentScene::decreaseMaterial(QList<bool> list)
{

     int n=MenuScene::getNumberOfDishes();
    for(int i=0;i<n;i++){
        if(list[i]){
             QString sql;
             sql = QString("select * from  menu "
                           " where number = '%0' ").arg(i+1);
             QSqlQuery query;
             query.exec(sql);
             query.first();
            QString s=query.value(3).toString();
           QStringList strList = s.split(" ");
            for(int i=0;i<strList.length();i++){
                QString sql1;
                sql1 = QString("select * from  material "
                              " where number = '%0' ").arg(strList.value(i).toInt());
                QSqlQuery query;
                bool ok=query.exec(sql1);
                query.first();
                int rest=query.value(2).toInt();

              if(ok){
                       QString sql2;
                        sql2=QString( "UPDATE material SET rest = '%1' WHERE number='%2'").arg(rest-1).arg(strList.value(i).toInt());
                    query.exec(sql2);
              }

            }

      }
     }
}


void PaymentScene::addSalesAmountInDay(QList<bool>list){
    int n=MenuScene::getNumberOfDishes();
   for(int i=0;i<n;i++){
       if(list[i]){
            QString sql;
            sql = QString("select * from  menu "
                          " where number = '%0' ").arg(i+1);
            QSqlQuery query;
            query.exec(sql);
            query.first();
            QString cs=query.value(1).toString();
            query.first();
           QString es=query.value(2).toString();
        query.first();

               QString sql2;
               QDateTime current_date_time =QDateTime::currentDateTime();
               QString current_m =current_date_time.toString("M");
               QString current_d =current_date_time.toString("dd");
     sql2=QString("select * from  SaleAmount_day "
                  " where date = '%0' and month='%2' and dishNameInEnglish='%3'").arg(current_d).arg(current_m).arg(es);
    bool ok2= query.exec(sql2);
    if(ok2){
        int initialPos = query.at();
          int pos = 0;
          if (query.last()){
              pos = query.at() + 1;
          }else{
              pos = 0;
          }
          // Important to restore initial pos
          query.seek(initialPos);
          if(pos==0){
              QString sql3;
              sql3=QString("insert into  SaleAmount_day  (month,date,dishNameInChinese ,dishNameInEnglish ,SaleAmount)"
                           " VALUES ('%1', '%2' , '%3' , '%4' , '%5')")
                     .arg(current_m).arg(current_d).arg(cs).arg(es).arg(1);
              bool ok3=query.exec(sql3);
              if(!ok3){
                  qDebug()<<"error3";
              }

    }
          else {
              QString sql4;
                query.exec(sql2);
                query.first();
                int am=query.value(4).toInt();
             //   qDebug()<<am;
              sql4=QString( "UPDATE  SaleAmount_day SET  SaleAmount = '%0' "
                            " WHERE date = '%1' AND month='%2' AND dishNameInEnglish='%3'").arg(am+1).arg(current_d).arg(current_m).arg(es);
         //     qDebug()<<sql4;
             bool ok4= query.exec(sql4);
             if(!ok4) qDebug()<<"error4";
                query.exec(sql2);
                query.first();
            //   qDebug()<<query.value(4).toInt();
          }

     }
    else qDebug()<<"error 2";
           }

             }

           }

void PaymentScene::addSalesAmountInMonth(QList<bool> list){
    int n=MenuScene::getNumberOfDishes();
   for(int i=0;i<n;i++){
       if(list[i]){
            QString sql;
            sql = QString("select * from  menu "
                          " where number = '%0' ").arg(i+1);
            QSqlQuery query;
            query.exec(sql);
            query.first();
            QString cs=query.value(1).toString();
            query.first();
           QString es=query.value(2).toString();
        query.first();

               QString sql2;
               QDateTime current_date_time =QDateTime::currentDateTime();
               QString current_m =current_date_time.toString("M");
     sql2=QString("select * from  SaleAmount_month "
                  " where month='%0' and dishNameInEnglish='%1'").arg(current_m).arg(es);
    bool ok2= query.exec(sql2);
    if(ok2){
        int initialPos = query.at();
          int pos = 0;
          if (query.last()){
              pos = query.at() + 1;
          }else{
              pos = 0;
          }
          // Important to restore initial pos
          query.seek(initialPos);
          if(pos==0){
              QString sql3;
              sql3=QString("insert into  SaleAmount_month (month,dishNameInChinese ,dishNameInEnglish ,SaleAmount)"
                           " VALUES ('%1', '%2' , '%3' , '%4' )")
                     .arg(current_m).arg(cs).arg(es).arg(1);
              bool ok3=query.exec(sql3);
              if(!ok3){
                  qDebug()<<"error3";
              }

    }
          else {
              QString sql4;
                query.exec(sql2);
                query.first();
                int am=query.value(3).toInt();
             // qDebug()<<am;
              sql4=QString("UPDATE  SaleAmount_month SET  SaleAmount = '%0' "
                           " WHERE  month='%2' AND dishNameInEnglish='%3'").arg(am+1).arg(current_m).arg(es);
              bool ok4=query.exec(sql4);
           //   qDebug()<<sql4;
             if(!ok4) qDebug()<<"error4";

                query.exec(sql2);
                query.first();
           //    qDebug()<<query.value(3).toInt();
          }

     }
    else qDebug()<<"error 2";
           }

             }
}

void PaymentScene::set_job(int a)
{
    job = a;
    qDebug()<<"patment setjob"<<job;
}

