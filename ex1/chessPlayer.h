#ifndef PLAYER_H
#define PLAYER_H
#include "chessDefs.h"
#include "map.h"

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
Player playerCreate(int id);

/**
 * playerDestroy: free a player from memory, while updating played
 * games and tournaments.
 *
 * @param player - the player to free from memory. A NULL value is
 *     allowed, and in that case the function does nothing.
 */
void playerDestroy(Player player);

/**
* playerCopy: Creates a copy of the target player.
*
* @param node - Target player.
* @return
* 	NULL if a NULL was sent or a memory allocation failed.
* 	A Player containing the same elements as player otherwise.
*/
Player playerCopy(Player player);

int playerGetID(Player player);
int playerGetPlayingTime(Player player);
double playerGetLevel(Player player);
Map playerGetGames(Player player);
int playerGetNumOfGames(Player player);
int playerGetNumOfWins(Player player);
int playerGetNumOfLosses(Player player);
int playerGetNumOfDraws(Player player);


/**
 * playerAddGame: add a new Game a player participates in.
 *
 * @param player - player to add the game to. Must be non-NULL.
 * @param game - new game. Must be non-NULL.
 *
 * @return
 *     PLAYER_NULL_ARGUMENT - if player or game are NULL.
 *     PLAYER_GAME_ALREADY_EXIST - if a game with the same players already
 *     exists in the games map.
 *     PLAYER_SUCCESS - if game was added successfully.
 */
PlayerResult playerAddGame (Player player, ChessGame game);


///**
// * playerRemoveTournament: removes the tournament and all the games played in it from the player.
// *
// * @param player - player that contains the tournament. Must be non-NULL.
// * @param tournament_id - the tournament id. Must be non-negative, and unique.
// *
// * @return
// *     PLAYER_NULL_ARGUMENT - if player is NULL.
// *     PLAYER_INVALID_ID - if the tournament ID number is invalid.
// *     PLAYER_TOURNAMENT_NOT_EXIST - if the tournament does not exist in the system.
// *     PLAYER_SUCCESS - if tournament was removed successfully.
// */
//PlayerResult playerRemoveGame (Player player, int tournament_id);
//

///**
// * playerCalculateAveragePlayTime: the function returns the average playing time for a particular player.
// *
// * @param player - a player that contains the player. Must be non-NULL.
// * @param player_id - player ID. Must be non-negative.
// * @param player_result - this variable will contain the returned error code.
// * @return
// *     PLAYER_NULL_ARGUMENT - if player is NULL.
// *     PLAYER_INVALID_ID - if the player ID number is invalid.
// *     PLAYER_PLAYER_NOT_EXIST - if the player does not exist in the system.
// *     PLAYER_SUCCESS - if average playing time was returned successfully.
// */
//double playerCalculateAveragePlayTime (Player player, int player_id, PlayerResult* player_result);




#endif //MAP_PLAYER_H
