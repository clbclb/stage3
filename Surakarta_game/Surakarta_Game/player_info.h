#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include <QWidget>
#include <QLabel>
#include "surakarta_piece.h"

class PlayerInfo : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerInfo(QWidget *parent = nullptr);
    ~PlayerInfo();

    void set_current_player(SurakartaPlayer);

private:
    QLabel _current_player;

signals:

public slots:
    void slot_player_is_black();
    void slot_player_is_white();
};

#endif // PLAYERINFO_H
