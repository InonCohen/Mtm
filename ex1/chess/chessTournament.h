#ifndef EX1_CHESSTOURNAMENT_H
#define EX1_CHESSTOURNAMENT_H
#include <stdbool.h>
#include "../map/map.h"
#include "chessSystem.h"
#include "chessGame.h"
#include "chessPlayerID.h"

/** Type for representing a chess game in a tournament */
typedef struct chess_tournament_t *ChessTournament;

ChessTournament tournamentCreate(int tournament_id, int max_games_per_player, const char* tournament_location);

ChessTournament tournamentCopy(ChessTournament src_tournament);

void tournamentDestroy(ChessTournament tournament);

int tournamentGetID(ChessTournament tournament);
/**
 * tournamentGetGames: Get the Map of games of the tournament.
 * @param tournament - The tournament to get Map of games from.
 * @return
 *      A Map of the tournament games.
 *      Notice: returns a reference to the original Map, not a copy.
 */
Map tournamentGetGames(ChessTournament tournament);

char* tournamentGetTournamentLocation(ChessTournament tournament);

Map tournamentGetGamesCounterOfPlayers(ChessTournament tournament);

bool tournamentIsOver(ChessTournament tournament);

ChessResult tournamentAddGame(ChessTournament tournament, ChessGame game);
/**TODO: Implement a function called from chessRemovePlayer
 * tournamentRemovePlayer: remove a player from
 * @param player_id
 */
void tournamentRemovePlayer(ChessTournament tournament, PlayerID player_id);

int tournamentGetWinnerID(ChessTournament tournament);

int tournamentGetLongestGameTime(ChessTournament tournament);

double tournamentGetAverageGameTime(ChessTournament tournament);

int tournamentGetNumOfGames(ChessTournament tournament);

int tournamentGetNumOfAllPlayers(ChessTournament tournament);

ChessResult tournamentEndTournament(ChessTournament tournament);
/**
 * findMaxWinsPlayerID: Finds the *single* player_id with the less Loses. If There is no such player return 0.
 * @param tournament
 * @return
 */
int findMinLosesPlayerID(ChessTournament tournament);
/**
 * findMaxWinsPlayerID: Finds the *single* player_id with the most wins. If There is no such player return 0.
 * @param tournament
 * @return
 */
int findMaxWinsPlayerID(ChessTournament tournament);

int tournamentGetNumOfAllPlayers(ChessTournament current_tournament);

#endif //EX1_CHESSTOURNAMENT_H
