//
// Created by Viktor Hundahl Strate on 18/02/2019.
//

#include "ChessBoard.h"

#include "logger.h"

void ChessBoard::printBoard() const
{
    const ChessPiece* piece;

    for (int y = 7; y >= 0; y--) {
        if (y == 7) {
            print("   ");
            for (int x = 0; x < 8; x++) {
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

        for (int x = 0; x < 8; x++) {
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

        if (y == 0) {
            print("   ");
            for (int x = 0; x < 8; x++) {
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

void ChessBoard::performMove(const ChessMove& move)
{
    board[move.to] = board[move.from];
    board[move.from] = ' ';
}

LinkedList<int> ChessBoard::possibleMoves(int index, bool whitePlays) const
{
    ChessPiece piece = board[index];
    char kind = piece.kind();

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

        if ((xNew > 7 || xNew < 0) || (yNew > 7 || yNew < 0))
            return -1;

        return fieldToIndex(xNew, yNew);
    };

    auto getPiece = [&](int xoffset, int yoffset) {
        int i = offsetIndex(xoffset, yoffset);
        if (i < 0)
            return ChessPiece::invalidPiece();

        const ChessPiece& checkPiece = board[i];
        return checkPiece;
    };

    auto oppositeOrFreePiece = [&](int xoffset, int yoffset) {
        const ChessPiece& checkPiece = getPiece(xoffset, yoffset);
        if (checkPiece.invalid()) return false;
        return checkPiece.empty() || checkPiece.whiteOwns() != whitePlays;
    };

    auto oppositePiece = [&](int xoffset, int yoffset) {
        const ChessPiece& checkPiece = getPiece(xoffset, yoffset);
        if (checkPiece.invalid()) return false;
        return !checkPiece.empty() && checkPiece.whiteOwns() != whitePlays;
    };

    auto checkPush = [&](int xoffset, int yoffset) {
        if (oppositeOrFreePiece(xoffset, yoffset)) {
            result.push(offsetIndex(xoffset, yoffset));
            if (oppositePiece(xoffset, yoffset)) return false;
        } else return false;
        return true;
    };

    if (kind == 'p') {
        if (getPiece(0, 1).empty())
            result.push(offsetIndex(0, 1));

        int startPosY = whitePlays ? 1 : 6;

        if (y == startPosY && getPiece(0, 1).empty() && getPiece(0, 2).empty())
            result.push(offsetIndex(0, 2));

        if (oppositePiece(1, 1))
            result.push(offsetIndex(1, 1));

        if (oppositePiece(-1, 1))
            result.push(offsetIndex(-1, 1));

        return result;
    }

    if (kind == 'n') {

        // i = -1 and 1
        for (int i = -1; i <= 1; i += 2) {
            for (int j = -1; j <= 1; j += 2) {
                checkPush(1*i, 2*j);
                checkPush(2*j, 1*i);
            }
        }

        return result;
    }

    bool up, down, left, right;
    up = down = left = right = true;

    bool ne, nw, se, sw;
    ne = nw = se = sw = true;

    for (int i = 1; i < 8; i++) {
        if (up)
            if (kind == 'r' || kind == 'q' || (kind == 'k' && i == 1)) up = checkPush(0, i);

        if (down)
            if (kind == 'r' || kind == 'q' || (kind == 'k' && i == 1)) down = checkPush(0, -i);

        if (right)
            if (kind == 'r' || kind == 'q' || (kind == 'k' && i == 1)) right = checkPush(i, 0);

        if (left)
            if (kind == 'r' || kind == 'q' || (kind == 'k' && i == 1)) left = checkPush(-i, 0);

        if (ne)
            if (kind == 'b' || kind == 'q' || (kind == 'k' && i == 1)) ne = checkPush(i, i);

        if (nw)
            if (kind == 'b' || kind == 'q' || (kind == 'k' && i == 1)) nw = checkPush(-i, i);

        if (se)
            if (kind == 'b' || kind == 'q' || (kind == 'k' && i == 1)) se = checkPush(i, -i);

        if (sw)
            if (kind == 'b' || kind == 'q' || (kind == 'k' && i == 1)) sw = checkPush(-i, -i);
    }

    return result;
}

bool ChessBoard::validMove(const ChessMove& move, bool whitePlays) const
{
    auto moves = possibleMoves(move.from, whitePlays);

    return moves.contains(move.to);
}
