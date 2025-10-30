#include "querystuff.h"
#include "ui_querystuff.h"

QueryStuff::QueryStuff(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QueryStuff)
{
    ui->setupUi(this);
}

QueryStuff::~QueryStuff()
{
    delete ui;
}
