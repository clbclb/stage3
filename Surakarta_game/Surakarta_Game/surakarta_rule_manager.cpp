#include "surakarta_rule_manager.h"
#include <iostream>

static unsigned abs_mine(unsigned a){
    signed a2 = static_cast<signed>(a);
    if(a2>=0)
        return a2;
    else
        return 0-a2;
}

void SurakartaRuleManager::OnUpdateBoard() {
    // TODO:
    // Every time the board and game_info is updated to the next round version, this function will be called.
    // You don't need to implement this function if you don't need it.
    // A more delicate way is to use Qt's signal and slot mechanism, but that's the advanced part.
}

SurakartaIllegalMoveReason SurakartaRuleManager::JudgeMove(const SurakartaMove& move) {
    // TODO: Implement this function.

    // An example of how to get the color of a piece and the current player.
    // for (unsigned int i = 0; i < board_size_; i++) {
    //     for (unsigned int j = 0; j < board_size_; j++) {
    //         PieceColor color = (*board_)[i][j]->GetColor();
    //         if (color == PieceColor::BLACK) {
    //             // i,j is the position of a black piece
    //         } else if (color == PieceColor::WHITE) {
    //             // i,j is the position of a white piece
    //         } else {
    //             // i,j is an empty position
    //         }
    //     }
    // }
    SurakartaPlayer current_player = game_info_->current_player_;
    if (current_player == SurakartaPlayer::BLACK) {
        if (move.player != game_info_->current_player_) {
            return SurakartaIllegalMoveReason::NOT_PLAYER_TURN;
        } else if (move.to.x >= board_size_ || move.to.y >= board_size_ || move.from.x >= board_size_ || move.from.y >= board_size_) {
            return SurakartaIllegalMoveReason::OUT_OF_BOARD;
        } else if ((*board_)[move.from.x][move.from.y]->GetColor() == PieceColor::WHITE) {
            return SurakartaIllegalMoveReason::NOT_PLAYER_PIECE;
        } else if ((*board_)[move.from.x][move.from.y]->GetColor() == PieceColor::NONE) {
            return SurakartaIllegalMoveReason::NOT_PIECE;
        } else if ((*board_)[move.from.x][move.from.y]->GetColor() == PieceColor::BLACK && (*board_)[move.to.x][move.to.y]->GetColor() == PieceColor::NONE) {
            int minus_x = abs_mine(move.to.x - move.from.x);
            int minus_y = abs_mine(move.to.y - move.from.y);
            if (minus_x <= 1 && minus_y <= 1) {
                return SurakartaIllegalMoveReason::LEGAL_NON_CAPTURE_MOVE;
            } else {
                return SurakartaIllegalMoveReason::ILLIGAL_NON_CAPTURE_MOVE;
            }
        } else if ((*board_)[move.from.x][move.from.y]->GetColor() == PieceColor::BLACK && (*board_)[move.to.x][move.to.y]->GetColor() == PieceColor::BLACK)
            return SurakartaIllegalMoveReason::ILLIGAL_NON_CAPTURE_MOVE;
        else if ((*board_)[move.from.x][move.from.y]->GetColor() == PieceColor::BLACK && (*board_)[move.to.x][move.to.y]->GetColor() == PieceColor::WHITE && ((move.from.x == 0 && move.from.y == 0) || (move.from.x == 0 && move.from.y == board_size_ - 1) || (move.from.x == board_size_ - 1 && move.from.y == 0) || (move.from.x == board_size_ - 1 && move.from.y == board_size_ - 1)))
            return SurakartaIllegalMoveReason::ILLIGAL_CAPTURE_MOVE;
        else if (SurakartaRuleManager::Judge_capture_move(move)) {
            return SurakartaIllegalMoveReason::LEGAL_CAPTURE_MOVE;
        } else
            return SurakartaIllegalMoveReason::ILLIGAL_CAPTURE_MOVE;
    } else if (current_player == SurakartaPlayer::WHITE) {
        if (move.player != game_info_->current_player_) {
            return SurakartaIllegalMoveReason::NOT_PLAYER_TURN;
        } else if (move.to.x >= board_size_ || move.to.y >= board_size_ || move.from.x >= board_size_ || move.from.y >= board_size_) {
            return SurakartaIllegalMoveReason::OUT_OF_BOARD;
        } else if ((*board_)[move.from.x][move.from.y]->GetColor() == PieceColor::BLACK) {
            return SurakartaIllegalMoveReason::NOT_PLAYER_PIECE;
        } else if ((*board_)[move.from.x][move.from.y]->GetColor() == PieceColor::NONE) {
            return SurakartaIllegalMoveReason::NOT_PIECE;
        } else if ((*board_)[move.from.x][move.from.y]->GetColor() == PieceColor::WHITE && (*board_)[move.to.x][move.to.y]->GetColor() == PieceColor::NONE) {
            int minus_x = abs_mine(move.to.x - move.from.x);
            int minus_y = abs_mine(move.to.y - move.from.y);
            if (minus_x <= 1 && minus_y <= 1) {
                return SurakartaIllegalMoveReason::LEGAL_NON_CAPTURE_MOVE;
            } else {
                return SurakartaIllegalMoveReason::ILLIGAL_NON_CAPTURE_MOVE;
            }
        } else if ((*board_)[move.from.x][move.from.y]->GetColor() == PieceColor::WHITE && (*board_)[move.to.x][move.to.y]->GetColor() == PieceColor::WHITE)
            return SurakartaIllegalMoveReason::ILLIGAL_NON_CAPTURE_MOVE;
        else if ((*board_)[move.from.x][move.from.y]->GetColor() == PieceColor::WHITE && (*board_)[move.to.x][move.to.y]->GetColor() == PieceColor::BLACK && ((move.from.x == 0 && move.from.y == 0) || (move.from.x == 0 && move.from.y == board_size_ - 1) || (move.from.x == board_size_ - 1 && move.from.y == 0) || (move.from.x == board_size_ - 1 && move.from.y == board_size_ - 1)))
            return SurakartaIllegalMoveReason::ILLIGAL_CAPTURE_MOVE;
        else if (SurakartaRuleManager::Judge_capture_move(move)) {
            return SurakartaIllegalMoveReason::LEGAL_CAPTURE_MOVE;
        } else
            return SurakartaIllegalMoveReason::ILLIGAL_CAPTURE_MOVE;
    }

    return SurakartaIllegalMoveReason::LEGAL;
}

std::pair<SurakartaEndReason, SurakartaPlayer> SurakartaRuleManager::JudgeEnd(const SurakartaIllegalMoveReason reason) {
    // TODO: Implement this function.
    int cnt = 0;
    if (reason == SurakartaIllegalMoveReason::LEGAL_CAPTURE_MOVE) {
        for (int i = 0; (unsigned int)i < board_size_; i++) {
            for (int j = 0; (unsigned int)j < board_size_; j++) {
                if ((*board_)[i][j]->GetColor() == ReverseColor(game_info_->current_player_))
                    cnt++;
            }
        }
        if (cnt == 1)
            return std::make_pair(SurakartaEndReason::CHECKMATE, game_info_->current_player_);
    }
    if (reason == SurakartaIllegalMoveReason::ILLIGAL_CAPTURE_MOVE || reason == SurakartaIllegalMoveReason::NOT_PLAYER_TURN || reason == SurakartaIllegalMoveReason::OUT_OF_BOARD || reason == SurakartaIllegalMoveReason::NOT_PIECE || reason == SurakartaIllegalMoveReason::NOT_PLAYER_PIECE || reason == SurakartaIllegalMoveReason::ILLIGAL_NON_CAPTURE_MOVE)
        return std::make_pair(SurakartaEndReason::ILLIGAL_MOVE, ReverseColor(game_info_->current_player_));
    if (game_info_->num_round_ - game_info_->last_captured_round_ == game_info_->max_no_capture_round_ && reason != SurakartaIllegalMoveReason::LEGAL_CAPTURE_MOVE) {  // no plus 1!!!
        int cnt_w = 0, cnt_b = 0;
        for (int i = 0; (unsigned int)i < board_size_; i++) {
            for (int j = 0; (unsigned int)j < board_size_; j++) {
                if ((*board_)[i][j]->GetColor() == PieceColor::WHITE) {
                    cnt_w++;
                } else if ((*board_)[i][j]->GetColor() == PieceColor::BLACK) {
                    cnt_b++;
                }
            }
        }
        if (cnt_w < cnt_b) {
            return std::make_pair(SurakartaEndReason::STALEMATE, SurakartaPlayer::BLACK);  // stalemate means that >maxnocapture round
        } else if (cnt_b < cnt_w) {
            return std::make_pair(SurakartaEndReason::STALEMATE, SurakartaPlayer::WHITE);
        } else {
            return std::make_pair(SurakartaEndReason::STALEMATE, SurakartaPlayer::NONE);
        }
    }
    // Note that at this point, the board and game_info have not been updated yet.

    return std::make_pair(SurakartaEndReason::NONE, SurakartaPlayer::NONE);
}

std::unique_ptr<std::vector<SurakartaPosition>> SurakartaRuleManager::GetAllLegalTarget(const SurakartaPosition postion [[maybe_unused]]) {
    // TODO:
    // We don't test this function, you don't need to implement this function if you don't need it.
    return std::make_unique<std::vector<SurakartaPosition>>();
}

void SurakartaRuleManager::HelloWorld() {
    std::cout << "Hello World!" << std::endl;
}
