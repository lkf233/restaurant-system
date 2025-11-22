#ifndef STOCKWIDGET_H
#define STOCKWIDGET_H

#include <QWidget>

namespace Ui {
class Stockwidget;
}

class Stockwidget : public QWidget
{
    Q_OBJECT

public:

    explicit Stockwidget(QString name1,QWidget *parent = nullptr);
    ~Stockwidget();
    void paintEvent(QPaintEvent *);


    void setName(QString name1);


private slots:


    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Stockwidget *ui;
    QString name;
};

#endif // STOCKWIDGET_H
