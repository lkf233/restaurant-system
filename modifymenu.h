#ifndef MODIFYMENU_H
#define MODIFYMENU_H

#include <QDialog>

namespace Ui {
class Modifymenu;
}

class Modifymenu : public QDialog
{
    Q_OBJECT

public:
    explicit Modifymenu(QString name1,QWidget *parent = nullptr);
    QString name;
    ~Modifymenu();
  void paintEvent(QPaintEvent *);
private slots:
    void on_pushButton_2_clicked();

private:
    Ui::Modifymenu *ui;
};

#endif // MODIFYMENU_H
