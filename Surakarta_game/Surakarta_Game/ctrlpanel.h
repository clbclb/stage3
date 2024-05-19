#ifndef CTRLPANEL_H
#define CTRLPANEL_H

#include <QWidget>
#include <QPushButton>
#include"player_info.h"
#include"clock.h"


class CtrlPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CtrlPanel(QWidget *parent = nullptr);
    ~CtrlPanel();

    QPushButton *_buttons[4];
    int _selected;
    PlayerInfo* playerinfo;
    class clock* _clock;

signals:

public slots:

};

#endif // CTRLPANEL_H
