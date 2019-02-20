//
// Created by Viktor Hundahl Strate on 18/02/2019.
//

#ifdef DESKTOP

#include <algorithm>

using namespace std;
#endif

#include "chess-minimax.h"

ChessMove calculateMove(ChessBoard board, unsigned depth, bool whitePlays, int* steps, int* swaps, int alpha, int beta)
{
    if(steps != nullptr)
        *steps += 1;

    if (depth == 0) {
        ChessMove scoreMove = ChessMove(evaluateMoveScore(board));
        return scoreMove;
    }

    // Sort pieces by most likely to be good choices
    LinkedList<byte> searchOrder;
    int swappedPieces = 0;

    for (byte i = 0; i < 64; i++)
        searchOrder.push(i);

    for (byte i = 0; i < 64; i++) {
        auto sortPieceMoves = board.possibleMoves(i, whitePlays);
        auto* move = &sortPieceMoves;

        while(!move->end())
        {
            const ChessPiece& piece = board.board[move->value];

            if (!piece.empty() && piece.whiteOwns() != whitePlays) {
                if (swaps != nullptr) *swaps += 1; // for statistics
                searchOrder.swap(swappedPieces, move->value);
                swappedPieces++;
            }

            if (move->next != nullptr) {
                move = move->next;
            } else break;
        }

    }

    // Explore every move
    auto* searchIndex = &searchOrder;
    ChessMove bestMove = ChessMove(whitePlays ? -10000 : 10000);

    while(!searchIndex->end()) {
        byte i = searchIndex->value;
        auto possibleMoves = board.possibleMoves(i, whitePlays);

        auto* move = &possibleMoves;

        while (!move->end()) {
            ChessBoard newBoard = board;
            ChessMove newMove = ChessMove(i, move->value);
            newBoard.performMove(newMove);

            int evalScore = calculateMove(newBoard, depth - 1, !whitePlays, steps, swaps, alpha, beta).score;

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

        if (searchIndex->next != nullptr) {
            searchIndex = searchIndex->next;
        } else break;
    }

    return bestMove;
}

int evaluateMoveScore(const ChessBoard& board)
{
    int whiteScore = 0;
    int blackScore = 0;

    for (byte i = 0; i < 64; i++) {
        const ChessPiece& piece = board.board[i];

        if (piece.empty())
            continue;

        // Values of pieces
        if (piece.whiteOwns())
            whiteScore += piece.value()*3;
        else
            blackScore += piece.value()*3;

        // Pieces controlling middle pieces
        auto moveList = board.possibleMoves(i, piece.whiteOwns());
        auto* move = &moveList;

        while(!move->end()) {

            switch (move->value) {
                case fieldToIndex(3, 3):
                case fieldToIndex(3, 4):
                case fieldToIndex(4, 3):
                case fieldToIndex(4, 4):
                {
                    if (piece.whiteOwns())
                        whiteScore += 1;
                    else
                        blackScore += 1;
                }
                default: break;
            }

            if (move->next == nullptr) break;
            move = move->next;
        }
    }

    return whiteScore - blackScore;
}