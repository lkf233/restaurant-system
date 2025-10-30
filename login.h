#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "register.h"
#include <QPushButton>


namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    void paintEvent(QPaintEvent *) override;
void set(QPushButton* m);
private:
    Ui::Login *ui;
};

#endif // LOGIN_H
