#ifndef EVE_GAME_H
#define EVE_GAME_H
#include "widget.h"
class eve_game:public Widget
{
    Q_OBJECT
public:
    explicit eve_game(QWidget *parent = 0);
    virtual ~eve_game();
};


#endif // EVE_GAME_H
