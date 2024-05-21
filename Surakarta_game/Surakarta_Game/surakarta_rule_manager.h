#pragma once
#include <cstring>
#include <iostream>
#include <memory>
#include <vector>
#include "surakarta_common.h"
#include "surakarta_board.h"
class SurakartaRuleManager {
   public:
    SurakartaRuleManager() = default;

    SurakartaRuleManager(std::shared_ptr<SurakartaBoard> board,
                         std::shared_ptr<SurakartaGameInfo> game_info)
        : board_size_(board->board_size_),
          board_(std::const_pointer_cast<const SurakartaBoard>(board)),
          game_info_(std::const_pointer_cast<const SurakartaGameInfo>(game_info)) {}

    unsigned int GetBoardSize() {
        return board_size_;
    }

    virtual void OnUpdateBoard();

    /**
     * @brief Judge whether a move is legal.
     * @param move The move to be judged.
     */
    virtual SurakartaIllegalMoveReason JudgeMove(const SurakartaMove& move);

    /**
     * @brief Judge whether the game is end.
     * @param reason SurakartaIllegalMoveReason of the last move.
     */
    virtual std::pair<SurakartaEndReason, SurakartaPlayer> JudgeEnd(const SurakartaIllegalMoveReason reason);

    /**
     * @brief Get all legal target positions of a piece.
     * @param postion The position of the piece.
     */
    virtual std::unique_ptr<std::vector<SurakartaPosition>> GetAllLegalTarget(const SurakartaPosition postion);

    //    protected:
    unsigned int board_size_;
    std::shared_ptr<const SurakartaBoard> board_;
    std::shared_ptr<const SurakartaGameInfo> game_info_;

   public:
    // TODO:
    //  define your own functions/variables here
    void HelloWorld();
    int returnlinex(unsigned int x) {
        if (x < board_size_ / 2)
            return x;
        else
            return (board_size_ - 1 - x);
    }
    int returnliney(unsigned int y) {
        if (y < board_size_ / 2)
            return y;
        else
            return (board_size_ - 1 - y);
    }
    int up(const SurakartaMove& move) {
        if (move.from.x == 0 || move.from.x == board_size_ - 1)
            return 0;
        for (int i = move.from.y - 1; i >= 0; i--) {
            if (((*board_)[move.from.x][i]->GetColor() != PieceColor::NONE))
                return 0;
        }
        if (move.from.x < board_size_ / 2) {
            int tmp_x = 0;
            int tmp_y = move.from.x;
            for (; (unsigned int)tmp_x < board_size_; tmp_x++) {
                if ((*board_)[tmp_x][tmp_y]->GetColor() != PieceColor::NONE && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                    return 0;
                else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                    return 1;
            }
            tmp_x = board_size_ - 1 - tmp_y;
            tmp_y = 0;
            for (; (unsigned int)tmp_y < board_size_; tmp_y++) {
                if ((*board_)[tmp_x][tmp_y]->GetColor() != PieceColor::NONE && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                    return 0;
                else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                    return 1;
            }
            tmp_y = tmp_x;
            tmp_x = board_size_ - 1;
            for (; tmp_x >= 0; tmp_x--) {
                if ((*board_)[tmp_x][tmp_y]->GetColor() != PieceColor::NONE && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                    return 0;
                else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                    return 1;
            }
            tmp_x = board_size_ - 1 - tmp_y;
            tmp_y = board_size_ - 1;
            for (; (unsigned int)tmp_y > move.from.y; tmp_y--) {
                if ((*board_)[tmp_x][tmp_y]->GetColor() != PieceColor::NONE && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                    return 0;
                else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                    return 1;
            }
        } else if (move.from.x >= board_size_ / 2) {
            int tmp_x = board_size_ - 1;
            int tmp_y = board_size_ - 1 - move.from.x;
            for (; tmp_x >= 0; tmp_x--) {
                if ((*board_)[tmp_x][tmp_y]->GetColor() != PieceColor::NONE && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                    return 0;
                else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                    return 1;
            }
            tmp_x = tmp_y;
            tmp_y = 0;
            for (; (unsigned int)tmp_y < board_size_; tmp_y++) {
                if ((*board_)[tmp_x][tmp_y]->GetColor() != PieceColor::NONE && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                    return 0;
                else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                    return 1;
            }
            tmp_y = board_size_ - 1 - tmp_x;
            tmp_x = 0;
            for (; (unsigned int)tmp_x < board_size_; tmp_x++) {
                if ((*board_)[tmp_x][tmp_y]->GetColor() != PieceColor::NONE && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                    return 0;
                else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                    return 1;
            }
            tmp_x = tmp_y;
            tmp_y = board_size_ - 1;
            for (; (unsigned int)tmp_y > move.from.y; tmp_y--) {
                if ((*board_)[tmp_x][tmp_y]->GetColor() != PieceColor::NONE && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                    return 0;
                else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                    return 1;
            }
        }
        return 0;
    }
    int down(const SurakartaMove& move) {
        if (move.from.x == 0 || move.from.x == board_size_ - 1)
            return 0;
        for (int i = move.from.y + 1; (unsigned int)i < board_size_; i++) {
            if ((*board_)[move.from.x][i]->GetColor() != PieceColor::NONE)
                return 0;
        }
        if (move.from.x < board_size_ / 2) {
            int tmp_x = 0;
            int tmp_y = board_size_ - 1 - move.from.x;
            for (; (unsigned int)tmp_x < board_size_; tmp_x++) {
                if ((*board_)[tmp_x][tmp_y]->GetColor() != PieceColor::NONE && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                    return 0;
                else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                    return 1;
            }
            tmp_x = tmp_y;
            tmp_y = board_size_ - 1;
            for (; tmp_y >= 0; tmp_y--) {
                if ((*board_)[tmp_x][tmp_y]->GetColor() != PieceColor::NONE && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                    return 0;
                else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                    return 1;
            }
            tmp_y = board_size_ - 1 - tmp_x;
            tmp_x = board_size_ - 1;
            for (; tmp_x >= 0; tmp_x--) {
                if ((*board_)[tmp_x][tmp_y]->GetColor() != PieceColor::NONE && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                    return 0;
                else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                    return 1;
            }
            tmp_x = tmp_y;
            tmp_y = 0;
            for (; (unsigned int)tmp_y < move.from.y; tmp_y++) {
                if ((*board_)[tmp_x][tmp_y]->GetColor() != PieceColor::NONE && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                    return 0;
                else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                    return 1;
            }
        } else if (move.from.x >= board_size_ / 2) {
            int tmp_x = board_size_ - 1;
            int tmp_y = move.from.x;
            for (; tmp_x >= 0; tmp_x--) {
                if ((*board_)[tmp_x][tmp_y]->GetColor() != PieceColor::NONE && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                    return 0;
                else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                    return 1;
            }
            tmp_x = board_size_ - 1 - tmp_y;
            tmp_y = board_size_ - 1;
            for (; tmp_y >= 0; tmp_y--) {
                if ((*board_)[tmp_x][tmp_y]->GetColor() != PieceColor::NONE && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                    return 0;
                else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                    return 1;
            }
            tmp_y = tmp_x;
            tmp_x = 0;
            for (; (unsigned int)tmp_x < board_size_; tmp_x++) {
                if ((*board_)[tmp_x][tmp_y]->GetColor() != PieceColor::NONE && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                    return 0;
                else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                    return 1;
            }
            tmp_x = board_size_ - 1 - tmp_y;
            tmp_y = 0;
            for (; (unsigned int)tmp_y < move.from.y; tmp_y++) {
                if ((*board_)[tmp_x][tmp_y]->GetColor() != PieceColor::NONE && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                    return 0;
                else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                    return 1;
            }
        }
        return 0;
    }
    int left(const SurakartaMove& move) {
        if (move.from.y == 0 || move.from.y == board_size_ - 1)
            return 0;
        for (int i = move.from.x - 1; i >= 0; i--) {
            if ((*board_)[i][move.from.y]->GetColor() != PieceColor::NONE)
                return 0;
        }
        if (move.from.y < board_size_ / 2) {
            int tmp_y = 0;
            int tmp_x = move.from.y;
            for (; (unsigned int)tmp_y < board_size_; tmp_y++) {
                if ((*board_)[tmp_x][tmp_y]->GetColor() != PieceColor::NONE && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                    return 0;
                else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                    return 1;
            }
            tmp_y = board_size_ - 1 - tmp_x;
            tmp_x = 0;
            for (; (unsigned int)tmp_x < board_size_; tmp_x++) {
                if ((*board_)[tmp_x][tmp_y]->GetColor() != PieceColor::NONE && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                    return 0;
                else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                    return 1;
            }
            tmp_x = tmp_y;
            tmp_y = board_size_ - 1;
            for (; tmp_y >= 0; tmp_y--) {
                if ((*board_)[tmp_x][tmp_y]->GetColor() != PieceColor::NONE && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                    return 0;
                else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                    return 1;
            }
            tmp_y = board_size_ - 1 - tmp_x;
            tmp_x = board_size_ - 1;
            for (; (unsigned int)tmp_x > move.from.x; tmp_x--) {
                if ((*board_)[tmp_x][tmp_y]->GetColor() != PieceColor::NONE && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                    return 0;
                else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                    return 1;
            }
        } else if (move.from.y >= board_size_ / 2)  // tab
        {
            int tmp_y = board_size_ - 1;
            int tmp_x = board_size_ - 1 - move.from.y;
            for (; tmp_y >= 0; tmp_y--) {
                if ((*board_)[tmp_x][tmp_y]->GetColor() != PieceColor::NONE && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                    return 0;
                else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                    return 1;
            }
            tmp_y = tmp_x;
            tmp_x = 0;
            for (; (unsigned int)tmp_x < board_size_; tmp_x++) {
                if ((*board_)[tmp_x][tmp_y]->GetColor() != PieceColor::NONE && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                    return 0;
                else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                    return 1;
            }
            tmp_x = board_size_ - 1 - tmp_y;
            tmp_y = 0;
            for (; (unsigned int)tmp_y < board_size_; tmp_y++) {
                if ((*board_)[tmp_x][tmp_y]->GetColor() != PieceColor::NONE && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                    return 0;
                else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                    return 1;
            }
            tmp_y = tmp_x;
            tmp_x = board_size_ - 1;
            for (; (unsigned int)tmp_x > move.from.x; tmp_x--) {
                if ((*board_)[tmp_x][tmp_y]->GetColor() != PieceColor::NONE && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                    return 0;
                else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                    return 1;
            }
        }
        return 0;
    }
    int right(const SurakartaMove& move) {
        if (move.from.y == 0 || move.from.y == board_size_ - 1)
            return 0;
        for (int i = move.from.x + 1; (unsigned int)i < board_size_; i++) {
            if ((*board_)[i][move.from.y]->GetColor() != PieceColor::NONE)
                return 0;
        }
        if (move.from.y < board_size_ / 2) {
            int tmp_y = 0;
            int tmp_x = board_size_ - 1 - move.from.y;
            for (; (unsigned int)tmp_y < board_size_; tmp_y++) {
                if ((*board_)[tmp_x][tmp_y]->GetColor() != PieceColor::NONE && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                    return 0;
                else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                    return 1;
            }
            tmp_y = tmp_x;
            tmp_x = board_size_ - 1;
            for (; tmp_x >= 0; tmp_x--) {
                if ((*board_)[tmp_x][tmp_y]->GetColor() != PieceColor::NONE && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                    return 0;
                else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                    return 1;
            }
            tmp_x = board_size_ - 1 - tmp_y;
            tmp_y = board_size_ - 1;
            for (; tmp_y >= 0; tmp_y--) {
                if ((*board_)[tmp_x][tmp_y]->GetColor() != PieceColor::NONE && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                    return 0;
                else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                    return 1;
            }
            tmp_y = tmp_x;
            tmp_x = 0;
            for (; (unsigned int)tmp_x < move.from.x; tmp_x++) {
                if ((*board_)[tmp_x][tmp_y]->GetColor() != PieceColor::NONE && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                    return 0;
                else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                    return 1;
            }
        } else if (move.from.y >= board_size_ / 2) {
            int tmp_y = board_size_ - 1;
            int tmp_x = move.from.y;
            for (; tmp_y >= 0; tmp_y--) {
                if ((*board_)[tmp_x][tmp_y]->GetColor() != PieceColor::NONE && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                    return 0;
                else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                    return 1;
            }
            tmp_y = board_size_ - 1 - tmp_x;
            tmp_x = board_size_ - 1;
            for (; tmp_x >= 0; tmp_x--) {
                if ((*board_)[tmp_x][tmp_y]->GetColor() != PieceColor::NONE && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                    return 0;
                else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                    return 1;
            }
            tmp_x = tmp_y;
            tmp_y = 0;
            for (; (unsigned int)tmp_y < board_size_; tmp_y++) {
                if ((*board_)[tmp_x][tmp_y]->GetColor() != PieceColor::NONE && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                    return 0;
                else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                    return 1;
            }
            tmp_y = board_size_ - 1 - tmp_x;
            tmp_x = 0;
            for (; (unsigned int)tmp_x < move.from.x; tmp_x++) {
                if ((*board_)[tmp_x][tmp_y]->GetColor() != PieceColor::NONE && !((unsigned int)tmp_x == move.from.x && (unsigned int)tmp_y == move.from.y) && !((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y))
                    return 0;
                else if ((unsigned int)tmp_x == move.to.x && (unsigned int)tmp_y == move.to.y)
                    return 1;
            }
        }
        return 0;
    }
    bool Judge_capture_move(const SurakartaMove& move) {
        int line[board_size_][board_size_ * 5];
        memset(line, 0, sizeof(line));
        int line_fromx = returnlinex(move.from.x);
        int line_fromy = returnliney(move.from.y);
        int line_tox = returnlinex(move.to.x);
        int line_toy = returnliney(move.to.y);
        int flag = 0;
        if (line_fromx != line_tox && line_fromy != line_toy && line_fromx != line_toy && line_fromy != line_tox)
            return 0;
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
            return 0;
        else
            return 1;
    }
    void InlineHelloWorld() {
        std::cout << "Hello World!" << std::endl;
    }

    int bye_world_ = 0;
};
