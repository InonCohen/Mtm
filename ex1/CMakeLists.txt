cmake_minimum_required(VERSION 3.19)
project(ex1 C)

set(CMAKE_C_STANDARD 99)

add_executable(ex1 PlayerTests.c chessPlayer.c chessGame.c)