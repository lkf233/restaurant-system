#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();
    void paintEvent(QPaintEvent *) override;
void set(QPushButton* m);
private:
    Ui::Register *ui;
};

#endif // REGISTER_H
