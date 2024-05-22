#ifndef SERVER_H
#define SERVER_H

#include<widget.h>
#include<networkserver.h>
#include<networksocket.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class Server;
}
QT_END_NAMESPACE

class Server : public QWidget
{
    Q_OBJECT
public:
    QString dep;
    int len;char ans[5100];
    NetworkServer* server;
    explicit Server(QWidget *parent = nullptr);
    ~Server();
    QTcpSocket *_white,*_black;
    QString _white_name,_black_name,current_player;
    const QString room_id="1";

    void paintEvent(QPaintEvent *);
    void drawPiece(QPainter &painter,int x,int y);
    int interval=500/(BOARD_SIZE-1);
    int vb=200;//棋盘与窗口上边的距离
    int hb=400;//棋盘与窗口左边的距离
    int r=interval/2-5;//棋子半径
    int PieceNum=4*BOARD_SIZE;//棋子数
    int arcnum=(BOARD_SIZE/2-1)*4;//弯曲轨道数

    PieceColor color[20][20];
    bool judgemove(int frx,int fry,int tx,int ty);
    void makemove(int frx,int fry,int tx,int ty);
    QString pos_to_data(int x,int y);
    const int dx[4]={0,0,-1,1};
    const int dy[4]={-1,1,0,0};
    bool check(int x,int y,int dir,int edx,int edy,bool bk);
    int qchar_to_int(QChar ss);
    int judgeend();
    void restart_game();

    int move_with_no_eat;

signals:
    void Player_Black();
    void Player_White();
    void prt();
public slots:
    void receiveData(QTcpSocket* client, NetworkData data);
    void slotNewConnection();
private:
    Ui::Server* ui;
};

#endif // SERVER_H
