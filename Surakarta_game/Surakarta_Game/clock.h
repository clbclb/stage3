#ifndef CLOCK_H
#define CLOCK_H

#include <QWidget>
#include "timecontrol.h"
namespace Ui {
class clock;
}

class clock : public QWidget
{
    Q_OBJECT

public:
    explicit clock(QWidget *parent = nullptr);
    ~clock();

private:
    Ui::clock *ui;
    timecontrol* tc;
    int roundseconds=60;//从此设置每轮秒数

signals:
    void timeout();

private slots:
    void showCurrentSecond(int s);
    void new_round();
    void on_endtime_clicked();
};

#endif // CLOCK_H
