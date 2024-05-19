#pragma once

#ifndef SURAKARTA_COMMON_H
#define SURAKARTA_COMMON_H

// #include "surakarta_board.h"
#include "surakarta_piece.h"
#include "surakarta_reason.h"

struct SurakartaMove {
    SurakartaPosition from;
    SurakartaPosition to;
    SurakartaPlayer player;
    SurakartaMove()
        : from(0, 0), to(0, 0), player(SurakartaPlayer::NONE) {}
    SurakartaMove(unsigned int from_x, unsigned int from_y, unsigned int to_x, unsigned int to_y, SurakartaPlayer player)
        : from(from_x, from_y), to(to_x, to_y), player(player) {}
    SurakartaMove(SurakartaPosition from, SurakartaPosition to, SurakartaPlayer player)
        : from(from), to(to), player(player) {}
};

struct SurakartaGameInfo {
    SurakartaPlayer current_player_;
    unsigned int num_round_;
    unsigned int last_captured_round_;
    SurakartaEndReason end_reason_;
    SurakartaPlayer winner_;
    unsigned int max_no_capture_round_;

    SurakartaGameInfo(unsigned int max_no_capture_round = 40)
        : current_player_(SurakartaPlayer::BLACK),
        num_round_(1),
        last_captured_round_(0),
        end_reason_(SurakartaEndReason::NONE),
        winner_(SurakartaPlayer::NONE),
        max_no_capture_round_(max_no_capture_round) {}

    void Reset() {
        current_player_ = SurakartaPlayer::BLACK;
        num_round_ = 1;
        last_captured_round_ = 0;
        end_reason_ = SurakartaEndReason::NONE;
        winner_ = SurakartaPlayer::NONE;
    }

    bool IsEnd() const { return IsEndReason(end_reason_); }
    SurakartaPlayer Winner() const { return winner_; }
};

class SurakartaException : public std::exception {
public:
    SurakartaException(const std::string& message)
        : message_(message) {}
    virtual const char* what() const throw() { return message_.c_str(); }

private:
    std::string message_;
};

#endif // SURAKARTA_COMMON_H
