project(ex1 LANGUAGES C)
set(CMAKE_C_STANDARD 99)
set(MTM_FLAGS_DEBUG "-std=c99 --pedantic-errors -Wall -Werror")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDEBUG")
set(CMAKE_C_FLAGS "${MTM_FLAGS_RELEASE}")


add_executable(ex1 ../test/chessTournamentTest.c map.c DLLNode.c LinkedList.c chessGameMap.c strUtils.c chessTournament.c chessGame.c chessPlayer.c)
