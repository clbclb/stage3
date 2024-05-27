#include "surakarta_agent_mine.h"
#include <algorithm>
#include <cstdlib>
#include <random>
#include <vector>
#include "global_random_generator.h"
#include "surakarta_common.h"
#include "widget.h"

SurakartaMove SurakartaAgentMine::CalculateMove() {
    // TODO: Implement your own ai here.
    // 生成from集与to集
    std::vector<SurakartaMove> random_move1;
    std::vector<SurakartaMove> random_move2;
    std::vector<SurakartaPosition> from;
    std::vector<SurakartaPosition> to;
    for (unsigned int i = 0; i < board_size_; i++) {
        for (unsigned int j = 0; j < board_size_; j++) {
            SurakartaPosition position = {i, j};
            if ((*board_)[i][j]->GetColor() == game_info_->current_player_) {
                from.push_back(position);
            } else {
                to.push_back(position);
            }
        }
    }
    std::shuffle(from.begin(), from.end(), GlobalRandomGenerator::getInstance());
    std::shuffle(to.begin(), to.end(), GlobalRandomGenerator::getInstance()); //time saving

    // 获得对手棋子位置,用于判断移动后是否会被吃
    std::vector<SurakartaPosition> opponent;
    for (unsigned int i = 0; i < board_size_; i++) {
        for (unsigned int j = 0; j < board_size_; j++) {
            SurakartaPosition position = {i, j};
            if ((*board_)[i][j]->GetColor() != game_info_->current_player_ && (*board_)[i][j]->GetColor() != PieceColor::NONE && (*board_)[i][j]->GetColor() != PieceColor::UNKNOWN) {
                opponent.push_back(position);
            }
        }
    }

    // 优先保命，防止有被吃的子
    SurakartaMove rd_move1({0, 0}, {0, 0}, game_info_->current_player_);
    int capflag_of_being_captured = 0, nonflag_of_not_captured = 0;  // 前者用于指示是否存在吃掉对方子后会被吃的情况，后者用于指示是否存在不能吃掉对方子但移动后不会被吃的情况
    for (auto& p1 : from) {                                          // 枚举我方子，判断是否安全
        for (auto& p0 : opponent) {                                  // 枚举对方子，判断是否会吃掉当前被枚举的我方子
            SurakartaMove move_of_opponent0 = {p0,
                                               p1,
                                               (*board_)[p0.x][p0.y]->GetColor()};
            SurakartaIllegalMoveReason reason_of_opponent0 = rule_manager_->JudgeMove(move_of_opponent0);
            if (reason_of_opponent0 == SurakartaIllegalMoveReason::LEGAL_CAPTURE_MOVE) {  // 当前被枚举我方子会被当前被枚举对方子吃掉
                for (auto& p2 : to) {                                                     // 寻找当前被枚举我方子的可行去处，优先级见100行，接下来的代码几乎与100行之后的代码相同，详细注释见100行后的代码
                    {
                        SurakartaMove move = {p1, p2, game_info_->current_player_};
                        SurakartaIllegalMoveReason reason = rule_manager_->JudgeMove(move);
                        if (reason == SurakartaIllegalMoveReason::LEGAL_CAPTURE_MOVE) {
                            for (auto& p : opponent) {
                                SurakartaMove move_of_opponent = {p,
                                                                  p2,
                                                                  (*board_)[p.x][p.y]->GetColor()};
                                PieceColor origin = (*board_)[p2.x][p2.y]->GetColor();
                                PieceColor origin_from = (*board_)[p1.x][p1.y]->GetColor();
                                (*board_)[p2.x][p2.y]->SetColor(game_info_->current_player_);
                                (*board_)[p1.x][p1.y]->SetColor(PieceColor::NONE);
                                SurakartaIllegalMoveReason reason_of_opponent = rule_manager_->JudgeMove(move_of_opponent);
                                (*board_)[p2.x][p2.y]->SetColor(origin);
                                (*board_)[p1.x][p1.y]->SetColor(origin_from);
                                if (reason_of_opponent != SurakartaIllegalMoveReason::LEGAL_CAPTURE_MOVE) {
                                    return move;  // 移动后该子不仅不会被吃，还会吃掉对方的子
                                }
                            }
                            if (capflag_of_being_captured == 0) {
                                rd_move1 = move;
                                random_move1.push_back(move);
                                capflag_of_being_captured = 1;
                            }
                        }

                        else if (reason == SurakartaIllegalMoveReason::LEGAL_NON_CAPTURE_MOVE) {
                            for (auto& p : opponent) {
                                SurakartaMove move_of_opponent = {p,
                                                                  p2,
                                                                  (*board_)[p.x][p.y]->GetColor()};
                                PieceColor origin = (*board_)[p2.x][p2.y]->GetColor();
                                PieceColor origin_from = (*board_)[p1.x][p1.y]->GetColor();
                                (*board_)[p2.x][p2.y]->SetColor(game_info_->current_player_);
                                (*board_)[p1.x][p1.y]->SetColor(PieceColor::NONE);
                                SurakartaIllegalMoveReason reason_of_opponent = rule_manager_->JudgeMove(move_of_opponent);
                                (*board_)[p2.x][p2.y]->SetColor(origin);
                                (*board_)[p1.x][p1.y]->SetColor(origin_from);
                                if (reason_of_opponent != SurakartaIllegalMoveReason::LEGAL_CAPTURE_MOVE && capflag_of_being_captured == 0 && nonflag_of_not_captured == 0) {
                                    rd_move1 = move;
                                    random_move1.push_back(move);
                                    nonflag_of_not_captured = 1;
                                }
                            }
                            if (capflag_of_being_captured == 0 && nonflag_of_not_captured == 0) {
                                rd_move1 = move;
                                random_move1.push_back(move);
                            }
                        }
                    }
                }
            }
            if (capflag_of_being_captured != 0 || nonflag_of_not_captured != 0)
                // return rd_move1;  // 经移动后该子不会被吃
            {
                std::shuffle(random_move1.begin(),random_move1.end(),GlobalRandomGenerator::getInstance());
                return random_move1[0];
            }
            else
                break;  // 该子无论如何都会被吃，不移动该子，枚举下一个子，尝试保护它
        }
    }



    // 只有所有子移动前都不会被吃或都无法避免被吃的情况下才会到这里并继续进行
    //  优先选择能吃子且不被吃的MOVE，其次选能吃子但会被吃的MOVE，再次选不能吃子但不会被吃的MOVE，最后选不能吃子且会被吃的MOVE <-优先级
    SurakartaMove rd_move2({0, 0}, {0, 0}, game_info_->current_player_);
    capflag_of_being_captured = 0, nonflag_of_not_captured = 0;
    for (auto& p1 : from) {    // 枚举我方可移动棋子
        for (auto& p2 : to) {  // 枚举当前被枚举我方子的去处
            SurakartaMove move = {p1, p2, game_info_->current_player_};
            SurakartaIllegalMoveReason reason = rule_manager_->JudgeMove(move);
            if (reason == SurakartaIllegalMoveReason::LEGAL_CAPTURE_MOVE) {  // 当前被枚举我方子有吃掉对方子的机会
                for (auto& p : opponent) {                                   // 枚举对方子，检查我方子移动后是否会被对方子吃掉
                    SurakartaMove move_of_opponent = {p,
                                                      p2,
                                                      (*board_)[p.x][p.y]->GetColor()};
                    PieceColor origin = (*board_)[p2.x][p2.y]->GetColor();
                    PieceColor origin_from = (*board_)[p1.x][p1.y]->GetColor();  // 改变原来棋盘，便于judgemove
                    (*board_)[p2.x][p2.y]->SetColor(game_info_->current_player_);
                    (*board_)[p1.x][p1.y]->SetColor(PieceColor::NONE);
                    SurakartaIllegalMoveReason reason_of_opponent = rule_manager_->JudgeMove(move_of_opponent);
                    (*board_)[p2.x][p2.y]->SetColor(origin);
                    (*board_)[p1.x][p1.y]->SetColor(origin_from);                                // 恢复棋盘
                    if (reason_of_opponent != SurakartaIllegalMoveReason::LEGAL_CAPTURE_MOVE) {  // 可吃对方子且不会被吃
                        return move;
                    }
                }
                if (capflag_of_being_captured == 0) {  // 记录第一个可吃对方子且会被吃掉的情况，不再记录之后相同的情况
                    rd_move2 = move;
                    random_move2.push_back(move);
                    capflag_of_being_captured = 1;
                }
            } else if (reason == SurakartaIllegalMoveReason::LEGAL_NON_CAPTURE_MOVE) {  // 当前被枚举我方子没有吃掉对方子的机会
                for (auto& p : opponent) {                                              // 判断移动后是否会被对方子吃掉
                    SurakartaMove move_of_opponent = {p,
                                                      p2,
                                                      (*board_)[p.x][p.y]->GetColor()};
                    PieceColor origin = (*board_)[p2.x][p2.y]->GetColor();
                    PieceColor origin_from = (*board_)[p1.x][p1.y]->GetColor();
                    (*board_)[p2.x][p2.y]->SetColor(game_info_->current_player_);
                    (*board_)[p1.x][p1.y]->SetColor(PieceColor::NONE);
                    SurakartaIllegalMoveReason reason_of_opponent = rule_manager_->JudgeMove(move_of_opponent);
                    (*board_)[p2.x][p2.y]->SetColor(origin);
                    (*board_)[p1.x][p1.y]->SetColor(origin_from);
                    if (reason_of_opponent != SurakartaIllegalMoveReason::LEGAL_CAPTURE_MOVE && capflag_of_being_captured == 0 && nonflag_of_not_captured == 0) {  // 记录第一个不会吃掉对方子且移动后不会被对方子吃掉的情况，不再记录之后相同的情况，且优先级高于此种情况的情况出现后也不再记录此种情况
                        rd_move2 = move;
                        random_move2.push_back(move);
                        nonflag_of_not_captured = 1;
                    }
                }
                if (capflag_of_being_captured == 0 && nonflag_of_not_captured == 0) {  // 优先级高于此种情况（移动不会吃掉对方子且会被对方子吃掉，出现概率极低但确实会出现）的情况出现后，不再记录此种情况
                    rd_move2 = move;
                    random_move2.push_back(move);
                }
            }
        }
    }
    std::shuffle(random_move2.begin(),random_move2.end(),GlobalRandomGenerator::getInstance());
    return random_move2[0];
}
