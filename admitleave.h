#ifndef ADMITLEAVE_H
#define ADMITLEAVE_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class AdmitLeave;
}

class AdmitLeave : public QWidget
{
    Q_OBJECT

public:

    explicit AdmitLeave(QString name1,QWidget *parent = nullptr);
    QString name;
    ~AdmitLeave();
    void paintEvent(QPaintEvent *event);
    void writeIn(QString information);
    int readfile();
    void set(QPushButton* m);

private slots:
    void on_btn_changedata_del_clicked();
    void on_pushButton_clicked();

private:

    Ui::AdmitLeave *ui;
    QList<QString> stuff_line;
};

#endif // ADMITLEAVE_H
