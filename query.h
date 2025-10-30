#ifndef QUERY_H
#define QUERY_H

#include <QWidget>
#include <QPushButton>



#include <QDialog>
#include <QStandardItem>
#include <QStandardItemModel>

extern QString name1;
extern QString time1;
extern QString time2;
extern QString reason;


namespace Ui {
class Query;
}

class Query : public QWidget
{
    Q_OBJECT

public:
    explicit Query(QString name1,QWidget *parent = nullptr);
    QString name;
    ~Query();
    void paintEvent(QPaintEvent *event);
    int readfile();
    void reset();
    void display(int row, QStringList score_line);
void set(QPushButton* m);
private slots:
    void on_btn_doquery_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

public:
    Ui::Query *ui;
    QStandardItemModel *model;
    QList<QString> stuff_line;
};

#endif // QUERY_H
