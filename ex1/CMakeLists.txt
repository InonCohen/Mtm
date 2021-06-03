cmake_minimum_required(VERSION 3.0.0)
project(EX1 VERSION 0.1.0 LANGUAGES C)

# If you want to see "under the hood" of CMake, uncomment this:
set(CMAKE_VERBOSE_MAKEFILE ON)

# Define variables containing compiler flags for gcc
set(MTM_FLAGS_DEBUG "-std=c99 --pedantic-errors -Wall -Werror -g")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDEBUG")
# Set the flags for gcc
set(CMAKE_C_FLAGS ${MTM_FLAGS_RELEASE})

# Include directories
include_directories(map)
include_directories(chess)
include_directories(chess/test)

# Add the names of your source files here
set(CHESS_C_FILES
        chess/chessSystem.c
        chess/chessTournament.c
        chess/chessGame.c
        chess/chessDefinitions.h
        chess/chessPlayer.c
        chess/chessPlayerID.c
        chess/chessDefs.h
        chess/chessMapUtils.c
        chess/strUtils.c)
set(MAP_C_FILES
        map/map.c
        map/DLLNode.c
        map/LinkedList.c
        )
set(TEST_C_FILES
        chess/test/chessSystemTestsExample.c)

add_executable(chessSystem ${CHESS_C_FILES} ${MAP_C_FILES} ${TEST_C_FILES})

