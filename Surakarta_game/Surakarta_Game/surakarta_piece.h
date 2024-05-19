#pragma once

#ifndef SURAKARTAPIECE_H
#define SURAKARTAPIECE_H

#define BOARD_SIZE 6

using PieceColorMemoryType = int;
enum class PieceColor : PieceColorMemoryType { BLACK,
                                               WHITE,
                                               NONE,
                                               UNKNOWN
};

using SurakartaPlayer = PieceColor;

inline PieceColor ReverseColor(PieceColor color) {
    switch (color) {
    case PieceColor::BLACK:
        return PieceColor::WHITE;
    case PieceColor::WHITE:
        return PieceColor::BLACK;
    default:
        return color;
    }
}

struct SurakartaPosition {
    unsigned int x;
    unsigned int y;
    SurakartaPosition(unsigned int x = 0, unsigned int y = 0)
        : x(x), y(y) {}
    bool operator==(const SurakartaPosition& rhs) const {
        return x == rhs.x && y == rhs.y;
    }
    bool operator!=(const SurakartaPosition& rhs) const {
        return !(*this == rhs);
    }
};

class SurakartaPiece {
public:
    SurakartaPiece()
        : position_({0, 0}), color_(PieceColor::NONE) {}

    SurakartaPiece(unsigned int x, unsigned int y, PieceColor color)
        : position_({x, y}), color_(color) {}

    SurakartaPiece(SurakartaPosition position, PieceColor color)
        : position_(position), color_(color) {}

    void SetPosition(SurakartaPosition position) { position_ = position; }
    void SetColor(PieceColor color) { color_ = color; }
    void Set(SurakartaPosition position, PieceColor color,int ID,bool _isdead) {
        position_ = position;
        color_ = color;
        id=ID;
        isdead=_isdead;
    }
    void dead()
    {
        isdead=true;
        SetPosition(SurakartaPosition(BOARD_SIZE,BOARD_SIZE));
    }
    void alive()//复活
    {
        isdead=false;
    }
    bool _isdead()
    {
        return isdead;
    }
    SurakartaPosition GetPosition() const { return position_; }
    PieceColor GetColor() const { return color_; }


 //private:
    int id;
    SurakartaPosition position_;
    PieceColor color_;
    bool isdead;
};

#endif // SURAKARTAPIECE_H
