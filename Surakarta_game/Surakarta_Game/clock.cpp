#include "clock.h"
#include "ui_clock.h"
#include "timecontrol.h"
#include<QDebug>
clock::clock(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::clock)
{
    ui->setupUi(this);
    this->tc=new timecontrol();
    connect(tc,&timecontrol::freshSignal,this,&clock::showCurrentSecond);
    // tc->endcount();
    tc->readyCount(roundseconds);
    tc->startcount();
}
void clock::showCurrentSecond(int s)
{
    if(s<=0)
    {
        tc->endcount();
        emit timeout();
    }
    int h=0,m=0;
    h=s/3600;
    s%=3600;
    m=s/60;
    s%=60;
    ui->lcdhour->display(h);
    ui->lcdminute->display(m);
    ui->lcdsecond->display(s);
}

clock::~clock()
{
    delete ui;
}
void clock::new_round()
{
    tc->endcount();
    tc->readyCount(roundseconds);
    tc->startcount();
}
void clock::on_endtime_clicked()
{
    tc->endcount();
}

