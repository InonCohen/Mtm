#ifndef EX1_CHESSTOURNAMENT_H
#define EX1_CHESSTOURNAMENT_H
#include <stdbool.h>
#include "../map/map.h"
#include "chessSystem.h"
#include "chessGame.h"
#include "chessPlayerID.h"

/** Type for representing a chess game in a tournament */
typedef struct chess_tournament_t *ChessTournament;

typedef enum {
    TOURNAMENT_OUT_OF_MEMORY,
    TOURNAMENT_NULL_ARGUMENT,
    TOURNAMENT_INVALID_ID,
    TOURNAMENT_INVALID_LOCATION,
    TOURNAMENT_INVALID_MAX_GAMES,
    TOURNAMENT_TOURNAMENT_ALREADY_EXISTS,
    TOURNAMENT_TOURNAMENT_NOT_EXIST,
    TOURNAMENT_GAME_ALREADY_EXISTS,
    TOURNAMENT_INVALID_PLAY_TIME,
    TOURNAMENT_EXCEEDED_GAMES,
    TOURNAMENT_PLAYER_NOT_EXIST,
    TOURNAMENT_TOURNAMENT_ENDED,
    TOURNAMENT_NO_TOURNAMENTS_ENDED,
    TOURNAMENT_NO_GAMES,
    TOURNAMENT_SAVE_FAILURE,
    TOURNAMENT_SUCCESS
} TournamentResult ;

ChessTournament tournamentCreate(int tournament_id, int max_games_per_player, const char* tournament_location);

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

int tournamentGetSumPointsOfPlayer(ChessTournament tournament, PlayerID player_id);

TournamentResult tournamentAddGame(ChessTournament tournament, ChessGame game);
/**
 * tournamentRemovePlayer: remove a player from
 * @param player_id
 */
void tournamentRemovePlayer(int player_id);

#endif //EX1_CHESSTOURNAMENT_H
