cmake_minimum_required(VERSION 3.12)
project(skak_math)

set(CMAKE_CXX_STANDARD 11)

set(
    SOURCES

        main.cpp
        logger.cpp
        ChessPiece.cpp
        ChessBoard.cpp
        ChessMove.cpp
        chess-minimax.cpp
)

add_executable(skak_math ${SOURCES})

add_compile_definitions(DESKTOP)