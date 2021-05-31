#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../map/map.h"
#include "chessSystem.h"
#include "chessTournament.h"
#include "chessMapUtils.h"
#include "chessGame.h"
#include "strUtils.h"
#include "chessPlayer.h"
#include "chessPlayerID.h"


#define NO_PLAYER_ID 0

struct chess_tournament_t{
    int tournament_id;
    int max_games_per_player;
    int tournament_winner_player_id;
    char* tournament_location;
    Map tournament_games;
    Map games_counter_of_players;
};
/**
 * tournamentLocationIsValid: Check if a tournament name is valid, by the following rules:
 *  - Starts with a capital letter.
 *  - Following letters can be only lowercase or space.
 * @param tournament_name: Tournament name to check
 * @return true if name isvalid, false otherwise.
<<<<<<< HEAD
 */
static bool tournamentLocationIsValid(const char* tournament_name);

/**
 *
 * @param to_copy
 * @return
 */
ChessTournament tournamentCreate(int tournament_id, int max_games_per_player, const char* tournament_location){
    if(tournament_id <= 0 || max_games_per_player <= 0) {
        return NULL;
    }
    if(!tournamentLocationIsValid(tournament_location)){
        return NULL;
    }
    ChessTournament result = malloc(sizeof (*result));
    if(!result){
        return NULL;
    }
    Map tournament_games = mapCreate(gamesMapCopyData, stringCopyFunc, gamesMapFreeData,
                                     mapFreeStringKey, mapCompareStringKeys);
    if(!tournament_games){
        tournamentDestroy(result);
        return NULL;
    }
    Map games_counter_of_players = mapCreate(intCopyFunc, intCopyFunc, intFreeFunc, intFreeFunc, intCompFunc);
    if(!games_counter_of_players){
        tournamentDestroy(result);
        mapDestroy(tournament_games);
        return NULL;
    }

    result->tournament_id = tournament_id;
    result->tournament_winner_player_id = NO_PLAYER_ID;
    result->max_games_per_player = max_games_per_player;
    result->tournament_games = tournament_games;
    result->games_counter_of_players = games_counter_of_players;
    result->tournament_location = malloc(strlen(tournament_location)+1);
    strcpy(result->tournament_location, tournament_location);

    return result;
}

ChessTournament tournamentCopy(ChessTournament to_copy){
    if(!to_copy){
        return NULL;
    }
    ChessTournament new_tournament = malloc(sizeof (*new_tournament));
    if (!new_tournament) {
        return NULL;
    }

    new_tournament->tournament_location = malloc(strlen(to_copy->tournament_location) + 1);
    if(!new_tournament->tournament_location){
        tournamentDestroy(new_tournament);
        return NULL;
    }

    Map tournament_games = mapCopy(to_copy->tournament_games);
    if(!tournament_games){
        tournamentDestroy(new_tournament);
        return NULL;
    }
    Map games_counter_of_players = mapCopy(to_copy->games_counter_of_players);
    if(!games_counter_of_players){
        mapDestroy(tournament_games);
        tournamentDestroy(new_tournament);
        return NULL;
    }

    new_tournament->tournament_id = to_copy->tournament_id;
    new_tournament->max_games_per_player = to_copy->max_games_per_player;
    new_tournament->tournament_winner_player_id = to_copy->tournament_winner_player_id;
    strcpy(new_tournament->tournament_location, to_copy->tournament_location);
    new_tournament->tournament_games = tournament_games;
    new_tournament->games_counter_of_players = games_counter_of_players;

    return new_tournament;
}

void tournamentDestroy(ChessTournament tournament){
    if(!tournament){
        return;
    }
    mapDestroy(tournament->tournament_games);
    mapDestroy(tournament->games_counter_of_players);
    free(tournament->tournament_location);
    free(tournament);
}

int tournamentGetID(ChessTournament tournament){
    return tournament->tournament_id;
}

int tournamentGetMaxGamesPerPlayer(ChessTournament tournament){
    return tournament->max_games_per_player;
}

Map tournamentGetGames(ChessTournament tournament){
    return tournament->tournament_games;
}

Map tournamentGetGamesCounterOfPlayers(ChessTournament tournament){
    return tournament->tournament_games;
}

char* tournamentGetTournamentLocation(ChessTournament tournament){
    return tournament->tournament_location;
}

bool tournamentIsOver(ChessTournament tournament){
    return tournament->tournament_winner_player_id != NO_PLAYER_ID;
}

int tournamentGetSumPointsOfPlayer(ChessTournament tournament, PlayerID player_id){
    return 0;
}

int tournamentCountLosingGames(ChessTournament tournament, char* player_id){
    return 0;
}

/**
 * tournamentAddGame: Add a game into tournament.
 * Assumes that Game and Tournament validity check is made by Chess System ADT.
 *  Do:
 *  1. Add game into tournament_games
 *  2. Update games_counter_of_players
 *  3. Check if a player exceeded max_games_per_player, raise an error accordingly.
 * @param tournament: tournament to add game into
 * @param game: game to be added
 * @return TOURNAMENT_SUCCESS if game was added successfully, matching TournamentResult otherwise.
 */
TournamentResult tournamentAddGame(ChessTournament tournament, ChessGame game){
    if(!tournament || !game){
        return TOURNAMENT_INVALID_ID;
    }
    char* game_id = gameGetID(game);
    if (mapGet(tournament->tournament_games, game_id)){
        return TOURNAMENT_GAME_ALREADY_EXISTS;
    }

    mapPut(tournament->tournament_games, game_id, game);
    int player1_id = playerIDGetIntID(gameGetPlayer1ID(game));
    int player2_id = playerIDGetIntID(gameGetPlayer2ID(game));
    int* player1_game_counter = mapGet(tournament->games_counter_of_players, &player1_id);
    int* player2_game_counter = mapGet(tournament->games_counter_of_players, &player2_id);

    if (!player1_game_counter){
        int new_player_counter = 0;
        mapPut(tournament->games_counter_of_players, &player1_id, &new_player_counter);
        player1_game_counter = mapGet(tournament->games_counter_of_players, &player1_id);
    }
    if (!player2_game_counter){
        int new_player_counter = 0;
        mapPut(tournament->games_counter_of_players, &player2_id, &new_player_counter);
        player2_game_counter = mapGet(tournament->games_counter_of_players, &player2_id);
    }
    (*player1_game_counter)++;
    (*player2_game_counter)++;
    if (*player1_game_counter > tournament->max_games_per_player ||
        *player2_game_counter > tournament->max_games_per_player){
        return TOURNAMENT_EXCEEDED_GAMES;
    }
    return TOURNAMENT_SUCCESS;
}

static bool tournamentLocationIsValid(const char* tournament_name){
    if (!isupper(tournament_name[0])){
        return false;
    }
    for (int i = 1; i < strlen(tournament_name) ;i++){
        if (!(isspace(tournament_name[i]) || islower(tournament_name[i]))){
            return false;
        }
    }
    return true;
}

void tournamentRemovePlayer(ChessTournament tournament, PlayerID player_id){
    if(!tournament || !player_id){
        return;
    }
    return;
}
