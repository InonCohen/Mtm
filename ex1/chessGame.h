#ifndef EX1_CHESSGAME_H
#define EX1_CHESSGAME_H

#include "chessSystem.h"

/** Type for representing a chess game in a tournament */
typedef struct chess_game_t *ChessGame;

ChessGame chessGameCreate(unsigned int game_id, unsigned int player1, unsigned int player2, int play_time, Winner winner);

ChessGame chessGameCopy(ChessGame);

void chessGameDestroy(ChessGame);

#endif //EX1_CHESSGAME_H
