#include "checkcomments_.h"
#include "ui_checkcomments_.h"
#include "administratorhomepage.h"
#include <QIcon>
#include <QTimer>
#include <QPainter>
#include <QPushButton>
#include <QMessageBox>
#include <QTableWidget>
#include <QHeaderView>
#include <QSqlQuery>
#include <QDebug>


void CheckComments_::paintEvent(QPaintEvent *event)
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




CheckComments_::CheckComments_(QString name1,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CheckComments_)
{
    ui->setupUi(this);
    name = name1;
    //配置主场景

    //设置固定大小
    setFixedSize(750,427);

    //设置图标

    setWindowIcon(QIcon(":/icon.jpg"));

    //设置标题
    setWindowTitle("查看评论");

    set(ui->delete_2);
    set(ui->return_2);

    initDB();  //打开数据库

    onBtnRefresh(); //程序启动时，查询数据

    ui->setupUi(this);
    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() <<"时间" << "ID"<< "整体评价"
                                               <<"味道" <<"服务" <<"性价比" <<"环境"<<"评论");

    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    initDB();  //打开数据库

    onBtnRefresh(); //程序启动时，查询数据

    connect(ui->return_2,&QPushButton::clicked,[=](){

        //延时进入评论界面
        QTimer::singleShot(100,this,[=](){

        //自身隐藏
        this->hide();

        //显示homepage
        administratorHomePage *administratorhomepage = new administratorHomePage(name);
        administratorhomepage->show();

        });

        });

    connect(ui->delete_2,&QPushButton::clicked,[=](){

        onBtnDel();


        });

    set(ui->delete_2);
    set(ui->return_2);
}

CheckComments_::~CheckComments_()
{
    delete ui;
}

void CheckComments_::appendRowData(QStringList rowData)
{
    int row = ui->tableWidget->rowCount();

    ui->tableWidget->insertRow(row);

    for(int i  = 0 ; i < rowData.size() ; i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(rowData.at(i));
        ui->tableWidget->setItem(row , i , item);
    }
}

void CheckComments_::clearTableData()
{
    //清除表格
    int rowCount = ui->tableWidget->rowCount();
    for(int r = rowCount-1 ; r >=0 ; r--)
    {
        ui->tableWidget->removeRow(r);
    }
}

QStringList CheckComments_::getCurrentRowData()
{
    QStringList rowData;
    int row = ui->tableWidget->currentRow();
    if(row != -1)
    {
        rowData << ui->tableWidget->item(row , 0)->text();
        rowData << ui->tableWidget->item(row , 1)->text();
        rowData << ui->tableWidget->item(row , 2)->text();
        rowData << ui->tableWidget->item(row , 3)->text();
        rowData << ui->tableWidget->item(row , 4)->text();
        rowData << ui->tableWidget->item(row , 5)->text();
        rowData << ui->tableWidget->item(row , 6)->text();
        rowData << ui->tableWidget->item(row , 7)->text();
        rowData << ui->tableWidget->item(row , 8)->text();
    }
    return rowData;
}

QString CheckComments_::getCurrentID()
{
    QString ID ;
    int row = ui->tableWidget->currentRow();
    if(row != -1)
    {
        ID =  ui->tableWidget->item(row , 0)->text();
    }
    return ID;
}

void CheckComments_::ExecDelSql(QString id)
{
    QString sql;
    sql = QString("DELETE FROM comments "
                  " where time = '%9' ").arg(id);

    QSqlQuery query;
    bool ok = query.exec(sql);
    if(ok)
    {
        onBtnRefresh(); //重新加载数据
        QMessageBox::information(this ,tr("提示") , tr("删除成功!"));
    }
    else
    {
        QMessageBox::information(this ,tr("提示") , tr("删除失败!"));
    }
}

void CheckComments_::onBtnRefresh()
{
    qDebug()<<"onBtnRefresh";
    QList<QStringList> tableData;

    tableData = selectDataFromBase();
    if(!tableData.isEmpty())
    {
        clearTableData();
        QListIterator<QStringList> itr(tableData);
        while(itr.hasNext())
        {
            appendRowData(itr.next());
        }
    }
}

void CheckComments_::initDB()
{



        QSqlDatabase comments = QSqlDatabase::addDatabase("QODBC");
        QString dsn = QString::fromLocal8Bit("restaurant");//你配置的Data Source
        comments.setHostName("192.168.56.102");//你的IP地址
        comments.setDatabaseName(dsn);
        comments.setUserName("my_root"); //用户名
        comments.setPassword("my_root@123");//密码
        comments.setPort(26000); //opengauss端口号为26000

    bool ok = comments.open();
    if(ok)
    {
        qDebug()<<"Create DB";

        QSqlQuery query;

    }
    else
    {
        qDebug()<<comments.databaseName();
    }
}

QList<QStringList> CheckComments_::selectDataFromBase()
{
    QSqlQuery query("SELECT * FROM comments");

    QList<QStringList> stuInfo;

    while (query.next())
    {
        QStringList rowData ;

        rowData <<query.value(0).toString();
        rowData <<query.value(1).toString();
        rowData <<query.value(2).toString();
        rowData <<query.value(3).toString();
        rowData <<query.value(4).toString();
        rowData <<query.value(5).toString();
        rowData <<query.value(6).toString();
        rowData <<query.value(7).toString();
        rowData <<query.value(8).toString();

        stuInfo.append(rowData);
    }
    return stuInfo;
}

void CheckComments_::onBtnDel()
{
    qDebug()<<"onBtnDel";
    QString ID = getCurrentID();
    if(ID.isEmpty())
    {
        QMessageBox::information(this , tr("提示") , tr("请选中一条记录！"));
        return ;
    }

    QMessageBox::StandardButton button = QMessageBox::question(this , tr("提示") ,tr("确定删除这一条记录？"));
    if(button == QMessageBox::Yes)
    {
        //删除操作
        ExecDelSql(ID);
    }
}

void CheckComments_::set(QPushButton* m)
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
