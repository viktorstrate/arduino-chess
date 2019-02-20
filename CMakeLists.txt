cmake_minimum_required(VERSION 3.12)
project(arduino_chess)

set(CMAKE_CXX_STANDARD 11)

set(
    SOURCES

        main.cpp
        ChessPiece.cpp
        ChessBoard.cpp
        ChessMove.cpp
        chess-minimax.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

# To distinguish between desktop and arduino
add_compile_definitions(DESKTOP)