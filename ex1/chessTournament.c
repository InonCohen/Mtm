#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "chessTournament.h"
#include "chessGameMap.h"
#include "chessPlayer.h"

# define NO_PLAYER_ID 0

struct chess_tournament_t{
    int tournament_id;
    int max_games_per_player;
    int tournament_winner_player_id;
    char* tournament_location;
    Map tournament_players;
    Map tournament_games;
};
/**
 *
 * @param to_copy
 * @return
 */
void* playersMapCopyData (void* to_copy) {
    if(to_copy == NULL){
        return NULL;
    }
    ChessPlayer copy = playerCopy((ChessPlayer)to_copy);
    if(!copy){
        return NULL;
    }
    return (void*)copy;
}
/**
 *
 * @param to_free
 */
void playersMapFreeData(void* to_free){
    if(to_free == NULL){
        return;
    }
    playerDestroy((ChessPlayer)to_free);
}

ChessTournament tournamentCreate(int tournament_id, int max_games_per_player, char* tournament_location){
    if(tournament_id <= 0 || max_games_per_player <= 0) {
        return NULL;
    }
    ChessTournament result = malloc(sizeof (*result));
    if(!result){
        return NULL;
    }

    Map tournament_games = mapCreate(gamesMapCopyData, mapCopyStringKey, gamesMapFreeData,
                                     mapFreeStringKey, mapCompareStringKeys);
    if(!tournament_games){
        free(result);
        return NULL;
    }

    Map tournament_players = mapCreate(playersMapCopyData, mapCopyStringKey, playersMapFreeData,
                                       mapFreeStringKey, mapCompareStringKeys);
    if(!tournament_players){
        free(result);
        return NULL;
    }

    result->tournament_games = tournament_games;
    result->tournament_players = tournament_players;
    result->tournament_id = tournament_id;
    result->tournament_winner_player_id = NO_PLAYER_ID;
    strcpy(result->tournament_location, tournament_location);
    result->max_games_per_player = max_games_per_player;
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
    Map games = mapCopy(to_copy->tournament_games);
    Map players = mapCopy(to_copy->tournament_players);
    if(!players || !games){
        return NULL;
    }
    new_tournament->tournament_games = to_copy->tournament_games;
    new_tournament->tournament_players = to_copy->tournament_players;
    new_tournament->tournament_id = to_copy->tournament_id;
    strcpy(new_tournament->tournament_location, to_copy->tournament_location);
    new_tournament->max_games_per_player = to_copy->max_games_per_player;
    return new_tournament;
}

void tournamentDestroy(ChessTournament tournament){
    if(!tournament){
        return;
    }
    mapDestroy(tournament->tournament_games);
    mapDestroy(tournament->tournament_players);
    free(tournament->tournament_location);
    free(tournament);
}

int tournamentGetID(ChessTournament tournament){
    return tournament->tournament_id;
}

Map tournamentGetGames(ChessTournament tournament){
    return tournament->tournament_games;
}

char* tournamentGetTournamentLocation(ChessTournament tournament){
    return tournament->tournament_location;
}

int tournamentGetMaxGamesPerPlayer(ChessTournament tournament){
    return tournament->max_games_per_player;
}

bool tournamentIsOver(ChessTournament tournament){
    if(tournament->tournament_winner_player_id == NO_PLAYER_ID){
        return false;
    }
    return true;
}

int tournamentGetSumPointsOfPlayer(ChessTournament tournament, char* player_id){
    return 0;
}

int tournamentCountLosingGames(ChessTournament tournament, char* player_id){
    return 0;
}
