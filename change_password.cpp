#include "change_password.h"
#include "ui_change_password.h"
#include "servant_open.h"
#include "widget1.h"
#include "administratorhomepage.h"
#include "stockwidget.h"
#include <QTimer>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QTextCodec>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QTime>
#include <QPainter>
#include <QtSql/QSqlError>
#include <QtDebug>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlRecord>

Change_Password::Change_Password(QString name1,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Change_Password)
{
    ui->setupUi(this);
    name = name1;
    setBtn();
     setWindowTitle("修改密码");

     setWindowIcon(QIcon(":/icon.jpg"));
}

Change_Password::~Change_Password()
{
    delete ui;
}

void Change_Password::paintEvent(QPaintEvent *)
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

void Change_Password::set_job(QString job1)
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
    else
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::critical(this, tr("QMessageBox::critical()"),
                                            "无效的职位",
                                            QMessageBox::Abort | QMessageBox::Retry | QMessageBox::Ignore);

    }
}

//返回原岗位主页面
void Change_Password::on_pushButton_2_clicked()
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
                default:
                    qDebug()<<"wrong job!";
                    break;
                }

            });

}


void Change_Password::on_pushButton_3_clicked()
{
    if(canChange)
    {
    QString newpassword = ui->lineEdit_3->text();
    QString newpassword_2 = ui->lineEdit_4->text();
    if(QString::compare(newpassword,newpassword_2,Qt::CaseSensitive) == 0)//两次输入的密码相同
    {

        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
            db.setDatabaseName("test.db");
            if( !db.open())
            {
              qDebug()<<"Connection fails.";
            }
             if( db.open())
             {
                 qDebug()<<"Connection success.";
                 QSqlQuery q;
                 q=QSqlQuery(db);
                 if(q.exec(QString("update employee set password='%1' where id='%2';").arg(newpassword).arg(id)))
                 {
                     QPalette pa;
                     pa.setColor(QPalette::WindowText,Qt::red);
                     ui->label_6->setPalette(pa);//设置颜色
                     ui->label_6->setText("修改密码成功！");
                 }
                 else
                 {
                     QPalette pa;
                     pa.setColor(QPalette::WindowText,Qt::red);
                     ui->label_6->setPalette(pa);//设置颜色
                     ui->label_6->setText("修改失败！"+q.lastError().text());
                 }
             }
             db.close();
    }
    else
    {
        QPalette pa;
        pa.setColor(QPalette::WindowText,Qt::red);
        ui->label_6->setPalette(pa);//设置颜色
        ui->label_6->setText("两次输入密码不一致！");
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
    }
    }
    else
    {
        QPalette pa;
        pa.setColor(QPalette::WindowText,Qt::red);
        ui->label_6->setPalette(pa);//设置颜色
        ui->label_6->setText("请先输入并通过上面的账号密码！");
    }
}



void Change_Password::on_pushButton_clicked()
{

    id = ui->lineEdit->text();
    password = ui->lineEdit_2->text();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("test.db");
        if( !db.open())
        {
          qDebug()<<"Connection fails.";
        }
         if( db.open())
         {
             qDebug()<<"Connection success.";
             QSqlQuery q;
             q=QSqlQuery(db);
             if(q.exec(QString("select * from employee where id='%1' and password='%2'").arg(id).arg(password)))
             {
                 if(q.next())//找到了对应的人
                 {
                     QPalette pa;
                     pa.setColor(QPalette::WindowText,Qt::red);
                     ui->label_4->setPalette(pa);//设置颜色
                     ui->label_4->setText("输入账号密码正确！请在下面输入新密码：");

                     ui->lineEdit->clear();
                     ui->lineEdit_2->clear();
                     canChange = true;
                 }
                 else
                 {
                     QPalette pa;
                     pa.setColor(QPalette::WindowText,Qt::red);
                     ui->label_4->setPalette(pa);//设置颜色
                     ui->label_4->setText("输入账号/密码不正确，请重新输入！");
                     ui->lineEdit->clear();
                     ui->lineEdit_2->clear();
                 }
             }
         }
         db.close();
}

void Change_Password::setBtn()
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
                "}");

    ui->pushButton_2->setStyleSheet(
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

    ui->pushButton_3->setStyleSheet(
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


