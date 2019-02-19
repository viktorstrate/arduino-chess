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

LinkedList<int> ChessBoard::possibleMoves(int index, bool whitePlays) const
{
    ChessPiece piece = board[index];
    LinkedList<int> result;

    // You cannot move your opponents pieces
    if (piece.whiteOwns() != whitePlays)
        return result;

    int x = indexToX(index);
    int y = indexToY(index);

    auto offsetIndex = [&](int xoffset, int yoffset) {
        int direction = piece.whiteOwns() ? 1 : -1;

        int xNew = x + xoffset;
        int yNew = y + yoffset*direction;

        return fieldToIndex(xNew, yNew);
    };

    auto getPiece = [&](int xoffset, int yoffset) {

        if((xoffset+x > 7 || xoffset+x < 0) && (yoffset+y > 7 || yoffset+y < 0))
            return ChessPiece::invalidPiece();

        int index = offsetIndex(xoffset, yoffset);

        const ChessPiece& checkPiece = board[index];
        return checkPiece;
    };

    auto oppositeOrFreePiece = [&](int xoffset, int yoffset) {
        const ChessPiece& checkPiece = getPiece(xoffset, yoffset);
        if (checkPiece.isInvalid()) return false;
        return checkPiece.empty() || checkPiece.whiteOwns() != whitePlays;
    };

    auto oppositePiece = [&](int xoffset, int yoffset) {
        const ChessPiece& checkPiece = getPiece(xoffset, yoffset);
        if (checkPiece.isInvalid()) return false;
        return !checkPiece.empty() && checkPiece.whiteOwns() != whitePlays;
    };

    if (piece.kind() == 'p')
    {
        if (oppositeOrFreePiece(0, 1))
            result.push(offsetIndex(0, 1));

        int startPosY = whitePlays ? 1 : 6;

        if (y == startPosY && oppositeOrFreePiece(0, 2))
            result.push(offsetIndex(0, 2));

        if (oppositePiece(1, 1))
            result.push(offsetIndex(1, 1));

        if (oppositePiece(-1, 1))
            result.push(offsetIndex(-1, 1));
    }

    return result;
}

bool ChessBoard::validMove(const ChessMove& move, bool whitePlays) const
{
    auto moves = possibleMoves(move.from, whitePlays);

    return moves.contains(move.to);
}
