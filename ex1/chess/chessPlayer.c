#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../map/map.h"
#include "chessDefs.h"
#include "chessGameMap.h"
#include "chessGame.h"
#include "chessPlayer.h"


struct chess_player_t{
    char* id;
    Map games;//keys: char*, data: chessGame
    int wins;
    int losses;
    int draws;
    int level;
    int total_time;
    bool is_deleted;
};


ChessPlayer playerCreate(char* id){
    ChessPlayer new_player = malloc(sizeof(*new_player));
    if(!new_player){
        return NULL;
    }
    Map games = mapCreate(gamesMapCopyData, mapCopyStringKey, gamesMapFreeData, mapFreeStringKey,
                        mapCompareStringKeys);
    if(!games){
        free(new_player);
        return NULL;
    }
    int id_length = strlen(id);
    new_player->id = malloc(id_length+1);
    if(!new_player->id){
        mapDestroy(games);
        free(new_player);
        return NULL;
    }
    strcpy(new_player->id, id);
    new_player->games = games;
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
    free(player->id);
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
    int id_length = strlen(player->id);
    player_copy->id = malloc(id_length+1);
    if(!player_copy->id){
        mapDestroy(player->games);
        free(player_copy);
        return NULL;
    }
    strcpy(player_copy->id,player->id);
    player_copy->wins = player->wins;
    player_copy->losses = player->losses;
    player_copy->draws = player->draws;
    player_copy->level = player->level;
    player_copy->total_time = player->total_time;
    player_copy->is_deleted = player->is_deleted;
    return player_copy;
}

char* playerGetID(ChessPlayer player){
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
int playerGetLevel(ChessPlayer player){
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
