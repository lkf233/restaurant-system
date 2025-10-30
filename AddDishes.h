#ifndef MODIFYDISHES_H
#define MODIFYDISHES_H

#include <QDialog>

namespace Ui {
class AddDishes;
}

class AddDishes : public QDialog
{
    Q_OBJECT

public:
    explicit AddDishes(QWidget *parent = nullptr);
    ~AddDishes();

private slots:


private:
    Ui::AddDishes *ui;
};

#endif // MODIFYDISHES_H
