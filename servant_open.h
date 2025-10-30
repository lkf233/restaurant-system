#ifndef SERVANT_OPEN_H
#define SERVANT_OPEN_H
#include <QPainter>
#include <QWidget>
#include <QString>
QT_BEGIN_NAMESPACE
namespace Ui { class Servant_open; }
QT_END_NAMESPACE

class Servant_open : public QWidget
{
    Q_OBJECT
    friend class Ask_for_leave;

public:

    Servant_open(QString name1,QWidget *parent = nullptr);
    ~Servant_open();
    void paintEvent(QPaintEvent *);
    //void set_servant();//将servant角色设定到每个附属功能的类里面
    void setName(QString);
    void setBtn();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::Servant_open *ui;
    QString job = "servant";
    QString name = "";
};
#endif // SERVANT_OPEN_H
