#include "timecontrol.h"

timecontrol::timecontrol(QObject *parent) :QObject(parent)
{
    this->s=0;
}
void timecontrol::on_timer_out()
{
    this->s--;
    emit freshSignal(s);
}
void timecontrol::readyCount(int s)
{
    this->s=s;
    emit freshSignal(s);
    fTimer=new QTimer(this);
    fTimer->stop();//设置一开始是停止计时还是开始计时
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
