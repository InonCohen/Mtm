#ifndef EX1_CHESSPLAYER_H
#define EX1_CHESSPLAYER_H
#include "chessDefs.h"
#include "../map/map.h"

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
//
///** Type for defining the Player */
// In the meantime, defined in: chessDefs.h
// typedef struct chess_player_t *chessPlayer;


/**
 * playerCreate: create an empty player.
 *
 * @param id - the new player id
 * @return A new player in case of success, and NULL otherwise (e.g.
 *     in case of an allocation error)
 */
ChessPlayer playerCreate(int id);

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

int playerGetID(ChessPlayer player);
int playerGetPlayingTime(ChessPlayer player);
int playerGetLevel(ChessPlayer player);
Map playerGetGames(ChessPlayer player);
int playerGetNumOfGames(ChessPlayer player);
int playerGetNumOfWins(ChessPlayer player);
int playerGetNumOfLosses(ChessPlayer player);
int playerGetNumOfDraws(ChessPlayer player);


///**
// * playerAddGame: add a new Game a player participates in.
// *
// * @param player - player to add the game to. Must be non-NULL.
// * @param game_id - new game id. Must be non-NULL.
// *
// * @return
// *     PLAYER_NULL_ARGUMENT - if player or game_id are NULL.
// *     PLAYER_INVALID_ID - the player ID number is invalid.
// *     PLAYER_GAME_ALREADY_EXIST - if a game with the same players already
// *     exists in the games map.
// *     PLAYER_SUCCESS - if game was added successfully.
// */
//PlayerResult playerAddGame (Player player, char* tournament_id);

///**
// * playerAddGame: add a new match to a player tournament.
// *
// * @param player - player that contains the tournament. Must be non-NULL.
// * @param tournament_id - the tournament id. Must be non-negative, and unique.
// * @param first_player - first player id. Must be non-negative.
// * @param second_player - second player id. Must be non-negative.
// * @param winner - indicates the winner in the match. if it is FIRST_PLAYER, then the first player won.
// *                 if it is SECOND_PLAYER, then the second player won, otherwise the match has ended with a draw.
// * @param play_time - duration of the match in seconds. Must be non-negative.
// *
// * @return
// *     PLAYER_NULL_ARGUMENT - if player is NULL.
// *     PLAYER_INVALID_ID - if the tournament ID number, either the players or the winner is invalid.
// *     PLAYER_TOURNAMENT_NOT_EXIST - if the tournament does not exist in the system.
// *     PLAYER_GAME_ALREADY_EXIST - if there is already a game in the tournament with the same two players.
// *     PLAYER_INVALID_PLAY_TIME - if the play time is negative.
// *     PLAYER_SUCCESS - if game was added successfully.
// */
//PlayerResult playerAddGame(Player player, int tournament_id, int first_player,
//                         int second_player, Winner winner, int play_time);
//
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
//PlayerResult playerRemoveTournament (Player player, int tournament_id);
//
///**
// * playerRemovePlayer: removes the player from the player.
// *                      In games where the player has participated and not yet ended,
// *                      the opponent is the winner automatically after removal.
// *
// * @param player - player that contains the player. Must be non-NULL.
// * @param player_id - the player id. Must be non-negative.
// *
// * @return
// *     PLAYER_NULL_ARGUMENT - if player is NULL.
// *     PLAYER_INVALID_ID - if the player ID number is invalid.
// *     PLAYER_PLAYER_NOT_EXIST - if the player does not exist in the system.
// *     PLAYER_SUCCESS - if player was removed successfully.
// */
//PlayerResult playerRemovePlayer(Player player, int player_id);
//
///**
// * playerEndTournament: The function will end the tournament and calculate the id of the winner.
// *                     The winner of the tournament is the player with the highest score.
// *                     Once the tournament is over, no games can be added for that tournament.
// *
// * @param player - player that contains the tournament. Must be non-NULL.
// * @param tournament_id - the tournament id. Must be non-negative, and unique.
// *
// * @return
// *     PLAYER_NULL_ARGUMENT - if player is NULL.
// *     PLAYER_INVALID_ID - if the tournament ID number is invalid.
// *     PLAYER_TOURNAMENT_NOT_EXIST - if the tournament does not exist in the system.
// *     PLAYER_SUCCESS - if tournament was ended successfully.
// */
//PlayerResult playerEndTournament (Player player, int tournament_id);
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
//
///**
// * playerSavePlayersLevels: prints the rating of all players in the system as
// * explained in the *.pdf
// *
// * @param player - a player. Must be non-NULL.
// * @param file - an open, writable output stream, to which the ratings are printed.
// * @return
// *     PLAYER_NULL_ARGUMENT - if player is NULL.
// *     PLAYER_SAVE_FAILURE - if an error occurred while saving.
// *     PLAYER_SUCCESS - if the ratings was printed successfully.
// */
//PlayerResult playerSavePlayersLevels (Player player, FILE* file);
//
///**
// * playerSaveTournamentStatistics: prints to the file the statistics for each tournament that ended as
// * explained in the *.pdf
// *
// * @param player - a player. Must be non-NULL.
// * @param path_file - the file path which within it the tournament statistics will be saved.
// * @return
// *     PLAYER_NULL_ARGUMENT - if player is NULL.
// *     PLAYER_NO_TOURMENTS_ENDED - if there are no tournaments ended in the system.
// *     PLAYER_SAVE_FAILURE - if an error occurred while saving.
// *     PLAYER_SUCCESS - if the ratings was printed successfully.
// */
//PlayerResult playerSaveTournamentStatistics (Player player, char* path_file);
//


#endif //EX1_CHESSPLAYER_H
