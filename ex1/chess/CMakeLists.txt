# The first line states the minimum CMake version to use with this project
# and is requires by CMake.
cmake_minimum_required(VERSION 3.0.0)

project(EX1 VERSION 0.1.0 LANGUAGES C)

# Define variables containing compiler flags for gcc
set(MTM_FLAGS_DEBUG "-std=c99 --pedantic-errors -Wall -Werror")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDEBUG")

# Set the flags for gcc
set(CMAKE_C_FLAGS ${MTM_FLAGS_DEBUG})

#add additional directories
add_library(map ../map)

# Add the names of your source files here
set(CHESS_C_FILES strUtils.c chessGameMap.c chessGame.c chessPlayer.c chessTournament.c test/chessTournamentTest.c)
add_executable(Chess ${CHESS_C_FILES})

#Finally, link all libaries
target_link_libraries(Chess map)

