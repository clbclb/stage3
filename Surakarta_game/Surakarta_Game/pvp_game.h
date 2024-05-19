#ifndef PVPGAME_H
#define PVPGAME_H

#include "widget.h"

class PVPGame: public Widget
{
    Q_OBJECT
public:
    explicit PVPGame(QWidget *parent = 0);
    ~PVPGame();
};

#endif // PVPGAME_H
