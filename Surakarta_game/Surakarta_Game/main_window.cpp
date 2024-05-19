#include "main_window.h"
#include "Client.h"
#include "pvp_game.h"
#include "ctrlpanel.h"
#include "player_info.h"
#include <QMessageBox>
#include<QApplication>
#include<QHBoxLayout>
#include <QVBoxLayout>

MainWnd::MainWnd(int gameType,QWidget *parent)
    : QWidget{parent}
{
    _gameType=gameType;

    if(_gameType==0)
    {
        QMessageBox msgbox(QMessageBox::Information,"提示","功能开发中~");
        msgbox.exec();
    }
    else if(_gameType==1)
    {
        PVPGame* game = new PVPGame;
        CtrlPanel* panel = new CtrlPanel;
        // PlayerInfo* playerinfo = new PlayerInfo;

        connect(panel->_buttons[0],SIGNAL(clicked()),game,SLOT(slot_panel_button0_Clicked()));
        connect(panel->_buttons[1],SIGNAL(clicked()),this,SLOT(slot_panel_button1_Clicked()));
        connect(panel->_buttons[2],SIGNAL(clicked()),game,SLOT(slot_panel_button2_Clicked()));
        connect(panel->_buttons[3],SIGNAL(clicked()),game,SLOT(slot_panel_button3_Clicked()));
        connect(game,SIGNAL(Player_Black()),panel->playerinfo,SLOT(slot_player_is_black()));
        connect(game,SIGNAL(Player_White()),panel->playerinfo,SLOT(slot_player_is_white()));
        connect(game,SIGNAL(Player_Black()),panel->_clock,SLOT(new_round()));
        connect(game,SIGNAL(Player_White()),panel->_clock,SLOT(new_round()));
        connect(panel->_clock,SIGNAL(timeout()),game,SLOT(slot_timeout()));

        // game->show();
        QHBoxLayout* hlay =new QHBoxLayout(this);
        hlay->addWidget(game,1);
        hlay->addWidget(panel);

        this->resize(1900,890);
        this->show();
    }
    else if(_gameType==2)
    {


    }
    else if(_gameType==3)
    {

    }
}

void MainWnd::slot_panel_button1_Clicked()
{
    qApp->exit(RESTART);//重启码
}

MainWnd::~MainWnd()
{

}
