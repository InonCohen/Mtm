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


#define LENGTH_OF_ZERO_STRING 2


struct chess_system_t{
    Map tournaments; // Key: int id,  Data: Tournament tour
    Map Players; // Key: int id,  Data: Player
    int ended_tournaments;
};

/*
 * Required to function:
 *              - Tournaments ADT copy, destroy funcs
 *              - Players ADT copy, destroy funcs
 */


static char* createGameID(char* player1_id, char* player2_id, int tournament_id){
    if(!player1_id || !player2_id || tournament_id <= 0){
        return NULL;
    }
    // TODO: Implement: char* chessSystem->createPlayerID(chessPlayer player)
    char* tournament_id_str= castIntToString((int) tournament_id);
    int len1, len2, len3;
    len1=(int)strlen(player1_id);
    len2=(int)strlen(player2_id);
    len3=(int)strlen(tournament_id_str);
    int size = len1 + strlen(ID_SEP) + len2  + strlen(ID_SEP) + len3 + strlen(ID_SEP);
    char* game_id = malloc(size);
    if(!game_id){
        return NULL;
    }
    nullifyString(game_id, size);
    game_id = strcat(game_id,tournament_id_str);
    game_id = strcat(game_id, ID_SEP);
    game_id = strcat(game_id,strcmp(player1_id,player2_id) < 0 ? player1_id: player2_id);
    game_id = strcat(game_id, ID_SEP);
    game_id = strcat(game_id,strcmp(player1_id,player2_id) > 0 ? player1_id: player2_id);
    return game_id;
}

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


//returns the last version_int of the player with id_int, whether it is deleted or not
void getPlayerIdFromMap (Map players, int id_int, char* id_str) {
    assert(id_str == NULL);
    if(!players || id_int <= 0) {
        id_str=NULL;
    }
    char* converted_id = castIntToString(id_int);
    if(!converted_id) {
        return;
    }
    int size_before_version = strlen(converted_id)+ strlen(ID_SEP);
    char* converted_id_with_underscore = malloc(size_before_version+1);
    if(!converted_id_with_underscore){
        free(converted_id);
    }
    nullifyString(converted_id_with_underscore, size_before_version);
    strcpy(converted_id_with_underscore, converted_id);
    strcat(converted_id_with_underscore, ID_SEP);
    int id_version=0;
    MAP_FOREACH(char*, iter, players) {
        if (strncmp(converted_id, iter, strlen(converted_id)) == 0) {
            id_version++;
        }
        free(iter);
    }
    char* version = castIntToString(id_version);
    if(!version){
        free(converted_id_with_underscore);
        free(converted_id);
    }
    int size_of_version = strlen(version);
    int size_of_new_id = size_before_version+size_of_version;
    id_str = malloc(size_of_new_id+1);
    if(!id_str) {
        freeAll(version, converted_id, converted_id_with_underscore, NULL);
    }
    nullifyString(id_str, size_of_new_id);
    strcat(id_str, converted_id_with_underscore);
    strcat(id_str, version);
    freeAll(version, converted_id, converted_id_with_underscore, NULL);
}

static char* convertPlayerIntIdToCharId(Map players, int id){
    if(!players || id<=0){
        return NULL;
    }
    char* id_str = NULL;
    getPlayerIdFromMap(players, id, id_str);
    if(!id_str) {
        return NULL;
    }
    if(playerIsDeleted(mapGet(players, id_str))) {
        playerGetVersion()
    }


}



ChessSystem chessCreate(){
    ChessSystem system = malloc(sizeof(*system));
    if(!system){
        return NULL;
    }
    Map tournaments = mapCreate(tournamentCreate, tournamentMapKeyCopy, tournamentDestroy, tournamentMapKeyFree, tournamentMapKeyComp);
    if(!tournaments){
        free(system);
        return NULL;
    }
    Map players = mapCreate(playerCopy, );
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
    return CHESS_SUCCESS;
}

ChessResult chessAddGame(ChessSystem chess, int tournament_id, int first_player,
                         int second_player, Winner winner, int play_time) {
/*Rundown:
 * check validity of inputs
 * create players string ids
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
    if (!mapContains(chess->tournaments, tournament_id)) {
        return CHESS_TOURNAMENT_NOT_EXIST;
    }
    Tournament tournament = mapGet(chess->tournaments, tournament_id);
    if (tournamentIsOver(tournament)) {
        return CHESS_TOURNAMENT_ENDED;
    }
    char *player1_id = NULL, *player2_id = NULL;
    getPlayerIdOfMap(chess->players, first_player, player1_id);// iterates over the map and return the last id that matches the int
    // and puts its value in the char* it gets
    getPlayerIdOfMap(chess->players, second_player, player2_id);
    if (player1_id) {
        ChessPlayer player1 = mapGet(chess->players, player1_id);
        if (winner == FIRST_PLAYER) {
            playerAddWin(player1);
        } else if (winner == SECOND_PLAYER) {
            playerAddLoss(player1);
        } else {
            playerAddDraw(player1);
        }
    }

}



    TournamentResult res = tournamentAddGame(tournament, first_player, second_player,play_time, winner);
    if(res == TOURNAMENT_SUCCESS){
        if(!mapContains(chess->players))
    }

}

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

int main(){

}
