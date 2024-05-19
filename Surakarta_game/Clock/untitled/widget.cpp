#include "widget.h"
#include "ui_widget.h"
#include<QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->tc=new timecontrol();
    connect(tc,SIGNAL(freshSignal(int)),this,SLOT(showCurrentSecond(int)));
}

void Widget::showCurrentSecond(int s)
{
    if(s<=0)
    {
        tc->endcount();
        ui->startTime->setEnabled(true);
        ui->endTime->setEnabled(false);
    }
    int h=0,m=0;
    h=s/3600;
    m=s/60;
    s%=60;
    ui->lcdhour->display(h);
    ui->lcdminute->display(m);
    ui->lcdsecond->display(s);
}
Widget::~Widget()
{
    delete ui;
}

void Widget::on_startTime_clicked()
{
    int second=ui->textEdit->toPlainText().toInt();
    qDebug()<<QString(second);
    tc->readyCount(second);
    tc->startcount();
    ui->startTime->setEnabled(false);
    ui->endTime->setEnabled(true);
}

void Widget::on_endTime_clicked()
{
    tc->endcount();
    ui->startTime->setEnabled(true);
    ui->endTime->setEnabled(false);
}
