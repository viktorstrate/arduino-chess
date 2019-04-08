//
// Created by Viktor Hundahl Strate on 18/02/2019.
//

#ifdef DESKTOP

#include <algorithm>

using namespace std;
#endif

#include "chess-minimax.h"

ChessMove ChessEngine::calculateMoveIterative(ChessBoard board, unsigned maxSteps, bool whitePlays)
{
    this->maxSteps = maxSteps;
    unsigned depth = 0;
    ChessMove bestMove = ChessMove(whitePlays ? -10000 : 10000);

    int lastTransSize = 0;

    while (depth < 10) {

        ChessMove move = calculateMove(board, depth, whitePlays);

        if (whitePlays) {
            if (move.score > bestMove.score)
                bestMove = move;
        } else if (move.score < bestMove.score)
            bestMove = move;

        Print("Analyzed depth: ");
        Print(depth);
        Print(", transposition table increase: ");
        int newTransSize = getTransTableSize();
        Println(newTransSize - lastTransSize);
        lastTransSize = newTransSize;

        depth++;
    }

    return bestMove;
}

ChessMove ChessEngine::calculateMove(ChessBoard board, unsigned depth, bool whitePlays, int alpha, int beta)
{
    steps += 1;

    if (steps % 1000 == 0) {
        Print(".");
    }

    if (depth == 0 || (maxSteps > 0 && steps >= maxSteps)) {
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
                swaps += 1; // for statistics
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

            int evalScore = 0;
            bool foundScore = false;

            // Check if move is in transposition table
            auto* tablePtr = &transpositionTable;
            while (!tablePtr->end()) {

                bool boardMatch = true;

                for (int a = 0; a < 64; a++) {
                    if (tablePtr->value.board.board[a].value() != newBoard.board[a].value()) {
                        boardMatch = false;
                        break;
                    }
                }

                if (boardMatch) {
                    evalScore = tablePtr->value.move.score;
                    foundScore = true;
                    break;
                }

                if (tablePtr->next != nullptr)
                    tablePtr = tablePtr->next;
                else break;
            }

            if (!foundScore)
                evalScore = calculateMove(newBoard, depth - 1, !whitePlays, alpha, beta).score;

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

    TransTable table = {
        board, bestMove
    };

    transpositionTable.push(table);

    return bestMove;
}

int ChessEngine::evaluateMoveScore(const ChessBoard& board)
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

ChessEngine::ChessEngine() : transpositionTable()
{}

int ChessEngine::getTransTableSize() const
{
    int count = 0;
    auto* transPtr = &transpositionTable;
    while (!transPtr->end()) {
        count++;

        if (transPtr->next == nullptr) break;
        transPtr = transPtr->next;
    }

    return count;
}

int ChessEngine::getSteps() const
{
    return steps;
}

int ChessEngine::getSwaps() const
{
    return swaps;
}
