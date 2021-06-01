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

/**
* gameCreate: Allocates a new game.
*
* @param tournament_id - the tournament in which the game takes place
* @param player1_id - id of the first player
* @param player2_id - id of the second player
* @param play_time - the duration of the game in seconds
* @param winner - the winner of the game
* @return
*     NULL if an invalid argument was sent or if a memory allocation failed
*     a new ChessGame otherwise
*/

ChessGame gameCreate(int tournament_id, PlayerID player1_id, PlayerID player2_id, int play_time, Winner winner);

/**
* gameCopy: Creates a copy of target game.
*
* @param game - Target game.
* @return
* 	NULL if a NULL was sent or a memory allocation failed.
* 	A ChessGame identical to game otherwise.
*/

ChessGame gameCopy(ChessGame game);

/**
* gameDestroy: Deallocates an existing game and its components.
*
* @param game - Target game to be deallocated. If game is NULL nothing will be
* 		done
*/
void gameDestroy(ChessGame game);

/**
* gameGetPlayer1ID: Returns the id of the first player of the game
* @param game - The game in which player1 plays
* @return
* 	NULL if a NULL pointer was sent.
* 	Otherwise the first player ID.
*/
PlayerID gameGetPlayer1ID(ChessGame game);

/**
* gameGetPlayer2ID: Returns the id of the second player of the game
* @param game - The game in which player2 plays
* @return
* 	NULL if a NULL pointer was sent.
* 	Otherwise the second player ID.
*/
PlayerID gameGetPlayer2ID(ChessGame game);

/**
* gameGetTournamentID: Returns the id of the tournament in which game was played
* @param game - The game which tournament is required
* @return
* 	(-999) if a NULL pointer was sent.
* 	Otherwise the game's tournament ID.
*/
int gameGetTournamentID(ChessGame game);

/**
* gameGetPlayTime: Returns the play time during which the game was played
* @param game - The game which duration time is required
* @return
* 	(-999) if a NULL pointer was sent.
* 	Otherwise the game's duration time.
*/
int gameGetPlayTime(ChessGame game);

/**
* gameGetID: Returns the id of the game
* @param game - The game of which id is required
* @return
* 	NULL if a NULL pointer was sent.
* 	Otherwise the game ID.
*/
char* gameGetID(ChessGame game);

/**
* gameGetWinner: Returns the winner of the game
* @param game - The game of which winner is required
* @return
* 	(-999) if a NULL pointer was sent.
* 	Otherwise the game winner.
*/
Winner gameGetWinner(ChessGame game);

/**
* gameUpdateLoser: sets the players new victory status.
*                  The function updates the game's two players' statistics,
*                  and the game_winner
* @param game - The game in which the players are competing
* @param loser - The player which is to be assigned as loser
* @param winner - The player which is to be assigned as winner
*/
void gameUpdateLoser(ChessGame game, ChessPlayer loser, ChessPlayer winner);

/**
* gameSetWinner: Updates the winner of the game
* @param game - The game of which winner is to be updated
* @param winner - The new winner which is to be assigned
*/
void gameSetWinner(ChessGame game, Winner winner);

/**
* gamePlayerIsDeleted: Returns whether one or more of the game's players were deleted
* @param game - The game of which players status is required.
* @return
* 	true if a NULL pointer was sent.
* 	Otherwise the game player_deleted field, which indicates if at least one of the players is marked as deleted
*/
bool gamePlayerIsDeleted(ChessGame game);

/**
* gameMarkDeletedPlayerTrue: Marks the game's player_deleted as true
* @param game - The game of which player has been deleted
*/
void gameMarkDeletedPlayerTrue(ChessGame game);
#endif //EX1_CHESSGAME_H
