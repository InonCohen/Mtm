#include <stdlib.h>
#include <string.h>
#include "../map/map.h"
#include "strUtils.h"
#include "chessSystem.h"
#include "chessTournament.h"
#include "chessGameMap.h"
#include "chessGame.h"
#include "chessPlayer.h"

#define NO_PLAYER_ID 0

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

// TODO: Implement gameIdentifier and then implement: gameSamePlayers, getGameIdentifier, tournamentAddGame
/**
 *
 * @param game
 * @param player1ID
 * @param player2
 * @return
 */
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

//int getGameIdentifier(ChessTournament tournament, int player1, int player2){
//    if(!tournament){
//        return BAD_INPUT;
//    }
//    int count =0;
//    MAP_FOREACH(char*, iter, tournament->tournament_games){
//        if(gameSamePlayers(mapGet(tournament->games, player1, player2))){
//            count++;
//        }
//        free(iter);
//    }
//    return count;
//}

ChessTournament chessTournamentCreate();

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

int countLosingGames(int playerID);

//TournamentResult tournamentAddGame(ChessTournament tournament, int first_player,
//                                   int second_player,int play_time, Winner winner){
//    if(!tournament){
//        return TOURNAMENT_NULL_ARGUMENT;
//    }
//    if(tournament->tournament_id <= 0 || first_player<=0 || second_player<=0 || first_player == second_player){
//        return TOURNAMENT_INVALID_ID;
//    }
//    int identifier = getGameIdentifier(tournament, first_player, second_player);
//    char* game_id = createGameID(first_player, second_player, tournament->tournament_id, identifier);
//    if(!game_id){
//        return TOURNAMENT_OUT_OF_MEMORY;
//    }
//    if(mapContains(tournament->games, game_id){
//       ChessGame game = mapGet(tournament->games, game_id);
//       if (!(gamePlayerIsDeleted(game))){
//           return TOURNAMENT_GAME_ALREADY_EXIST;
//       }
//    }
//    if(play_time<0){
//        return TOURNAMENT_INVALID_PLAY_TIME;
//    }
//    if(mapContains(tournament->players, player1) || mapContains(tournament->players, player2) ){
//        Player player1_ptr = mapGet(tournament->players, player1);
//        Player player2_ptr = mapGet(tournament->players, player2);
//        if(player1_ptr && tournament->max_games_per_player = mapGetSize(playerGetGames(player1_ptr))){
//            return TOURNAMENT_EXCEEDED_GAMES;
//        }
//        if(player2_ptr && tournament->max_games_per_player = mapGetSize(playerGetGames(player2_ptr))){
//            return TOURNAMENT_EXCEEDED_GAMES;
//        }
//    }
//    ChessGame to_add = gameCreate(game_id, tournament->tournament_id, player1, player2, play_time, winner);
//    if(!to_add){
//        free(game_id);
//        return TOURNAMENT_OUT_OF_MEMORY;
//    }
//    free(game_id);
//    MapResult res = mapPut(tournament->games, to_add);
//    gameDestroy(to_add);
//    if(res != MAP_SUCCESS){
//        return TOURNAMENT_OUT_OF_MEMORY;
//    }
//    return TOURNAMENT_SUCCESS;
//}
int tournamentCountLosingGames(ChessTournament tournament, char* player_id){
    return 0;
}

