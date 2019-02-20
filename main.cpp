#ifdef DESKTOP

#include "logger.h"
#include "ChessBoard.h"
#include "ChessMove.h"

#include <stdio.h>
#include <cstring>

void startGame();

int main()
{
    println("$== CHESS MATH ==$");
    println("Moves are written like 'e2 e4'\n");

    startGame();

    return 0;
}

void startGame()
{
    ChessBoard board;
    bool whitePlays = true;

    while(true)
    {
        board.printBoard();

        if (whitePlays)
            print("White");
        else
            print("Black");

        println(" goes next");

        println("Perform move:");
        char buffer[12];
        fgets(buffer, 12, stdin);

        if (strlen(buffer) == 3) {
            print("Possible moves: ");
            ChessMove move = ChessMove(buffer);
            board.possibleMoves(move.from, whitePlays).printList();
            println("");
            continue;
        }

        if (strncmp(buffer, "exit\n", sizeof("exit\n")) == 0) break;

        ChessMove move(buffer);

        if (board.validMove(move, whitePlays))
        {
            print("Moving ");
            char name[16];
            board.board[move.from].name(name);
            print(name);
            print(" ");
            move.printMove();

            if (!board.board[move.to].empty()) {
                print("Taking ");
                board.board[move.to].name(name);
                println(name);
            }

            println("");

            board.performMove(move);
            whitePlays = !whitePlays;
        }
        else
        {
            println("Invalid move try again");
        }
    }
}

#endif // #ifdef DESKTOP