#ifndef WIDGET_H
#define WIDGET_H

#include <QFrame>
#include <QMessageBox>
#include "surakarta_piece.h"
#include "surakarta_common.h"

#define NCMCR_MAX 40  //连续不吃子的最大轮数

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QFrame
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);

    ~Widget();

    void initPiece(int id);

    QPoint SPosition_to_QPoint(SurakartaPosition);

    QPoint ID_to_QPoint(int);

    SurakartaPosition QPoint_to_SPosition(QPoint);

    int QPoint_to_ID(QPoint);

    void drawPiece(QPainter &painter,int id);

    void paintEvent(QPaintEvent *);

    virtual void mouseReleaseEvent(QMouseEvent *);

    bool isPiece(QPoint);

    bool isPiece(SurakartaPosition);

    bool Judge_capture_move(SurakartaMove&);

    int returnlinex(unsigned int x);

    int returnliney(unsigned int y);

    int up(const SurakartaMove& move);

    int down(const SurakartaMove& move);

    int left(const SurakartaMove& move);

    int right(const SurakartaMove& move);

    bool Game_is_over();

    void messagefunc(QMessageBox &messagebox);

private:
    SurakartaPiece Piece[4*BOARD_SIZE];//棋子集，[]中的数即为棋子ID（编号）,从左上角的白棋开始为0号，往右一个是1号，依此类推
    int selected_id;

    //图形化相关属性
    Ui::Widget *ui;
    int interval=500/(BOARD_SIZE-1);
    int vb=200;//棋盘与窗口上边的距离
    int hb=400;//棋盘与窗口左边的距离
    int r=interval/2-5;//棋子半径
    int PieceNum=4*BOARD_SIZE;//棋子数
    int arcnum=(BOARD_SIZE/2-1)*4;//弯曲轨道数

    //规则相关
    SurakartaGameInfo gameinfo;
    int NCMCR; //连续不吃子的轮数

signals:
    void Player_Black();
    void Player_White();

public slots:
    // void slotBack();
    void slot_panel_button0_Clicked();
    void slot_panel_button2_Clicked();
    void slot_panel_button3_Clicked();
    void slot_timeout();
};

#endif // WIDGET_H
