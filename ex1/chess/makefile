CC = gcc
OBJS = chessSystem.o chessGame.o chessMapUtils.o chessPlayer.o chessPlayerID.o chessTournament.o strUtils.o chessSystemTestsExample.o
EXEC = chess
DEBUG_FLAG = # now empty, assign -g for debug
COMP_FLAG=-std=c99  -Wall -pedantic-errors -Werror -DNDEBUG $(DEBUG)

$(EXEC) : $(OBJS)
	$(CC) $(COMP_FLAG) $(OBJS) -o $@ -L. -lmap

chessSystem.o: chessSystem.c map.h chessMapUtils.h chessSystem.h chessTournament.h chessGame.h chessDefinitions.h chessPlayerID.h chessPlayer.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
chessGame.o: chessGame.c strUtils.h chessGame.h chessDefinitions.h chessSystem.h chessPlayerID.h chessPlayer.h map.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
chessMapUtils.o: chessMapUtils.c strUtils.h chessGame.h chessDefinitions.h chessSystem.h chessPlayerID.h chessPlayer.h map.h chessTournament.h chessMapUtils.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
chessPlayer.o: chessPlayer.c map.h chessMapUtils.h chessGame.h chessDefinitions.h chessSystem.h chessPlayerID.h chessPlayer.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
chessPlayerID.o: chessPlayerID.c chessPlayerID.h chessDefinitions.h strUtils.h chessSystem.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
chessTournament.o: chessTournament.c map.h strUtils.h chessSystem.h chessTournament.h chessGame.h chessDefinitions.h chessPlayerID.h chessPlayer.h chessMapUtils.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
strUtils.o: strUtils.c strUtils.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
chessSystemTestsExample.o: tests/chessSystemTestsExample.c chessSystem.h test_utilities.h strUtils.h chessMapUtils.h map.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) tests/$*.c

clean:
	rm -f $(OBJS) $(EXEC)