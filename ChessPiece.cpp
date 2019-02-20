//
// Created by Viktor Hundahl Strate on 18/02/2019.
//

#ifdef DESKTOP
#include <cstring>
#else
#include <arduino.h>
#endif

#include "ChessPiece.h"

char toLowercase(char sign)
{
    if (sign >= 'A' && sign <= 'Z')
    {
        return sign + ('a'-'A');
    }

    return sign;
}

ChessPiece::ChessPiece() : key(' ') {}

ChessPiece::ChessPiece(char key) : key(key) {}

ChessPiece ChessPiece::invalidPiece()
{
    return ChessPiece('!');
}

bool ChessPiece::invalid() const
{
    return key == '!';
}

void ChessPiece::name(char result[14]) const
{
    if (invalid())
    {
        strcpy(result, "INVALID PIECE");
        return;
    }

    if (whiteOwns()) {
        strcpy(result, "white ");
    } else {
        strcpy(result, "black ");
    }

    switch(toLowercase(key))
    {
        case 'p': strcpy(result+6, "pawn"); break;
        case 'n': strcpy(result+6, "knight"); break;
        case 'b': strcpy(result+6, "bishop"); break;
        case 'r': strcpy(result+6, "rook"); break;
        case 'q': strcpy(result+6, "queen"); break;
        case 'k': strcpy(result+6, "king"); break;
        default: strcpy(result+6, "ERROR");
    }
}

byte ChessPiece::value() const
{
    if (invalid()) return '!';

    switch (toLowercase(key))
    {
        case 'p': return 1;
        case 'n': return 3;
        case 'b': return 3;
        case 'r': return 5;
        case 'q': return 9;
        case 'k': return 255;
        default: return 0;
    }
}

bool ChessPiece::whiteOwns() const
{
    // Key is lowercase
    return key > 'Z';
}

bool ChessPiece::empty() const
{
    return key == ' ';
}

char ChessPiece::kind() const
{
    if (invalid()) return '!';

    return toLowercase(key);
}
