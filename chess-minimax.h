//
// Created by Viktor Hundahl Strate on 18/02/2019.
//

#pragma once

#include "ChessBoard.h"
#include "ChessMove.h"
#include "LinkedList.h"

class ChessEngine {
public:
    ChessEngine();

    /**
     * Calculate the best move on the board, for the given player
     * @param board the board to base the calculations on
     * @param depth how many moves into the future that should be calculated
     * @param whitePlays whether or not white plays next turn
     * @param alpha should be set to default, used for optimization
     * @param beta should be set to default, used for optimization
     * @return
     */
    ChessMove calculateMove(ChessBoard board, unsigned depth, int alpha = -10000, int beta = 10000, int currentDepth = 0);

    ChessMove calculateMoveIterative(ChessBoard board, unsigned maxSteps);

    static int evaluateMoveScore(const ChessBoard& board);

    int getSteps() const;

    int getSwaps() const;

    int getTransTableSize() const;

    int getTransTableUses() const;

private:
    struct TransTable {
        ChessBoard board;
        ChessMove move;
        int depth;
    };

    LinkedList<TransTable> transpositionTable;
    int steps = 0;
    int swaps = 0;
    int maxSteps = -1;
    int tableUses = 0;

    const TransTable* transTableFind(const ChessBoard* board);

};