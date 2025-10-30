#ifndef CUSTOMERLOGIN_H
#define CUSTOMERLOGIN_H

#include <QWidget>
#include <QPushButton>
#include "commentscene.h"

namespace Ui {
class CustomerLogin;
}

class CustomerLogin : public QWidget
{
    Q_OBJECT

public:

    friend class CommentScene;
    explicit CustomerLogin(QWidget *parent = nullptr);
    ~CustomerLogin();
    void paintEvent(QPaintEvent *) override;
    void set(QPushButton* m);



   QString static getName();
private:
    Ui::CustomerLogin *ui;


};

#endif // CUSTOMERLOGIN_H
