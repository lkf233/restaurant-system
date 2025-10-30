#ifndef GOTOCOMMENT_H
#define GOTOCOMMENT_H
#include <QTimer>
#include <QDialog>
#include<QPainter>
namespace Ui {
class GoToComment;
}

class GoToComment : public QDialog
{
    Q_OBJECT

public:

    explicit GoToComment(int job1,QString name1,QWidget *parent = nullptr);
    ~GoToComment();
    void paintEvent(QPaintEvent *);
     void setBtn();
     QString name;
     int job =0;
private:

    Ui::GoToComment *ui;

};

#endif // GOTOCOMMENT_H
