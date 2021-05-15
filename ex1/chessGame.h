#ifndef EX1_CHESSGAME_H
#define EX1_CHESSGAME_H

/** Type for representing a chess game in a tournament */
typedef struct chess_game_t *ChessGame;

ChessGame chessGameCreate();

ChessGame chessGameCopy(ChessGame);

void chessGameDestroy(ChessGame);

#endif //EX1_CHESSGAME_H
