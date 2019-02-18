//
// Created by Viktor Hundahl Strate on 18/02/2019.
//


#pragma once

struct ChessMove
{
    unsigned from;
    unsigned to;
    int score;

    ChessMove(const char code[6]);
    ChessMove(unsigned from, unsigned to);

    void printMove() const;
};

