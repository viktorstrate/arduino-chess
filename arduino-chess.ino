#include "logger.h"
#include "ChessBoard.h"
#include "ChessMove.h"
#include "chess-minimax.h"

#define DEPTH 2

ChessBoard board;
bool whitePlays;

void setup() {
  Serial.begin(9600);
  whitePlays = true;
}

void loop() {

  print("Current board score: ");
  println(evaluateMoveScore(board));

  board.printBoard();

  println("Computer is thinking...");
  int steps = 0;
  int swaps = 0;
  ChessMove computerMove = calculateMove(board, DEPTH, whitePlays, &steps, &swaps);

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
  print(" - Total minimax optimization swaps: ");
  println(swaps);
  println("");
  if (!board.board[computerMove.to].empty()) {
      print("Taking ");
      board.board[computerMove.to].name(name);
      println(name);
  }

  board.performMove(computerMove);
  whitePlays = !whitePlays;

  int endState = board.gameEnded();
  if (endState != 0) {
      if (endState == 1)
          print("White");
      else
          print("Black");

      println(" has won!");
      for(;;);
  }
}
