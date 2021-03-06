#ifndef EX1_CHESSPLAYER_H
#define EX1_CHESSPLAYER_H
#include "map.h"
#include "chessDefinitions.h"
#include "chessGame.h"
#include "chessPlayerID.h"

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
* 	NULL if NULL was sent or a memory allocation failed.
* 	A ChessPlayer containing the same elements as player otherwise.
*/
ChessPlayer playerCopy(ChessPlayer player);

/**
* playerGetID: Returns the id of target player.
*
* @param player - Target player.
* @return
* 	NULL if NULL was sent ot NULL.
*   The PlayerID otherwise.
*/
PlayerID playerGetID(ChessPlayer player);

/**
* playerGetPlayingTime: Returns the total playing time in all games of target player.
*
* @param player - Target player.
* @return
* 	(-999) if NULL was sent.
*   the player's total_time otherwise.
*/
int playerGetPlayingTime(ChessPlayer player);

/**
* playerGetLevel: Returns the level of target player.
*
* @param player - Target player.
* @return
* 	(-999) if a NULL was sent.
*   the player's level otherwise.
*/
double playerGetLevel(ChessPlayer player);

/**
* playerGetGames: Returns the Map of games of target player.
*
* @param player - Target player.
* @return
* 	NULL if a NULL was sent.
*   the player's games map otherwise.
*/
Map playerGetGames(ChessPlayer player);

/**
* playerGetNumOfGames: Returns the size of the Map of games of target player.
*
* @param player - Target player.
* @return
* 	(-999) if NULL was sent.
*   the player's games map's size otherwise.
*/
int playerGetNumOfGames(ChessPlayer player);

/**
* playerGetNumOfWins: Returns the number of games of target player in which
*                  he finished as the game's winner.
*
* @param player - Target player.
* @return
* 	(-999) if NULL was sent.
*   The player's number of wins otherwise.
*/
int playerGetNumOfWins(ChessPlayer player);

/**
* playerGetNumOfLosses: Returns the number of games of target player in which
*                  he finished as the game's loser.
*
* @param player - Target player.
* @return
* 	(-999) if NULL was sent.
*   The player's number of losses otherwise.
*/
int playerGetNumOfLosses(ChessPlayer player);

/**
* playerGetNumOfDraws: Returns the number of games of target player in which
*                  he finished as a game's tier.
*
* @param player - Target player.
* @return
* 	(-999) if NULL was sent.
*   The player's number of draws otherwise.
*/
int playerGetNumOfDraws(ChessPlayer player);

/**
* playerIsDeleted: Returns whether target player is deleted.
*
* @param player - Target player.
* @return
* 	True if NULL was sent or the player is deleted.
*   False otherwise.
*/
bool playerIsDeleted(ChessPlayer player);

/**
 * playerAddGame: add a new game to a player.
 *                The function updates the player's statistics according
 *                to his victory status in the game.
 *
 * @param player - player that contains map of games. Must be non-NULL.
 * @param game - game to be added to player's map of games.
 *
 * @return
 *     CHESS_NULL_ARGUMENT - if player is NULL or game is NULL.
 *     CHESS_INVALID_ID - if the player ID number, doesn't match either of game's players' ids.
 *     CHESS_GAME_ALREADY_EXISTS - if there is already a game in the player's games map with the same two players
 *                                  (and both were not removed).
 *     CHESS_OUT_OF_MEMORY - if an allocation failed(the game couldn't be inserted to the player's games map).
 *     CHESS_SUCCESS - if game was added successfully.
 */
ChessResult playerAddGame(ChessPlayer player, ChessGame game);

/**
 * playerRemoveGame: Remove a game from a player.
 *                The function updates the player's statistics according
 *                to his victory status in the game.
 *
 * @param player - player that contains map of games. Must be non-NULL.
 * @param game - game to be removed from player's map of games.
 *
 * @return
 *     CHESS_NULL_ARGUMENT - if player is NULL or game is NULL.
 *     CHESS_OUT_OF_MEMORY - if an allocation failed(the game couldn't be removed from the player's games map).
 *     CHESS_SUCCESS - if game was removed successfully or didn't exist in the games map.
 */
ChessResult playerRemoveGame(ChessPlayer player, ChessGame game);

/**
 * playerMarkDeleted: update the player as deleted
 *
 * @param player - the player to mark as deleted. Must be non-NULL.
 */
void playerSetIsDeleted(ChessPlayer player);

/**
 * playerAddWin: updates the player's statistics according to given game that is already in player's games map
 *
 * @param player - player whose statistics are to be updated to add another win
 * @param game - game of which the player is the winner
 */
void playerAddWin(ChessPlayer player, ChessGame game);

/**
 * playerRemoveWin: updates the player's statistics according to given game that is already in player's games map
 *
 * @param player - player whose statistics are to be updated to remove a win
 * @param game - game of which the player is the winner
 */
void playerRemoveWin(ChessPlayer player, ChessGame game);

/**
 * playerAddLose: updates the player's statistics according to given game that is already in player's games map
 *
 * @param player - player whose statistics are to be updated to add another lose
 * @param game - game of which the player is the loser
 */
void playerAddLose(ChessPlayer player, ChessGame game);

/**
 * playerRemoveLose: updates the player's statistics according to given game that is already in player's games map
 *
 * @param player - player whose statistics are to be updated to remove a lose
 * @param game - game of which the player is the loser
 */
void playerRemoveLose(ChessPlayer player, ChessGame game);

/**
 * playerAddDraw: updates the player's statistics according to given game that is already in player's games map
 *
 * @param player - player whose statistics are to be updated to add another draw
 * @param game - game of which the player is the tier
 */
void playerAddDraw(ChessPlayer player, ChessGame game);

/**
 * playerRemoveDraw: updates the player's statistics according to given game that is already in player's games map
 *
 * @param player - player whose statistics are to be updated to remove a draw
 * @param game - game of which the player is the tier
 */
void playerRemoveDraw(ChessPlayer player, ChessGame game);

#endif //EX1_CHESSPLAYER_H
