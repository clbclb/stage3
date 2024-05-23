#include "networkdata.h"
#include<QMessageBox>
#include<QPainter>
#include<surakarta_piece.h>
#include "Client.h"
#include<QWidget>
#include <QVBoxLayout>
#include "ui_Client.h"
#include<QtNetwork>
#include"Surakarta_Board.h"
#include"Surakarta_agent_mine.h"

Client::Client(QWidget *parent)
    :QWidget{parent}, ui(new Ui::Client)
{
    dep="";
    for(int i=0;i<6;i++)
        for(int j=0;j<2;j++)
            color[i][j]=PieceColor::BLACK;
    for(int i=0;i<6;i++)
        for(int j=2;j<4;j++)
            color[i][j]=PieceColor::NONE;
    for(int i=0;i<6;i++)
        for(int j=4;j<6;j++)
            color[i][j]=PieceColor::WHITE;
    fromx=-1;
    ui->setupUi(this);
    QMessageBox::StandardButton ret;
    ret=QMessageBox::question(NULL,"white or black", "你是否想成为黑方（先手）");
    black=0;
    if(ret==QMessageBox::Yes)black=1;
    socket = new NetworkSocket(new QTcpSocket(),this);
    connect(socket,&NetworkSocket::receive,this,&Client::receiveData);
    connect(this,SIGNAL(ip_reset()),this,SLOT(initgame()));
}

void Client::initgame(){
    ui->label->hide();
    ui->label_2->hide();
    ui->textEdit->hide();
    ui->pushButton->hide();
    ui->textEdit_2->hide();

    socket->hello(new_ip,new_port);
    this->socket->base()->waitForConnected(2000);

    /*
initialize :
isblack your_turn
*/
    if(black){
        socket->send(NetworkData(OPCODE::READY_OP,"A","BLACK","1"));
        // QMessageBox::about(this,"send","send ready op");
    }
    else{
        socket->send(NetworkData(OPCODE::READY_OP,"A","WHITE","1"));
        // QMessageBox::about(this,"send","send ready op");
    }
    flag=1;
    update();
}

Client::~Client(){
    delete ui;
}

void Client::receiveData(NetworkData data){
    if(data.op==OPCODE::READY_OP){
        if(data.data2=="BLACK"){
            isblack=0;
            your_turn=0;
            QMessageBox::about(this,"color","you become white player");
        }
        else{
            isblack=1;
            your_turn=1;
            QMessageBox::about(this,"color","you become black player");
        }
        emit Player_Black();
        ai_help_black();
    }
    else if(data.op==OPCODE::MOVE_OP){
        dep+=data.data1;
        dep+="-";
        dep+=data.data2;
        dep+=" ";
        int frx,fry,tx,ty;
        frx=qchar_to_int(data.data1[0]);
        fry=qchar_to_int(data.data1[1]);
        tx=qchar_to_int(data.data2[0]);
        ty=qchar_to_int(data.data2[1]);
        makemove(frx,fry,tx,ty);
    }
    else if(data.op==OPCODE::END_OP){
        dep+="#";
        dep+=data.data2[0];
        len=0;
        for(int i=0;i<dep.length();i++){
            char now=dep[i].toLatin1();
            qDebug()<<" "<<now;
            ans[len++]=now;
        }
        ans[len]=0;
        emit prt();
        if(data.data3=="BLACK"){
            if(isblack){
                QMessageBox message(QMessageBox::Information,"对局结束","你赢了！",QMessageBox::Yes|QMessageBox::No,NULL);
                message.setButtonText(QMessageBox::Yes,"再来一局");
                message.setButtonText(QMessageBox::No,"退出游戏");
                messagefunc(message);
            }
            else{
                QMessageBox message(QMessageBox::Information,"对局结束","你输了！",QMessageBox::Yes|QMessageBox::No,NULL);
                message.setButtonText(QMessageBox::Yes,"再来一局");
                message.setButtonText(QMessageBox::No,"退出游戏");
                messagefunc(message);
            }
        }
        else if(data.data3=="WHITE"){
            if(!isblack){
                QMessageBox message(QMessageBox::Information,"对局结束","你赢了！",QMessageBox::Yes|QMessageBox::No,NULL);
                message.setButtonText(QMessageBox::Yes,"再来一局");
                message.setButtonText(QMessageBox::No,"退出游戏");
                messagefunc(message);
            }
            else{
                QMessageBox message(QMessageBox::Information,"对局结束","你输了！",QMessageBox::Yes|QMessageBox::No,NULL);
                message.setButtonText(QMessageBox::Yes,"再来一局");
                message.setButtonText(QMessageBox::No,"退出游戏");
                messagefunc(message);
            }
        }
        else{
            QMessageBox message(QMessageBox::Information,"对局结束","平局！",QMessageBox::Yes|QMessageBox::No,NULL);
            message.setButtonText(QMessageBox::Yes,"再来一局");
            message.setButtonText(QMessageBox::No,"退出游戏");
            messagefunc(message);
        }
        // exit(0);
    }
}

void Client::messagefunc(QMessageBox &message)
{
    if(message.exec()==QMessageBox::Yes)//再来一局
    {
        QMessageBox::StandardButton ret;
        ret=QMessageBox::question(NULL,"white or black", "你是否想成为黑方（先手）");
        bool black=0;
        if(ret==QMessageBox::Yes)black=1;
        /*
initialize :
isblack your_turn
*/

        if(black){
            socket->send(NetworkData(OPCODE::READY_OP,"A","BLACK","1"));
            // QMessageBox::about(this,"send","send ready op");
        }
        else{
            socket->send(NetworkData(OPCODE::READY_OP,"A","WHITE","1"));
            // QMessageBox::about(this,"send","send ready op");
        }
        for(int i=0;i<6;i++)
            for(int j=0;j<2;j++)
                color[i][j]=PieceColor::BLACK;
        for(int i=0;i<6;i++)
            for(int j=2;j<4;j++)
                color[i][j]=PieceColor::NONE;
        for(int i=0;i<6;i++)
            for(int j=4;j<6;j++)
                color[i][j]=PieceColor::WHITE;
        fromx=-1;
    }
    else   //退出游戏
    {
        socket->send(NetworkData(OPCODE::LEAVE_OP,"","",""));
        socket->bye();
        exit(0);
    }
}

int Client::qchar_to_int(QChar ss){
    if(ss=='A')return 0;
    if(ss=='B')return 1;
    if(ss=='C')return 2;
    if(ss=='D')return 3;
    if(ss=='E')return 4;
    if(ss=='F')return 5;

    if(ss=='1')return 0;
    if(ss=='2')return 1;
    if(ss=='3')return 2;
    if(ss=='4')return 3;
    if(ss=='5')return 4;
    if(ss=='6')return 5;
    return 666;
}

void Client::paintEvent(QPaintEvent *)
{
    if(!flag)return;
    QPainter painter(this);

    //设置棋盘颜色为浅蓝色
    painter.setPen(QPen(Qt::black,3));
    painter.setBrush(QBrush(Qt::cyan));
    QRect rect(hb,vb,500,500);
    painter.drawRect(rect);

    //画boardsize条横线
    for(int i=0;i<BOARD_SIZE;i++)
    {
        painter.drawLine(QPoint(hb,(interval*i)+vb),QPoint((BOARD_SIZE-1)*interval+hb,interval*i+vb));
    }

    //画boardsize条竖线
    for(int i=0;i<BOARD_SIZE;i++)
    {
        painter.drawLine(QPoint((interval*i)+hb,vb),QPoint((interval*i+hb),(BOARD_SIZE-1)*interval+vb));
    }

    //画弧线
    for(int i=1;i<=arcnum/4;i++)
    {
        QRect rectlt(hb-interval*i,vb-interval*i,interval*2*i,interval*2*i);//左上弯曲轨道
        QRect rectlb(hb-interval*i,interval*(BOARD_SIZE-1-i)+vb,interval*2*i,interval*2*i);//左下弯曲轨道
        QRect rectrt((BOARD_SIZE-1-i)*interval+hb,vb-interval*i,interval*2*i,interval*2*i);//右上弯曲轨道
        QRect rectrb((BOARD_SIZE-1-i)*interval+hb,interval*(BOARD_SIZE-1-i)+vb,interval*2*i,interval*2*i);//右下弯曲轨道
        painter.drawArc(rectlt,0*16,270*16);
        painter.drawArc(rectlb,90*16,270*16);
        painter.drawArc(rectrt,180*16,-270*16);
        painter.drawArc(rectrb,90*16,-270*16);
    }

    // 画棋子
    for(int i=0;i<6;i++)
        for(int j=0;j<6;j++)
            drawPiece(painter,i,j);
}

void Client::drawPiece(QPainter &painter,int x,int y)
{
    if(color[x][y]==PieceColor::BLACK)
    {
        painter.setPen(QPen(Qt::black));
        painter.setBrush(QBrush(Qt::black));
        if(x==fromx&&y==fromy)
        {
            painter.setPen(QPen(Qt::white));
            painter.setBrush(QBrush(Qt::black,Qt::Dense1Pattern));
        }
        painter.drawEllipse(QPoint(hb+100*x,vb+100*y),r,r);
    }
    else if(color[x][y]==PieceColor::WHITE)
    {
        painter.setPen(QPen(Qt::white));
        painter.setBrush(QBrush(Qt::white));
        if(x==fromx&&y==fromy)
        {
            painter.setPen(QPen(Qt::black));
            painter.setBrush(QBrush(Qt::white,Qt::Dense1Pattern));
        }
        painter.drawEllipse(QPoint(hb+100*x,vb+100*y),r,r);
    }
}


void Client::mouseReleaseEvent(QMouseEvent *ev)
{
    if(!your_turn)return;
    if(enable_ai)return;
    QPoint pt= ev->pos();
    int xx,yy;
    if(hb-50<pt.x()&&pt.x()<hb+50)xx=0;
    else if(hb+50<pt.x()&&pt.x()<hb+150)xx=1;
    else if(hb+150<pt.x()&&pt.x()<hb+250)xx=2;
    else if(hb+250<pt.x()&&pt.x()<hb+350)xx=3;
    else if(hb+350<pt.x()&&pt.x()<hb+450)xx=4;
    else if(hb+450<pt.x()&&pt.x()<hb+550)xx=5;
    else return;
    if(vb-50<pt.y()&&pt.y()<vb+50)yy=0;
    else if(vb+50<pt.y()&&pt.y()<vb+150)yy=1;
    else if(vb+150<pt.y()&&pt.y()<vb+250)yy=2;
    else if(vb+250<pt.y()&&pt.y()<vb+350)yy=3;
    else if(vb+350<pt.y()&&pt.y()<vb+450)yy=4;
    else if(vb+450<pt.y()&&pt.y()<vb+550)yy=5;
    else return;
    double dx=pt.x()-(double)(hb+xx*100);
    double dy=pt.y()-(double)(vb+yy*100);
    if(dx*dx+dy*dy>1.0*r*r)return;

    // QMessageBox::about(this,"click","ok click");

    if(color[xx][yy]==PieceColor::NONE){
        if(fromx==-1)return;
        if(judgemove(fromx,fromy,xx,yy)){
            sendmove(fromx,fromy,xx,yy);
            return;
        }
    }
    else if(color[xx][yy]==PieceColor::WHITE){
        if(!isblack){
            fromx=xx,fromy=yy;
            update();
        }
        else{
            if(judgemove(fromx,fromy,xx,yy)){
                sendmove(fromx,fromy,xx,yy);
                return;
            }
        }
    }
    else if(color[xx][yy]==PieceColor::BLACK){
        if(isblack){
            fromx=xx,fromy=yy;
            update();
        }
        else{
            if(judgemove(fromx,fromy,xx,yy)){
                sendmove(fromx,fromy,xx,yy);
                return;
            }
        }
    }
}

QString Client::pos_to_data(int x,int y){
    QString ans="";
    ans+=(QChar)('A'+x);
    ans+=(QChar)('1'+y);
    return ans;
}

void Client::sendmove(int frx,int fry,int tx,int ty){
    if(isblack){
        socket->send(NetworkData(OPCODE::MOVE_OP,pos_to_data(frx,fry),pos_to_data(tx,ty),""));
    }
    else{
        socket->send(NetworkData(OPCODE::MOVE_OP,pos_to_data(frx,fry),pos_to_data(tx,ty),""));
    }
    makemove(frx,fry,tx,ty);
    fromx=-1;
}

void Client::makemove(int frx,int fry,int tx,int ty){
    color[tx][ty]=color[frx][fry];
    color[frx][fry]=PieceColor::NONE;
    your_turn^=1;
    update();
    if(your_turn){
        if(isblack){
            emit Player_Black();
            ai_help_black();
        }
        else{
            emit Player_White();
            ai_help_white();
        }
    }
    else{
        if(!isblack){
            emit Player_Black();
        }
        else{
            emit Player_White();
        }
    }
}

bool Client::judgemove(int frx,int fry,int tx,int ty){
    if(frx==tx&&fry==ty)return 0;
    if(frx<0||frx>=6||fry<0||fry>=6)return 0;
    if(tx<0||tx>=6||ty<0||ty>=6)return 0;

    if(color[frx][fry]==PieceColor::NONE)return 0;
    if(color[frx][fry]==color[tx][ty])return 0;

    if(color[tx][ty]==PieceColor::NONE){
        return abs(frx-tx)<=1&&abs(fry-ty)<=1;
    }
    PieceColor now=color[frx][fry];
    color[frx][fry]=PieceColor::NONE;
    if(check(frx,fry,0,tx,ty,0)||check(frx,fry,1,tx,ty,0)||check(frx,fry,2,tx,ty,0)||check(frx,fry,3,tx,ty,0)){
        color[frx][fry]=now;
        return 1;
    }
    color[frx][fry]=now;
    return 0;
}

bool Client::check(int x,int y,int dir,int edx,int edy,bool bk){
    if(x==edx&&y==edy)return bk;
    if(color[x][y]!=PieceColor::NONE)return 0;
    int xx=x+dx[dir],yy=y+dy[dir];
    if(0<=xx&&xx<=5&&0<=yy&&yy<=5)return check(xx,yy,dir,edx,edy,bk);
    if((x==0||x==5)&&(y==0||y==5))return 0;
    if(xx<0){
        if(0<=yy&&yy<3)return check(y,x,1,edx,edy,1);
        else return check(5-y,5,0,edx,edy,1);
    }
    if(xx>5){
        if(0<=yy&&yy<3)return check(5-y,0,1,edx,edy,1);
        else return check(y,5,0,edx,edy,1);
    }
    if(yy<0){
        if(0<=xx&&xx<3)return check(0,x,3,edx,edy,1);
        else return check(5,5-x,2,edx,edy,1);
    }
    if(yy>5){
        if(0<=xx&&xx<3)return check(0,5-x,3,edx,edy,1);
        else return check(5,x,2,edx,edy,1);
    }
    return 0;
}

void Client::slot_panel_button2_Clicked(){
    if(your_turn){
        socket->send(NetworkData(OPCODE::RESIGN_OP,"","",""));
    }
}

void Client::on_pushButton_clicked()
{
    if(flag)return;
    QString ss;
    ss=ui->textEdit->toPlainText();
    if(ss.length()){
        new_ip=ui->textEdit->toPlainText();
    }
    ss=ui->textEdit_2->toPlainText();
    if(ss.length()){
        new_port=0;
        for(int i=0;i<ss.length();i++){
            int tt;
            if(ss[i]=='0')tt=0;
            if(ss[i]=='1')tt=1;
            if(ss[i]=='2')tt=2;
            if(ss[i]=='3')tt=3;
            if(ss[i]=='4')tt=4;
            if(ss[i]=='5')tt=5;
            if(ss[i]=='6')tt=6;
            if(ss[i]=='7')tt=7;
            if(ss[i]=='8')tt=8;
            if(ss[i]=='9')tt=9;
            new_port=new_port*10+tt;
        }
    }
    emit ip_reset();
}

void Client::ai_help_black(){
    if(!your_turn)return;
    if(!isblack||!enable_ai)return;
    QThread::sleep(1);
    auto board_temp = std::make_shared<SurakartaBoard> (BOARD_SIZE);
    for(int x=0; x<BOARD_SIZE; x++){
        for(int y=0; y<BOARD_SIZE; y++){
            (*board_temp)[x][y] = std::make_shared<SurakartaPiece>();
            (*board_temp)[x][y]->SetColor(color[x][y]);
        }
    }
    auto game_info=std::make_shared<SurakartaGameInfo>();
    game_info->current_player_ = PieceColor::BLACK;
    auto rule_manager = std::make_shared<SurakartaRuleManager>(board_temp,game_info);
    SurakartaAgentMine agent(board_temp,game_info,rule_manager);
    auto move = agent.CalculateMove();
    // QThread::sleep(1);
    qDebug()<<move.from.x<<" "<<move.from.y<<" "<<move.to.x<<" "<<move.to.y;
    sendmove(move.from.x,move.from.y,move.to.x,move.to.y);
}


void Client::ai_help_white(){
    if(!your_turn)return;
    if(isblack||!enable_ai)return;
    QThread::sleep(1);
    auto board_temp = std::make_shared<SurakartaBoard> (BOARD_SIZE);
    for(int x=0; x<BOARD_SIZE; x++){
        for(int y=0; y<BOARD_SIZE; y++){
            (*board_temp)[x][y] = std::make_shared<SurakartaPiece>();
            (*board_temp)[x][y]->SetColor(color[x][y]);
        }
    }
    auto game_info=std::make_shared<SurakartaGameInfo>();
    game_info->current_player_ = PieceColor::WHITE;
    auto rule_manager = std::make_shared<SurakartaRuleManager>(board_temp,game_info);
    SurakartaAgentMine agent(board_temp,game_info,rule_manager);
    auto move = agent.CalculateMove();
    // QThread::sleep(1);
    qDebug()<<move.from.x<<" "<<move.from.y<<" "<<move.to.x<<" "<<move.to.y;
    sendmove(move.from.x,move.from.y,move.to.x,move.to.y);
}
