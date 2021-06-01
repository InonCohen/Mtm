#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../map/map.h"
#include "chessMapUtils.h"
#include "chessGame.h"
#include "chessPlayer.h"
#include "chessPlayerID.h"

#define WIN_WEIGHT 6
#define LOSE_WEIGHT (-10)
#define DRAW_WEIGHT 2
#define ADD '+'
#define REMOVE '-'

struct chess_player_t{
    PlayerID id;
    Map games;//keys: char*, data: chessGame
    int wins;
    int losses;
    int draws;
    double level;
    int total_time;
    bool is_deleted;
};


/**
 * playerUpdateWin: updates the player's statistics according to given game that is already in player's games map
 *
 * @param player - player whose statistics are to be updated to either add or remove a draw
 * @param game - game of which the player is the tier
 * @param sign - a char signing whether the game is the draw is to be added or removed
 */
static void playerUpdateWin(ChessPlayer player, ChessGame game, char sign);

/**
 * playerUpdateLose: updates the player's statistics according to given game that is already in player's games map
 *
 * @param player - player whose statistics are to be updated to either add or remove a lose
 * @param game - game of which the player is the loser
 * @param sign - a char signing whether the game is the lose is to be added or removed
 */
static void playerUpdateLose(ChessPlayer player, ChessGame game, char sign);

/**
 * playerUpdateDraw: updates the player's statistics according to given game that is already in player's games map
 *
 * @param player - player whose statistics are to be updated to either add or remove a draw
 * @param game - game of which the player is the tier
 * @param sign - a char signing whether the game is the draw is to be added or removed
 */
static void playerUpdateDraw(ChessPlayer player, ChessGame game, char sign);

ChessPlayer playerCreate(PlayerID id){
    ChessPlayer new_player = malloc(sizeof(*new_player));
    if(!new_player){
        return NULL;
    }
    new_player->id = playerIDCopy(id);{
        if(!new_player->id){
            free(new_player);
            return NULL;
        }
    }
    new_player->games = mapCreate(gamesMapCopyData, stringCopyFunc, gamesMapFreeData, mapFreeStringKey,
                        mapCompareStringKeys);
    if(!new_player->games){
        playerIDDestroy(new_player->id);
        free(new_player);
        return NULL;
    }
    if(!new_player->id){
        playerIDDestroy(new_player->id);
        mapDestroy(new_player->games);
        free(new_player);
        return NULL;
    }
    new_player->wins = 0;
    new_player->losses = 0;
    new_player->draws = 0;
    new_player->level = 0;
    new_player->total_time = 0;
    new_player->is_deleted = false;
    return new_player;
}

void playerDestroy(ChessPlayer player){
    if(!player){
        return;
    }
    if(player->games){
        mapDestroy(player->games);
    }
    if(player->id){
        playerIDDestroy(player->id);
    }
    free(player);
}

ChessPlayer playerCopy(ChessPlayer player){
    if(!player){
        return NULL;
    }
    ChessPlayer player_copy = malloc(sizeof(*player_copy));
    if(!player_copy){
        return NULL;
    }
    if(player->games){
        player_copy->games = mapCopy(player->games);
        if(!player_copy->games){
            playerDestroy(player_copy);
            return NULL;
        }
    }
    player_copy->id = playerIDCopy(player->id);
    if(!player_copy->id){
        mapDestroy(player->games);
        playerDestroy(player_copy);
        return NULL;
    }
    player_copy->wins = player->wins;
    player_copy->losses = player->losses;
    player_copy->draws = player->draws;
    player_copy->level = player->level;
    player_copy->total_time = player->total_time;
    player_copy->is_deleted = player->is_deleted;
    return player_copy;
}

PlayerID playerGetID(ChessPlayer player){
    if(!player){
        return NULL;
    }
    return player->id;
}

int playerGetPlayingTime(ChessPlayer player){
    if(!player){
        return BAD_INPUT;
    }
    return player->total_time;
}

double playerGetLevel(ChessPlayer player){
    if(!player){
        return BAD_INPUT;
    }
    return player->level;
}

Map playerGetGames(ChessPlayer player){
    if(!player){
        return NULL;
    }
    return player->games;
}

int playerGetNumOfGames(ChessPlayer player){
    if(!player){
        return BAD_INPUT;
    }
    if(!player->games){
        return 0;
    }
    return mapGetSize(player->games);
}

int playerGetNumOfWins(ChessPlayer player){
    if(!player){
        return BAD_INPUT;
    }
    return player->wins;
}

int playerGetNumOfLosses(ChessPlayer player){
    if(!player){
        return BAD_INPUT;
    }
    return player->losses;
}

int playerGetNumOfDraws(ChessPlayer player){
    if(!player){
        return BAD_INPUT;
    }
    return player->draws;
}

bool playerIsDeleted(ChessPlayer player){
    if(!player){
        return true;
    }
    return player->is_deleted;
}

PlayerResult playerAddGame(ChessPlayer player, ChessGame game){
    if(!player || !game){
        return PLAYER_NULL_ARGUMENT;
    }
    Map games = player->games;
    if(mapContains(games, gameGetID(game))){
        return PLAYER_GAME_ALREADY_EXISTS;
    }
    PlayerID game_player1 = gameGetPlayer1ID(game);
    PlayerID game_player2 = gameGetPlayer2ID(game);
    char* id1 = playerIDGetFullID(game_player1);
    char* id2 = playerIDGetFullID(game_player2);
    char* player_id = playerIDGetFullID(playerGetID(player));
    if(strcmp(id1, player_id) != 0 && strcmp(id2, player_id) != 0) {
        return PLAYER_INVALID_ID;
    }
    MapResult result = mapPut(games, gameGetID(game), game);
    if(result == MAP_OUT_OF_MEMORY){
        return PLAYER_OUT_OF_MEMORY;
    }
    if(gameGetWinner(game) == DRAW){
        playerAddDraw(player, game);
    }
    else if(gameGetWinner(game)==FIRST_PLAYER){
        if(strcmp(id1, player_id) == 0){
            playerAddWin(player, game);
        }
        else{
            playerAddLose(player, game);
        }
    }
    else{
        if(strcmp(id1, player_id) == 0){
            playerAddLose(player, game);
        }
        else{
            playerAddWin(player, game);
        }
    }
    return PLAYER_SUCCESS;
}

PlayerResult playerRemoveGame(ChessPlayer player, ChessGame game){
    if(!player || !game){
        return PLAYER_NULL_ARGUMENT;
    }
    Map games = player->games;
    if(!mapContains(games, gameGetID(game))){
        return PLAYER_SUCCESS;
    }
    MapResult res = mapRemove(games, gameGetID(game));
    if(res != MAP_SUCCESS){
        return PLAYER_OUT_OF_MEMORY;
    }
    Winner game_winner = gameGetWinner(game);
    if(game_winner == DRAW){
        playerRemoveDraw(player, game);
    }
    else{
        PlayerID game_player1 = gameGetPlayer1ID(game);
        char* id1 = playerIDGetFullID(game_player1);
        char* player_id = playerIDGetFullID(playerGetID(player));
        if(game_winner == FIRST_PLAYER){
            if(strcmp(id1, player_id) == 0){
                playerRemoveWin(player, game);
            }
            else{
                playerRemoveLose(player, game);
            }
        }
        else{
            if(strcmp(id1, player_id) == 0){
                playerRemoveLose(player, game);
            }
            else{
                playerRemoveWin(player, game);
            }
        }
    }
    return PLAYER_SUCCESS;
}

void playerUpdateLevel(ChessPlayer player){
    if(!player){
        return;
    }
    int total_games = mapGetSize(player->games);
    if(total_games == 0){
        player->level = 0;
        return;
    }
    int player_score = WIN_WEIGHT*player->wins+LOSE_WEIGHT*player->losses+DRAW_WEIGHT*player->draws;
    player->level = (double)player_score/(double)total_games;
}

void playerUpdateAccordingToGame(ChessPlayer player, GamePlayerOutcome old_outcome, GamePlayerOutcome new_outcome) {
    if (!player) {
        return;
    }
    if (old_outcome == new_outcome) {
        return;
    }
    if (new_outcome == WINNER) {
        if (old_outcome == LOSER) {
            player->losses--;
        }
        else{
            player->draws--;
        }
        player->wins++;
    }
    else if(new_outcome == LOSER){
        if(old_outcome == WINNER){
            player->wins--;
        }
        else{
            player->draws--;
        }
        player->losses++;
    }
    else{
        if(old_outcome == WINNER){
            player->wins--;
        }
        else{
            player->losses--;
        }
        player->draws++;
    }
    playerUpdateLevel(player);
}

void playerSetIsDeleted(ChessPlayer player){
    if(!player){
        return;
    }
    player->is_deleted = true;
}

void playerAddWin(ChessPlayer player, ChessGame game){
    playerUpdateWin(player, game, ADD);
}

void playerRemoveWin(ChessPlayer player, ChessGame game){
    playerUpdateWin(player, game, REMOVE);

}

void playerAddLose(ChessPlayer player, ChessGame game){
    playerUpdateLose(player, game, ADD);
}

void playerRemoveLose(ChessPlayer player, ChessGame game){
    playerUpdateLose(player, game, REMOVE);
}

void playerAddDraw(ChessPlayer player, ChessGame game){
    playerUpdateDraw(player, game, ADD);
}

void playerRemoveDraw(ChessPlayer player, ChessGame game){
    playerUpdateDraw(player, game, REMOVE);
}

static void playerUpdateWin(ChessPlayer player, ChessGame game, char sign){
    if(!player || !game){
        return;
    }
    if(playerIsDeleted(player)){
        return;
    }
    int play_time = gameGetPlayTime(game);
    if(sign == REMOVE) {
        if (player->wins > 0) {
            player->wins--;
        }
        if(player->total_time >= play_time){
            player->total_time-=play_time;
        }
        else{
            player->total_time = 0;
        }
    }
    else {
        player->wins++;
        player->total_time += play_time;
    }
    playerUpdateLevel(player);
}

static void playerUpdateLose(ChessPlayer player, ChessGame game, char sign){
    if(!player || !game){
        return;
    }
    if(playerIsDeleted(player)){
        return;
    }
    int play_time = gameGetPlayTime(game);
    if(sign == REMOVE) {
        if (player->losses > 0) {
            player->losses--;
        }
        if(player->total_time >= play_time){
            player->total_time-=play_time;
        }
        else{
            player->total_time = 0;
        }
    }
    else {
        player->losses++;
        player->total_time += play_time;
    }
    playerUpdateLevel(player);
}

static void playerUpdateDraw(ChessPlayer player, ChessGame game, char sign){
    if(!player || !game){
        return;
    }
    if(playerIsDeleted(player)){
        return;
    }
    int play_time = gameGetPlayTime(game);
    if(sign == REMOVE) {
        if (player->draws > 0) {
            player->draws--;
        }
        if(player->total_time >= play_time){
            player->total_time-=play_time;
        }
        else{
            player->total_time = 0;
        }
    }
    else {
        player->draws++;
        player->total_time += play_time;
    }
    playerUpdateLevel(player);
}

