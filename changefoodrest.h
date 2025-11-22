#ifndef CHANGEFOODREST_H
#define CHANGEFOODREST_H
#include <QVariantMap>
#include <QDialog>

namespace Ui {
class changeFoodRest;
}

class changeFoodRest : public QDialog
{
    Q_OBJECT

public:
    explicit changeFoodRest(QString name1,QWidget *parent = nullptr);
    QString name;
    ~changeFoodRest();

     void paintEvent(QPaintEvent *);
signals:
    void signalStuInfo(QVariantMap stuInfo);
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::changeFoodRest *ui;
    void clearData();
 void closeEvent(QCloseEvent *event);
};

#endif // CHANGEFOODREST_H
