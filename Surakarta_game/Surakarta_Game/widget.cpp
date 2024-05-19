#include "widget.h"
#include "ui_widget.h"
#include "choose_dialog.h"
#include<QPainter>
#include<QMouseEvent>
#include<cmath>
#include<QMessageBox>

Widget::Widget(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    selected_id=-1;//未选中任何棋子

    for(int i=0;i<PieceNum;i++)
    {
        initPiece(i);
    }//初始化棋子

    NCMCR=0;

    gameinfo.current_player_=PieceColor::BLACK;
}

Widget::~Widget()
{
    delete ui;
}

//棋子初始化
void Widget::initPiece(int id)
{
    if(id<2*BOARD_SIZE)
    {
        Piece[id].Set(SurakartaPosition(id%BOARD_SIZE,id/BOARD_SIZE),PieceColor::WHITE,id,false);
        //(*board)[id%BOARD_SIZE][id/BOARD_SIZE]=std::make_shared<SurakartaPiece>(Piece[id]);
    }//上方白棋
    else
    {
        Piece[id].Set(SurakartaPosition(id%BOARD_SIZE,(id-(2*BOARD_SIZE))/BOARD_SIZE+BOARD_SIZE-2),PieceColor::BLACK,id,false);
        //(*board)[id%BOARD_SIZE][(id-(2*BOARD_SIZE))/BOARD_SIZE+BOARD_SIZE-2]=std::make_shared<SurakartaPiece>(Piece[id]);
    }//下方黑棋
}

//坐标转换为QPoint(窗口中的位置)(返回的是棋子像素中心点)
QPoint Widget::SPosition_to_QPoint(SurakartaPosition position)
{
    if(position.x>=BOARD_SIZE || position.y>=BOARD_SIZE) return QPoint(0,0);
    QPoint point(hb+position.x*interval,vb+position.y*interval);
    return point;
}

//棋子编号转换为QPoint(窗口中的位置)(返回的是棋子像素中心点)
QPoint Widget::ID_to_QPoint(int ID)
{
    if(ID>=PieceNum) return QPoint(0,0);
    return SPosition_to_QPoint(Piece[ID].GetPosition());
}

//像素转换为坐标（坐标周围棋子大小圆形区域均能转化为该坐标）
SurakartaPosition Widget::QPoint_to_SPosition(QPoint point)
{
    for(int y=0;y<BOARD_SIZE;y++)
    {
        for(int x=0;x<BOARD_SIZE;x++)
        {
            QPoint center(hb+x*interval,vb+y*interval);
            bool in_the_region=(sqrt(pow(center.x()-point.x(),2)+pow(center.y()-point.y(),2))<r);
            if(in_the_region)
                return SurakartaPosition(x,y);
        }
    }
    return SurakartaPosition(BOARD_SIZE,BOARD_SIZE);//若像素点在某些特殊区域，则返回棋盘上不存在的点
}

//像素转换为棋子ID（坐标周围棋子大小圆形区域均能转化为该ID）
int Widget::QPoint_to_ID(QPoint point)
{
    for (int i=0;i<PieceNum;i++)
    {
        if(Piece[i].GetPosition()==QPoint_to_SPosition(point))
            return i;
    }

    return PieceNum;//若像素点在某些特殊区域或没有棋子的区域，则返回棋子集合不存在的ID
}

//画图
void Widget::paintEvent(QPaintEvent *)
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
    for(int i=0;i<PieceNum;i++)
    {
        drawPiece(painter,i);
    }
}

//画单个棋子（ID已知）
void Widget::drawPiece(QPainter &painter,int id)
{
    if(id>=PieceNum) return;
    if(Piece[id].isdead) return;
    if(Piece[id].GetPosition().x>=BOARD_SIZE||Piece[id].GetPosition().y>=BOARD_SIZE) return;
    else if(Piece[id].GetColor()==PieceColor::BLACK)
    {
        painter.setPen(QPen(Qt::black));
        painter.setBrush(QBrush(Qt::black));
        if(id==selected_id)
        {
            painter.setPen(QPen(Qt::white));
            painter.setBrush(QBrush(Qt::black,Qt::Dense1Pattern));
        }
        painter.drawEllipse(ID_to_QPoint(id),r,r);
    }
    else if(Piece[id].GetColor()==PieceColor::WHITE)
    {
        painter.setPen(QPen(Qt::white));
        painter.setBrush(QBrush(Qt::white));
        if(id==selected_id)
        {
            painter.setPen(QPen(Qt::black));
            painter.setBrush(QBrush(Qt::white,Qt::Dense1Pattern));
        }
        painter.drawEllipse(ID_to_QPoint(id),r,r);
    }
}

//判断某个像素范围内是否有棋子
bool Widget::isPiece(QPoint point)
{
    if(QPoint_to_ID(point)<PieceNum)
        return true;
    else return false;
}

//判断某个坐标上是否有棋子
bool Widget::isPiece(SurakartaPosition pos)
{
    if(QPoint_to_ID(SPosition_to_QPoint(pos))<PieceNum)
        return true;
    else return false;
}

int Widget::returnlinex(unsigned int x) {
    if (x < BOARD_SIZE / 2)
        return x;
    else
        return (BOARD_SIZE - 1 - x);
}

int Widget::returnliney(unsigned int y) {
    if (y < BOARD_SIZE / 2)
        return y;
    else
        return (BOARD_SIZE - 1 - y);
}

int Widget::up(const SurakartaMove& move) {
    if (move.from.x == 0 || move.from.x == BOARD_SIZE - 1)
        return 0;
    for (int i = move.from.y - 1; i >= 0; i--) {
        if (isPiece(SurakartaPosition(move.from.x,i)))
            return 0;
    }
    if (move.from.x < BOARD_SIZE / 2) {
        int tmp_x = 0;
        int tmp_y = move.from.x;
        for (; (unsigned int)tmp_x < BOARD_SIZE; tmp_x++) {
            if (isPiece(SurakartaPosition(tmp_x,tmp_y)) && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                return 0;
            else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                return 1;
        }
        tmp_x = BOARD_SIZE - 1 - tmp_y;
        tmp_y = 0;
        for (; (unsigned int)tmp_y < BOARD_SIZE; tmp_y++) {
            if (isPiece(SurakartaPosition(tmp_x,tmp_y)) && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                return 0;
            else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                return 1;
        }
        tmp_y = tmp_x;
        tmp_x = BOARD_SIZE - 1;
        for (; tmp_x >= 0; tmp_x--) {
            if (isPiece(SurakartaPosition(tmp_x,tmp_y)) && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                return 0;
            else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                return 1;
        }
        tmp_x = BOARD_SIZE - 1 - tmp_y;
        tmp_y = BOARD_SIZE - 1;
        for (; (unsigned int)tmp_y > move.from.y; tmp_y--) {
            if (isPiece(SurakartaPosition(tmp_x,tmp_y)) && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                return 0;
            else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                return 1;
        }
    } else if (move.from.x >= BOARD_SIZE / 2) {
        int tmp_x = BOARD_SIZE - 1;
        int tmp_y = BOARD_SIZE - 1 - move.from.x;
        for (; tmp_x >= 0; tmp_x--) {
            if (isPiece(SurakartaPosition(tmp_x,tmp_y)) && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                return 0;
            else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                return 1;
        }
        tmp_x = tmp_y;
        tmp_y = 0;
        for (; (unsigned int)tmp_y < BOARD_SIZE; tmp_y++) {
            if (isPiece(SurakartaPosition(tmp_x,tmp_y)) && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                return 0;
            else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                return 1;
        }
        tmp_y = BOARD_SIZE - 1 - tmp_x;
        tmp_x = 0;
        for (; (unsigned int)tmp_x < BOARD_SIZE; tmp_x++) {
            if (isPiece(SurakartaPosition(tmp_x,tmp_y)) && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                return 0;
            else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                return 1;
        }
        tmp_x = tmp_y;
        tmp_y = BOARD_SIZE - 1;
        for (; (unsigned int)tmp_y > move.from.y; tmp_y--) {
            if (isPiece(SurakartaPosition(tmp_x,tmp_y)) && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                return 0;
            else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                return 1;
        }
    }
    return 0;
}

int Widget::down(const SurakartaMove& move) {
    if (move.from.x == 0 || move.from.x == BOARD_SIZE - 1)
        return 0;
    for (int i = move.from.y + 1; (unsigned int)i < BOARD_SIZE; i++) {
        if (isPiece(SurakartaPosition(move.from.x,i)))
            return 0;
    }
    if (move.from.x < BOARD_SIZE / 2) {
        int tmp_x = 0;
        int tmp_y = BOARD_SIZE - 1 - move.from.x;
        for (; (unsigned int)tmp_x < BOARD_SIZE; tmp_x++) {
            if (isPiece(SurakartaPosition(tmp_x,tmp_y)) && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                return 0;
            else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                return 1;
        }
        tmp_x = tmp_y;
        tmp_y = BOARD_SIZE - 1;
        for (; tmp_y >= 0; tmp_y--) {
            if (isPiece(SurakartaPosition(tmp_x,tmp_y)) && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                return 0;
            else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                return 1;
        }
        tmp_y = BOARD_SIZE - 1 - tmp_x;
        tmp_x = BOARD_SIZE - 1;
        for (; tmp_x >= 0; tmp_x--) {
            if (isPiece(SurakartaPosition(tmp_x,tmp_y)) && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                return 0;
            else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                return 1;
        }
        tmp_x = tmp_y;
        tmp_y = 0;
        for (; (unsigned int)tmp_y < move.from.y; tmp_y++) {
            if (isPiece(SurakartaPosition(tmp_x,tmp_y)) && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                return 0;
            else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                return 1;
        }
    } else if (move.from.x >= BOARD_SIZE / 2) {
        int tmp_x = BOARD_SIZE - 1;
        int tmp_y = move.from.x;
        for (; tmp_x >= 0; tmp_x--) {
            if (isPiece(SurakartaPosition(tmp_x,tmp_y)) && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                return 0;
            else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                return 1;
        }
        tmp_x = BOARD_SIZE - 1 - tmp_y;
        tmp_y = BOARD_SIZE - 1;
        for (; tmp_y >= 0; tmp_y--) {
            if (isPiece(SurakartaPosition(tmp_x,tmp_y)) && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                return 0;
            else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                return 1;
        }
        tmp_y = tmp_x;
        tmp_x = 0;
        for (; (unsigned int)tmp_x < BOARD_SIZE; tmp_x++) {
            if (isPiece(SurakartaPosition(tmp_x,tmp_y)) && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                return 0;
            else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                return 1;
        }
        tmp_x = BOARD_SIZE - 1 - tmp_y;
        tmp_y = 0;
        for (; (unsigned int)tmp_y < move.from.y; tmp_y++) {
            if (isPiece(SurakartaPosition(tmp_x,tmp_y)) && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                return 0;
            else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                return 1;
        }
    }
    return 0;
}

int Widget::left(const SurakartaMove& move) {
    if (move.from.y == 0 || move.from.y == BOARD_SIZE - 1)
        return 0;
    for (int i = move.from.x - 1; i >= 0; i--) {
        if (isPiece(SurakartaPosition(i,move.from.y)))
            return 0;
    }
    if (move.from.y < BOARD_SIZE / 2) {
        int tmp_y = 0;
        int tmp_x = move.from.y;
        for (; (unsigned int)tmp_y < BOARD_SIZE; tmp_y++) {
            if (isPiece(SurakartaPosition(tmp_x,tmp_y)) && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                return 0;
            else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                return 1;
        }
        tmp_y = BOARD_SIZE - 1 - tmp_x;
        tmp_x = 0;
        for (; (unsigned int)tmp_x < BOARD_SIZE; tmp_x++) {
            if (isPiece(SurakartaPosition(tmp_x,tmp_y)) && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                return 0;
            else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                return 1;
        }
        tmp_x = tmp_y;
        tmp_y = BOARD_SIZE - 1;
        for (; tmp_y >= 0; tmp_y--) {
            if (isPiece(SurakartaPosition(tmp_x,tmp_y)) && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                return 0;
            else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                return 1;
        }
        tmp_y = BOARD_SIZE - 1 - tmp_x;
        tmp_x = BOARD_SIZE - 1;
        for (; (unsigned int)tmp_x > move.from.x; tmp_x--) {
            if (isPiece(SurakartaPosition(tmp_x,tmp_y)) && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                return 0;
            else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                return 1;
        }
    } else if (move.from.y >= BOARD_SIZE / 2)  // tab
    {
        int tmp_y = BOARD_SIZE - 1;
        int tmp_x = BOARD_SIZE - 1 - move.from.y;
        for (; tmp_y >= 0; tmp_y--) {
            if (isPiece(SurakartaPosition(tmp_x,tmp_y)) && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                return 0;
            else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                return 1;
        }
        tmp_y = tmp_x;
        tmp_x = 0;
        for (; (unsigned int)tmp_x < BOARD_SIZE; tmp_x++) {
            if (isPiece(SurakartaPosition(tmp_x,tmp_y)) && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                return 0;
            else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                return 1;
        }
        tmp_x = BOARD_SIZE - 1 - tmp_y;
        tmp_y = 0;
        for (; (unsigned int)tmp_y < BOARD_SIZE; tmp_y++) {
            if (isPiece(SurakartaPosition(tmp_x,tmp_y)) && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                return 0;
            else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                return 1;
        }
        tmp_y = tmp_x;
        tmp_x = BOARD_SIZE - 1;
        for (; (unsigned int)tmp_x > move.from.x; tmp_x--) {
            if (isPiece(SurakartaPosition(tmp_x,tmp_y)) && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                return 0;
            else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                return 1;
        }
    }
    return 0;
}

int Widget::right(const SurakartaMove& move) {
    if (move.from.y == 0 || move.from.y == BOARD_SIZE - 1)
        return 0;
    for (int i = move.from.x + 1; (unsigned int)i < BOARD_SIZE; i++) {
        if (isPiece(SurakartaPosition(i,move.from.y)))
            return 0;
    }
    if (move.from.y < BOARD_SIZE / 2) {
        int tmp_y = 0;
        int tmp_x = BOARD_SIZE - 1 - move.from.y;
        for (; (unsigned int)tmp_y < BOARD_SIZE; tmp_y++) {
            if (isPiece(SurakartaPosition(tmp_x,tmp_y)) && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                return 0;
            else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                return 1;
        }
        tmp_y = tmp_x;
        tmp_x = BOARD_SIZE - 1;
        for (; tmp_x >= 0; tmp_x--) {
            if (isPiece(SurakartaPosition(tmp_x,tmp_y)) && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                return 0;
            else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                return 1;
        }
        tmp_x = BOARD_SIZE - 1 - tmp_y;
        tmp_y = BOARD_SIZE - 1;
        for (; tmp_y >= 0; tmp_y--) {
            if (isPiece(SurakartaPosition(tmp_x,tmp_y)) && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                return 0;
            else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                return 1;
        }
        tmp_y = tmp_x;
        tmp_x = 0;
        for (; (unsigned int)tmp_x < move.from.x; tmp_x++) {
            if (isPiece(SurakartaPosition(tmp_x,tmp_y)) && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                return 0;
            else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                return 1;
        }
    } else if (move.from.y >= BOARD_SIZE / 2) {
        int tmp_y = BOARD_SIZE - 1;
        int tmp_x = move.from.y;
        for (; tmp_y >= 0; tmp_y--) {
            if (isPiece(SurakartaPosition(tmp_x,tmp_y)) && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                return 0;
            else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                return 1;
        }
        tmp_y = BOARD_SIZE - 1 - tmp_x;
        tmp_x = BOARD_SIZE - 1;
        for (; tmp_x >= 0; tmp_x--) {
            if (isPiece(SurakartaPosition(tmp_x,tmp_y)) && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                return 0;
            else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                return 1;
        }
        tmp_x = tmp_y;
        tmp_y = 0;
        for (; (unsigned int)tmp_y < BOARD_SIZE; tmp_y++) {
            if (isPiece(SurakartaPosition(tmp_x,tmp_y)) && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                return 0;
            else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                return 1;
        }
        tmp_y = BOARD_SIZE - 1 - tmp_x;
        tmp_x = 0;
        for (; (unsigned int)tmp_x < move.from.x; tmp_x++) {
            if (isPiece(SurakartaPosition(tmp_x,tmp_y)) && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                return 0;
            else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                return 1;
        }
    }
    return 0;
}

bool Widget::Judge_capture_move(SurakartaMove &move)
{
    int line[BOARD_SIZE][BOARD_SIZE * 5];
    memset(line, 0, sizeof(line));
    int line_fromx = returnlinex(move.from.x);
    int line_fromy = returnliney(move.from.y);
    int line_tox = returnlinex(move.to.x);
    int line_toy = returnliney(move.to.y);
    int flag = 0;
    if (line_fromx != line_tox && line_fromy != line_toy && line_fromx != line_toy && line_fromy != line_tox)
        return false;
    else {
        if (line_fromx == line_tox || line_fromx == line_toy) {
            flag += up(move);
            flag += down(move);
        }

        if (line_fromy == line_toy || line_fromy == line_tox) {
            flag += left(move);
            flag += right(move);
        }
    }
    if (!flag)
        return false;
    else
        return true;
}

void Widget::mouseReleaseEvent(QMouseEvent *ev)
{
    QPoint pt= ev->pos();

    //第一次点击
    if(selected_id==-1)
    {
        if(!isPiece(pt)||Piece[QPoint_to_ID(pt)].GetColor()!=gameinfo.current_player_)
            return;
        selected_id=QPoint_to_ID(pt);
        update();
    }//只能选中棋子

    //再次点击，涉及棋子移动
    else
    {
        if(QPoint_to_SPosition(pt).x>=BOARD_SIZE||QPoint_to_SPosition(pt).y>=BOARD_SIZE) return;
        if(QPoint_to_ID(pt)==selected_id)
        {
            selected_id=-1;
            update();
            return;
        }//再次点击会取消选中

        //不吃子
        if(!isPiece(pt))
        {
            SurakartaPosition pos_to=QPoint_to_SPosition(pt);
            int from_x,from_y,to_x,to_y;
            from_x=Piece[selected_id].GetPosition().x;
            from_y=Piece[selected_id].GetPosition().y;
            to_x=pos_to.x;
            to_y=pos_to.y;
            if(abs(to_x-from_x)>1||abs(to_y-from_y)>1) return;//不在走棋范围内

            //移动棋子
            Piece[selected_id].SetPosition(QPoint_to_SPosition(pt));

            //释放选中
            selected_id=-1;

            //更换current_player_
            if(gameinfo.current_player_==PieceColor::BLACK)
            {
                gameinfo.current_player_=PieceColor::WHITE;
                emit Player_White();
            }
            else
            {
                gameinfo.current_player_=PieceColor::BLACK;
                emit Player_Black();
            }
            update();

            NCMCR++;
            if(NCMCR>NCMCR_MAX)
            {
                int white_living=0,black_living=0;
                for(int i=0;i<PieceNum/2;i++)
                {
                    if(!Piece[i]._isdead())
                        white_living++;
                }
                for(int i=PieceNum/2;i<PieceNum;i++)
                {
                    if(!Piece[i]._isdead())
                        black_living++;
                }
                if(white_living>black_living)
                {
                    QMessageBox message(QMessageBox::Information,"对局结束","白方胜！",QMessageBox::Yes|QMessageBox::No,NULL);
                    message.setButtonText(QMessageBox::Yes,"再来一局");
                    message.setButtonText(QMessageBox::No,"退出游戏");
                    messagefunc(message);
                }
                else if(white_living<black_living)
                {
                    QMessageBox message(QMessageBox::Information,"对局结束","黑方胜！",QMessageBox::Yes|QMessageBox::No,NULL);
                    message.setButtonText(QMessageBox::Yes,"再来一局");
                    message.setButtonText(QMessageBox::No,"退出游戏");
                    messagefunc(message);
                }
                else
                {
                    QMessageBox message(QMessageBox::Information,"对局结束","平局！",QMessageBox::Yes|QMessageBox::No,NULL);
                    message.setButtonText(QMessageBox::Yes,"再来一局");
                    message.setButtonText(QMessageBox::No,"退出游戏");
                    messagefunc(message);
                }
            }


            return;
        }

        //吃子
        if(isPiece(pt))
        {
            if(Piece[QPoint_to_ID(pt)].GetColor()==Piece[selected_id].GetColor())
            {
                selected_id=QPoint_to_ID(pt);//改变选中子
                update();
                return; //不能吃自己的子
            }

            SurakartaMove move(Piece[selected_id].GetPosition(),QPoint_to_SPosition(pt),gameinfo.current_player_);

            if(Judge_capture_move(move))
            {
                //对方棋子死亡
                Piece[QPoint_to_ID(pt)].dead();


                //移动棋子
                Piece[selected_id].SetPosition(QPoint_to_SPosition(pt));

                //释放选中
                selected_id=-1;

                NCMCR=0;//连续不吃子的轮数清零

                update();

                if(Game_is_over())
                {
                    return;
                }

                //更换current_player_
                if(gameinfo.current_player_==PieceColor::BLACK)
                {
                    gameinfo.current_player_=PieceColor::WHITE;
                    emit Player_White();
                }
                else
                {
                    gameinfo.current_player_=PieceColor::BLACK;
                    emit Player_Black();
                }

                return;
            }
        }
    }
}

bool Widget::Game_is_over()
{
    if(gameinfo.current_player_==PieceColor::BLACK)//黑棋吃完子后，判断白棋死光了没
    {
        for(int i=0;i<PieceNum/2;i++)
        {
            if(!Piece[i]._isdead())
                return false;
        }
        QMessageBox message(QMessageBox::Information,"对局结束","黑方胜！",QMessageBox::Yes|QMessageBox::No,NULL);
        message.setButtonText(QMessageBox::Yes,"再来一局");
        message.setButtonText(QMessageBox::No,"退出游戏");
        messagefunc(message);
        return true;
    }
    else//白棋吃完子后，判断黑棋死光了没
    {
        for(int i=PieceNum/2;i<PieceNum;i++)
        {
            if(!Piece[i]._isdead())
                return false;
        }
        QMessageBox message(QMessageBox::Information,"对局结束","白方胜！",QMessageBox::Yes|QMessageBox::No,NULL);
        message.setButtonText(QMessageBox::Yes,"再来一局");
        message.setButtonText(QMessageBox::No,"退出游戏");
        messagefunc(message);
        return true;
    }
}

void Widget::messagefunc(QMessageBox &message)
{
    if(message.exec()==QMessageBox::Yes)//再来一局
    {
        selected_id=-1;//未选中任何棋子

        for(int i=0;i<PieceNum;i++)
        {
            initPiece(i);
        }//初始化棋子

        gameinfo.current_player_=PieceColor::BLACK;

        emit Player_Black();

        NCMCR=0;

        update();
    }
    else   //退出游戏
    {
        exit(0);
    }
}

void Widget::slot_panel_button0_Clicked()
{
    selected_id=-1;//未选中任何棋子

    for(int i=0;i<PieceNum;i++)
    {
        initPiece(i);
    }//初始化棋子

    gameinfo.current_player_=PieceColor::BLACK;

    emit Player_Black();

    update();
}

void Widget::slot_panel_button2_Clicked()
{
    if(gameinfo.current_player_==PieceColor::BLACK)
    {
        QMessageBox message(QMessageBox::Information,"对局结束","白方胜！",QMessageBox::Yes|QMessageBox::No,NULL);
        message.setButtonText(QMessageBox::Yes,"再来一局");
        message.setButtonText(QMessageBox::No,"退出游戏");
        messagefunc(message);
    }
    else
    {
        QMessageBox message(QMessageBox::Information,"对局结束","黑方胜！",QMessageBox::Yes|QMessageBox::No,NULL);
        message.setButtonText(QMessageBox::Yes,"再来一局");
        message.setButtonText(QMessageBox::No,"退出游戏");
        messagefunc(message);
    }
}

void Widget::slot_panel_button3_Clicked()
{
    QMessageBox msgbox(QMessageBox::Information,"提示","功能开发中~");
    msgbox.exec();
}

void Widget::slot_timeout()
{
    if(gameinfo.current_player_==PieceColor::BLACK)
    {
        QMessageBox message(QMessageBox::Information,"对局结束","白方胜！",QMessageBox::Yes|QMessageBox::No,NULL);
        message.setButtonText(QMessageBox::Yes,"再来一局");
        message.setButtonText(QMessageBox::No,"退出游戏");
        messagefunc(message);
    }
    else
    {
        QMessageBox message(QMessageBox::Information,"对局结束","黑方胜！",QMessageBox::Yes|QMessageBox::No,NULL);
        message.setButtonText(QMessageBox::Yes,"再来一局");
        message.setButtonText(QMessageBox::No,"退出游戏");
        messagefunc(message);
    }
}
