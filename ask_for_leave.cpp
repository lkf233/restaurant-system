#include "ask_for_leave.h"
#include "ui_ask_for_leave.h"
#include "widget1.h"
#include "administratorhomepage.h"
#include "servant_open.h"
#include <QTimer>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QPainter>

Ask_for_leave::Ask_for_leave(QString name1,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ask_for_leave)
{
    ui->setupUi(this);
    name = name1;
    /*QDateTimeEdit *dateEdit = new QDateTimeEdit(QDate::currentDate(), this);
    dateEdit->setMinimumDate(QDate::currentDate().addDays(-0));  // -365天
    dateEdit->setMaximumDate(QDate::currentDate().addDays(365));  // +365天
    */
     setWindowTitle("Ask for leave");

     setWindowIcon(QIcon(":/icon.jpg"));
    check_leaveStatus();
    setBtn();
      ui->plainTextEdit->setPlaceholderText("没事不要请假嗷");
}

Ask_for_leave::~Ask_for_leave()
{
    delete ui;
}

void Ask_for_leave::paintEvent(QPaintEvent *)
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

void Ask_for_leave::set_job(QString job1)
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
                                            "invalid job",
                                            QMessageBox::Abort | QMessageBox::Retry | QMessageBox::Ignore);

    }
}

//返回原岗位界面
void Ask_for_leave::on_pushButton_clicked()
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

void Ask_for_leave::check_leaveStatus()
{
    QFile file;
    file.setFileName("C:/Users/HUAWEI/Desktop/new/new/leave.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return;
    QTextStream in(&file);
    QString line;
    QString readTxt;//txt中内容
    while (!in.atEnd()) {
    line = in.readLine();
    readTxt.append(line);
    readTxt.append("\n");
    }

    if(readTxt.contains(name,Qt::CaseSensitive))//找到员工名字仍在text中 未请假成功
    {
        QFont ft;
        ft.setPointSize(14);
        ui->label_6->setFont(ft);//设置字体大小
       ui->label_6->setText("请假审核中...");
     }
    else
    {
        QFont ft;
        ft.setPointSize(14);
        ui->label_6->setFont(ft);//设置字体大小
        ui->label_6->setText("未请假/请假已通过");
    }

}

void Ask_for_leave::on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    leavetime = dateTime;
}

void Ask_for_leave::on_dateTimeEdit_2_dateTimeChanged(const QDateTime &dateTime)
{
    backtime = dateTime;
}

void Ask_for_leave::on_textBrowser_textChanged()
{
    //leavetext = ui->textBrowser->toPlainText();
}

void Ask_for_leave::on_pushButton_2_clicked()
{
    leavetime = ui->dateTimeEdit->dateTime();
    backtime = ui->dateTimeEdit_2->dateTime();
    if(leavetime.msecsTo(backtime)<=0)//离开时间晚于回来时间，不合理
    {
        QMessageBox::information(NULL, "不合理的输入", "回来时间不得早于离开时间！");
    }
    else
    {
    //读入文件
        QFile file;
        QString res ="";

    //写入文件
        file.setFileName("C:/Users/HUAWEI/Desktop/new/new/leave.txt");//转移后这个路径记得要改
        if(file.open(QIODevice::Text | QIODevice::ReadWrite | QIODevice::Append)){
            QTextStream stream(&file);
            QString leavetimestr = leavetime.toString("yyyy-MM-dd-hh:mm:ss");
            QString backtimestr = backtime.toString("yyyy-MM-dd-hh:mm:ss");
           // stream<<qSetFieldWidth(20)<<name;
            stream<<name;
            stream<<" "<<leavetimestr<<" "<<backtimestr<<" "<<leavetext<<"\n";
            file.close();

            QFont ft;
            ft.setPointSize(14);
            ui->label_6->setFont(ft);//设置字体大小

            ui->label_6->setText("请假审核中...");
            QMessageBox::information(NULL, "提示", "请假信息已提交，请等待主管确认");
            ui->plainTextEdit->clear();
        }
    }

}

void Ask_for_leave::on_plainTextEdit_textChanged()
{
    leavetext = ui->plainTextEdit->toPlainText();
}

//设置员工名字
void Ask_for_leave::setName(QString a)
{
    name = a;
}

void Ask_for_leave::setBtn()
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


}

