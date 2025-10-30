#ifndef AFTERCOMMENT_H
#define AFTERCOMMENT_H

#include <QDialog>
#include <QTimer>
#include <QDialog>
#include<QPainter>
namespace Ui {
class AfterComment;
}

class AfterComment : public QDialog
{
    Q_OBJECT

public:
    explicit AfterComment(QString name1,QWidget *parent = nullptr);
    QString name;
    ~AfterComment();
    void paintEvent(QPaintEvent *);
    void setBtn();

private:
    Ui::AfterComment *ui;
};

#endif // AFTERCOMMENT_H
