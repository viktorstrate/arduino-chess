//
// Created by Viktor Hundahl Strate on 18/02/2019.
//

#include "ChessBoard.h"

#include "logger.h"

void ChessBoard::printBoard() const
{
    const ChessPiece* piece;

    for(int y = 7; y >= 0; y--)
    {
        if (y == 7)
        {
            print("   ");
            for (int x = 0; x < 8; x++)
            {
                char buffer[] = {
                        static_cast<char>('a' + x), ' ', '\0'
                };
                print(buffer);
            }
            println("");
        }

        {
            char buffer[] = {
                    static_cast<char>('1' + y), ' ', '|', '\0'
            };
            print(buffer);
        }

        for(int x = 0; x < 8; x++)
        {
            piece = &board[fieldToIndex(x, y)];

            char buffer[] = {
                    piece->key, '|', '\0'
            };
            print(buffer);
        }

        {
            char buffer[] = {
                    ' ', static_cast<char>('1' + y), '\n', '\0'
            };
            print(buffer);
        }

        if (y == 0)
        {
            print("   ");
            for (int x = 0; x < 8; x++)
            {
                char buffer[] = {
                        static_cast<char>('a' + x), ' ', '\0'
                };
                print(buffer);
            }
            println("");
        }
    }

    println("");
}

void ChessBoard::performMove(const ChessMove &move)
{
    board[move.to] = board[move.from];
    board[move.from] = ' ';
}
