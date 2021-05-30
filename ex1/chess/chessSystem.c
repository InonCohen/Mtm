#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../map/map.h"
#include "chessSystem.h"
#include "../map/map.h"
#include "chessPlayer.h"
#include "chessGame.h"
#include "chessTournament.h"
#include "strUtils.h"
#include "chessPlayerID.h"
#include "chessMapUtils.h"


#define LENGTH_OF_ZERO_STRING 2


struct chess_system_t{
    Map tournaments; // Key: int id,  Data: Tournament tour
    Map players; // Key: int id,  Data: Player
    int ended_tournaments;
};

/*
 * Required to function:
 *              - Tournaments ADT copy, destroy funcs
 *              - Players ADT copy, destroy funcs
 */



//static char* createGameID(char* player1_id, char* player2_id, int tournament_id){
//    if(!player1_id || !player2_id || tournament_id <= 0){
//        return NULL;
//    }
//    char* tournament_id_str= castIntToString((int) tournament_id);
//    int len1, len2, len3;
//    len1=(int)strlen(player1_id);
//    len2=(int)strlen(player2_id);
//    len3=(int)strlen(tournament_id_str);
//    int size = len1 + strlen(ID_SEP) + len2  + strlen(ID_SEP) + len3 + strlen(ID_SEP);
//    char* game_id = malloc(size);
//    if(!game_id){
//        return NULL;
//    }
//    nullifyString(game_id, size);
//    game_id = strcat(game_id,tournament_id_str);
//    game_id = strcat(game_id, ID_SEP);
//    game_id = strcat(game_id,strcmp(player1_id,player2_id) < 0 ? player1_id: player2_id);
//    game_id = strcat(game_id, ID_SEP);
//    game_id = strcat(game_id,strcmp(player1_id,player2_id) > 0 ? player1_id: player2_id);
//    return game_id;
//}

static bool chessGameInTournament(ChessTournament tournament, char* game_id){
    if(!tournament || !game_id){
        return false;
    }
    Map games = tournamentGetGames(tournament);
    if(mapContains(games,game_id)){
        if (gamePlayerIsDeleted(mapGet(games,game_id))) {
            return false;
        }
        else{
            return true;
        }
    }
    return false;
}


/**
 * getPlayerIDFromMap: inserts the relevant PlayerID into id. If no player has ever been entered to the system
 *                      with  id_int, id will be made with version 0.
 *
 * @param players    - a map that contains the chess system players. Must be non-NULL.
 * @param id_int     - the player id. Must be positive.
 * @param id         - an empty PlayerId type. Must be NULL.
 * @return
 *     a PlayerID which contains:
 *          the player's ID - if there is such a player in the system with int_id.
 *          a new id that never existed in the system's players map -
 *                      if there was a player with such id_int, but it was deleted.
 *          NULL - if there was a memory problem or the inputs were corrupted.
 */
PlayerID getPlayerIdFromMap (Map players, int id_int) {
    if(!players || id_int <= 0) {
        return NULL;
    }
    int id_version = 0;
    MAP_FOREACH(PlayerID , iter, players) {
        if (playerIDGetIntID(iter) == id_int) {
            id_version++;
        }
        free(iter);
    }
    PlayerID new_id = playerIDCreate(id_int, id_version);
    if(!new_id) {
        return NULL;
    }
    if(mapContains(players, new_id)) {
        PlayerID id = NULL;
        if (playerIsDeleted(mapGet(players, new_id))) {
            playerIDDestroy(new_id);
            id = playerIDCreate(id_int, ++id_version);
            if (!id) {
                return NULL;
            }
        }
    }
    return new_id;
}

//static char* convertPlayerIntIdToCharId(Map players, int id){
//    if(!players || id<=0){
//        return NULL;
//    }
//    char* id_str = NULL;
//    getPlayerIdFromMap(players, id, id_str);
//    if(!id_str) {
//        return NULL;
//    }
//    if(playerIsDeleted(mapGet(players, id_str))) {
//        playerGetVersion()
//    }
//
//
//}



ChessSystem chessCreate(){
    ChessSystem system = malloc(sizeof(*system));
    if(!system){
        return NULL;
    }
    Map tournaments = mapCreate(tournamentsMapCopyData, intCopyFunc, tournamentsMapFreeData, intFreeFunc, intCompFunc);
    if(!tournaments){
        free(system);
        return NULL;
    }
    Map players = mapCreate(playersMapCopyData, playersMapCopyKey, playersMapFreeData, playersMapFreeKey, playersMapComp);
    if(!players){
        mapDestroy(tournaments);
        free(system);
        return NULL;
    }
    system->tournaments = tournaments;
    system->players = players;
    system->ended_tournaments = 0;
    return system;
}//Done. TODO: Debug

void chessDestroy(ChessSystem chess){
    if(!chess){
        return;
    }
    if(chess->tournaments){
        mapDestroy(chess->tournaments);
    }
    if(chess->players){
        mapDestroy(chess->players);
    }
    free(chess);
}//Done. TODO: Debug

ChessResult chessAddTournament (ChessSystem chess, int tournament_id,
                                int max_games_per_player, const char* tournament_location){
    ChessTournament tour = tournamentCreate(tournament_id, max_games_per_player, tournament_location);
    mapPut(chess->tournaments, &tournament_id, tour);
    tournamentDestroy(tour);
    return CHESS_SUCCESS;
}

ChessResult chessAddGame(ChessSystem chess, int tournament_id, int first_player,
                         int second_player, Winner winner, int play_time) {
/*Rundown:
 * check validity of inputs -V-
 * check if players are in players map -V-
         * if yes - check if they are alive
            * if yes - add the game to the player
            * if not - add the a new player to the players map and add the game to him
        * if not - add the a new player to the players map and add the game to him
 * add the game to tournament (and update the players in the tournament's map as well)
 * add the players to the system's players map or update their info in it
 */
    if (!chess) {
        return CHESS_NULL_ARGUMENT;
    }
    if (tournament_id <= 0 || first_player <= 0 || second_player <= 0 || first_player == second_player) {
        return CHESS_INVALID_ID;
    }
    assert(chess->tournaments);
    if (!mapContains(chess->tournaments, &tournament_id)) {
        return CHESS_TOURNAMENT_NOT_EXIST;
    }
    ChessTournament tournament = mapGet(chess->tournaments, &tournament_id);
    if (tournamentIsOver(tournament)) {
        return CHESS_TOURNAMENT_ENDED;
    }
    PlayerID player1_id = getPlayerIdFromMap(chess->players, first_player);
    if(!player1_id) {
        return CHESS_OUT_OF_MEMORY;
    }
    PlayerID player2_id = getPlayerIdFromMap(chess->players, second_player);
    if (!player2_id) {
        playerIDDestroy(player1_id);
        return CHESS_OUT_OF_MEMORY;
    }
    ChessGame game = gameCreate(tournament_id, player1_id, player2_id, play_time, winner);
    if (!game) {
        playerIDDestroy(player1_id);
        playerIDDestroy(player2_id);
        return CHESS_OUT_OF_MEMORY;
    }
    if(chessGameInTournament(tournament, gameGetID(game))) {
        gameDestroy(game);
        playerIDDestroy(player1_id);
        playerIDDestroy(player2_id);
        return CHESS_GAME_ALREADY_EXISTS;
    }
    bool player1_is_new = false, player2_is_new = false;
    ChessPlayer player1 = mapGet(chess->players, player1_id);
    if (!player1) {
        player1_is_new = true;
        player1 = playerCreate(player1_id);
        if (!player1) {
            gameDestroy(game);
            playerIDDestroy(player1_id);
            playerIDDestroy(player2_id);
            return CHESS_OUT_OF_MEMORY;
        }
    }
    ChessPlayer player2 = mapGet(chess->players, player2_id);
    if (!player2) {
        player2 = playerCreate(player2_id);
        player2_is_new = true;
        if (!player2) {
            gameDestroy(game);
            playerIDDestroy(player1_id);
            playerIDDestroy(player2_id);
            return CHESS_OUT_OF_MEMORY;
        }
    }
    PlayerResult player_res = playerAddGame(player1, game);
    if (player_res != PLAYER_SUCCESS) {
        if (player1_is_new) {
            playerDestroy(player1);
        }
        if (player2_is_new) {
            playerDestroy(player2);
        }
        gameDestroy(game);
        playerIDDestroy(player1_id);
        playerIDDestroy(player2_id);
        return (ChessResult)player_res;
    }
    player_res = playerAddGame(player2, game);
    if (player_res != PLAYER_SUCCESS) {
        if (player1_is_new) {
            playerDestroy(player1);
        }
        if (player2_is_new) {
            playerDestroy(player2);
        }
        gameDestroy(game);
        playerIDDestroy(player1_id);
        playerIDDestroy(player2_id);
        return (ChessResult)player_res;
    }
    MapResult map_res;
    if (player1_is_new) {
        map_res = mapPut(chess->players, player1_id, player1);
        if (map_res != MAP_SUCCESS) {
            if (player1_is_new) {
                playerDestroy(player1);
            }
            if (player2_is_new) {
                playerDestroy(player2);
            }
            gameDestroy(game);
            playerIDDestroy(player1_id);
            playerIDDestroy(player2_id);
            return CHESS_OUT_OF_MEMORY;
        }
    }
    if (player2_is_new) {
        map_res = mapPut(chess->players, player2_id, player2);
        if (map_res != MAP_SUCCESS) {
            mapRemove(chess->players, player1);
            if (player1_is_new) {
                playerDestroy(player1);
            }
            if (player2_is_new) {
                playerDestroy(player2);
            }
            gameDestroy(game);
            playerIDDestroy(player1_id);
            playerIDDestroy(player2_id);
            return CHESS_OUT_OF_MEMORY;
        }
    }
    TournamentResult tour_res = tournamentAddGame(tournament, game);
    if (tour_res != TOURNAMENT_SUCCESS) {
        playerRemoveGame(player1, game);
        playerRemoveGame(player2, game);
        if (player1_is_new) {
            mapRemove(chess->players, player1_id);
            playerDestroy(player1);
        }
        if (player2_is_new) {
            mapRemove(chess->players, player2_id);
            playerDestroy(player2);
        }
        gameDestroy(game);
        playerIDDestroy(player1_id);
        playerIDDestroy(player2_id);
        return CHESS_OUT_OF_MEMORY;
    }
    if(player1_is_new){
        playerDestroy(player1);
    }
    if(player2_is_new){
        playerDestroy(player2);
    }
    gameDestroy(game);
    playerIDDestroy(player1_id);
    playerIDDestroy(player2_id);
    return CHESS_SUCCESS;
}



//    if (winner == FIRST_PLAYER) {
//        playerAddWin(player1);
//    } else if (winner == SECOND_PLAYER) {
//        playerAddLoss(player1);
//    } else {
//        playerAddDraw(player1);
//    }
//
//        if()
//        int version = playerIDGetIntVersion(player1);
//        version++;
//        PlayerID new_player_id = playerIDCreate(first_player, version);
//        if(!new_player_id) {
//            playerIDDestroy(player1_id);
//            playerIDDestroy(player2_id);
//            return CHESS_OUT_OF_MEMORY;
//        }
//        ChessPlayer new_player = playerCreate(new_player_id);
//        if(!new_player_id){
//            playerIDDestroy(new_player_id);
//            playerIDDestroy(player1_id);
//            playerIDDestroy(player2_id);
//            return CHESS_OUT_OF_MEMORY;
//        }
//        MapResult  res = mapPut(chess->players, new_player_id, new_player);
//        if(res!=MAP_SUCCESS){
//            playerDestroy(new_player);
//            playerIDDestroy(new_player_id);
//            playerIDDestroy(player1_id);
//            playerIDDestroy(player2_id);
//            return MAP_OUT_OF_MEMORY;
//        }
//
//}

ChessResult chessRemovePlayer(ChessSystem chess, int player_id){
    return CHESS_SUCCESS;
}

ChessResult chessEndTournament (ChessSystem chess, int tournament_id){
    return CHESS_SUCCESS;
}

double chessCalculateAveragePlayTime (ChessSystem chess, int player_id, ChessResult* chess_result){
    return 0;
}

ChessResult chessSavePlayersLevels (ChessSystem chess, FILE* file){
    return CHESS_SUCCESS;
}

ChessResult chessSaveTournamentStatistics (ChessSystem chess, char* path_file){
    return CHESS_SUCCESS;
}

