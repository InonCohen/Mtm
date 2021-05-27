#ifndef EX1_CHESSGAME_H
#define EX1_CHESSGAME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "chessDefs.h"
typedef enum {
    FIRST_PLAYER,
    SECOND_PLAYER,
    DRAW
} Winner;
typedef enum {
    GAME_OUT_OF_MEMORY,
    GAME_NULL_ARGUMENT,
    GAME_INVALID_ID,
    GAME_INVALID_LOCATION,
    GAME_INVALID_MAX_GAMES,
    GAME_TOURNAMENT_ALREADY_EXISTS,
    GAME_TOURNAMENT_NOT_EXIST,
    GAME_GAME_ALREADY_EXISTS,
    GAME_INVALID_PLAY_TIME,
    GAME_EXCEEDED_GAMES,
    GAME_PLAYER_NOT_EXIST,
    GAME_TOURNAMENT_ENDED,
    GAME_NO_TOURNAMENTS_ENDED,
    GAME_SAVE_FAILURE,
    GAME_SUCCESS
} GameResult ;

ChessGame gameCreate(char* game_id, int tournament_id, int player1, int player2, int play_time, Winner winner);
void gameDestroy(ChessGame game);
ChessGame gameCopy(ChessGame game);
bool gamePlayerIsDeleted(ChessGame game);
char* gameGetID(ChessGame game);
int gameGetPlayer1(ChessGame game);
int gameGetPlayer2(ChessGame game);
int gameGetTournament(ChessGame game);
int gameGetPlayTime(ChessGame game);
Winner gameGetWinner(ChessGame game);
void gameSetWinner(ChessGame game, Winner winner);
bool gamePlayerIsDeleted(ChessGame game);
/*
ChessGame gameCreate(unsigned int game_id, Player player1, Player player2, int play_time, Winner winner);

ChessGame gameCopy(ChessGame game);

void gameDestroy(ChessGame game);

Player gameGetPlayer1(ChessGame game);

Player gameGetPlayer2(ChessGame game);

char* gameGetID(ChessGame game);

Winner gameGetWinner(ChessGame game);

GameResult gameUpdateLoser(char* game_id, Player player);

void gameSetWinner(Game game, Winner winner);
*/




#endif //EX1_CHESSGAME_H
