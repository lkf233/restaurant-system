#ifndef CHECKLEAVE_H
#define CHECKLEAVE_H

#include <QWidget>
#include <QDialog>
#include <QStandardItem>
#include <QStandardItemModel>



namespace Ui {
class CheckLeave;
}

class CheckLeave : public QWidget
{
    Q_OBJECT

public:
    explicit CheckLeave(QString name1,QWidget *parent = nullptr);
    QString name;
    ~CheckLeave();
    void paintEvent(QPaintEvent *event);
    void display(int row,QStringList subs);
    void set(QPushButton* m);
private slots:
    void reset();

    int readfile();



public:
    Ui::CheckLeave *ui;
    QStandardItemModel *model;
    QList<QString> stuff_line;
};

#endif // CHECKLEAVE_H
