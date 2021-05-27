#ifndef EX1_CHESSGAME_H
#define EX1_CHESSGAME_H
#include "chessDefs.h"
#include "chessSystem.h"

///** Type for representing a chess game in a tournament */
// In the meantime, defined in: chessDefs.h
//typedef struct chess_game_t *ChessGame;

ChessGame gameCreate(int tournament_id, int player1, int player2, int playTime, Winner winner);

ChessGame gameCopy(ChessGame);

void gameDestroy(ChessGame);

char* getChessGameID(ChessGame);


#endif //EX1_CHESSGAME_H
