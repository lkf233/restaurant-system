#ifndef QUERYSTUFF_H
#define QUERYSTUFF_H

#include <QWidget>
#include <QStandardItem>
#include <QStandardItemModel>



namespace Ui {
class QueryStuff;
}

class QueryStuff : public QWidget
{
    Q_OBJECT

public:
    explicit QueryStuff(QString name1,QWidget *parent = nullptr);
    QString name;
    ~QueryStuff();

private:
    Ui::QueryStuff *ui;
};

#endif // QUERYSTUFF_H
