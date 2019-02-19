//
// Created by Viktor Hundahl Strate on 18/02/2019.
//

#include "chess-minimax.h"

static int evaluateMoveScore(const ChessBoard& board);

ChessMove calculateMove(const ChessBoard &board, unsigned depth, ChessMove move, bool whitePlays, int alpha, int beta)
{
    if (depth == 0)
    {
        move.score = evaluateMoveScore(board);
        return move;
    }

    if (whitePlays)
    {
        int maxEval = -1000;
    }

    return {0, 0};
}

static int evaluateMoveScore(const ChessBoard& board)
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

    return whiteScore - blackScore;
}