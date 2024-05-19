#ifndef TIMECONTROL_H
#define TIMECONTROL_H
#include<QObject>
#include<QTimer>
class timecontrol:public QObject
{
    Q_OBJECT
public:
    explicit timecontrol(QObject *parent = 0);
    void readyCount(int s);
    void startcount();
    void endcount();
signals:
    void freshSignal(int s);
public slots:
    void on_timer_out();
private:
    int s;
    QTimer *fTimer;
};

#endif // TIMECONTROL_H
