#include "timecontrol.h"

timecontrol::timecontrol(QWidget *parent)
    : QWidget{parent}
{
    this->s=0;
}
void timecontrol::on_timer_out()
{
    this->s--;
    emit freshSignal(s);
}
void timecontrol::readyCount(int s){
    this->s=s;
    fTimer=new QTimer(this);
    fTimer->stop();
    fTimer->setInterval(1000);
    connect(fTimer,SIGNAL(timeout()),this,SLOT(on_timer_out()));
}
void timecontrol::startcount()
{
    fTimer->start();
}
void timecontrol::endcount()
{
    fTimer->stop();
}
