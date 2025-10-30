#include "shoppingscene.h"
#include "ui_shoppingscene.h"
#include "menuscene.h"

ShoppingScene::ShoppingScene(QString name1,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShoppingScene)
{
    name = name1;
    ui->setupUi(this);
    setWindowTitle("餐厅管理系统");
    setWindowIcon(QIcon(":/image/shopping.png"));
    setBtn();
    ui->shoppingList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->exit,&QPushButton::clicked,[this](){
   this-> hide();
  });


}
ShoppingScene::~ShoppingScene()
{
    delete ui;
}

void ShoppingScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

/*void ShoppingScene::connectDB()
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
}*/

void ShoppingScene::printDishes(QList<bool> list)
{
    //计算选择的菜数
    int n=MenuScene::getNumberOfDishes();
    int count=0;
        for(int i=0;i<n;i++){
            if (list[i])     count++;
        }

    //打印
    ui->shoppingList->setRowCount(count);
    ui->shoppingList->setColumnCount(3);
    //count2表示行数
    int count2=0;
    ui->shoppingList->setHorizontalHeaderItem(0,new QTableWidgetItem("菜品名(中文)"));
    ui->shoppingList->setHorizontalHeaderItem(1,new QTableWidgetItem("菜品名(英文)"));
    ui->shoppingList->setHorizontalHeaderItem(2,new QTableWidgetItem("价格"));
    for(int i=0;i<n;i++){
        if(list[i]){
            QString sql;

            sql = QString("select * from  menu "
                          " where number = '%0' ").arg(i+1);
            QSqlQuery query;
            query.exec(sql);
             query.first();
            for(int j=0;j<3;j++){
           ui->shoppingList->setItem(count2,j-1,new QTableWidgetItem(query.value(j).toString()));
            }

         QString nn=query.value(5).toString();

        ui->shoppingList->setItem(count2,2,new QTableWidgetItem(nn));
        count2++;
    }
ui->shoppingList->show();

}

}

void ShoppingScene::printSum(QList<bool>list)
{
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
      ui->listWidget->clear();
      ui->listWidget->addItem("TOTAL SUM : "+QString::number(sum));
      ui->listWidget->addItem(" ");
       ui->listWidget->addItem("DISCOUNT : ");

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
                  ui->listWidget->addItem("Intial price : "+query.value(5).toString()+"       Discount price : "+QString::number(query.value(5).toInt()*discount));

         }
        }
ui->listWidget->addItem(" ");

       ui->listWidget->addItem("FINAL SUM : "+QString::number(sum*discount));
}
void ShoppingScene::on_pushButton_clicked()
{

}

void ShoppingScene::setBtn()
{

        ui->exit->setStyleSheet(
                    //正常状态样式
                    "QPushButton{"
                    "background-color:rgba(100,225,100,30);"//背景色
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


