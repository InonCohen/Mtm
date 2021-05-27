cmake_minimum_required(VERSION 3.19)
project(ex1 C)

set(CMAKE_C_STANDARD 99)

link_directories(.)

add_executable(ex1 ChessTests.c  chessGameCopy.c chessPlayer.c map.c LinkedList.c DLLNode.c)

target_link_libraries(ex1 libmap.a)