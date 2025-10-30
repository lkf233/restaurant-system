#ifndef TABLE_H
#define TABLE_H
#include <QTime>

#include <string>

class Table
{
public:
    Table();
    Table(QString name1,int);
    QString name;
    void setReservationStatus(bool);
    void setUsageStatus(bool);
    void setReservationTime();
    QTime getRestReservationTime();
    bool getReservationStatus();
    bool getUsageStatus();
    int getNumber();
    void setReservationTimeFromDb(QTime);

    void setNumber(int);

private:
    int number;
    bool reservation_status = false;
    bool usage_status = false;
    QTime reservation_time;
};

#endif // TABLE_H
