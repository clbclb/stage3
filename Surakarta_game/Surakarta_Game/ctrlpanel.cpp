#include "ctrlpanel.h"
#include <QVBoxLayout>
#include <QMessageBox>

CtrlPanel::CtrlPanel(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout* lay = new QVBoxLayout(this);
    lay->addWidget(_clock=new class clock);
    lay->addWidget(playerinfo = new PlayerInfo);
    lay->addWidget(_buttons[0] = new QPushButton("重开！"));
    lay->addWidget(_buttons[1] = new QPushButton("重新选择模式"));
    lay->addWidget(_buttons[2] = new QPushButton("认输"));
    lay->addWidget(_buttons[3] = new QPushButton("设置"));
}

CtrlPanel::~CtrlPanel()
{

}
