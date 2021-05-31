#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "../map/map.h"
#include "chessMapUtils.h"
#include "strUtils.h"
#include "chessSystem.h"
#include "chessTournament.h"
#include "chessGame.h"
#include "chessPlayer.h"
#include "chessPlayerID.h"


#define LENGTH_OF_ZERO_STRING 2


struct chess_system_t{
    Map tournaments; // Key: int id,  Data: Tournament tour
    Map players; // Key: int id,  Data: Player
    int ended_tournaments;
};
/**
 * Validity Check:
 *  - Starts with capital letter.
 *  - All other chars will bee space or lowercase.
 * @param tournament_name
 * @return
 */
static bool tournamentLocationIsValid(const char* tournament_name);

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
        ChessPlayer current_player = mapGet(players, iter);
        if (playerIDGetIntID(iter) == id_int && playerIsDeleted(current_player)) {
            id_version++;
        }
        playerIDDestroy(iter);
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
    if(tournament_id <= 0){
        return CHESS_INVALID_ID;
    }
    if(mapGet(chess->tournaments,&tournament_id)){
        return CHESS_TOURNAMENT_ALREADY_EXISTS;
    }
    if(!tournamentLocationIsValid(tournament_location)){
        return CHESS_INVALID_LOCATION;
    }
    if(!(max_games_per_player > 0)){
        return CHESS_INVALID_MAX_GAMES;
    }

    ChessTournament new_tournament = tournamentCreate(tournament_id, max_games_per_player, tournament_location);
    MapResult result = mapPut(chess->tournaments, &tournament_id, new_tournament);
    if(result != MAP_SUCCESS){
        return CHESS_OUT_OF_MEMORY;
    }
    tournamentDestroy(new_tournament);
    return CHESS_SUCCESS;
}
//TODO: Make much shorter
ChessResult chessAddGame(ChessSystem chess, int tournament_id, int first_player,
                         int second_player, Winner winner, int play_time) {
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

ChessResult chessRemovePlayer(ChessSystem chess, int player_id){
    if(!chess){
        return CHESS_NULL_ARGUMENT;
    }
    if(player_id <= 0){
        return CHESS_INVALID_ID;
    }
    Map players = chess->players;
    PlayerID new_player_id = getPlayerIdFromMap(players, player_id);
    if(!new_player_id){
        return CHESS_OUT_OF_MEMORY;
    }
    ChessPlayer player = mapGet(players, new_player_id);
    if(!player){
        playerIDDestroy(new_player_id);
        return CHESS_PLAYER_NOT_EXIST;
    }
    playerIDDestroy(new_player_id);
    Map player_games = playerGetGames(player);
    MAP_FOREACH(char*, iter, player_games){
        ChessGame current_game = (ChessGame)mapGet(player_games, iter);
        int current_game_tournament_id = gameGetTournamentID(current_game);
        ChessTournament current_tournament = mapGet(chess->tournaments, &current_game_tournament_id);
        assert(current_tournament!=NULL);
        if(!tournamentIsOver(current_tournament)){
            gameUpdateLoser(current_game, player);
            tournamentRemovePlayer(current_tournament, new_player_id);//TODO: ask Ohad - should it be here inside the if, or outside of it
        }
        gameMarkDeletedPlayerTrue(current_game);
        free(iter);
    }

    playerMarkDeleted(player);
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