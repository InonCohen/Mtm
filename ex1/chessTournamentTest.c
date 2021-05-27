#include <stdbool.h>
#include <stdlib.h>
#include "chessTournament.h"


bool testTournamentCreate(int tournament_id,int tournament_max_games_per_player, char* tournament_location,
                         ChessTournament* tournamentPtr){
    ChessTournament tournament = tournamentCreate(tournament_id, tournament_max_games_per_player, tournament_location);
    if(!tournament){
        return false;
    }
    *tournamentPtr = tournament;
    return true;
}

bool testTournamentCopy(ChessTournament to_copy, ChessTournament* tournamentPtr){
    ChessTournament new_tournament = tournamentCopy(to_copy);
    if(!new_tournament){
        return false;
    }
    *tournamentPtr = new_tournament;
    return true;
}

bool testTournamentDestroy(ChessTournament tournament){
    tournamentDestroy(tournament);
    return true;
}

bool testTournamentGetSumPointsOfPlayer(ChessTournament tournament, char* player_id){
    int sum_points = tournamentGetSumPointsOfPlayer(tournament, player_id);
    if(!sum_points){
        return false;
    }
    return true;
}

bool testTournamentCountLosingGames(ChessTournament tournament, char* player_id){
    int counter = tournamentCountLosingGames(tournament, player_id);
    if(!counter){
        return false;
    }
    return true;
}

int main(){
    int TOURNAMENT_ID = 1;
    int TOURNAMENT_MAX_GAMES_PER_PLAYER = 5;
    char* TOURNAMENT_LOCATION = "Belgium";
    char* PLAYER_ID = "1_1";
    ChessTournament *ptr1 = NULL, *ptr2 = NULL;

    testTournamentCreate(TOURNAMENT_ID, TOURNAMENT_MAX_GAMES_PER_PLAYER, TOURNAMENT_LOCATION, ptr1);
    testTournamentCopy(*ptr1, ptr2);
    testTournamentDestroy(*ptr1);
    testTournamentCreate(TOURNAMENT_ID,TOURNAMENT_MAX_GAMES_PER_PLAYER,TOURNAMENT_LOCATION, ptr2);
    testTournamentGetSumPointsOfPlayer(*ptr2, PLAYER_ID);
    testTournamentCountLosingGames(*ptr2, PLAYER_ID);
    testTournamentDestroy(*ptr2);

    return 0;
}
