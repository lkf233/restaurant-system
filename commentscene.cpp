#include "commentscene.h"
#include "ui_commentscene.h"
#include"aftercomment.h"
#include "customerlogin.h"
#include <QSqlError>
#include "customerlogin.h"
#include "widget1.h"
#include "stockwidget.h"
#include "administratorhomepage.h"
#include "servant_open.h"

CommentScene::CommentScene(QString name1,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommentScene)
{


    ui->setupUi(this);
    name = name1;
    setBtn();
    setSlider();
    changeLable();
    setWindowTitle("评论");
    setWindowIcon(QIcon(":/image/shopping.png"));
    ui->plainTextEdit->setPlaceholderText("字数超过10，会说英语多说点~");
    connect(ui->ok,&QPushButton::clicked,[this](){
     setComment();
});
    connect(ui->ok,&QPushButton::clicked,[this](){
        AfterComment *af=new AfterComment(name);
        QTimer::singleShot(400,this,[=](){
          this->hide();
         af->show();
          });

    });

    connect(ui->exit,&QPushButton::clicked,[this](){
    CustomerLogin *commentScene=new CustomerLogin();
    QTimer::singleShot(400,this,[=](){
      this->hide();
     commentScene->show();
      });

 });


}


CommentScene::~CommentScene()
{
    delete ui;
}

void CommentScene::changeLable()
{
    connect(ui->priceS,&QSlider::valueChanged,[this](){
        if(ui->priceS->value()==1) ui->price->setText("too expensive");
       if(ui->priceS->value()==2) ui->price->setText("勉强接受");
       if(ui->priceS->value()==3) ui->price->setText("平平无奇");
       if(ui->priceS->value()==4) ui->price->setText("挺不错的");
       if(ui->priceS->value()==5) ui->price->setText("perfect");
    });

    connect(ui->tasteS,&QSlider::valueChanged,[this](){
        if(ui->tasteS->value()==1) ui->taste_2->setText("吃不下去");
       if(ui->tasteS->value()==2) ui->taste_2->setText("勉强能吃");
       if(ui->tasteS->value()==3) ui->taste_2->setText("just so so");
       if(ui->tasteS->value()==4) ui->taste_2->setText("满分怕你骄傲");
       if(ui->tasteS->value()==5) ui->taste_2->setText("太好吃啦");
    });

    connect(ui->serviceS,&QSlider::valueChanged,[this](){
        if(ui->serviceS->value()==1) ui->service->setText("服务态度恶劣");
       if(ui->serviceS->value()==2) ui->service->setText("勉强接受");
       if(ui->serviceS->value()==3) ui->service->setText("一般般");
       if(ui->serviceS->value()==4) ui->service->setText("人美心善");
       if(ui->serviceS->value()==5) ui->service->setText("想加微信");
    });

    connect(ui->totalS,&QSlider::valueChanged,[this](){
        if(ui->totalS->value()==1) ui->total->setText("太失望啦");
       if(ui->totalS->value()==2) ui->total->setText("勉强可以");
       if(ui->totalS->value()==3) ui->total->setText("说得过去");
       if(ui->totalS->value()==4) ui->total->setText("良心商家");
       if(ui->totalS->value()==5) ui->total->setText("下次再来");
    });

    connect(ui->environmentS,&QSlider::valueChanged,[this](){
        if(ui->environmentS->value()==1) ui->environmrent->setText("terrible");
       if(ui->environmentS->value()==2) ui->environmrent->setText("勉强算好");
       if(ui->environmentS->value()==3) ui->environmrent->setText("平平无奇");
       if(ui->environmentS->value()==4) ui->environmrent->setText("蛮舒服的");
       if(ui->environmentS->value()==5) ui->environmrent->setText("想过来住");
    });
}

void CommentScene::setSlider(){
    ui->priceS->setTickPosition(QSlider::TicksAbove);
    ui->tasteS->setTickPosition(QSlider::TicksAbove);
    ui->totalS->setTickPosition(QSlider::TicksAbove);
    ui->environmentS->setTickPosition(QSlider::TicksAbove);
    ui->serviceS->setTickPosition(QSlider::TicksAbove);
    ui->priceS->setStyleSheet("  \
         QSlider::add-page:Horizontal\
         {     \
            background-color: rgb(87, 97, 106);\
            height:10px;\
         }\
         QSlider::sub-page:Horizontal \
        {\
            background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(231,80,229, 255), stop:1 rgba(7,208,255, 255));\
            height:10px;\
         }\
        QSlider::groove:Horizontal \
        {\
            background:transparent;\
            height:10px;\
        }\
        QSlider::handle:Horizontal \
        {\
            height: 30px;\
            width:8px;\
            border-image: url(:/images/ic_music_thumb.png);\
            margin: -8 0px; \
        }\
        ");
   ui->environmentS->setStyleSheet("  \
                                   QSlider::add-page:Horizontal\
                                   {     \
                                      background-color: rgb(87, 97, 106);\
                                      height:10px;\
                                   }\
                                   QSlider::sub-page:Horizontal \
                                  {\
                                      background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(231,80,229, 255), stop:1 rgba(7,208,255, 255));\
                                      height:10px;\
                                   }\
                                  QSlider::groove:Horizontal \
                                  {\
                                      background:transparent;\
                                      height:10px;\
                                  }\
                                  QSlider::handle:Horizontal \
                                  {\
                                      height: 30px;\
                                      width:8px;\
                                      border-image: url(:/images/ic_music_thumb.png);\
                                      margin: -8 0px; \
                                  }\
                                  ");
    ui->tasteS->setStyleSheet("  \
                                                             QSlider::add-page:Horizontal\
                                                             {     \
                                                                background-color: rgb(87, 97, 106);\
                                                                height:10px;\
                                                             }\
                                                             QSlider::sub-page:Horizontal \
                                                            {\
                                                                background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(231,80,229, 255), stop:1 rgba(7,208,255, 255));\
                                                                height:10px;\
                                                             }\
                                                            QSlider::groove:Horizontal \
                                                            {\
                                                                background:transparent;\
                                                                height:10px;\
                                                            }\
                                                            QSlider::handle:Horizontal \
                                                            {\
                                                                height: 30px;\
                                                                width:8px;\
                                                                border-image: url(:/images/ic_music_thumb.png);\
                                                                margin: -8 0px; \
                                                            }\
                                                            ");

                              ui->totalS->setStyleSheet("  \
                                   QSlider::add-page:Horizontal\
                                   {     \
                                      background-color: rgb(87, 97, 106);\
                                      height:10px;\
                                   }\
                                   QSlider::sub-page:Horizontal \
                                  {\
                                      background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(231,80,229, 255), stop:1 rgba(7,208,255, 255));\
                                      height:10px;\
                                   }\
                                  QSlider::groove:Horizontal \
                                  {\
                                      background:transparent;\
                                      height:10px;\
                                  }\
                                  QSlider::handle:Horizontal \
                                  {\
                                      height: 30px;\
                                      width:8px;\
                                      border-image: url(:/images/ic_music_thumb.png);\
                                      margin: -8 0px; \
                                  }\
                                  ");
            ui->serviceS->setStyleSheet("  \
                                                             QSlider::add-page:Horizontal\
                                                             {     \
                                                                background-color: rgb(87, 97, 106);\
                                                                height:10px;\
                                                             }\
                                                             QSlider::sub-page:Horizontal \
                                                            {\
                                                                background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(231,80,229, 255), stop:1 rgba(7,208,255, 255));\
                                                                height:10px;\
                                                             }\
                                                            QSlider::groove:Horizontal \
                                                            {\
                                                                background:transparent;\
                                                                height:10px;\
                                                            }\
                                                            QSlider::handle:Horizontal \
                                                            {\
                                                                height: 30px;\
                                                                width:8px;\
                                                                border-image: url(:/images/ic_music_thumb.png);\
                                                                margin: -8 0px; \
                                                            }\
                                                            ");

}

void CommentScene::setBtn()
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

    ui->exit->setStyleSheet(
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

void CommentScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void CommentScene::setComment()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd");
    int tas=ui->tasteS->value();
     int tot=ui->totalS->value();
      int ser=ui->serviceS->value();
       int cos=ui->priceS->value();
        int env=ui->environmentS->value();
     QString com=ui->plainTextEdit->toPlainText();
     QString sql;
     QString n=name;
     qDebug()<<n;
           sql = QString("insert into comments (time,id,total ,taste ,service ,cost_performance ,environment ,comments)"
                         " VALUES ('%1', '%2' , '%3' , '%4' , '%5' , '%6' , '%7' , '%8')")
                   .arg(current_date).arg(name).arg(tot).arg(tas).arg(ser).arg(cos).arg(env).arg(com);
           QSqlQuery query;
          // qDebug()<<sql;
           bool ok = query.exec(sql);

           if(!ok)
           {
               QMessageBox::information(this ,tr("呜呜") , tr("评论失败"));
               QMessageBox::critical(0, QObject::tr("Database Error"),
                                     query.lastError().text());
           }

}

void CommentScene::set_job(QString job1)
{
    //进入此页面的身份是服务员
    if(job1 == "servant")
    {
        job = 1;
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
    else if(job1 == "manager")
    {
        job = 5;
    }
    else
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::critical(this, tr("QMessageBox::critical()"),
                                            "invalid job",
                                            QMessageBox::Abort | QMessageBox::Retry | QMessageBox::Ignore);

    }
}




