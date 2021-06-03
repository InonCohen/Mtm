# The first line states the minimum CMake version to use with this project
# and is requires by CMake.
cmake_minimum_required(VERSION 3.0.0)
project(EX1 VERSION 0.1.0 LANGUAGES C)

# If you want to see "under the hood" of CMake, uncomment this:
set(CMAKE_VERBOSE_MAKEFILE ON)

# Define variables containing compiler flags for gcc
set(MTM_FLAGS_DEBUG "-std=c99 --pedantic-errors -Wall -Werror")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDEBUG")
# Set the flags for gcc
set(CMAKE_C_FLAGS ${MTM_FLAGS_RELEASE})

# Include directories
include_directories(map)
include_directories(chess)
include_directories(chess/test)

# Add the names of your source files here
set(CHESS_C_FILES
        strUtils.c
        chessMapUtils.c
        chessGame.c
        chessPlayer.c
        chessPlayerID.c
        chessTournament.c
        chessSystem.c)
set(MAP_C_FILES
        map.c
        DLLNode.c
        LinkedList.c)
set(TEST_C_FILES
        test/chessSystemTestsExample.c)

add_executable(chessSystem ${CHESS_C_FILES} ${MAP_C_FILES} ${TEST_C_FILES})


