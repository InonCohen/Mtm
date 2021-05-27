#ifndef EX1_CHESSTOURNAMENT_H
#define EX1_CHESSTOURNAMENT_H
#include <stdbool.h>
#include "map.h"

/** Type for representing a chess game in a tournament */
typedef struct chess_tournament_t *ChessTournament;

ChessTournament tournamentCreate(int tournament_id, int max_games_per_player, char* tournament_location);

ChessTournament tournamentCopy(ChessTournament tournament);

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

int tournamentGetMaxGamesPerPlayer(ChessTournament tournament);

bool tournamentIsOver(ChessTournament tournament);

int tournamentGetSumPointsOfPlayer(ChessTournament tournament, char *player_id);

int tournamentCountLosingGames(ChessTournament tournament, char *player_id);

#endif //EX1_CHESSTOURNAMENT_H
