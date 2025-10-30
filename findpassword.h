#ifndef FINDPASSWORD_H
#define FINDPASSWORD_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class FindPassword;
}

class FindPassword : public QWidget
{
    Q_OBJECT

public:
    explicit FindPassword(QWidget *parent = nullptr);

    ~FindPassword();
    void paintEvent(QPaintEvent *event);
void set(QPushButton* m);
private:
    Ui::FindPassword *ui;
};

#endif // FINDPASSWORD_H
