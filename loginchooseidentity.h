#ifndef LOGINCHOOSEIDENTITY_H
#define LOGINCHOOSEIDENTITY_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class LoginChooseIdentity;
}

class LoginChooseIdentity : public QWidget
{
    Q_OBJECT

public:
    explicit LoginChooseIdentity(QWidget *parent = nullptr);
    ~LoginChooseIdentity();
    void paintEvent(QPaintEvent *event);
    void shoppingBtn();
    void shoppingBtn2();
void set(QPushButton* m);
private:
    Ui::LoginChooseIdentity *ui;
};

#endif // LOGINCHOOSEIDENTITY_H
