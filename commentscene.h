#ifndef COMMENTSCENE_H
#define COMMENTSCENE_H

#include<QComboBox>
#include <QApplication>
#include <QTextCodec>
#include<QAction>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QTime>
#include<QVector>
#include <QtSql/QSqlError>
#include <QtDebug>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlRecord>
#include <QSqlTableModel>
#include<QPainter>
#include<QPixmap>
#include <QIcon>
#include<QTableWidget>
#include <QMessageBox>
#include<QCheckBox>
#include<QPropertyAnimation>
#include<QTimer>
#include<QVariant>
#include<QList>

namespace Ui {
class CommentScene;
}

class CommentScene : public QWidget
{
    Q_OBJECT

public:

    explicit CommentScene(QString name1,QWidget *parent = nullptr);
    ~CommentScene();
    void setSlider();
     void setBtn();
     void paintEvent(QPaintEvent *);
     void setComment();
      void connectDB();
      void set_job(QString);//设置进入此界面的员工岗位信息
QString name;

private:
    Ui::CommentScene *ui;
    int job = 0;
  private  slots:
    void changeLable();


};

#endif // COMMENTSCENE_H
