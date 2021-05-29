#include <stdlib.h>
#include <string.h>
#include "../map/map.h"
#include "chessTournament.h"
#include "chessMapUtils.h"
#include "chessGame.h"
#include "chessDefs.h"
#include "chessPlayer.h"

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
 *
 * @param to_copy
 * @return
 */
ChessTournament tournamentCreate(int tournament_id, int max_games_per_player, const char* tournament_location){
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
    // TODO: Include chessMapUtils and send it as an argument in
    Map count_games_for_player = mapCreate()
    if(!count_games_for_player){
        free(result);
        return NULL;
    }

    result->tournament_games = tournament_games;
    result->games_counter_of_players = count_games_for_player;
    result->tournament_id = tournament_id;
    result->tournament_winner_player_id = NO_PLAYER_ID;
    result->tournament_location = malloc(strlen(tournament_location)+1);
    result->max_games_per_player = max_games_per_player;
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
    Map games = mapCopy(to_copy->tournament_games);
    if(!games){
        return NULL;
    }
    Map games_counter_of_players = mapCopy(to_copy->tournament_games);
    if(!games_counter_of_players){
        return NULL;
    }
    new_tournament->tournament_id = to_copy->tournament_id;
    new_tournament->max_games_per_player = to_copy->max_games_per_player;
    strcpy(new_tournament->tournament_location, to_copy->tournament_location);

    return new_tournament;
}

void tournamentDestroy(ChessTournament tournament){
    if(!tournament){
        return;
    }
    mapDestroy(tournament->tournament_games);
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
    return tournament->tournament_winner_player_id == NO_PLAYER_ID;
}

int tournamentGetSumPointsOfPlayer(ChessTournament tournament, PlayerID player_id){
    return 0;
}

int tournamentCountLosingGames(ChessTournament tournament, char* player_id){
    return 0;
}
/**
 * tournamentAddGame
 *  1. Add game to GameMap
 *  2. Update player map
 *  3. Update player counter
 * @param tournament
 * @param player1_id
 * @param player2_id
 * @param play_time
 * @param winner
 * @return
 */
TournamentResult tournamentAddGame(ChessTournament tournament, ChessGame game){
    if(!tournament){
        return TOURNAMENT_NULL_ARGUMENT;
    }
    if(!game){

    }
    if(tournament->tournament_id <= 0 || playerIDGetIntID(game->pla) <= 0 || playerIDGetIntID(player2_id)<=0 ||
            playerIDGetFullID(player1_id) == playerIDGetFullID(player2_id)) {
        return TOURNAMENT_INVALID_ID;
    }
    mapPut(tournament->tournament_games,)
    return TOURNAMENT_SUCCESS;
}

// TODO: Implement gameIdentifier and then implement: gameSamePlayers, getGameIdentifier, tournamentAddGame
//
//bool gameSamePlayers(ChessGame game, char* player1ID, char* player2){
//    if(!game){
//        return false;
//    }
//    int id1 = gameGetPlayer1(game);
//    int id2 = gameGetPlayer2(game);
//    if(player1 == id1){
//        if(player2 == id2){
//            return true;
//        }
//    }
//    if(player1 == id2){
//        if(player2 == id1){
//            return true;
//        }
//    }
//    return false;
//}




