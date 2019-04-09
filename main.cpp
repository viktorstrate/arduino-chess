#ifdef DESKTOP

#include "logger.h"
#include "ChessBoard.h"
#include "ChessMove.h"
#include "chess-minimax.h"

#include <stdio.h>
#include <cstring>

void startGamePlayerComputer(int depth, int maxSteps);
void startGameComputerComputer(int depth, int maxSteps);

int main(int argc, char** argv)
{
    Println("$== CHESS MATH ==$");
    Println("Moves are written like 'e2 e4'");

    int mode = 0;
    int depth = 8;
    int maxSteps = 100000;

    for(int i = 1; i < argc; i++){
        if (strncmp(argv[i], "-c", 3) == 0) {
            mode = 1;
            continue;
        }

        if (strncmp(argv[i], "-n", 3) == 0) {
            depth = std::stoi(argv[i+1]);
            continue;
        }

        if (strncmp(argv[i], "-s", 3) == 0) {
            maxSteps = std::stoi(argv[i+1]);
            continue;
        }
    }

    Print("Depth set to: ");
    Println(depth);

    Print("Max steps set to: ");
    Println(maxSteps);

    Println("");

    switch(mode) {
        case 1: {
            startGameComputerComputer(depth, maxSteps);
            break;
        }
        default: {
            startGamePlayerComputer(depth, maxSteps);
            break;
        }
    }



    return 0;
}

int userMove(ChessBoard& board)
{

    if (board.whitePlays)
        Print("White");
    else
        Print("Black");

    Println(" goes next");

    Println("Perform move:");
    char buffer[12];
    fgets(buffer, 12, stdin);

    if (strlen(buffer) == 3) {
        Print("Possible moves: ");
        ChessMove move = ChessMove(buffer);
        board.possibleMoves(move.from).printList();
        Println("");
        return 1;
    }

    if (strncmp(buffer, "exit\n", sizeof("exit\n")) == 0) return 2;

    ChessMove move(buffer);

    if (board.validMove(move)) {
        Print("Moving ");
        char name[16];
        board.board[move.from].name(name);
        Print(name);
        Print(" ");
        move.printMove();

        if (!board.board[move.to].empty()) {
            Print("Taking ");
            board.board[move.to].name(name);
            Println(name);
        }

        Println("");

        board.performMove(move);
    } else {
        Println("Invalid move try again");
        return 1;
    }

    return 0;
}

void computerMove(ChessBoard& board, int depth, int maxSteps)
{
    Println("Computer is thinking...");

    ChessEngine engine;

    ChessMove computerMove = engine.calculateMoveIterative(board, maxSteps);
    //ChessMove computerMove = engine.calculateMove(board, depth, whitePlays);

    Print("Computer moving ");
    char name[16];
    board.board[computerMove.from].name(name);
    Print(name);
    Print(" ");
    computerMove.printMove();
    Print(" - With calculated score: ");
    Println(computerMove.score);
    Print(" - Total minimax calls: ");
    Println(engine.getSteps());
    Print(" - Total minimax optimization swaps: ");
    Println(engine.getSwaps());
    Print(" - Total transposition table size: ");
    Println(engine.getTransTableSize());
    Print(" - Total transposition table uses: ");
    Println(engine.getTransTableUses());
    Println("");
    if (!board.board[computerMove.to].empty()) {
        Print("Taking ");
        board.board[computerMove.to].name(name);
        Println(name);
    }

    board.performMove(computerMove);
}

void startGamePlayerComputer(int depth, int maxSteps)
{
    ChessBoard board;

    while (true) {

        Print("Current board score: ");
        Println(ChessEngine::evaluateMoveScore(board));

        board.printBoard();

        if (!board.whitePlays) {
            computerMove(board, depth, maxSteps);
            continue;
        }

        int status;
        status = userMove(board);
        if (status == 1) continue;
        if (status == 2) break;

        int endState = board.gameEnded();
        if (endState != 0) {
            if (endState == 1)
                Print("Black");
            else
                Print("White");

            Println(" has won!");
            break;
        }
    }
}

void startGameComputerComputer(int depth, int maxSteps)
{
    ChessBoard board;

    int count = 0;

    while (true) {

        count++;

        Print("Move #");
        Println(count);

        Print("Current board score: ");
        Println(ChessEngine::evaluateMoveScore(board));

        board.printBoard();

        computerMove(board, depth, maxSteps);

        int endState = board.gameEnded();
        if (endState != 0) {
            if (endState == 1)
                Print("Black");
            else
                Print("White");

            Println(" has won!");
            break;
        }
    }
}

#endif // #ifdef DESKTOP