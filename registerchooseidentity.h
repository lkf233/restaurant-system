#ifndef REGISTERCHOOSEIDENTITY_H
#define REGISTERCHOOSEIDENTITY_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class RegisterChooseIdentity;
}

class RegisterChooseIdentity : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterChooseIdentity(QWidget *parent = nullptr);
    ~RegisterChooseIdentity();
    void paintEvent(QPaintEvent *event);
    void shoppingBtn();
    void shoppingBtn2();
void set(QPushButton* m);
private:
    Ui::RegisterChooseIdentity *ui;
};

#endif // REGISTERCHOOSEIDENTITY_H
