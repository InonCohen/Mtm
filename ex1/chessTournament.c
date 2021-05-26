#include <stdlib.h>
#include <stdio.h>
#include "chessTournament.h"
#include "map.h"

struct chess_tournament_t{
    int tournament_id;
    char* tournament_location;
    int max_games_per_player;
    int tournament_winner_player_id;
    Map games;
};

ChessTournament tournamentCreate(int tournament_id, int max_games_per_player, char* tournament_location){
    if(tournament_id <= 0 || max_games_per_player <= 0) {
        return NULL;
    }

    ChessTournament result = malloc(sizeof (*result));
    if(!result){
        return NULL;
    }
    result->tournament_id = tournament_id;
    result->tournament_location = tournament_location;
    result->max_games_per_player = max_games_per_player;
    Map games = mapCreate();

    return result;
}

ChessTournament tournamentCopy(ChessTournament tournament){
    return NULL;
}

void tournamentDestroy(ChessTournament tournament){}

int tournamentGetID(ChessTournament tournament){
    return 0;
}

Map tournamentGetGames(ChessTournament tournament){
    return NULL;
}

char* tournamentGetTournamentLocation(ChessTournament tournament){
    return NULL;
}

int tournamentGetMaxGamesPerPlayer(ChessTournament tournament){
    return 0;
}

bool tournamentIsOver(ChessTournament tournament){
    return NULL;
}

int tournamentGetSumPointsOfPlayer(int player_id){
    return 0;
}

int tournamentCountLosingGames(int player_id){
    return 0;
}
