#ifdef DESKTOP

#include "logger.h"
#include "ChessBoard.h"
#include "ChessMove.h"
#include "chess-minimax.h"

#include <stdio.h>
#include <cstring>

void startGamePlayerComputer(int depth);
void startGameComputerComputer(int depth);

int main(int argc, char** argv)
{
    println("$== CHESS MATH ==$");
    println("Moves are written like 'e2 e4'");

    int mode = 0;
    int depth = 4;

    for(int i = 1; i < argc; i++){
        if (strncmp(argv[i], "-c", 3) == 0) {
            mode = 1;
            continue;
        }

        if (strncmp(argv[i], "-n", 3) == 0) {
            depth = std::stoi(argv[i+1]);
            continue;
        }
    }

    print("Depth set to: ");
    println(depth);

    println("");

    switch(mode) {
        case 1: {
            startGameComputerComputer(depth);
            break;
        }
        default: {
            startGamePlayerComputer(depth);
            break;
        }
    }



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

void computerMove(bool& whitePlays, ChessBoard& board, int depth)
{
    println("Computer is thinking...");

    ChessEngine engine;

    ChessMove computerMove = engine.calculateMoveIterative(board, 120000, whitePlays);
    //ChessMove computerMove = engine.calculateMove(board, depth, whitePlays);

    print("Computer moving ");
    char name[16];
    board.board[computerMove.from].name(name);
    print(name);
    print(" ");
    computerMove.printMove();
    print(" - With calculated score: ");
    println(computerMove.score);
    print(" - Total minimax calls: ");
    println(engine.getSteps());
    print(" - Total minimax optimization swaps: ");
    println(engine.getSwaps());
    print(" - Total transposition table size: ");
    println(engine.getTransTableSize());
    println("");
    if (!board.board[computerMove.to].empty()) {
        print("Taking ");
        board.board[computerMove.to].name(name);
        println(name);
    }

    board.performMove(computerMove);
    whitePlays = !whitePlays;
}

void startGamePlayerComputer(int depth)
{
    ChessBoard board;
    bool whitePlays = true;

    while (true) {

        print("Current board score: ");
        println(ChessEngine::evaluateMoveScore(board));

        board.printBoard();

        if (!whitePlays) {
            computerMove(whitePlays, board, depth);
            continue;
        }

        int status;
        status = userMove(whitePlays, board);
        if (status == 1) continue;
        if (status == 2) break;

        int endState = board.gameEnded();
        if (endState != 0) {
            if (endState == 1)
                print("Black");
            else
                print("White");

            println(" has won!");
            break;
        }
    }
}

void startGameComputerComputer(int depth)
{
    ChessBoard board;
    bool whitePlays = true;

    int count = 0;

    while (true) {

        count++;

        print("Move #");
        println(count);

        print("Current board score: ");
        println(ChessEngine::evaluateMoveScore(board));

        board.printBoard();

        computerMove(whitePlays, board, depth);

        int endState = board.gameEnded();
        if (endState != 0) {
            if (endState == 1)
                print("Black");
            else
                print("White");

            println(" has won!");
            break;
        }
    }
}

#endif // #ifdef DESKTOP