#ifndef CLIENT_H
#define CLIENT_H

#include<widget.h>
#include<networksocket.h>
#include<surakarta_piece.h>
#include<QMouseEvent>
#include"ctrlpanel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Client;
}
QT_END_NAMESPACE

class Client : public QWidget
{
   Q_OBJECT
public:
   QString dep;
   int len;char ans[5100];
   bool black,flag=0;
   //flag means you have create you are ready and you can begin to paint
   bool enable_ai=1;
   //pay attention : black is the color you choose, while isblack is about the color you get
   
   NetworkSocket *socket;
   explicit Client(QString s1="127.0.0.1",QString s2="10086",QString s3="BLACK",QWidget *parent = nullptr);
    ~Client();
   bool isblack,your_turn;
   class CtrlPanel* _ctrlpanel;

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
   void ai_help_black();
   void ai_help_white();
   int move_with_no_eat;
   void judgeend(int &s1,int &s2);

public slots:
    void receiveData(NetworkData data);
private:
    Ui::Client *ui;

signals:
    void Player_Black();
    void Player_White();
    void ip_reset();
    void prt();

public slots:
    // void slotBack();
    // void slot_panel_button0_Clicked();
    void slot_panel_button2_Clicked();
    // void slot_panel_button3_Clicked();
    // void slot_timeout();
    void initgame();
public:
    QString new_ip="127.0.0.1";
    quint64 new_port=10086;
private slots:
    void on_pushButton_clicked();
};

#endif // CLIENT_H
