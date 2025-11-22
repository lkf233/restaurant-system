#ifndef CHANGEFOODAMOUNT_H
#define CHANGEFOODAMOUNT_H
#include <QVariantMap>
#include <QDialog>

namespace Ui {
class changeFoodAmount;
}

class changeFoodAmount : public QDialog
{
    Q_OBJECT
    enum OperateType
       {

           Edit
       };
public:
    explicit changeFoodAmount(QString name1,QWidget *parent = nullptr);
    QString name;
    ~changeFoodAmount();
    void paintEvent(QPaintEvent *);
    void onShowDb();

    void set_job(QString);//设置进入此界面的员工岗位信息
 void appendRowData(QStringList rowData);
 QStringList getCurrentRowData();
  QList<QStringList> selectDataFromBase();
  QString getCurrentID();
signals:

private slots:

  void ExecEditSql(QVariantMap stuInfo);
  void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();
     void clearTableData();

     void on_pushButton_5_clicked();

     void on_pushButton_3_clicked();


private:
    Ui::changeFoodAmount *ui;
    int job = 0;
    class changeFoodRest* m_pAddStuDlg;

  void initchangeDlg();
   OperateType m_operateType;
};

#endif // CHANGEFOODAMOUNT_H
