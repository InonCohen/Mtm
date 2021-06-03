#ifndef EX1_CHESSTOURNAMENT_H
#define EX1_CHESSTOURNAMENT_H
#include <stdbool.h>
#include "map.h"
#include "chessSystem.h"
#include "chessGame.h"
#include "chessPlayerID.h"

/** Type for representing a chess tournament in system */
typedef struct chess_tournament_t *ChessTournament;

/**
* tournamentCreate: Allocates a new tournament.
*
* @param tournament_id - the id number that is unique to the new tournament in the system
* @param max_games_per_player - the maximal number of games a player can play in that tournament
* @param tournament_location - a string representing the place where the tournament takes place
*                              Must begin with a capital letter, then followed by lower_case
*                              letters and spaces only
* @return
*     NULL if an invalid argument was sent or if a memory allocation failed
*     a new ChessTournament otherwise
*/
ChessTournament tournamentCreate(int tournament_id, int max_games_per_player, const char* tournament_location);

/**
* tournamentCopy: Creates a copy of target tournament.
*
* @param src_tournament - Target tournament.
* @return
* 	NULL if a NULL was sent or a memory allocation failed.
* 	A ChessTournament identical to src_tournament otherwise.
*/
ChessTournament tournamentCopy(ChessTournament src_tournament);

/**
* tournamentDestroy: Deallocates an existing tournament and its components.
*
* @param tournament - Target tournament to be deallocated. If tournament is
*                   NULL nothing will be done
*/
void tournamentDestroy(ChessTournament tournament);

/**
* tournamentGetID: Returns the id of the tournament
* @param tournament - The tournament of which id is required
* @return
* 	NULL if a NULL pointer was sent.
* 	Otherwise the tournament ID.
*/
int tournamentGetID(ChessTournament tournament);

/**
 * tournamentGetGames: Get the Map of games of the tournament.
 * @param tournament - The tournament to get Map of games from.
 * @return
 *      A Map of the tournament games.
 *      Notice: returns a reference to the original Map, not a copy.
 */
Map tournamentGetGames(ChessTournament tournament);

/**
 * tournamentGetPlayers: Get the Map of players of the tournament.
 * @param tournament
 * @return
 *      A Map of the tournament players.
 *      Notice: returns a reference to the original Map, not a copy.
 */
Map tournamentGetPlayers(ChessTournament tournament);

//TODO: Document, get source, is it used?
Map tournamentGetGamesCounterOfPlayers(ChessTournament tournament);

/**
* tournamentGetTournamentLocation: Returns the location of the tournament
* @param tournament - The tournament of which location is required
* @return
* 	NULL if a NULL pointer was sent.
* 	Otherwise the tournament location string.
*      Notice: returns a reference to the original string, not a copy.
*/
char* tournamentGetTournamentLocation(ChessTournament tournament);

/**
* tournamentIsOver: Returns whether the tournament is over, aka there is a winner
* @param tournament - The tournament of which finished status is required.
* @return
* 	true if a NULL pointer was sent or the tournament is over.
* 	false otherwise
 * 	*/
bool tournamentIsOver(ChessTournament tournament);

/**
 * tournamentLocationIsValid: Check if a tournament name is valid, by the following rules:
 *  - Starts with a capital letter.
 *  - Following letters can be only lowercase or space.
 * @param tournament_name: Tournament name to check
 * @return true if name is valid and non-NULL, false otherwise.
 */
bool tournamentLocationIsValid(const char* tournament_name);

/**
 * tournamentAddGame: add a new match to a chess tournament.
 *
 * @param tournament - chess tournament to which game is to be added. Must be non-NULL.
 * @param game - the game to be added.

 * @return
 *     CHESS_NULL_ARGUMENT - if tournament or game are NULL.
 *     CHESS_OUT_OF_MEMORY - if an allocation failed
 *     CHESS_TOURNAMENT_ENDED - if the tournament already ended
 *     CHESS_GAME_ALREADY_EXISTS - if there is already a game in the tournament with the same two players
 *                                  (both were not removed).
 *     CHESS_EXCEEDED_GAMES - if one of the players played the maximum number of games allowed
 *     CHESS_SUCCESS - if game was added successfully.
 */
ChessResult tournamentAddGame(ChessTournament tournament, ChessGame game);

/**
 * tournamentRemovePlayer: removes the player from the target tournament.
 *
 * @param tournament - tournament that contains the player. Must be non-NULL.
 * @param player_id - the player id. Must be non-NULL.
 *
 * @return
 *     CHESS_NULL_ARGUMENT - if tournament or player_id are NULL.
 *     CHESS_PLAYER_NOT_EXIST - if the player does not exist in the tournament.
 *     CHESS_SUCCESS - if player was removed successfully.
 */
ChessResult tournamentRemovePlayer(ChessTournament tournament, PlayerID player_id);

/**
 * tournamentGetWinnerPlayerID: returns the ID of the winner of target tournament
 * @param tournament - target tournament
 * @return
 *      NULL if tournament is NULL or if it is still ongoing (no winner yet)
 *      The tournament's winner ID, otherwise
 */
PlayerID tournamentGetWinnerPlayerID(ChessTournament tournament);

/**
 * tournamentGetLongestGameTime: returns the time duration in seconds of the longest
 *                              game in target tournament
 * @param tournament - target tournament
 * @return
 *      (-999) if tournament is NULL or no games were played yet
 *      the longest time of an existing game in the tournament, otherwise
 */
int tournamentGetLongestGameTime(ChessTournament tournament);

/**
 * tournamentGetAverageGameTime: returns the average time duration in seconds of games in target
 *                              tournament
 * @param tournament - target tournament
 * @return
 *      (-999) if tournament is NULL
 *      the average time of a game in the tournament, otherwise
 *      Notice: if no games took place, the average time for game is 0
 */
double tournamentGetAverageGameTime(ChessTournament tournament);

/**
* tournamentGetNumOfGames: Returns the number of games that were played in the tournament
* @param tournament - The target tournament of which the number of games is required
* @return
* 	(-999) if a NULL pointer was sent.
* 	Otherwise the number of target tournament's games.
*/
int tournamentGetNumOfGames(ChessTournament tournament);

/**
* tournamentGetNumOfAllPlayers: Returns the number of players who ever participated in the tournament
* @param tournament - The target tournament of which the number of participants is required
* @return
* 	(-999) if a NULL pointer was sent.
* 	Otherwise the number of target tournament's all time players.
*/
int tournamentGetNumOfAllPlayers(ChessTournament tournament);

/**
 * tournamentFindWinner: The function will find the winner of the target tournament.
 *                     The winner of the tournament is the player with the highest score:
 *                     player_score = ( num_of_wins * 2 + num_of_draws * 1 ) / ( num_of_games_of_player )
 *                     If two players have the same score, the player with least losses will be chosen.
 *                     If two players have the same number of losses, the player with the most wins will be chosen
 *                     If two players have the same number of wins and losses,
 *                     the player with smaller id will be chosen.
 *                     Once the tournament is over, no games can be added for that tournament.
 *
 * @param tournament - target tournament of which winner is to be found. Must be non-NULL.
 *
 * @return
 *     CHESS_NULL_ARGUMENT - if tournament is NULL.
 *     CHESS_OUT_OF_MEMORY - if an allocation fails.
 *     CHESS_SUCCESS - if tournament winner is found.
 */
ChessResult tournamentFindWinner(ChessTournament tournament);

/**
 * tournamentEndTournament: The function ends the tournament if it has at least one game and
 *                     finds the id of the winner.
 *                     Once the tournament is over, no games can be added for that tournament.
 *
 * @param tournament - target tournament to be ended. Must be non-NULL.
 *
 * @return
 *     CHESS_NULL_ARGUMENT - if tournament is NULL.
 *     CHESS_OUT_OF_MEMORY - if an allocation fails.
 *     CHESS_N0_GAMES - if the tournament does not have any games.
 *     CHESS_SUCCESS - if tournament is ended successfully.
 */
ChessResult tournamentEndTournament(ChessTournament tournament);

/**
 * findMaxWinsPlayerID: Finds the *single* player_id with the less Loses. If There is no such player return 0.
 * @param tournament
 * @return
 * TODO: is it ever used?
 */
int findMinLosesPlayerID(ChessTournament tournament);

/**
 * findMaxWinsPlayerID: Finds the *single* player_id with the most wins.
 * If There is no such player return 0.
 * @param tournament
 * @return
 * TODO: is it ever used?
 */
int findMaxWinsPlayerID(ChessTournament tournament);

#endif //EX1_CHESSTOURNAMENT_H
