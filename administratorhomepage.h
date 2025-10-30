#ifndef ADMINISTRATORHOMEPAGE_H
#define ADMINISTRATORHOMEPAGE_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class administratorHomePage;
}

class administratorHomePage : public QWidget
{
    Q_OBJECT

public:

    explicit administratorHomePage(QString name1,QWidget *parent = nullptr);
    ~administratorHomePage();
    void paintEvent(QPaintEvent *) override;
    void set(QPushButton* m);



     void setName(QString name1);
private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();


   // void on_pushButton_2_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_clicked();

private:
    Ui::administratorHomePage *ui;
    QString name;
};

#endif // ADMINISTRATORHOMEPAGE_H
