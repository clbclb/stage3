#ifndef CLIENT_H
#define CLIENT_H

#include<widget.h>
#include<networksocket.h>
#include<surakarta_piece.h>
#include<QMouseEvent>

//namespace Ui {
//class Client;
//}

class Client : public QWidget
{
   Q_OBJECT
public:
   NetworkSocket *socket;
   explicit Client(QWidget *parent = nullptr);
    ~Client();
   bool isblack,your_turn;

   void paintEvent(QPaintEvent *);
   void drawPiece(QPainter &painter,int x,int y);
   int interval=500/(BOARD_SIZE-1);
   int vb=200;//棋盘与窗口上边的距离
   int hb=400;//棋盘与窗口左边的距离
   int r=interval/2-5;//棋子半径
   int PieceNum=4*BOARD_SIZE;//棋子数
   int arcnum=(BOARD_SIZE/2-1)*4;//弯曲轨道数

   virtual void mouseReleaseEvent(QMouseEvent *);
   PieceColor color[20][20];
   int fromx,fromy;
   bool judgemove(int frx,int fry,int tx,int ty);
   void makemove(int frx,int fry,int tx,int ty);
   void sendmove(int frx,int fry,int tx,int ty);
   QString pos_to_data(int x,int y);
   const int dx[4]={0,0,-1,1};
   const int dy[4]={-1,1,0,0};
   bool check(int x,int y,int dir,int edx,int edy,bool bk);
   int qchar_to_int(QChar ss);
   void messagefunc(QMessageBox &message);

private:
    //Ui::Client *ui;

public slots:
    void receiveData(NetworkData data);
};

#endif // CLIENT_H
