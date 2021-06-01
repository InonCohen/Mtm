#ifndef EX1_CHESSPLAYER_H
#define EX1_CHESSPLAYER_H
#include "../map/map.h"
#include "chessDefs.h"
#include "chessGame.h"
#include "chessPlayerID.h"

typedef enum {
    PLAYER_OUT_OF_MEMORY,
    PLAYER_NULL_ARGUMENT,
    PLAYER_INVALID_ID,
    PLAYER_INVALID_LOCATION,
    PLAYER_INVALID_MAX_GAMES,
    PLAYER_TOURNAMENT_ALREADY_EXISTS,
    PLAYER_TOURNAMENT_NOT_EXIST,
    PLAYER_GAME_ALREADY_EXISTS,
    PLAYER_INVALID_PLAY_TIME,
    PLAYER_EXCEEDED_GAMES,
    PLAYER_PLAYER_NOT_EXIST,
    PLAYER_TOURNAMENT_ENDED,
    PLAYER_NO_TOURNAMENTS_ENDED,
    PLAYER_SAVE_FAILURE,
    PLAYER_SUCCESS
} PlayerResult ;
/**
 * playerCreate: create an empty player.
 *
 * @param id - the new player id
 * @return A new player in case of success, and NULL otherwise (e.g.
 *     in case of an allocation error)
 */
ChessPlayer playerCreate(PlayerID id);
/**
 * playerDestroy: free a player from memory, while updating played
 * games and tournaments.
 *
 * @param player - the player to free from memory. A NULL value is
 *     allowed, and in that case the function does nothing.
 */
void playerDestroy(ChessPlayer player);
/**
* playerCopy: Creates a copy of the target player.
*
* @param node - Target player.
* @return
* 	NULL if a NULL was sent or a memory allocation failed.
* 	A ChessPlayer containing the same elements as player otherwise.
*/
ChessPlayer playerCopy(ChessPlayer player);
/**
 *
 * @param player
 * @return
 */
PlayerID playerGetID(ChessPlayer player);

char* playerGetIDString(ChessPlayer player);

int playerGetPlayingTime(ChessPlayer player);

double playerGetLevel(ChessPlayer player);

Map playerGetGames(ChessPlayer player);

int playerGetNumOfGames(ChessPlayer player);

int playerGetNumOfWins(ChessPlayer player);

int playerGetNumOfLosses(ChessPlayer player);

int playerGetNumOfDraws(ChessPlayer player);

bool playerIsDeleted(ChessPlayer player);

PlayerResult playerAddGame(ChessPlayer player, ChessGame game);

PlayerResult playerRemoveGame(ChessPlayer player, ChessGame game);

void playerSetIsDeleted(ChessPlayer player);

void playerUpdateAccordingToGame(ChessPlayer player, GamePlayerOutcome old_outcome, GamePlayerOutcome new_outcome);

void playerRemoveDraw(ChessPlayer player);
#endif //EX1_CHESSPLAYER_H
