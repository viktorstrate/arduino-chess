//
// Created by Viktor Hundahl Strate on 18/02/2019.
//


#pragma once

#include "compatibility.h"

struct ChessMove
{
    byte from;
    byte to;
    int score;

    ChessMove();

    ChessMove(const char code[6]);
    ChessMove(byte from, byte to);
    ChessMove(int score);

    void printMove() const;
};

