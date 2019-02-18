#ifdef DESKTOP

#include "logger.h"
#include "ChessBoard.h"
#include "ChessMove.h"

#include <stdio.h>
#include <cstring>

int main()
{
    println("$== CHESS MATH ==$");

    ChessBoard board;

    while(true)
    {
        board.printBoard();


        println("Perform move (eg. 'e2 e4'):");
        char buffer[12];
        fgets(buffer, 12, stdin);

        if (strncmp(buffer, "exit\n", sizeof("exit\n")) == 0) break;

        ChessMove move(buffer);
        board.performMove(move);
    }

    return 0;
}

#endif // #ifdef DESKTOP