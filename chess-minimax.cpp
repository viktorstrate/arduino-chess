//
// Created by Viktor Hundahl Strate on 18/02/2019.
//

#ifdef DESKTOP

#include <algorithm>

using namespace std;
#endif

#include "chess-minimax.h"

ChessMove calculateMove(ChessBoard board, unsigned depth, bool whitePlays, int* steps, int alpha, int beta)
{
    *steps += 1;

    if (depth == 0) {
        ChessMove scoreMove = ChessMove(evaluateMoveScore(board));
        return scoreMove;
    }

    ChessMove bestMove = ChessMove(whitePlays ? -1000 : 1000);

    for (int i = 0; i < 64; i++) {
        auto possibleMoves = board.possibleMoves(i, whitePlays);
        auto* move = &possibleMoves;

        while (!move->end()) {
            ChessBoard newBoard = board;
            ChessMove newMove = ChessMove(i, move->value);
            newBoard.performMove(newMove);

            int evalScore = calculateMove(newBoard, depth - 1, !whitePlays, steps, alpha, beta).score;

            if (whitePlays) {

                if (evalScore > bestMove.score){
                    newMove.score = evalScore;
                    bestMove = newMove;
                }

                alpha = max(alpha, evalScore);

            } else {

                if (evalScore < bestMove.score){
                    newMove.score = evalScore;
                    bestMove = newMove;
                }

                beta = min(beta, evalScore);

            }

            if (beta <= alpha) {
                return bestMove;
            }

            if (move->next != nullptr) {
                move = move->next;
            } else break;
        }
    }

    return bestMove;
}

int evaluateMoveScore(const ChessBoard& board)
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