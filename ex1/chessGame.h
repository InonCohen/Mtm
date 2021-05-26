#ifndef EX1_CHESSGAME_H
#define EX1_CHESSGAME_H
#include "chessDefs.h"
#include "chessSystem.h"
///** Type for representing a chess game in a tournament */
//typedef struct chess_game_t *ChessGame;

ChessGame chessGameCreate(unsigned int tournament_id, unsigned int player1,
                          unsigned int player2, int playTime, Winner winner);

ChessGame chessGameCopy(ChessGame);

void chessGameDestroy(ChessGame);

char* getChessGameID(ChessGame);

#endif //EX1_CHESSGAME_H
