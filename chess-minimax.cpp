//
// Created by Viktor Hundahl Strate on 18/02/2019.
//

#include "chess-minimax.h"

static void evaluateMoveScore(const ChessBoard& board, ChessMove* move);

ChessMove calculateMove(const ChessBoard &board, unsigned depth, ChessMove move, bool whitePlays, int alpha, int beta)
{
    if (depth == 0)
    {
        evaluateMoveScore(board, &move);
        return move;
    }

    return {0, 0};
}

static void evaluateMoveScore(const ChessBoard& board, ChessMove* move)
{
    int whiteScore = 0;
    int blackScore = 0;

    for (auto& piece : board.board) {
        if (piece.empty())
            continue;

        if (piece.whiteOwns())
            whiteScore += piece.value();
        else
            blackScore += piece.value();
    }

    move->score = whiteScore - blackScore;
}