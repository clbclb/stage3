#ifndef TIMECONTROL_H
#define TIMECONTROL_H

#include <QWidget>
#include<QTimer>

class timecontrol : public QWidget
{
    Q_OBJECT
public:
    explicit timecontrol(QWidget *parent = nullptr);
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
