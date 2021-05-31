#ifndef EX1_CHESSGAME_H
#define EX1_CHESSGAME_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "chessDefs.h"
#include "chessSystem.h"
#include "chessPlayerID.h"
#include "chessPlayer.h"

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



ChessGame gameCreate(int tournament_id, PlayerID player1_id, PlayerID player2_id, int play_time, Winner winner);

ChessGame gameCopy(ChessGame game);

void gameDestroy(ChessGame game);

PlayerID gameGetPlayer1ID(ChessGame game);

PlayerID gameGetPlayer2ID(ChessGame game);

int gameGetTournamentID(ChessGame game);

int gameGetPlayTime(ChessGame game);

char* gameGetID(ChessGame game);

Winner gameGetWinner(ChessGame game);

void gameUpdateLoser(ChessGame game, ChessPlayer player);

void gameSetWinner(ChessGame game, Winner winner);

bool gamePlayerIsDeleted(ChessGame game);

void gameMarkDeletedPlayerTrue(ChessGame game);


#endif //EX1_CHESSGAME_H
