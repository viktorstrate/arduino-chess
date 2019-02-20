//
// Created by Viktor Hundahl Strate on 18/02/2019.
//


#pragma once

struct ChessMove
{
    int from;
    int to;
    int score;

    ChessMove(const char code[6]);
    ChessMove(int from, int to);
    ChessMove(int score);

    void printMove() const;
};

