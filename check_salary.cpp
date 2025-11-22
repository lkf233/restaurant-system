#include "check_salary.h"
#include "ui_check_salary.h"
#include "servant_open.h"
#include "widget1.h"
#include "administratorhomepage.h"
#include "stockwidget.h"
#include "employee.h"
#include "servant.h"
#include "manager.h"
#include "chef.h"
#include "warehouse.h"
#include <QTimer>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QTextCodec>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QTime>
#include <QtSql/QSqlError>
#include <QtDebug>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlRecord>
#include <QPainter>


Check_Salary::Check_Salary(QString name1,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Check_Salary)
{
    name = name1;
    ui->setupUi(this);
    setBtn();
    setWindowTitle("查看薪水");

    setWindowIcon(QIcon(":/icon.jpg"));
    //show_salary();
}

Check_Salary::~Check_Salary()
{
    delete ui;
}

void Check_Salary::paintEvent(QPaintEvent *)
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

void Check_Salary::set_job(QString job1)
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
    show_salary();
}

void Check_Salary::on_pushButton_clicked()
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

void Check_Salary::show_salary()
{
    Employee *employee;
    if(job == 1)//这个人是服务员
    {
        employee = new servant(name);
    }
    else if(job == 2)//这个人是厨师
    {
        employee = new chef(name);
    }
    else if(job == 3)//这个人是仓管
    {
        employee = new warehouse(name);
    }
    else if(job == 4)//这个人是管理员
    {
        employee = new manager(name);
    }
    else
    {
        qDebug()<<"show salary : wrong job!";
    }

    QFont ft;
    /*ft.setPointSize(16);
    ft.setBold(75);*/
    QFont font ( "Microsoft YaHei", 12, 75);
    ui->label_2->setFont(font); //设置字体
    //ui->label_2->setAlignment(Qt::AlignLeft);//对齐方式
    ui->label_2->setText(name);//name是员工的名字

    ft.setPointSize(16);
    ft.setWeight(50);

    //与工作时间挂钩的奖金
    qint64 workTimeSalary = 0;
    workTimeSalary = getMonthWorkSalary() * 0.0000001;
    ui->label_13->setAlignment(Qt::AlignHCenter);//对齐方式
    ui->label_13->setFont(ft);
    QString workTimeSalaryStr = QString::number(workTimeSalary);
    ui->label_13->setText(workTimeSalaryStr);

    //季度奖金（只在3.6.9.12月发放）
    ui->label_5->setAlignment(Qt::AlignHCenter);//对齐方式
    ui->label_5->setFont(ft);
    QDate date = QDate::currentDate();
    int month = date.month();
    int seasonSlary = 0;
    if(month == 3||month == 6||month == 9||month == 12)//处在3.6.9.12月
    {
        seasonSlary = employee->getSeasonSalary();//多态
    }
    else
    {
        seasonSlary = 0;
    }
    QString seasonSalarystr = QString::number(seasonSlary);
    ui->label_5->setText(seasonSalarystr);//季度奖金

    //基础工资
    ui->label_7->setAlignment(Qt::AlignHCenter);//对齐方式
    ui->label_7->setFont(ft);
    ui->label_7->setText(getBasicSalary());//基础工资
    int basic_Salary = getBasicSalary().toInt();

    //月销量挂钩奖金
    ui->label_9->setAlignment(Qt::AlignHCenter);//对齐方式
    ui->label_9->setFont(ft);
    int saleSalary = 0;
    saleSalary = employee->getMonthlySalary();//多态
    QString saleSlarystr = QString::number(saleSalary);
    ui->label_9->setText(saleSlarystr);//月销量挂钩奖金

    //总工资
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::red);
    ui->label_11->setPalette(pa);
    ui->label_11->setFont(ft);
    ui->label_11->setAlignment(Qt::AlignHCenter);//对齐方式
    int wholeSalary = seasonSlary + basic_Salary + saleSalary + workTimeSalary;
    QString wholeSalarystr = QString::number(wholeSalary);
    ui->label_11->setText(wholeSalarystr);//总工资
}

//获得基础工资
QString Check_Salary::getBasicSalary()
{
    QString basic_salary;
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
             if(q.exec(QString("select salary from employee where first_name='%1'").arg(name)))//这里的name应是对应员工的name
             {
                 if(q.next())//找到了对应的人
                 {
                    basic_salary = q.value(0).toString();
                 }
                 else
                 {
                     QMessageBox::information(NULL, "出错", "寻找对应名字的人的基本工资出错");
                 }
             }
         }
         db.close();
         return basic_salary;
}

//获得月工作时间
QTime Check_Salary::getMonthWorkTime()
{
    QTime monthWorkTime;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("workTime.db");
        if( !db.open())
        {
          qDebug()<<"Connection fails.";
        }
    if( db.open())
         {
             qDebug()<<"Connection success.";
             QSqlQuery q;
             q=QSqlQuery(db);
             if(q.exec(QString("select monthWorkTime from workTimeTable where name='%1'").arg(name)))
             {
                 if(q.next())//找到了
                 {
                     monthWorkTime = QTime::fromString(q.value(0).toString(),"hh::mm::ss");//获得当前这个人本月上班的时间

                 }

             }
         }
    db.close();
    return monthWorkTime;
}
//获得月工作时长奖金
qint64 Check_Salary::getMonthWorkSalary()
{
    qint64 monthTime = 0;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("workTime.db");
        if( !db.open())
        {
          qDebug()<<"Connection fails.";
        }
    if( db.open())
         {
             qDebug()<<"Connection success.";
             QSqlQuery q;
             q=QSqlQuery(db);
             if(q.exec(QString("select monthWorkTime from workTimeTable where name='%1'").arg(name)))
             {
                 if(q.next())//找到了
                 {
                     monthTime = q.value(0).toLongLong();//获得当前这个人本月上班的时间的总毫秒数
                 }

             }
         }
    db.close();

    //将毫秒数转回QTime的计算基数
    int ss = 1000;
    int mi = ss * 60;
    int hh = mi * 60;
    int dd = hh * 24;
    //QTime所需参数
    long day,hour,minute,second,milliSecond;
    //将毫秒数转回QTime
        day = monthTime / dd;
        hour = (monthTime - day * dd) / hh;
        minute = (monthTime - day * dd - hour * hh) / mi;
        second = (monthTime - day * dd - hour * hh - minute * mi) / ss;
        QString str = QString::number(day)+"D "+QString::number(hour)+":"+QString::number(minute)+":"+QString::number(second);
        ui->lcdNumber->setDigitCount(13);//设置显示位数
        ui->lcdNumber->display(str);

        return monthTime;
}

//设置员工名字
void Check_Salary::setName(QString a)
{
    name = a;
}

void Check_Salary::setBtn()
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



}

