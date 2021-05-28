cmake_minimum_required(VERSION 3.19)
project(map C)

set(CMAKE_C_STANDARD 99)

add_executable(map tests/mapTests1.c map.c LinkedList.c DLLNode.c ../Player.c ../Player.h ../PlayerTests.c)