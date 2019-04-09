//
// Created by Viktor Hundahl Strate on 18/02/2019.
//

#ifdef DESKTOP
#include <algorithm>
using namespace std;
#endif

#include "chess-minimax.h"

ChessMove ChessEngine::calculateMoveIterative(ChessBoard board, unsigned maxSteps)
{
    this->maxSteps = maxSteps;
    unsigned depth = 1;
    ChessMove move = ChessMove(board.whitePlays ? -10000 : 10000);

    while (depth < 10) {

        ChessMove newMove = calculateMove(board, depth);

        // Discard half calculated moves
        if (steps >= maxSteps) {
            break;
        }

        /*if (whitePlays) {
            if (move.score > bestMove.score)
                bestMove = move;
        } else if (move.score < bestMove.score)
            bestMove = move;*/

        Print("Depth: ");
        Print(depth);
        //Print(", transposition table size: ");
        //Print(getTransTableSize());

        Print(", score: ");
        Print(newMove.score);
        Print(", ");

        newMove.printMove();

        this->transpositionTable = LinkedList<TransTable>();

        move = newMove;
        depth++;
    }

    return move;
}

ChessMove ChessEngine::calculateMove(ChessBoard board, const unsigned depth, int alpha, int beta, int currentDepth)
{
    steps += 1;

    /*if (steps % 1000 == 0) {
        Print(".");
    }*/

    if (currentDepth >= depth || (maxSteps > 0 && steps >= maxSteps)) {
        ChessMove scoreMove = ChessMove(evaluateMoveScore(board));
        return scoreMove;
    }

    // Sort pieces by most likely to be good choices
    LinkedList<byte> searchOrder;
    int swappedPieces = 0;

    for (byte i = 0; i < 64; i++)
        searchOrder.push(i);

    for (byte i = 0; i < 64; i++) {
        auto sortPieceMoves = board.possibleMoves(i);
        auto* move = &sortPieceMoves;

        while(!move->end())
        {
            const ChessPiece& piece = board.board[move->value];

            if (!piece.empty() && piece.whiteOwns() != board.whitePlays) {
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
    ChessMove bestMove = ChessMove(board.whitePlays ? -10000 : 10000);

    while(!searchIndex->end()) {
        byte i = searchIndex->value;
        auto possibleMoves = board.possibleMoves(i);

        auto* move = &possibleMoves;

        while (!move->end()) {
            ChessBoard newBoard = board;
            ChessMove newMove = ChessMove(i, move->value);
            newBoard.performMove(newMove);

            int evalScore = 0;

            //auto* tableResult = transTableFind(&newBoard);

            //if (tableResult != nullptr && tableResult->depth >= depth) {
            //    tableUses++;
            //    evalScore = tableResult->move.score;
            //} else {
                evalScore = calculateMove(newBoard, depth, alpha, beta, currentDepth+1).score;
            //}


            if (board.whitePlays) {

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

    /*TransTable table = {
        board, bestMove, currentDepth
    };

    transpositionTable.push(table);*/

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

int ChessEngine::getTransTableUses() const
{
    return tableUses;
}

const ChessEngine::TransTable* ChessEngine::transTableFind(const ChessBoard* board)
{
    // Check if move is in transposition table
    auto* tablePtr = &transpositionTable;
    while (!tablePtr->end()) {

        bool boardMatch = true;

        for (int a = 0; a < 64; a++) {
            if (tablePtr->value.board.board[a].value() != board->board[a].value()) {
                boardMatch = false;
                break;
            }
        }

        if (boardMatch) {
            return &tablePtr->value;
        }

        if (tablePtr->next != nullptr)
            tablePtr = tablePtr->next;
        else break;
    }

    return nullptr;
}
