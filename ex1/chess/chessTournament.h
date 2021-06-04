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
 * Creates a new tournament, set the params described below as attributes. In addition, set the attribute
 * winner_player_id to NULL and creates games and players empty Maps.
 * Assumptions:
 *  - Tournament properties validity-check is made by Chess System.
 * @param tournament_id
 * @param max_games_per_player
 * @param tournament_location Must begin with a capital letter and trailing lowercase/space characters
 * @return
 *      an initialized ChessTournament object, or NULL in a case of an error occurred.
 */
ChessTournament tournamentCreate(int tournament_id, int max_games_per_player, const char* tournament_location);

/**
 * Creates a shallow copy of a tournament.
 * Assumptions:
 *  - Tournament properties validity-check is made by Chess System.
 * @param src_tournament Tournament to copy.
 * @return
 *      the copied ChessTournament, or NULL in a case an error ocurred.
 */
ChessTournament tournamentCopy(ChessTournament src_tournament);

/**
 * Destroys a tournament
 * @param tournament Tournament to destroy
 */
void tournamentDestroy(ChessTournament tournament);
/**
 * Get map of games of a tournament.
 * @param tournament Tournament to get Map of games from.
 * @return
 *  Map of tournament games.
 *  Notice: returns a pointer to original Map, not a copy.
 */
Map tournamentGetGames(ChessTournament tournament);

/**
 * Get map of players of a tournament.
 * @param tournament Tournament to get Map of players from.
 * @return
 *  Map of tournament_players.
 *  Notice: returns a pointer to original Map, not a copy.
 */
Map tournamentGetPlayers(ChessTournament tournament);

/**
 * Get location of a tournament.
 * @param tournament Tournament to get Map of players from.
 * @return
 *  tournament location pointer.
 */
char* tournamentGetTournamentLocation(ChessTournament tournament);

/**
 * @param tournament Tournament to check if is over, meaning that there is a winner to the tournament.
 * @return
 *  true if tournament is over, false otherwise.
 */

bool tournamentIsOver(ChessTournament tournament);

/**
 * Check if a tournament name is valid by the following rules:
 *  - Starts with a capital letter.
 *  - Following letters can be only lowercase or space.
 * @param tournament_name: Tournament name to check
 * @return
 *  true if name is valid, false otherwise.
 */
bool tournamentLocationIsValid(const char* tournament_name);

/**
 * tournamentAddGame: Add a game into tournament.
 *  Do:
 *  1. Check arguments validity
 *      RAISES: CHESS_NULL_ARGUMENT, CHESS_TOURNAMENT_ENDED, CHESS_GAME_ALREADY_EXISTS
 *  2. Foreach player call addPlayer(tournament, player).
 *  3. Foreach player call tournamentAddGameForPlayer(tournament, player)
 *      RAISES: CHESS_EXCEEDED_GAMES, CHESS_OUT_OF_MEMORY
 *  4. Finally, Add the game into  tournament_games and return CHESS_SUCCESS
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

 * TODO: USE IT
 * tournamentRemovePlayer: remove a player from
 * @param player_id
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
 *
 * @param tournament Tournament to calculate number of players for.
 * @return
 *  number of players <int>, or a negative number if an error occurred.
 */
int tournamentGetNumOfAllPlayers(ChessTournament tournament);

/**
 * End a tournament if it isn't empty (returns CHESS_NO_GAMES otherwise).
 * Tournament Winner Calculate: the winner of a tournament:
 *  - A single player with max points
 *  - Else, a single player with max winning games from players meet the previous requirements.
 *  - Else, a single player with min loses from players meet the previous requirements.
 *  - Else, a single player with min id meet the previous requirements.
 * Finally, set it in an internal property: tournament->tournament_winner_player_id
 * @param tournament
 * @return
 *  CHESS_SUCCESS if tournament ended successfully, proper ChessResult otherwise.
 */
ChessResult tournamentEndTournament(ChessTournament tournament);

#endif //EX1_CHESSTOURNAMENT_H
