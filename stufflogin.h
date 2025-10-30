#ifndef STUFFLOGIN_H
#define STUFFLOGIN_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class StuffLogin;
}

class StuffLogin : public QWidget
{
    Q_OBJECT

public:
    explicit StuffLogin(QWidget *parent = nullptr);
    ~StuffLogin();
    void paintEvent(QPaintEvent *) override;
void set(QPushButton* m);
private:
    Ui::StuffLogin *ui;
};

#endif // STUFFLOGIN_H
