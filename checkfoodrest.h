#ifndef CHECKFOODREST_H
#define CHECKFOODREST_H

#include <QDialog>

namespace Ui {
class checkFoodRest;
}

class checkFoodRest : public QDialog
{
    Q_OBJECT

public:
    explicit checkFoodRest(QString name1,QWidget *parent = nullptr);
    QString name;
    ~checkFoodRest();
    void paintEvent(QPaintEvent *);
  void onShowDb();
private slots:
    void on_pushButton_2_clicked();

private:
    Ui::checkFoodRest *ui;
};

#endif // CHECKFOODREST_H
