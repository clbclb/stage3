#ifndef MAINWND_H
#define MAINWND_H

#include <QWidget>

#define RESTART 1234567890


class MainWnd : public QWidget
{
    Q_OBJECT
public:
    explicit MainWnd(QString s1="127.0.0.1",QString s2="10086",QString s3="BLACK",int gameType=0,QWidget *parent = nullptr);
    ~MainWnd();

    int _gameType;

signals:

public slots:
    void slot_panel_button1_Clicked();
};

#endif // MAINWND_H
