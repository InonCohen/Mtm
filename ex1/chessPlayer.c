#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "chessDefs.h"
#include "chessGameMap.h"
#include "chessGame.h"
#include "chessPlayer.h"


struct chess_player_t{
    int ID;
    int wins;
    int losses;
    int draws;
    int level;
    int total_time;
    Map games;//keys: int, data: chessGame
};


ChessPlayer playerCreate(int id){
    ChessPlayer new_player = malloc(sizeof(*new_player));
    if(!new_player){
        return NULL;
    }
    Map map = mapCreate(gamesMapCopyData, mapCopyStringKey, gamesMapFreeData, mapFreeStringKey,
                        mapCompareStringKeys);
    if(!map){
        free (new_player);
        return NULL;
    }
    new_player->ID = id;
    new_player->wins = 0;
    new_player->losses = 0;
    new_player->draws = 0;
    new_player->level = 0;
    new_player->total_time = 0;
    return new_player;
}

void playerDestroy(ChessPlayer player){
    if(!player){
        return;
    }
    if(player->games){
        mapDestroy(player->games);
    }
    free(player);
}

ChessPlayer playerCopy(ChessPlayer player){
    if(!player){
        return NULL;
    }
    ChessPlayer copy = malloc(sizeof(*copy));
    if(!copy){
        return NULL;
    }
    if(!player->games){
        copy->games = mapCopy(player->games);
        if(!copy->games){
            free(copy);
            return NULL;
        }
    }
    copy->ID = player->ID;
    copy->wins = player->wins;
    copy->losses = player->losses;
    copy->draws = player->draws;
    copy->level = player->level;
    player->total_time = player->total_time;
    return copy;
}

int playerGetID(ChessPlayer player){
    if(!player){
        return BAD_INPUT;
    }
    return player->ID;
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
