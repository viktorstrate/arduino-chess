//
// Created by Viktor Hundahl Strate on 18/02/2019.
//

#pragma once

#include "ChessBoard.h"
#include "ChessMove.h"

/**
 * Calculate the best move on the board, for the given player
 * @param board the board to base the calculations on
 * @param depth how many moves into the future that should be calculated
 * @param whitePlays whether or not white plays next turn
 * @param alpha should be set to default, used for optimization
 * @param beta should be set to default, used for optimization
 * @return
 */
ChessMove calculateMove(ChessBoard board, unsigned depth, bool whitePlays, int* steps, int alpha = -10000, int beta = 10000);

int evaluateMoveScore(const ChessBoard& board);