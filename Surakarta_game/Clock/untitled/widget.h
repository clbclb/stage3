#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"timecontrol.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    timecontrol* tc;
private slots:
    void showCurrentSecond(int s);
    void on_startTime_clicked();
    void on_endTime_clicked();
};
#endif // WIDGET_H
