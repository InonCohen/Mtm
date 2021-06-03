#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "map.h"
#include "strUtils.h"
#include "chessSystem.h"
#include "chessTournament.h"
#include "chessMapUtils.h"
#include "chessGame.h"
#include "chessPlayer.h"
#include "chessPlayerID.h"

#define WIN_GAME_SCORE 2
#define DRAW_GAME_SCORE 1
#define BAD_INPUT (-999)

struct chess_tournament_t{
    int tournament_id;
    int max_games_per_player;
    char* tournament_location;
    PlayerID tournament_winner_player_id;
    Map tournament_games;
    Map tournament_players;
    Map games_counter_of_players;
};
/**
 * buildPlayersRankMap:
 * Assumptions:
 *  - tournament isn't empty (checked by related ChessSystem)
 * @param tournament
 * @return Map of player_id : total_rank
 */
static Map buildPlayersRankMap(ChessTournament tournament);

/**
 *
 * @param tournament_players
 * @param player_int_id
 * @return
 */
//static PlayerID playersIDMapGetLastVersion(Map tournament_players, int player_int_id);

/**
 *
 * @param tournament
 * @param player_int_id
 * @return
 */
//static int countWinGamesForPlayer(ChessTournament tournament, PlayerID player_id);
/**
 *
 * @param tournament
 * @param player_int_id_ptr
 * @return
 */
//static int countLostGamesForPlayer(ChessTournament tournament, PlayerID player_id);

static ChessResult tournamentAddPlayer(ChessTournament tournament, ChessPlayer player);
/**
 * tournamentCreate:
 * Assumptions:
 *  - Tournament properties validity-check is made by Chess System.
 * @param tournament_id
 * @param max_games_per_player
 * @param tournament_location
 * @return
 *  New ChessTournament, or NULL if a out_of_memory error has occurred
 */
ChessTournament tournamentCreate(int tournament_id, int max_games_per_player, const char* tournament_location){
    if(tournament_id <= 0 || max_games_per_player <= 0) {
        return NULL;
    }
    ChessTournament result = malloc(sizeof (*result));
    if(!result){
        return NULL;
    }
    result->tournament_location = malloc(strlen(tournament_location)+1);
    if(!tournament_location){
        free(result->tournament_location);
        tournamentDestroy(result);
        return NULL;
    }
    Map tournament_games = mapCreate(gamesMapCopyData, stringCopyFunc, gamesMapFreeData,
                                     mapFreeStringKey, mapCompareStringKeys);
    if(!tournament_games){
        free(result->tournament_location);
        tournamentDestroy(result);
        return NULL;
    }
    Map games_counter_of_players = mapCreate(intCopyFunc, intCopyFunc, intFreeFunc, intFreeFunc, intCompFunc);
    if(!games_counter_of_players){
        free(result->tournament_location);
        mapDestroy(tournament_games);
        tournamentDestroy(result);
        return NULL;
    }
    Map tournament_players = mapCreate(playersMapCopyData, playersMapCopyKey,
                                       playersMapFreeData, playersMapFreeKey, playersMapComp);
    if(!tournament_players){
        free(result->tournament_location);
        mapDestroy(tournament_games);
        mapDestroy(games_counter_of_players);
        tournamentDestroy(result);
        return NULL;
    }
    result->tournament_id = tournament_id;
    result->tournament_winner_player_id = NULL;
    result->max_games_per_player = max_games_per_player;
    strcpy(result->tournament_location, tournament_location);
    result->tournament_games = tournament_games;
    result->tournament_players = tournament_players;
    result->games_counter_of_players = games_counter_of_players;
    return result;
}
/**
 *
 * Assumptions:
 *  - Tournament properties validity-check is made by Chess System.
 * @param src_tournament
 * @return
 *  Copy of src_tournament
 */
ChessTournament tournamentCopy(ChessTournament src_tournament){
    if(!src_tournament){
        return NULL;
    }
    ChessTournament dst_tournament = malloc(sizeof (*dst_tournament));
    if (!dst_tournament) {
        return NULL;
    }

    dst_tournament->tournament_location = malloc(strlen(src_tournament->tournament_location) + 1);
    if(!dst_tournament->tournament_location){
        tournamentDestroy(dst_tournament);
        return NULL;
    }
    PlayerID dst_tournament_winner_player_id;
    if(src_tournament->tournament_winner_player_id == NULL){
        dst_tournament_winner_player_id = NULL;
    }
    else{
        dst_tournament_winner_player_id = playerIDCopy(src_tournament->tournament_winner_player_id);
        if(!dst_tournament_winner_player_id){
            free(dst_tournament->tournament_location);
            free(dst_tournament);
            return NULL;
        }
    }

    Map tournament_games = mapCopy(src_tournament->tournament_games);
    if(!tournament_games){
        free(dst_tournament->tournament_location);
        playerIDDestroy(dst_tournament_winner_player_id);
        free(dst_tournament);
        return NULL;
    }
    Map games_counter_of_players = mapCopy(src_tournament->games_counter_of_players);
    if(!games_counter_of_players){
        free(dst_tournament->tournament_location);
        playerIDDestroy(dst_tournament_winner_player_id);
        mapDestroy(tournament_games);
        free(dst_tournament);
        return NULL;
    }
    Map tournament_players = mapCopy(src_tournament->tournament_players);
    if(!tournament_players){
        free(dst_tournament->tournament_location);
        playerIDDestroy(dst_tournament_winner_player_id);
        mapDestroy(tournament_games);
        mapDestroy(games_counter_of_players);
        free(dst_tournament);
        return NULL;
    }

    dst_tournament->tournament_id = src_tournament->tournament_id;
    dst_tournament->max_games_per_player = src_tournament->max_games_per_player;
    strcpy(dst_tournament->tournament_location, src_tournament->tournament_location);
    dst_tournament->tournament_winner_player_id = dst_tournament_winner_player_id;
    dst_tournament->tournament_games = tournament_games;
    dst_tournament->tournament_players = tournament_players;
    dst_tournament->games_counter_of_players = games_counter_of_players;
    return dst_tournament;
}

void tournamentDestroy(ChessTournament tournament){
    if(!tournament){
        return;
    }
    free(tournament->tournament_location);
    if(tournament->tournament_winner_player_id){
        playerIDDestroy(tournament->tournament_winner_player_id);
    }
    if(tournament->tournament_games){
        mapDestroy(tournament->tournament_games);
    }
    if(tournament->tournament_players) {
        mapDestroy(tournament->tournament_players);
    }
    if(tournament->games_counter_of_players) {
        mapDestroy(tournament->games_counter_of_players);
    }
    free(tournament);
}

int tournamentGetID(ChessTournament tournament){
    if(!tournament){
        return BAD_INPUT;
    }
    return tournament->tournament_id;
}

Map tournamentGetGames(ChessTournament tournament){
    if(!tournament){
        return NULL;
    }
    if(!tournament->tournament_games){
        return NULL;
    }
    return tournament->tournament_games;
}

Map tournamentGetPlayers(ChessTournament tournament){
    if (!tournament){
        return NULL;
    }
    return tournament->tournament_players;
}

char* tournamentGetTournamentLocation(ChessTournament tournament){
    if(!tournament){
        return NULL;
    }
    return tournament->tournament_location;
}

bool tournamentIsOver(ChessTournament tournament){
    if(!tournament){
        return NULL;
    }
    return tournament->tournament_winner_player_id != NULL;
}
/**
 * tournamentAddGame: Add a game into tournament.
 *  Do:
 *  1. Check arguments validity
 *      RAISES: CHESS_NULL_ARGUMENT, CHESS_TOURNAMENT_ENDED, CHESS_GAME_ALREADY_EXISTS
 *  2. Foreach player call tournamentAddPlayer(tournament, player).
 *
 *  3. Foreach player call tournamentAddGameForPlayer(tournament, player)
 *      RAISES: CHESS_EXCEEDED_GAMES, CHESS_OUT_OF_MEMORY
 *  4. Finally, Add the game into  tournament_games and return CHESS_SUCCESS
 * @param tournament: tournament to add game into
 * @param game: game to be added
 * @return TOURNAMENT_SUCCESS if game was added successfully, matching TournamentResult otherwise.
 */
ChessResult tournamentAddGame(ChessTournament tournament, ChessGame game){
    if(!tournament || !game){
        return CHESS_NULL_ARGUMENT;
    }
    if (tournamentIsOver(tournament)){
        return CHESS_TOURNAMENT_ENDED;
    }
    char* game_id = gameGetID(game);
    if(!game_id){
        return CHESS_NULL_ARGUMENT;
    }
    if (mapGet(tournament->tournament_games, game_id)){
        return CHESS_GAME_ALREADY_EXISTS;
    }
    MapResult result = mapPut(tournament->tournament_games, game_id, game);
    if(result == MAP_OUT_OF_MEMORY){
        mapRemove(tournament->tournament_games, game_id);
        return CHESS_OUT_OF_MEMORY;
    }
    // Game is inserted to tournament->games
    // Insert players from game into tournament->players
    bool player1_is_new = false;
    bool player2_is_new = false;
    PlayerID player1_id = gameGetPlayer1ID(game);
    ChessPlayer player1 = mapGet(tournament->tournament_players, player1_id);
    if (!player1){
        player1_is_new = true;
        player1 = playerCreate(player1_id);
        ChessResult chess_result = tournamentAddPlayer(tournament, player1);
        if(chess_result != CHESS_SUCCESS){
            mapRemove(tournament->tournament_games, game_id);
            playerIDDestroy(player1_id);
            playerDestroy(player1);
            return chess_result;
        }
        playerDestroy(player1);
        player1 = NULL;
    }
    PlayerID player2_id = gameGetPlayer2ID(game);
    ChessPlayer player2 = mapGet(tournament->tournament_players, player2_id);
    if (!player2){
        player2_is_new = true;
        player2 = playerCreate(player2_id);
        ChessResult chess_result = tournamentAddPlayer(tournament, player2);
        if(chess_result != CHESS_SUCCESS){
            mapRemove(tournament->tournament_games, game_id);
            playerIDDestroy(player2_id);
            playerDestroy(player2);
            if(player1_is_new){
                mapRemove(tournament->tournament_players,player1_id);
            }
            return chess_result;
        }
        playerDestroy(player2);
        player2 = NULL;
    }
    player1 = mapGet(tournament->tournament_players, player1_id);
    player2 = mapGet(tournament->tournament_players, player2_id);
    int player1_num_of_games = playerGetNumOfGames(player1);
    int player2_num_of_games = playerGetNumOfGames(player2);
    if(player1_num_of_games == tournament->max_games_per_player || player2_num_of_games == tournament->max_games_per_player){
        mapRemove(tournament->tournament_games, game_id);
        return CHESS_EXCEEDED_GAMES;
    }
    PlayerResult res = playerAddGame(player1, game);
    if(res != PLAYER_SUCCESS)
    {
        mapRemove(tournament->tournament_games, game_id);
        playerRemoveGame(player1, game);
        if(player1_is_new){
            mapRemove(tournament->tournament_players,player1_id);
        }
        if(player2_is_new){
            mapRemove(tournament->tournament_players,player2_id);
        }
        return (ChessResult)res;
    }
    res = playerAddGame(player2, game);
    if (res != PLAYER_SUCCESS){
        mapRemove(tournament->tournament_games, game_id);
        if(player1_is_new){
            mapRemove(tournament->tournament_players,player1_id);
        }
        if(player2_is_new){
            mapRemove(tournament->tournament_players,player2_id);
        }
        playerRemoveGame(player1, game);
        return (ChessResult) res;
    }
    if ((!player1_is_new && playerGetNumOfGames(player1) > tournament->max_games_per_player) ||
            (!player2_is_new && playerGetNumOfGames(player2) > tournament->max_games_per_player)){
        mapRemove(tournament->tournament_games, game_id);
        if(player1_is_new){
            mapRemove(tournament->tournament_players,player1_id);
        }
        if(player2_is_new){
            mapRemove(tournament->tournament_players,player2_id);
        }
        playerRemoveGame(player1, game);
        playerRemoveGame(player2, game);
        return CHESS_EXCEEDED_GAMES;
    }

    return CHESS_SUCCESS;
}
/**
 * tournamentEndTournament: Check for the tournament winner and set it at:
 * tournament->tournament_winner_player_id.
 * Tournament Winner Calculate: the winner of a tournament:
 *  - A single player with max points
 *  - Else, a single player with max winning games from players meet the previous requirements.
 *  - Else, a single player with min loses from players meet the previous requirements.
 *  - Finally, a single player with min id meet the previous requirements.
 * @param tournament
 * @return CHESS_SUCCESS if calculation was over successfully or CHESS_OUT_OF_MEMORY if a memory error has occured.
 */
ChessResult tournamentEndTournament(ChessTournament tournament) {
    if(!tournament){
        return CHESS_NULL_ARGUMENT;
    }
    if(mapGetSize(tournament->tournament_games) == 0){
        return CHESS_NO_GAMES;
    }
    ChessResult res = tournamentFindWinner(tournament);
    return res;
}

ChessResult tournamentFindWinner(ChessTournament tournament){
    Map players_rank = buildPlayersRankMap(tournament);
    if(!players_rank){
        return CHESS_OUT_OF_MEMORY;
    }
    // Find max rank
    int max_rank=0;
    MAP_FOREACH(PlayerID ,player_id, players_rank){
        int current_player_rank = *(int*)(mapGet(players_rank, player_id));
        if(current_player_rank > max_rank){
            max_rank = current_player_rank;
        }
        playerIDDestroy(player_id);
    }
    // Find all players with rank max_rank
    Map players_have_max_rank = mapCopy(players_rank);
    if(!players_have_max_rank){
        mapDestroy(players_rank);
        return CHESS_OUT_OF_MEMORY;
    }
    MAP_FOREACH(PlayerID, player_id, players_rank){
        int current_player_rank = *(int*)(mapGet(players_rank, player_id));
        if(current_player_rank < max_rank){
            mapRemove(players_have_max_rank, player_id);
        }
        playerIDDestroy(player_id);
    }
    mapDestroy(players_rank);
    // In a case of a single player has max rank
    if(mapGetSize(players_have_max_rank) == 1){
        tournament->tournament_winner_player_id = (PlayerID)mapGetFirst(players_have_max_rank);;
        mapDestroy(players_have_max_rank);
        return CHESS_SUCCESS;
    }
    // Else, there are multiple players with max score. Continue calculating min_losses among players have max score
    // Find minimal loser
    PlayerID first_id_in_list = (PlayerID)mapGetFirst(players_have_max_rank);
    if(!first_id_in_list){
        mapDestroy(players_have_max_rank);
        return CHESS_OUT_OF_MEMORY;
    }
    ChessPlayer first_player = mapGet(tournament->tournament_players, first_id_in_list);
    int min_losing_games = playerGetNumOfLosses(first_player);
    playerIDDestroy(first_id_in_list);
    MAP_FOREACH(PlayerID, player_id, players_have_max_rank){
        ChessPlayer current_player = mapGet(tournament->tournament_players, player_id);
        int num_of_games_lost = playerGetNumOfLosses(current_player);
        if(num_of_games_lost<min_losing_games){
            min_losing_games = num_of_games_lost;
        }
        playerIDDestroy(player_id);
    }
    Map minimal_losers = mapCopy(players_have_max_rank);
    if(!minimal_losers){
        mapDestroy(players_have_max_rank);
        return CHESS_OUT_OF_MEMORY;
    }
    MAP_FOREACH(PlayerID, player_id, players_have_max_rank) {
        ChessPlayer current_player = mapGet(tournament->tournament_players, player_id);
        if(playerGetNumOfLosses(current_player)>min_losing_games){
            mapRemove(minimal_losers, player_id);
        }
        playerIDDestroy(player_id);
    }
    mapDestroy(players_have_max_rank);
    // In a case of a single player has max rank
    if(mapGetSize(minimal_losers) == 1){
        tournament->tournament_winner_player_id = (PlayerID)mapGetFirst(minimal_losers);
        mapDestroy(minimal_losers);
        return CHESS_SUCCESS;
    }
    // Else, there are multiple players with minimum losing games. Continue calculating maximum winning games
    // Find maximal winner
    int max_winning_games = 0;
    MAP_FOREACH(PlayerID, player_id, minimal_losers){
        ChessPlayer current_player = mapGet(tournament->tournament_players, player_id);
        int player_win_games = playerGetNumOfWins(current_player);
        if(player_win_games > max_winning_games){
            max_winning_games = player_win_games;
        }
        playerIDDestroy(player_id);
    }
    // Find all players have max_win_games
    Map maximal_winners = mapCopy(minimal_losers);
    if(!maximal_winners){
        mapDestroy(minimal_losers);
        return CHESS_OUT_OF_MEMORY;
    }
    MAP_FOREACH(PlayerID, player_id, minimal_losers){
        ChessPlayer current_player = mapGet(tournament->tournament_players, player_id);
        int player_win_games = playerGetNumOfWins(current_player);
        if (player_win_games < max_winning_games){
            mapRemove(maximal_winners, player_id);
        }
        playerIDDestroy(player_id);
    }
    mapDestroy(minimal_losers);
    // If there is a single player has maximal number of winning games, it will be the mapGetFirst (map length equals one), else
    // returns the min player_id, which is the mapGetFirst either due to map default ASC sort by key.
    tournament->tournament_winner_player_id = (PlayerID)mapGetFirst(maximal_winners);
    if(!tournament->tournament_winner_player_id){
        mapDestroy(maximal_winners);
        return CHESS_OUT_OF_MEMORY;
    }
    mapDestroy(maximal_winners);
    return CHESS_SUCCESS;
}

ChessResult tournamentRemovePlayer(ChessTournament tournament, PlayerID player_id){
    if(!tournament || !player_id){
        return CHESS_NULL_ARGUMENT;
    }
    ChessPlayer player = mapGet(tournament->tournament_players, player_id);
    if(!player){
        return CHESS_PLAYER_NOT_EXIST;
    }
    // For every game that player is taking part of set rival to be the winner.
    MAP_FOREACH(char*, game_id, tournament->tournament_games){
        ChessGame game = mapGet(tournament->tournament_games, game_id);
        if (playerIDCompare(gameGetPlayer1ID(game), player_id)){
            gameSetWinner(game,SECOND_PLAYER);
        }
        if (playerIDCompare(gameGetPlayer2ID(game), player_id)){
            gameSetWinner(game,FIRST_PLAYER);
        }
        free(game_id);
    }
    playerSetIsDeleted(player);
    return CHESS_SUCCESS;
}

PlayerID tournamentGetWinnerPlayerID(ChessTournament tournament){
    if(!tournament){
        return NULL;
    }
    return tournament->tournament_winner_player_id;
}

int tournamentGetLongestGameTime(ChessTournament tournament){
    if(!tournament){
        return BAD_INPUT;
    }
    Map games = tournament->tournament_games;
    int max_time = BAD_INPUT;
    MAP_FOREACH(char*, iter, games){
        ChessGame current_game = mapGet(games, iter);
        int current_play_time = gameGetPlayTime(current_game);
        if(current_play_time>max_time){
            max_time = current_play_time;
        }
        free(iter);
    }
    return max_time;
}

double tournamentGetAverageGameTime(ChessTournament tournament){
    if(!tournament){
        return (double)BAD_INPUT;
    }
    Map games = tournament->tournament_games;
    int all_time = 0;
    MAP_FOREACH(char*, iter, games){
        ChessGame current_game = mapGet(games, iter);
        int current_play_time = gameGetPlayTime(current_game);
        all_time+=current_play_time;
        free(iter);
    }
    int all_games = mapGetSize(games);
    return (double)all_time/(double)all_games;
}

int tournamentGetNumOfGames(ChessTournament tournament){
    if(!tournament){
        return BAD_INPUT;
    }
    return mapGetSize(tournament->tournament_games);
}

int tournamentGetNumOfAllPlayers(ChessTournament tournament){
    if(!tournament){
        return BAD_INPUT;
    }
    return mapGetSize(tournament->tournament_players);
}
/**
 * Validity Check:
 *  - Starts with capital letter.
 *  - All other chars will bee space or lowercase.
 * @param tournament_name
 * @return
 */
bool tournamentLocationIsValid(const char* tournament_name){
    if(!tournament_name){
        return false;
    }
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

/**
 * buildPlayersRankMap
 * @param tournament
 * @return
 *  Map of PlayerID player : <int> rank
 */
static Map buildPlayersRankMap(ChessTournament tournament){
    if(!tournament){
        return NULL;
    }
    Map active_players = mapCopy(tournamentGetPlayers(tournament));
    if (!active_players) {
        return NULL;
    }
    MAP_FOREACH(PlayerID, player_id, tournament->tournament_players){
        ChessPlayer current_player = mapGet(tournament->tournament_players, player_id);
        if(playerIsDeleted(current_player)){
            mapRemove(active_players, player_id);
        }
        playerIDDestroy(player_id);
    }
    Map players_rank = mapCreate(intCopyFunc, playersMapCopyKey, intFreeFunc, playersMapFreeKey, playersMapComp);
    if(!players_rank){
        mapDestroy(active_players);
        return NULL;
    }
    int init_rank = 0;
    MAP_FOREACH(PlayerID, player_id, active_players){
        mapPut(players_rank, player_id, &init_rank);
        playerIDDestroy(player_id);
    }
    mapDestroy(active_players);
    // Calculate Rank FOREACH Player
    MAP_FOREACH(char*, current_game_id, tournament->tournament_games) {
        ChessGame current_game = mapGet(tournament->tournament_games, current_game_id);
        PlayerID player1_id = gameGetPlayer1ID(current_game);
        PlayerID player2_id = gameGetPlayer2ID(current_game);
        int *player1_rank_ptr = NULL, *player2_rank_ptr = NULL;
        if (mapContains(players_rank, player1_id)) {
            player1_rank_ptr = (int *) mapGet(players_rank, player1_id);
        }
        if (mapContains(players_rank, player2_id)) {
            player2_rank_ptr = (int *) mapGet(players_rank, player2_id);
        }
        if (gameGetWinner(current_game) == FIRST_PLAYER) {
            if (player1_rank_ptr) {
                (*player1_rank_ptr) += WIN_GAME_SCORE;
            }
        }
        if (gameGetWinner(current_game) == SECOND_PLAYER) {
            if (player2_rank_ptr) {
                (*player2_rank_ptr) += WIN_GAME_SCORE;
            }
        }
        if (gameGetWinner(current_game) == DRAW) {
            if (player1_rank_ptr) {
                (*player1_rank_ptr) += DRAW_GAME_SCORE;
            }
            if (player2_rank_ptr) {
                (*player2_rank_ptr) += DRAW_GAME_SCORE;
            }
        }
        free(current_game_id);
    }
    return players_rank;
}

//static PlayerID playersIDMapGetLastVersion(Map tournament_players, int player_int_id){
//    if(!tournament_players){
//        return NULL;
//    }
//    PlayerID player_id_first_version = playerIDCreate(player_int_id, 0);
//    if(!mapContains(tournament_players, player_id_first_version)){
//        playerIDDestroy(player_id_first_version);
//        return NULL;
//    }
//    playerIDDestroy(player_id_first_version);
//    PlayerID player_id_last_version = NULL;
//    MAP_FOREACH(PlayerID, player_id, tournament_players){
//        if (playerIDGetIntID(player_id) <= player_int_id){
//            playerIDDestroy(player_id_last_version);
//            player_id_last_version = playerIDCopy(player_id);
//        }
//        else{
//            playerIDDestroy(player_id);
//            break;
//        }
//        playerIDDestroy(player_id);
//    }
//    return player_id_last_version;
//}

//static int countWinGamesForPlayer(ChessTournament tournament, PlayerID player_id){
//    int win_games_counter = 0;
//    ChessPlayer player = mapGet(tournament->tournament_players, player_id);
//    if(!player){
//        return BAD_INPUT;
//    }
//    Map games_of_player = playerGetGames(player);
//    MAP_FOREACH(char*, game_id, games_of_player){
//        ChessGame game = mapGet(games_of_player, game_id);
//        if((gameGetWinner(game) == FIRST_PLAYER && gameGetPlayer1ID(game) == playerGetID(player)) ||
//            (gameGetWinner(game) == SECOND_PLAYER && gameGetPlayer2ID(game) == playerGetID(player))){
//                win_games_counter++;
//        }
//        free(game_id);
//    }
//    return win_games_counter;
//}

//static int countLostGamesForPlayer(ChessTournament tournament, PlayerID player_id){
//    if(!tournament || !player_id){
//        return BAD_INPUT;
//    }
//    int lost_games_counter = 0;
//    ChessPlayer player = mapGet(tournament->tournament_players, player_id);
//    if(!player){
//        return BAD_INPUT;
//    }
//    Map games = playerGetGames(player);
//    MAP_FOREACH(char*, game_id, games){
//        ChessGame game = mapGet(games,game_id);
//        if((gameGetWinner(game) == SECOND_PLAYER && gameGetPlayer1ID(game) == playerGetID(player)) ||
//           (gameGetWinner(game) == FIRST_PLAYER && gameGetPlayer2ID(game) == playerGetID(player))){
//            lost_games_counter++;
//        }
//        free(game_id);
//    }
//    mapDestroy(games);
//    return lost_games_counter;
//}

static ChessResult tournamentAddPlayer(ChessTournament tournament, ChessPlayer player){
    if(!tournament || !player){
        return CHESS_NULL_ARGUMENT;
    }
    PlayerID player_id = playerGetID(player);
    if(!player_id){
        return CHESS_NULL_ARGUMENT;
    }
    MapResult map_result = mapPut(tournament->tournament_players, player_id, player);
    if (map_result == MAP_OUT_OF_MEMORY) {
        return CHESS_OUT_OF_MEMORY;
    }
    return CHESS_SUCCESS;
}

