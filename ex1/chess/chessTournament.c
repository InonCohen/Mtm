#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../map/map.h"
#include "chessSystem.h"
#include "chessTournament.h"
#include "chessMapUtils.h"
#include "chessGame.h"
#include "strUtils.h"
#include "chessPlayer.h"
#include "chessPlayerID.h"


#define NO_PLAYER_ID 0
#define WIN_GAME_SCORE 2
#define DRAW_GAME_SCORE 1

struct chess_tournament_t{
    int tournament_id;
    int max_games_per_player;
    int tournament_winner_player_id;
    char* tournament_location;
    Map tournament_games;
    Map games_counter_of_players;
};
/**
 * locationIsValid: Check if a tournament name is valid, by the following rules:
 *  - Starts with a capital letter.
 *  - Following letters can be only lowercase or space.
 * @param tournament_name: Tournament name to check
 * @return true if name isvalid, false otherwise.
 */
static bool locationIsValid(const char* tournament_name);
/**
 * generatePlayersRank:
 * Assumptions:
 *  - tournament isn't empty (checked by related ChessSystem)
 * @param tournament
 * @return Map of player_id : total_rank
 */
static Map generatePlayersRank(ChessTournament tournament);
/**
 *
 * @param tournament
 * @param player_int_id
 * @return
 */
static int countWinGamesForPlayer(ChessTournament tournament, int player_int_id);
/**
 *
 * @param tournament
 * @param player_int_id_ptr
 * @return
 */
static int countLostGamesForPlayer(ChessTournament tournament, int player_int_id_ptr);

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
    if(!locationIsValid(tournament_location)){
        return NULL;
    }
    ChessTournament result = malloc(sizeof (*result));
    if(!result){
        return NULL;
    }
    Map tournament_games = mapCreate(gamesMapCopyData, stringCopyFunc, gamesMapFreeData,
                                     mapFreeStringKey, mapCompareStringKeys);
    if(!tournament_games){
        tournamentDestroy(result);
        return NULL;
    }
    Map games_counter_of_players = mapCreate(intCopyFunc, intCopyFunc, intFreeFunc, intFreeFunc, intCompFunc);
    if(!games_counter_of_players){
        tournamentDestroy(result);
        mapDestroy(tournament_games);
        return NULL;
    }

    result->tournament_id = tournament_id;
    result->tournament_winner_player_id = NO_PLAYER_ID;
    result->max_games_per_player = max_games_per_player;
    result->tournament_games = tournament_games;
    result->games_counter_of_players = games_counter_of_players;
    result->tournament_location = malloc(strlen(tournament_location)+1);
    strcpy(result->tournament_location, tournament_location);

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

    Map tournament_games = mapCopy(src_tournament->tournament_games);
    if(!tournament_games){
        tournamentDestroy(dst_tournament);
        return NULL;
    }
    Map games_counter_of_players = mapCopy(src_tournament->games_counter_of_players);
    if(!games_counter_of_players){
        mapDestroy(tournament_games);
        tournamentDestroy(dst_tournament);
        return NULL;
    }

    dst_tournament->tournament_id = src_tournament->tournament_id;
    dst_tournament->max_games_per_player = src_tournament->max_games_per_player;
    dst_tournament->tournament_winner_player_id = src_tournament->tournament_winner_player_id;
    strcpy(dst_tournament->tournament_location, src_tournament->tournament_location);
    dst_tournament->tournament_games = tournament_games;
    dst_tournament->games_counter_of_players = games_counter_of_players;

    return dst_tournament;
}

void tournamentDestroy(ChessTournament tournament){
    if(!tournament){
        return;
    }
    free(tournament->tournament_location);
    mapDestroy(tournament->tournament_games);
    mapDestroy(tournament->games_counter_of_players);
    free(tournament);
}

int tournamentGetID(ChessTournament tournament){
    if(!tournament){
        return BAD_INPUT;
    }
    return tournament->tournament_id;
}

int tournamentGetMaxGamesPerPlayer(ChessTournament tournament){
    if(!tournament){
        return BAD_INPUT;
    }
    return tournament->max_games_per_player;
}

Map tournamentGetGames(ChessTournament tournament){
    if(!tournament){
        return NULL;
    }
    return tournament->tournament_games;
}

Map tournamentGetGamesCounterOfPlayers(ChessTournament tournament){
    if(!tournament){
        return NULL;
    }
    return tournament->games_counter_of_players;
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
    return tournament->tournament_winner_player_id != NO_PLAYER_ID;
}

int tournamentCountLosingGames(ChessTournament tournament, char* player_id){
    if(!tournament){
        return BAD_INPUT;
    }
    return 0;
}
/**
 * tournamentAddGame: Add a game into tournament.
 *  Do:
 *  1. Check argument validity
 *  2. Add game into tournament_games
 *  3. Update games_counter_of_players
 *  4. Check if a player exceeded max_games_per_player, raise an error accordingly.
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
    if(result != MAP_SUCCESS){
        return CHESS_OUT_OF_MEMORY;
    }
    int player1_id = playerIDGetIntID(gameGetPlayer1ID(game));
    int player2_id = playerIDGetIntID(gameGetPlayer2ID(game));
    int* player1_game_counter = mapGet(tournament->games_counter_of_players, &player1_id);
    int* player2_game_counter = mapGet(tournament->games_counter_of_players, &player2_id);
    // If player is new in tournament - update in games_counter_of_players Map.
    if (!player1_game_counter){
        int new_player_counter = 0;
        mapPut(tournament->games_counter_of_players, &player1_id, &new_player_counter);
        player1_game_counter = mapGet(tournament->games_counter_of_players, &player1_id);
    }
    if (!player2_game_counter){
        int new_player_counter = 0;
        mapPut(tournament->games_counter_of_players, &player2_id, &new_player_counter);
        player2_game_counter = mapGet(tournament->games_counter_of_players, &player2_id);
    }

    (*player1_game_counter)++;
    (*player2_game_counter)++;
    if (*player1_game_counter > tournament->max_games_per_player ||
        *player2_game_counter > tournament->max_games_per_player){
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
    Map players_rank = generatePlayersRank(tournament);
    if(!players_rank){
        return CHESS_OUT_OF_MEMORY;
    }
    // Find max rank
    int max_rank=0;
    MAP_FOREACH(int*,player_int_id_ptr,players_rank){
        int* current_player_rank_ptr = mapGet(players_rank, player_int_id_ptr);
        if(*(current_player_rank_ptr) > max_rank){
            max_rank = *(current_player_rank_ptr);
        }
        free(player_int_id_ptr);
    }
    // Find all players have max score
    Map players_have_max_rank = mapCopy(players_rank);
    if(!players_have_max_rank){
        return CHESS_OUT_OF_MEMORY;
    }
    mapClear(players_have_max_rank);
    MAP_FOREACH(int*,player_int_id_ptr,players_rank){
        int* current_player_rank = (int*)mapGet(players_rank,player_int_id_ptr);
        if(*(current_player_rank) == max_rank){
            int player_win_games_counter = countWinGamesForPlayer(tournament, *(player_int_id_ptr));
            mapPut(players_have_max_rank, player_int_id_ptr, &player_win_games_counter);
        }
        free(player_int_id_ptr);
    }
    // In a case of a single player has max rank
    if(mapGetSize(players_have_max_rank) == 1){
        tournament->tournament_winner_player_id = *(int*)mapGetFirst(players_have_max_rank);
        return CHESS_SUCCESS;
    }
    // Else, there are multiple players have max score. Continue calculating max_win_games among players have max score
    // Find max win_games
    int max_win_games = 0;
    Map players_win_games = mapCopy(players_have_max_rank);
    if(!players_win_games){
        return CHESS_OUT_OF_MEMORY;
    }
    MAP_FOREACH(int*, player_int_id_ptr, players_win_games){
        int player_win_games = *(int*)mapGet(players_win_games, player_int_id_ptr);
        if(player_win_games > max_win_games){
            max_win_games = player_win_games;
        }
        free(player_int_id_ptr);
    }
    // Find all players have max_win_games
    Map max_win_games_players = mapCopy(players_win_games);
    if(!max_win_games_players){
        return CHESS_OUT_OF_MEMORY;
    }
    mapClear(max_win_games_players);
    MAP_FOREACH(int*, player_int_id_ptr, players_win_games){
        int* player_win_games_ptr = mapGet(players_win_games, player_int_id_ptr);
        if (*player_win_games_ptr == max_win_games){
            int player_lost_games_counter = countLostGamesForPlayer(tournament, *(player_int_id_ptr));
            mapPut(max_win_games_players, player_int_id_ptr, &player_lost_games_counter);
        }
        free(player_int_id_ptr);
    }
    // In a case of a single player has max win_games
    if(mapGetSize(players_win_games) == 1){
        tournament->tournament_winner_player_id = *(int*)mapGetFirst(max_win_games_players);
        return CHESS_SUCCESS;
    }
    // Else, there are multiple players have max win_games, compare min lost_games among those players.
    // Find min lost_games
    Map players_lost_games = mapCopy(max_win_games_players);
    if (!players_lost_games){
        return CHESS_OUT_OF_MEMORY;
    }
    int min_lost_games = *(int*)(mapGet(max_win_games_players, mapGetFirst(players_lost_games)));
    MAP_FOREACH(int*, player_int_id_ptr, players_win_games){
        int player_win_games = *(int*)mapGet(players_lost_games, player_int_id_ptr);
        if(player_win_games < min_lost_games){
            max_win_games = player_win_games;
        }
        free(player_int_id_ptr);
    }
    // Find all players have min lost_games
    Map min_players_lost_games = mapCopy(players_lost_games);
    if(!min_players_lost_games){
        return CHESS_OUT_OF_MEMORY;
    }
    mapClear(min_players_lost_games);
    MAP_FOREACH(int*, player_int_id_ptr, players_lost_games){
        int player_lost_games = *(int*)mapGet(players_lost_games, player_int_id_ptr);
        if (player_lost_games == max_win_games){
            mapPut(min_players_lost_games, player_int_id_ptr,0);
        }
        free(player_int_id_ptr);
    }
    // If there is a single player has min lost games, it will be the mapGetFirst (map length equals one), else
    // returns the min player_id, which is the mapGetFirst either due to map default ASC sort by key.
    tournament->tournament_winner_player_id = *(int*)mapGetFirst(min_players_lost_games);
    return CHESS_SUCCESS;
}

static bool locationIsValid(const char* tournament_name){
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

static Map generatePlayersRank(ChessTournament tournament){
    Map players_rank = mapCopy(tournamentGetGamesCounterOfPlayers(tournament));
    if (!players_rank) {
        return NULL;
    }
    MAP_FOREACH(int*, player_int_id_ptr, players_rank) {
        MapResult result = mapPut(players_rank, player_int_id_ptr, 0);
        if (!result) {
            return NULL;
        }
        free(player_int_id_ptr);
    }
    MAP_FOREACH(char*, current_game_id, tournament->tournament_games) {
        ChessGame current_game = mapGet(tournament->tournament_games, current_game_id);
        int player1_int_id = playerIDGetIntID(gameGetPlayer1ID(current_game));
        int player2_int_id = playerIDGetIntID(gameGetPlayer2ID(current_game));
        int* player1_rank_ptr = mapGet(players_rank,&player1_int_id);
        int* player2_rank_ptr = mapGet(players_rank,&player2_int_id);

        if (gameGetWinner(current_game) == FIRST_PLAYER){
            *player1_rank_ptr = *player1_rank_ptr + WIN_GAME_SCORE;
        }
        if (gameGetWinner(current_game) == SECOND_PLAYER){
            *player2_rank_ptr = *player2_rank_ptr + WIN_GAME_SCORE;
        }
        else{
            *player1_rank_ptr = *player1_rank_ptr + DRAW_GAME_SCORE;
            *player2_rank_ptr = *player2_rank_ptr + DRAW_GAME_SCORE;
        }
        free(current_game_id);
    }
    return players_rank;
}

static int countWinGamesForPlayer(ChessTournament tournament, int player_int_id){
    int win_games_counter = 0;
    MAP_FOREACH(char*,game_id,tournament->tournament_games){
        ChessGame game = mapGet(tournament->tournament_games,game_id);
        if ((playerIDGetIntID(gameGetPlayer1ID(game)) == player_int_id && (gameGetWinner(game) == FIRST_PLAYER)) ||
                (playerIDGetIntID(gameGetPlayer2ID(game)) == player_int_id && (gameGetWinner(game) == SECOND_PLAYER))){
            win_games_counter++;
        }
        free(game_id);
    }
    return win_games_counter;
}

static int countLostGamesForPlayer(ChessTournament tournament, int player_int_id){
    int lost_games_counter = 0;
    MAP_FOREACH(ChessGame,game,tournament->tournament_games){
        if ((playerIDGetIntID(gameGetPlayer1ID(game)) == player_int_id && (gameGetWinner(game) == SECOND_PLAYER)) ||
            (playerIDGetIntID(gameGetPlayer2ID(game)) == player_int_id && (gameGetWinner(game) == FIRST_PLAYER))){
            lost_games_counter++;
        }
        gameDestroy(game);
    }
    return lost_games_counter;
}

void tournamentRemovePlayer(ChessTournament tournament, PlayerID player_id){
    if(!tournament || !player_id){
        return;
    }
    return;
}

int tournamentGetWinnerID(ChessTournament tournament){
    if(!tournament){
        return BAD_INPUT;
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
    return mapGetSize(tournament->games_counter_of_players);
}
