#include <stdlib.h>
#include <stdio.h>
#include "map.h"
#include "chessMapUtils.h"
#include "chessSystem.h"
#include "chessTournament.h"

struct chess_system_t{
    Map tournaments; 
    Map players;
    int ended_tournaments;
};

/**
 * chessGameInTournament: checks if a game_id is of a game belongs to the given tournament
 *
 * @param tournament    - a tournament in which it is required to check the existence of a game of which id is game_id. Must be non-NULL.
 * @param game_id       - the game id. Must be non-NULL.
 * @return
 *     False if tournament or id_game are NULL, or if the tournament doesn't contain a game as required.
 *     True otherwise.
 */
static bool chessGameInTournament(ChessTournament tournament, char* game_id);

/**
 * buildPlayerIDFromMap: Returns the relevant PlayerID from given map. If no player has ever been entered
 *                      to the system with  id_int, id will be made with version 0.
 *                      IMPORTANT: THE RETURNED PlayerID IS ALLOCATED, AND THUS MUST BE FREED BY USER
 *
 * @param players    - a map that contains the chess system players. Must be non-NULL.
 * @param id_int     - the player id. Must be positive.
 * @return
 *     a PlayerID which contains:
 *          - The player's ID - if there is such a player (active, not deleted) in the system with int_id.
 *          - A new id that never existed in the system's players map - if there was a player with such
 *              id_int, but it was deleted.
 *          - NULL - if there was a memory problem or the inputs were corrupted.
 */
static PlayerID buildPlayerIdFromMap (Map players, int id_int);

static bool chessGameInTournament(ChessTournament tournament, char* game_id){
    if(!tournament || !game_id){
        return false;
    }
    Map games = tournamentGetGames(tournament);
    if(mapContains(games,game_id)){
        ChessGame game = mapGet(games,game_id);
        if(!game){
            return false;
        }
        if (gamePlayerIsDeleted(game)) {
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
 * @return
 *     a PlayerID which contains:
 *          the player's ID - if there is such a player in the system with int_id.
 *          a new id that never existed in the system's players map -
 *                      if there was a player with such id_int, but it was deleted.
 *          NULL - if there was a memory problem or the inputs were corrupted.
 */
PlayerID buildPlayerIdFromMap (Map players, int id_int) {
    if(!players || id_int <= 0) {
        return NULL;
    }
    int id_version = 0;
    MAP_FOREACH(PlayerID , iter, players) {
        ChessPlayer current_player = mapGet(players, iter);
        if (playerIDGetIntID(iter) == id_int){
            if(playerIsDeleted(current_player)) {
                id_version++;
            }
            else{
                return iter;
            }
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
}//Done.

void chessDestroy(ChessSystem chess){
    if(!chess){
        return;
    }
    mapDestroy(chess->tournaments);
    mapDestroy(chess->players);
    free(chess);
}//Done.

ChessResult chessAddTournament (ChessSystem chess, int tournament_id,
                                int max_games_per_player, const char* tournament_location){
    if(!chess || !tournament_location){
        return CHESS_NULL_ARGUMENT;
    }
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
    if(!new_tournament){
        return CHESS_OUT_OF_MEMORY;
    }
    MapResult result = mapPut(chess->tournaments, &tournament_id, new_tournament);
    if(result == MAP_OUT_OF_MEMORY){
        tournamentDestroy(new_tournament);
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
    if(!chess->tournaments){
        return CHESS_NULL_ARGUMENT;
    }
    if (tournament_id <= 0 || first_player <= 0 || second_player <= 0 || first_player == second_player) {
        return CHESS_INVALID_ID;
    }
    if (!mapContains(chess->tournaments, &tournament_id)) {
        return CHESS_TOURNAMENT_NOT_EXIST;
    }
    ChessTournament tournament = mapGet(chess->tournaments, &tournament_id);
    if (tournamentIsOver(tournament)) {
        return CHESS_TOURNAMENT_ENDED;
    }
    PlayerID player1_id = buildPlayerIdFromMap(chess->players, first_player);
    if(!player1_id) {
        return CHESS_OUT_OF_MEMORY;
    }
    PlayerID player2_id = buildPlayerIdFromMap(chess->players, second_player);
    if (!player2_id) {
        playerIDDestroy(player1_id);
        return CHESS_OUT_OF_MEMORY;
    }
    ChessGame game = gameCreate(tournament_id, player1_id, player2_id, play_time, winner);
    if (!game) {
        playerIDDestroy(player1_id);
        playerIDDestroy(player2_id);
        if(play_time < 0){
            return CHESS_INVALID_PLAY_TIME;
        }
        return CHESS_OUT_OF_MEMORY;
    }
    if(chessGameInTournament(tournament, gameGetID(game))) {
        gameDestroy(game);
        playerIDDestroy(player1_id);
        playerIDDestroy(player2_id);
        return CHESS_GAME_ALREADY_EXISTS;
    }
    if(play_time < 0){
        gameDestroy(game);
        playerIDDestroy(player1_id);
        playerIDDestroy(player2_id);
        return CHESS_INVALID_PLAY_TIME;

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
    ChessResult player_res = playerAddGame(player1, game);
    if (player_res != CHESS_SUCCESS) {
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
    if (player_res != CHESS_SUCCESS) {
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
    if (player1_is_new) {
        MapResult result = mapPut(chess->players, player1_id, player1);
        if (result == MAP_OUT_OF_MEMORY) {
            playerDestroy(player1);
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
        MapResult result = mapPut(chess->players, player2_id, player2);
        if (result == MAP_OUT_OF_MEMORY) {
            mapRemove(chess->players, player1);
            playerDestroy(player2);
            if (player1_is_new) {
                playerDestroy(player1);
            }
            gameDestroy(game);
            playerIDDestroy(player1_id);
            playerIDDestroy(player2_id);
            return CHESS_OUT_OF_MEMORY;
        }
    }
    ChessResult tour_res = tournamentAddGame(tournament, game);
    if (tour_res != CHESS_SUCCESS) {
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
        return tour_res;
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

ChessResult chessRemoveTournament (ChessSystem chess, int tournament_id){
    if(!chess){
        return CHESS_NULL_ARGUMENT;
    }
    if(tournament_id<=0){
        return CHESS_INVALID_ID;
    }
    if(!mapContains(chess->tournaments, &tournament_id) || (mapGetSize(chess->tournaments)==0)){
        return CHESS_TOURNAMENT_NOT_EXIST;
    }
    ChessTournament tournament_to_remove = mapGet(chess->tournaments, &tournament_id);
    Map tournament_games = tournamentGetGames(tournament_to_remove);
    if (mapGetSize(tournament_games) > 0) {
        MAP_FOREACH(char*, iter, tournament_games) {
            ChessGame current_game = mapGet(tournament_games, iter);
            PlayerID id1 = gameGetPlayer1ID(current_game);
            PlayerID id2 = gameGetPlayer2ID(current_game);
            ChessPlayer player1 = mapGet(chess->players, id1);
            ChessPlayer player2 = mapGet(chess->players, id2);
            if (!playerIsDeleted(player1)) {
                playerRemoveGame(player1, current_game);
            }
            if (!playerIsDeleted(player2)) {
                playerRemoveGame(player2, current_game);
            }
            free(iter);
        }
    }

    mapClear(tournament_games);
    if(tournamentIsOver(tournament_to_remove)){
        chess->ended_tournaments--;
    }
    mapRemove(chess->tournaments, &tournament_id);
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
    PlayerID new_player_id = buildPlayerIdFromMap(players, player_id);
    if(!new_player_id){
        return CHESS_OUT_OF_MEMORY;
    }
    ChessPlayer player_in_system = mapGet(players, new_player_id);
    if(!player_in_system){
        playerIDDestroy(new_player_id);
        return CHESS_PLAYER_NOT_EXIST;
    }
    //Remove player from all the games in his map
    Map player_games = playerGetGames(player_in_system);
    MAP_FOREACH(char*, game_id, player_games) {
        ChessGame current_game_in_player = (ChessGame) mapGet(player_games, game_id);
        int current_game_tournament_id = gameGetTournamentID(current_game_in_player);
        PlayerID other_player_id = ((playerIDCompare(gameGetPlayer1ID(current_game_in_player), new_player_id) == 0)
                                    ? gameGetPlayer2ID(current_game_in_player) : gameGetPlayer1ID(current_game_in_player));
        ChessPlayer other_player_in_system = mapGet(players, other_player_id);
        ChessTournament current_tournament = mapGet(chess->tournaments, &current_game_tournament_id);
        if (!tournamentIsOver(current_tournament)) {
            gameUpdateLoser(current_game_in_player, player_in_system, other_player_in_system);
            gameSetWinner(current_game_in_player, (playerIDCompare(gameGetPlayer1ID(current_game_in_player), new_player_id) == 0) ? SECOND_PLAYER : FIRST_PLAYER);
            gameMarkDeletedPlayerTrue(current_game_in_player);
        }
        free(game_id);
    }

    //remove player from all active tournaments games
    MAP_FOREACH(int*, tournament_id, chess->tournaments) {
        ChessTournament current_tournament = mapGet(chess->tournaments, tournament_id);
        if (!tournamentIsOver(current_tournament)) {
            Map tournament_games = tournamentGetGames(current_tournament);
            ChessPlayer player_in_tournament = mapGet(tournamentGetPlayers(current_tournament), new_player_id);
            if(mapGetSize((tournament_games))>0){
                MAP_FOREACH(char*, game_id, tournament_games) {
                    ChessGame current_game_in_tournament = (ChessGame) mapGet(tournament_games, game_id);
                    if(playerIDCompare(gameGetPlayer1ID(current_game_in_tournament), new_player_id) == 0 || playerIDCompare(gameGetPlayer2ID(current_game_in_tournament), new_player_id) == 0 ){
                        PlayerID other_player_id = (
                                (playerIDCompare(gameGetPlayer1ID(current_game_in_tournament), new_player_id) == 0)
                                ? gameGetPlayer2ID(current_game_in_tournament) : gameGetPlayer1ID(current_game_in_tournament));
                        ChessPlayer other_player_in_tournament = mapGet(tournamentGetPlayers(current_tournament),
                                                                        other_player_id);
                        gameUpdateLoser(current_game_in_tournament, player_in_tournament, other_player_in_tournament);
                        gameSetWinner(current_game_in_tournament, (playerIDCompare(gameGetPlayer1ID(current_game_in_tournament), new_player_id) == 0) ? SECOND_PLAYER : FIRST_PLAYER);
                        gameMarkDeletedPlayerTrue(current_game_in_tournament);
                    }
                    free(game_id);
                }
                playerSetIsDeleted(player_in_tournament);
            }
        }
        free(tournament_id);
    }
    playerIDDestroy(new_player_id);
    playerSetIsDeleted(player_in_system);
    return CHESS_SUCCESS;
}
/**
 * chessEndTournament: Check if a tournament can be ended.
 *  Exceptions:
 *  - tournament_id is a positive integer, otherwise return: CHESS_INVALID_ID
 *  - tournament_id represents an existing tournament, otherwise return: CHESS_TOURNAMENT_NOT_EXIST
 *  - tournament isn't over, otherwise return: CHESS_TOURNAMENT_ENDED
 *  - tournament isn't empty, otherwise return: CHESS_NO_GAMES
 * @param chess: ChessSystem to end tournament in.
 * @param tournament_id: id of ChessTournament to be ended.
 * @return
 *  CHESS_SUCCESS if tournament has ended successfully, otherwise one of the above exceptions.
 */
ChessResult chessEndTournament (ChessSystem chess, int tournament_id){
    if(!chess){
        return CHESS_NULL_ARGUMENT;
    }
    if (tournament_id <= 0){
        return CHESS_INVALID_ID;
    }
    ChessTournament tournament = mapGet(chess->tournaments, &tournament_id);
    if(!(tournament)){
        return CHESS_TOURNAMENT_NOT_EXIST;
    }
    if(tournamentIsOver(tournament)){
        return CHESS_TOURNAMENT_ENDED;
    }
    ChessResult result = tournamentEndTournament(tournament);
    if(result == CHESS_SUCCESS){
        chess->ended_tournaments++;
    }
    return result;
}

double chessCalculateAveragePlayTime (ChessSystem chess, int player_id, ChessResult* chess_result){
    if(!chess || !chess_result){
        *chess_result = CHESS_NULL_ARGUMENT;
        return 0;
    }
    if(player_id<=0){
        *chess_result = CHESS_INVALID_ID;
        return 0;
    }
    Map players = chess->players;
    PlayerID new_player_id = buildPlayerIdFromMap(players, player_id);
    if(!new_player_id){
        *chess_result = CHESS_OUT_OF_MEMORY;
        return 0;
    }
    if(!mapContains(players, new_player_id)){
        playerIDDestroy(new_player_id);
        *chess_result = CHESS_PLAYER_NOT_EXIST;
        return 0;
    }
    ChessPlayer player = mapGet(players,new_player_id);
    playerIDDestroy(new_player_id);
    int wins = playerGetNumOfWins(player);
    int losses = playerGetNumOfLosses(player);
    int draws = playerGetNumOfDraws(player);
    *chess_result = CHESS_SUCCESS;
    if(wins==0 && losses==0 && draws==0){
        return 0;
    }
    int total_games = wins+losses+draws;
    int total_time = playerGetPlayingTime(player);
    return (double)total_time/total_games;
}

ChessResult chessSavePlayersLevels (ChessSystem chess, FILE* file){
    if(!chess || !file){
        return CHESS_NULL_ARGUMENT;
    }
    Map new_players_map = mapCreate(doubleCopyFunc,playersMapCopyKey, doubleFreeFunc, playersMapFreeKey, playersMapComp);
    Map levels = mapCreate(intCopyFunc, doubleCopyFunc, intFreeFunc, doubleFreeFunc, doubleCompFunc);
    if(!new_players_map){
       return CHESS_OUT_OF_MEMORY;
    }
    int players_to_print = 0;
    MAP_FOREACH(PlayerID, iter ,chess->players){
        ChessPlayer current_player = mapGet(chess->players,iter);
        if(!playerIsDeleted(current_player)){
            int wins = playerGetNumOfWins(current_player);
            int losses = playerGetNumOfLosses(current_player);
            int draws = playerGetNumOfDraws(current_player);
            if(wins != 0 || losses != 0 || draws != 0 ){
                players_to_print++;
                double level = playerGetLevel(current_player);
                level=-level;
                MapResult result = mapPut(new_players_map, iter, &level);
                if(result == MAP_OUT_OF_MEMORY){
                    mapDestroy(new_players_map);
                    mapDestroy(levels);
                    playerIDDestroy(iter);
                    return CHESS_OUT_OF_MEMORY;
                }
                int num_of_players_same_level = 0;
                if(!mapContains(levels, &level)){
                    num_of_players_same_level = 1;
                }
                else{
                    num_of_players_same_level = *(int*)mapGet(levels, &level);
                    num_of_players_same_level++;
                }
                MapResult map_result = mapPut(levels, &level, &num_of_players_same_level);
                if(map_result == MAP_OUT_OF_MEMORY){
                    mapDestroy(new_players_map);
                    mapDestroy(levels);
                    playerIDDestroy(iter);
                    return CHESS_OUT_OF_MEMORY;
                }
            }
        }
        playerIDDestroy(iter);
    }
    if(players_to_print == 0){
        mapDestroy(new_players_map);
        mapDestroy(levels);
        return CHESS_SUCCESS;
    }
    MAP_FOREACH(double*, level, levels){
        MAP_FOREACH(PlayerID, player_id, new_players_map){
           double* current_player_level = mapGet(new_players_map, player_id);
           if(doubleCompFunc(current_player_level, level) == 0){
               int player_id_int = playerIDGetIntID(player_id);
               fprintf(file, "%d %.2f\n",player_id_int, -*(current_player_level));
           }
            playerIDDestroy(player_id);
        }
        doubleFreeFunc(level);
    }
    mapDestroy(new_players_map);
    mapDestroy(levels);
    return CHESS_SUCCESS;
}

ChessResult chessSaveTournamentStatistics (ChessSystem chess, char* path_file){
    if(!chess ||  !path_file){
        return CHESS_NULL_ARGUMENT;
    }
    if(chess->ended_tournaments == 0){
        return CHESS_NO_TOURNAMENTS_ENDED;
    }
    FILE* file = fopen(path_file, "w");
    if(!file){
        return CHESS_SAVE_FAILURE;
    }
    Map tournaments = chess->tournaments;
    MAP_FOREACH(int*, iter, tournaments){
        ChessTournament current_tournament = mapGet(tournaments, iter);
        if(tournamentIsOver(current_tournament)){
            PlayerID winner_id = tournamentGetWinnerPlayerID(current_tournament);
            int winner_int_id = playerIDGetIntID(winner_id);
            int longest_game_time = tournamentGetLongestGameTime(current_tournament);
            double average_game_time = tournamentGetAverageGameTime(current_tournament);
            char* location = tournamentGetTournamentLocation(current_tournament);
            int num_of_games = tournamentGetNumOfGames(current_tournament);
            int num_of_players = tournamentGetNumOfAllPlayers(current_tournament);
            fprintf(file, "%d\n", winner_int_id);
            fprintf(file, "%d\n", longest_game_time);
            fprintf(file, "%.2f\n", average_game_time);
            fprintf(file, "%s\n", location);
            fprintf(file, "%d\n", num_of_games);
            fprintf(file, "%d\n", num_of_players);
        }
        free(iter);
    }
    fclose(file);
    return CHESS_SUCCESS;
}
