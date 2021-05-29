#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../map/map.h"
#include "chessDefs.h"
#include "chessMapUtils.h"
#include "chessGame.h"
#include "chessPlayer.h"
#include "chessPlayerID.h"

#define WIN_WEIGHT 6
#define LOSE_WEIGHT (-10)
#define DRAW_WEIGHT 2

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
    new_player->games = mapCreate(gamesMapCopyData, mapCopyStringKey, gamesMapFreeData, mapFreeStringKey,
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
            free(player_copy);
            return NULL;
        }
    }
    player_copy->id = playerIDCopy(player->id);
    if(!player_copy->id){
        mapDestroy(player->games);
        free(player_copy);
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

char* playerGetIDString(ChessPlayer player){
    if(!player || !player->id){
        return NULL;
    }
    return playerIDGetFullID(player->id);
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
        return false;
    }
    return player->is_deleted;
}

void updatePlayerLevel(ChessPlayer player){
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

void updatePlayerAccordingToGame(ChessPlayer player, GamePlayerOutcome old_outcome, GamePlayerOutcome new_outcome) {
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
    updatePlayerLevel(player);
}
