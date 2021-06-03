#ifndef EX1_CHESSTOURNAMENT_H
#define EX1_CHESSTOURNAMENT_H
#include <stdbool.h>
#include "../map/map.h"
#include "chessSystem.h"
#include "chessGame.h"
#include "chessPlayerID.h"

/** Type for representing a chess game in a tournament */
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
 *
 * @param tournament Tournament to get a winner_player_id
 * @return
 *  PlayerID of the winner if exist, NULL otherwise
 */
PlayerID tournamentGetWinnerPlayerID(ChessTournament tournament);

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
 * @param tournament: tournament to add game into
 * @param game: game to be added
 * @return TOURNAMENT_SUCCESS if game was added successfully, matching TournamentResult otherwise.
 */
ChessResult tournamentAddGame(ChessTournament tournament, ChessGame game);

/**
 * TODO: USE IT
 * tournamentRemovePlayer: remove a player from
 * @param player_id
 */
ChessResult tournamentRemovePlayer(ChessTournament tournament, PlayerID player_id);

/**
 * @param tournament Tournament to calculate longest game time for.
 * @return
 *  longest game time <int>, or a negative number if an error occurred.
 */
int tournamentGetLongestGameTime(ChessTournament tournament);

/**
 * @param tournament Tournament to calculate average game time for.
 * @return
 *  average game time <double>, or a negative number if an error occurred.
 */
double tournamentGetAverageGameTime(ChessTournament tournament);

/**
 * @param tournament Tournament to calculate number of games for.
 * @return
 *  number of games <int>, or a negative number if an error occurred.
 */
int tournamentGetNumOfGames(ChessTournament tournament);

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
