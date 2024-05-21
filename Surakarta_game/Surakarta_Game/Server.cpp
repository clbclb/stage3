#include<Server.h>
#include<networkdata.h>
#include<QPainter>

Server::Server(QWidget *parent)
    :QWidget{parent}
{
    _white=NULL;
    _black=NULL;
    move_with_no_eat=0;
    server=new NetworkServer(this);
    server->listen(QHostAddress::Any,1);
    connect(server, &NetworkServer::newConnection, this, &Server::slotNewConnection);
    connect(server, &NetworkServer::receive, this, &Server::receiveData);
    current_player="BLACK";
    for(int i=0;i<6;i++)
        for(int j=0;j<2;j++)
            color[i][j]=PieceColor::BLACK;
    for(int i=0;i<6;i++)
        for(int j=2;j<4;j++)
            color[i][j]=PieceColor::NONE;
    for(int i=0;i<6;i++)
        for(int j=4;j<6;j++)
            color[i][j]=PieceColor::WHITE;
}

Server::~Server(){

}

void Server::slotNewConnection(){
    // QMessageBox::about(this,"ooo","congratulations you build a new connection");
}

int Server::judgeend(){
    bool exist_white=0;
    for(int i=0;i<6;i++)
        for(int j=0;j<6;j++)
            if(color[i][j]==PieceColor::WHITE)
                exist_white=1;
    if(!exist_white)return 1;
    bool exist_black=0;
    for(int i=0;i<6;i++)
        for(int j=0;j<6;j++)
            if(color[i][j]==PieceColor::BLACK)
                exist_black=1;
    if(!exist_black)return 2;
    if(move_with_no_eat>4)return 3;
    return 4;
}

void Server::receiveData(QTcpSocket* client, NetworkData data){
    if(client==_white&&current_player=="BLACK"){
        return;
    }
    if(client==_black&&current_player=="WHITE"){
        return;
    }
    if(data.op==OPCODE::READY_OP){
        if(data.data3!=room_id)return;
        if(_white&&_black)return;
        if(_white==NULL&&_black==NULL){
            if(data.data2=="WHITE"){
                _white=client;
                _white_name=data.data1;
            }
            else if(data.data2=="BLACK"){
                _black=client;
                _black_name=data.data1;
            }
            else{
                return;
            }
        }
        else{
            if(_white==NULL){
                _white=client;
                _white_name=data.data1;
            }
            else{
                _black=client;
                _black_name=data.data1;
            }
            server->send(_white,NetworkData(OPCODE::READY_OP,_black_name,"BLACK",room_id));
            server->send(_black,NetworkData(OPCODE::READY_OP,_white_name,"WHITE",room_id));
        }
    }
    else if(data.op==OPCODE::MOVE_OP){
        int frx=qchar_to_int(data.data1[0]);
        int fry=qchar_to_int(data.data1[1]);
        int tx=qchar_to_int(data.data2[0]);
        int ty=qchar_to_int(data.data2[1]);
        if(judgemove(frx,fry,tx,ty)){
            if(color[tx][ty]==PieceColor::NONE)move_with_no_eat++;
            else move_with_no_eat=0;
            makemove(frx,fry,tx,ty);
            server->send(_white,NetworkData(OPCODE::MOVE_OP,pos_to_data(frx,fry),pos_to_data(tx,ty),""));
            server->send(_black,NetworkData(OPCODE::MOVE_OP,pos_to_data(frx,fry),pos_to_data(tx,ty),""));
            if(current_player=="BLACK")current_player="WHITE";
            else current_player="BLACK";
            int tt=judgeend();
            if(tt==1){
                //black eat all white
                server->send(_white,NetworkData(OPCODE::END_OP,"","CHECKMATE","BLACK"));
                server->send(_black,NetworkData(OPCODE::END_OP,"","CHECKMATE","BLACK"));
                restart_game();
            }
            else if(tt==2){
                //white eat all black
                server->send(_white,NetworkData(OPCODE::END_OP,"","CHECKMATE","WHITE"));
                server->send(_black,NetworkData(OPCODE::END_OP,"","CHECKMATE","WHITE"));
                restart_game();
            }
            else if(tt==3){
                //no capture move
                server->send(_white,NetworkData(OPCODE::END_OP,"","","NONE"));
                server->send(_black,NetworkData(OPCODE::END_OP,"","","NONE"));
                restart_game();
            }
            else{
                //move on
            }
        }
        else{
            //end
        }
    }
    else if(data.op==OPCODE::LEAVE_OP){

    }
}

void Server::restart_game(){
    _white=NULL;
    _black=NULL;
    current_player="BLACK";
    move_with_no_eat=0;
    for(int i=0;i<6;i++)
        for(int j=0;j<2;j++)
            color[i][j]=PieceColor::BLACK;
    for(int i=0;i<6;i++)
        for(int j=2;j<4;j++)
            color[i][j]=PieceColor::NONE;
    for(int i=0;i<6;i++)
        for(int j=4;j<6;j++)
            color[i][j]=PieceColor::WHITE;
    update();
}

void Server::paintEvent(QPaintEvent *)
{
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

void Server::drawPiece(QPainter &painter,int x,int y)
{
    if(color[x][y]==PieceColor::BLACK)
    {
        painter.setPen(QPen(Qt::black));
        painter.setBrush(QBrush(Qt::black));
        painter.drawEllipse(QPoint(hb+100*x,vb+100*y),r,r);
    }
    else if(color[x][y]==PieceColor::WHITE)
    {
        painter.setPen(QPen(Qt::white));
        painter.setBrush(QBrush(Qt::white));
        painter.drawEllipse(QPoint(hb+100*x,vb+100*y),r,r);
    }
}

QString Server::pos_to_data(int x,int y){
    QString ans="";
    ans+=(QChar)('A'+x);
    ans+=(QChar)('1'+y);
    return ans;
}

void Server::makemove(int frx,int fry,int tx,int ty){
    color[tx][ty]=color[frx][fry];
    color[frx][fry]=PieceColor::NONE;
    update();
}

bool Server::judgemove(int frx,int fry,int tx,int ty){

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

bool Server::check(int x,int y,int dir,int edx,int edy,bool bk){
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


int Server::qchar_to_int(QChar ss){
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
