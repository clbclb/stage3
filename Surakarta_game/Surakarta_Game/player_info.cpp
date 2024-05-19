#include "player_info.h"
#include <QVBoxLayout>


PlayerInfo::PlayerInfo(QWidget *parent)
    : QWidget{parent}
{
    set_current_player(PieceColor::BLACK);
    // _current_player.resize(400,200);
    QVBoxLayout* lay = new QVBoxLayout(this);
    lay->addWidget(&_current_player);
}

PlayerInfo::~PlayerInfo()
{

}

void PlayerInfo::set_current_player(SurakartaPlayer player)
{
    if(player==PieceColor::BLACK)
    {
        _current_player.setFont(QFont("Rockwell Extra Bold",20));
        _current_player.setText("Current Player : BLACK");
    }
    else
    {
        _current_player.setFont(QFont("Rockwell Extra Bold",20));
        _current_player.setText("Current Player : WHITE");
    }
}

void PlayerInfo::slot_player_is_black()
{
    this->set_current_player(PieceColor::BLACK);
    this->update();
}

void PlayerInfo::slot_player_is_white()
{
    this->set_current_player(PieceColor::WHITE);
    this->update();
}
