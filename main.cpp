#ifdef DESKTOP

#include "logger.h"
#include "ChessBoard.h"
#include "ChessMove.h"
#include "chess-minimax.h"

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

int userMove(bool& whitePlays, ChessBoard& board)
{

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
        return 1;
    }

    if (strncmp(buffer, "exit\n", sizeof("exit\n")) == 0) return 2;

    ChessMove move(buffer);

    if (board.validMove(move, whitePlays)) {
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
    } else {
        println("Invalid move try again");
        return 1;
    }

    return 0;
}

void computerMove(bool& whitePlays, ChessBoard& board)
{
    int steps = 0;
    ChessMove computerMove = calculateMove(board, 5, whitePlays, &steps);

    print("Computer moving ");
    char name[16];
    board.board[computerMove.from].name(name);
    print(name);
    print(" ");
    computerMove.printMove();
    print(" - With calculated score: ");
    println(computerMove.score);
    print(" - Total minimax calls: ");
    println(steps);
    println("");
    if (!board.board[computerMove.to].empty()) {
        print("Taking ");
        board.board[computerMove.to].name(name);
        println(name);
    }

    board.performMove(computerMove);
    whitePlays = !whitePlays;
}

void startGame()
{
    ChessBoard board;
    bool whitePlays = true;

    while (true) {

        print("Current board score: ");
        println(evaluateMoveScore(board));

        board.printBoard();

        if (!whitePlays) {
            computerMove(whitePlays, board);
            continue;
        }

        int status;
        status = userMove(whitePlays, board);
        if (status == 1) continue;
        if (status == 2) break;
    }
}

#endif // #ifdef DESKTOP