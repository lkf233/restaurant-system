#ifndef REGISTERSTUFF_H
#define REGISTERSTUFF_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class RegisterStuff;
}

class RegisterStuff : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterStuff(QWidget *parent = nullptr);
    ~RegisterStuff();
    void paintEvent(QPaintEvent *event);
void set(QPushButton* m);
private:
    Ui::RegisterStuff *ui;
};

#endif // REGISTERSTUFF_H
