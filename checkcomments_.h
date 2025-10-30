#ifndef CHECKCOMMENTS__H
#define CHECKCOMMENTS__H


#include <QWidget>
#include <QPushButton>

namespace Ui {
class CheckComments_;
}

class CheckComments_ : public QWidget
{
    Q_OBJECT

public:
    explicit CheckComments_(QString name1,QWidget *parent = nullptr);
    QString name;
    ~CheckComments_();
    void paintEvent(QPaintEvent *) override;

    void appendRowData(QStringList rowData); //添加一行数据

    void clearTableData(); //清除表格数据

    QStringList getCurrentRowData();

    QString getCurrentID();

    void ExecDelSql(QString id);

    void onBtnRefresh();

    void initDB();

    QList<QStringList> selectDataFromBase();

    void onBtnDel();
    void set(QPushButton* m);

private:


private:
    Ui::CheckComments_ *ui;

};

#endif // CHECKCOMMENTS__H
