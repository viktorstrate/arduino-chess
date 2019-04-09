//
// Created by Viktor Hundahl Strate on 18/02/2019.
//


#pragma once

#include "compatibility.h"
#include "ChessPiece.h"
#include "ChessMove.h"
#include "LinkedList.h"

#define fieldToIndex(x, y) (x) + (y*8)
#define indexToX(index) (index) % 8
#define indexToY(index) (index) / 8

class ChessBoard
{
public:
    ChessPiece board[64] = {
            'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r',
            'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
            ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
            'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R',
    };

    bool whitePlays = true;

    void printBoard() const;
    void performMove(const ChessMove& move);
    LinkedList<byte> possibleMoves(byte index) const;
    LinkedList<byte> possibleMoves(byte index, bool whitePlays) const;
    bool validMove(const ChessMove& move) const;

    /// Return values: 0 = game not ended; 1 = white has won; 2 = black has won
    byte gameEnded();
};

