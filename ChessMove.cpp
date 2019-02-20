//
// Created by Viktor Hundahl Strate on 18/02/2019.
//

#include "ChessMove.h"

#include "logger.h"
#include "ChessBoard.h"


/**
 * Parse string move
 * @param code the move described as 5 characters eg. "g4 e4"
 */
ChessMove::ChessMove(const char* code)
{
    int x1, y1, x2, y2;

    x1 = toLowercase(code[0]) - 'a';
    y1 = toLowercase(code[1]) - '1';

    from = static_cast<unsigned char>(fieldToIndex(x1, y1));

    if (strlen(code) == 2) return;

    x2 = toLowercase(code[3]) - 'a';
    y2 = toLowercase(code[4]) - '1';

    to = static_cast<unsigned char>(fieldToIndex(x2, y2));
}

ChessMove::ChessMove(byte from, byte to)
        : from(from), to(to)
{}

void ChessMove::printMove() const
{
    char x1 = static_cast<char>('a' + (from%8));
    char y1 = static_cast<char>('1' + (from/8));

    char x2 = static_cast<char>('a' + (to%8));
    char y2 = static_cast<char>('1' + (to/8));

    char buffer[] = {
            x1, y1, ' ', '-', '>', ' ', x2, y2, '\0'
    };

    println(buffer);
}

ChessMove::ChessMove(int score) : score(score), from(-1), to(-1)
{}
