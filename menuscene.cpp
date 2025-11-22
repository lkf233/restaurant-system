#include "menuscene.h"
#include "ui_menuscene.h"
#include "shoppingbutton.h"
#include "customerlogin.h"
#include "paymentscene.h"
#include"viewcomment.h"
#include "widget1.h"
#include "stockwidget.h"
#include "administratorhomepage.h"
#include "servant_open.h"
#include "menuscene.h"

MenuScene::MenuScene(QString name1,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuScene)
{name=name1;
//    qDebug()<<name;

    //基础配置
    ui->setupUi(this);
    setWindowTitle("点单");
    setWindowIcon(QIcon(":/image/shopping.png"));
    ui->menuList->setEditTriggers(QAbstractItemView::NoEditTriggers);
      ui->unclear->setPlaceholderText("输入英语嗷~");
     ui->menuList->setFrameShape(QFrame::NoFrame); //设置无边框
     ui->menuList->setShowGrid(false); //设置不显示格子线
    setBtn();
    shoppingBtn();
    connectDB();
    showMenu();
    connections();

}

MenuScene::~MenuScene()
{
    delete ui;
}

void MenuScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void MenuScene::connectDB()
{
    QSqlDatabase db ;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      db = QSqlDatabase::database("qt_sql_default_connection");
    else
      db = QSqlDatabase::addDatabase("QSQLITE");

            db.setDatabaseName("test.db");
            if( !db.open())
            {
              qDebug()<<"Connection fails.";
            }
             if( db.open()) qDebug()<<"Connection success.";
}

void MenuScene::showMenu()
{
    QSqlQuery query;
    int nColumn, nRow;
   query.prepare("select * from menu");
   query.exec(); //显示数据
   query.last();//指向最后一条记录 打印行数等于总行数加一
   nRow = query.at() + 1;
   QSqlRecord rec = query.record();
   nColumn=rec.count();
   //qDebug()<<nColumn;
   ui->menuList->setRowCount(nRow-1);
   nColumn = ui->menuList->columnCount();//列数等于总列数
   ui->menuList->setColumnCount(7);
    query.first();//指向第一条记录

    //设置表头
    ui->menuList->setHorizontalHeaderItem(0,new QTableWidgetItem("菜品名(英文)"));
    ui->menuList->setHorizontalHeaderItem(1,new QTableWidgetItem("菜品名(中文)"));
    ui->menuList->setHorizontalHeaderItem(2,new QTableWidgetItem("食材"));
    ui->menuList->setHorizontalHeaderItem(3,new QTableWidgetItem("价格"));
    ui->menuList->setHorizontalHeaderItem(4,new QTableWidgetItem("风格"));
    ui->menuList->setHorizontalHeaderItem(5,new QTableWidgetItem("辣度"));
    ui->menuList->setHorizontalHeaderItem(6,new QTableWidgetItem("选择"));
  int j=0;
    while(j<nRow)
    {
    for (int i = 1;i<8; i++)
   if(i<=3) ui->menuList->setItem(j, i-1, new QTableWidgetItem(query.value(i).toString()));//把这条记录放在j行i列
    else ui->menuList->setItem(j, i-2, new QTableWidgetItem(query.value(i).toString()));//把这条记录放在j行i列
    j++;
    query.next();//指向下一条记录
    }
//插入checkBox
     for(int i=0;i<ui->menuList->rowCount();i++)  {
            QTableWidgetItem* p_check = new QTableWidgetItem();
            p_check->setCheckState(Qt::Unchecked);        //设置为 CheckBox 控件
            ui->menuList->setItem(i,6,p_check);
     }
    ui->menuList->show();
}

void MenuScene::set_CheckBox(){
   QList<bool> list;
    int n=getNumberOfDishes();
  for(int i=0;i<n;i++){
      if(ui->menuList->item(i, 6)->checkState() == Qt::Checked){
          list.append(true);
  }
     else list.append(false);
}
 emit signalInfo(list);
}


int MenuScene::getNumberOfDishes()
{
    QSqlQuery query;
   query.prepare("select * from menu");
   query.exec(); //显示数据
   query.last();//指向最后一条记录
    return query.at();
}

void MenuScene::search()
{
    QString origin=QString("select * FROM menu ");

    //模糊查询

    QString text1 =ui->unclear->text();
    QString sql;
    sql=QString(" WHERE menuInEnglish LIKE '%8%'").arg(text1);
   //style查询
    QString sty;
    QString sql1;
     int style=ui->style->currentIndex();

    if(style==1) sty=QString("川菜");
    if(style==2) sty=QString("浙菜");
    if(style==3) sty=QString("鲁菜");
    if(style==4) sty=QString("苏菜");
    if(style==5) sty=QString("闽菜");
    if(style==6) sty=QString("粤菜");
    if(style==7) sty=QString("清真");

  if(style==0)   sql1=QString(" ");
   else   sql1=QString("and style LIKE '%8%'").arg(sty);
  //spicy查询
    QString spicy;
    QString sql2;
     int sp=ui->spicy->currentIndex()-1;
    if(sp==-1)   sql2=QString(" ");
      else   sql2=QString("and spicy LIKE '%8'").arg(sp);

    //排序
    QString order;
    if(ui->increasing->isChecked())    order=" ORDER BY price ASC";
    if(ui->decreasing->isChecked())    order=" ORDER BY price DESC";
  if(ui->default_2->isChecked())    order=" ";


   //打印
    int nColumn=0;
    int nRow=0;
    QSqlQuery query;
    bool ok=query.exec(origin+sql+sql1+sql2+order);
    if(ok)
    {

        ui->menuList->clear();
        query.exec(origin+sql+sql1+sql2+order);
        query.last();//指向最后一条记录 打印行数等于总行数加一
        nRow = query.at() + 1;
        QSqlRecord rec = query.record();
        nColumn=rec.count();
        //qDebug()<<nColumn;
        ui->menuList->setRowCount(nRow-1);
        nColumn = ui->menuList->columnCount();//列数等于总列数
        ui->menuList->setColumnCount(7);
         query.first();//指向第一条记录

         //设置表头
         ui->menuList->setHorizontalHeaderItem(0,new QTableWidgetItem("菜品名(英文)"));
         ui->menuList->setHorizontalHeaderItem(1,new QTableWidgetItem("菜品名(中文)"));
         ui->menuList->setHorizontalHeaderItem(2,new QTableWidgetItem("食材"));
         ui->menuList->setHorizontalHeaderItem(3,new QTableWidgetItem("价格"));
         ui->menuList->setHorizontalHeaderItem(4,new QTableWidgetItem("风格"));
         ui->menuList->setHorizontalHeaderItem(5,new QTableWidgetItem("辣度"));
         ui->menuList->setHorizontalHeaderItem(6,new QTableWidgetItem("选择"));
         int j=0;
           while(j<nRow)
           {
           for (int i = 1;i<8; i++)
          if(i<=3) ui->menuList->setItem(j, i-1, new QTableWidgetItem(query.value(i).toString()));//把这条记录放在j行i列
           else ui->menuList->setItem(j, i-2, new QTableWidgetItem(query.value(i).toString()));//把这条记录放在j行i列
           j++;
           query.next();//指向下一条记录
           }
       //插入checkBox
            for(int i=0;i<ui->menuList->rowCount();i++)  {
                   QTableWidgetItem* p_check = new QTableWidgetItem();
                   p_check->setCheckState(Qt::Unchecked);        //设置为 CheckBox 控件
                   ui->menuList->setItem(i,6,p_check);
            }
           ui->menuList->show();
    }
    else qDebug()<<"error";
}

void MenuScene::setBtn()
{
    ui->pay-> setStyleSheet(
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

    ui->comment->setStyleSheet(
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
                "}");
}

void MenuScene::shoppingBtn()
{
    ShoppingButton *shoppingButton=new ShoppingButton(":/image/shopping.png");
    shoppingButton->setParent(this);
    shoppingButton->move(this->width()*0.5-shoppingButton->width()*0.5,this->height()*0.02);
    shoppingScene=new ShoppingScene(name);
    connect(shoppingButton,&ShoppingButton::clicked,[=](){
        //弹起特效
        shoppingButton->zoom1();
        shoppingButton->zoom2();
        //进入购物车场景
        set_CheckBox();
        QTimer::singleShot(400,this,[=](){
          // this->hide();
            shoppingScene->show();

        });

    });
}


void MenuScene::connections()
{
      PaymentScene* pc=new PaymentScene(job,name);
      ViewComment* vc=new ViewComment(name);
    connect(ui->unclear,&QLineEdit::returnPressed,[this](){search();});
    connect(this,SIGNAL(signalInfo(QList<bool>)),shoppingScene,SLOT(printDishes(QList<bool>)));
    connect(this,SIGNAL(signalInfo(QList<bool>)),shoppingScene,SLOT(printSum(QList<bool>)));
    connect(this,SIGNAL(signalInfo(QList<bool>)),pc,SLOT(printInfo(QList<bool>)));
    connect(this,SIGNAL(signalInfo(QList<bool>)),pc,SLOT(decreaseMaterial(QList<bool>)));
    connect(this,SIGNAL(signalInfo(QList<bool>)),pc,SLOT(addSalesAmountInDay(QList<bool>)));
     connect(this,SIGNAL(signalInfo(QList<bool>)),pc,SLOT(addSalesAmountInMonth(QList<bool>)));
    connect(ui->increasing,SIGNAL(toggled( bool)),this,SLOT(search()));
    connect(ui->decreasing,SIGNAL(toggled( bool)),this,SLOT(search()));
   connect(ui->default_2,SIGNAL(toggled( bool)),this,SLOT(search()));
   connect(ui->spicy,SIGNAL(activated ( int )),this,SLOT(search()));
    connect(ui->style,SIGNAL(activated ( int )),this,SLOT(search()));


    connect(ui->pay,&QPushButton::clicked,[=](){

        QTimer::singleShot(400,this,[=](){
         this->hide();
          set_CheckBox();
          pc->set_job(job);
         pc->show();
        });

    });
   connect(ui->comment,&QPushButton::clicked,[=](){

       QTimer::singleShot(400,this,[=](){

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
          vc->set_job(jobName);
          vc->show();
          //this->hide();
       });

   });

}

//返回原岗位界面
void MenuScene::on_pushButton_clicked()
{
    //延时进入界面
    QTimer::singleShot(500,this,[=](){
    //自身隐藏
    this->hide();
    //返回原始界面
    //需要获得进入本界面时的员工岗位信息
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
    case 5://进入此页面的身份是顾客
    {
        //显示注册界面
        CustomerLogin *login = new CustomerLogin();
        login->show();
        break;

    }
    default:
        qDebug()<<"wrong job!";
        break;
    }

    });


}


void MenuScene::set_job(QString job1)
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
    else if(job1 == "customer")
    {
        job = 5;
    }
   /* else
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::critical(this, tr("QMessageBox::critical()"),
                                            "invalid job",
                                            QMessageBox::Abort | QMessageBox::Retry | QMessageBox::Ignore);

    }*/
    qDebug()<<"menujob:"<<job;
}

void MenuScene::on_pay_clicked()
{
    /*PaymentScene* pc=new PaymentScene(job,name);
    QTimer::singleShot(400,this,[=](){
     this->hide();
      set_CheckBox();
     pc->show();
    });*/
}
