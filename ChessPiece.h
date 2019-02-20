//
// Created by Viktor Hundahl Strate on 18/02/2019.
//


#pragma once

#include "compatibility.h"

char toLowercase(char sign);

struct ChessPiece
{
    char key;

    // result must be at least 13 bytes long
    void name(char result[14]) const;

    byte value() const;
    char kind() const;
    bool whiteOwns() const;
    bool empty() const;
    bool invalid() const;

    ChessPiece();
    ChessPiece(char key);

    static ChessPiece invalidPiece();
};
