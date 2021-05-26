#include <stdio.h>
#include <stdlib.h>
#include "chessPlayer.h"
#include "chessDefs.h"
#include "map.h"
#include "chessGame.h"

#define BAD_INPUT -1


struct chess_player_t{
    int ID;
    Map games;//keys: int tourIDopponentID, data: chessGame
    int wins;
    int losses;
    int draws;
    int level;
    int total_time;
};

void gamesMapKeyDestroy(void* to_free){
    if(to_free == NULL){
        return;
    }
    chessGameDestroy(*(ChessGame*)to_free);
}

void gamesMapDataDestroy(void* to_free){
    free(to_free);
}

void* gamesMapKeyCopy (void* to_copy){
    if(to_copy == NULL){
        return NULL;
    }
    int* new_int = malloc(sizeof(int));
    if(!new_int){
        return NULL;
    }
    *new_int = (*(int*)to_copy);
    return new_int;
}

void* gamesMapDataCopy (void* to_copy) {
    if(to_copy == NULL){
        return NULL;
    }
    ChessGame copy = chessGameCopy(*(ChessGame*)to_copy);
    if(!copy){
        return NULL;
    }
    return (void*)copy;
}

int compareGamesMapKeys (void* int1, void* int2){
    if(int1 == NULL || int2 == NULL){
        return BAD_INPUT;
    }
    return (*(int*)int1 - *(int*)int2);
}

Player playerCreate(int id){
    Player new_player = malloc(sizeof(*new_player));
    if(!new_player){
        return NULL;
    }
    Map map = mapCreate(gamesMapDataCopy, gamesMapKeyCopy, gamesMapDataDestroy, gamesMapKeyDestroy, compareGamesMapKeys);
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

void playerDestroy(Player player){
    if(!player){
        return;
    }
    if(player->games){
        mapDestroy(player->games);
    }
    free(player);
}

Player playerCopy(Player player){
    if(!player){
        return NULL;
    }
    Player copy = malloc(sizeof(*copy));
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

int playerGetID(Player player){
    if(!player){
        return BAD_INPUT;
    }
    return player->ID;
}
int playerGetPlayingTime(Player player){
    if(!player){
        return BAD_INPUT;
    }
    return player->total_time;
}
int playerGetLevel(Player player){
    if(!player){
        return BAD_INPUT;
    }
    return player->level;
}
Map playerGetGames(Player player){
    if(!player){
        return NULL;
    }
    return player->games;
}
int playerGetNumOfGames(Player player){
    if(!player){
        return BAD_INPUT;
    }
    if(!player->games){
        return 0;
    }
    return mapGetSize(player->games);
}
int playerGetNumOfWins(Player player){
    if(!player){
        return BAD_INPUT;
    }
    return player->wins;
}
int playerGetNumOfLosses(Player player){
    if(!player){
        return BAD_INPUT;
    }
    return player->losses;
}
int playerGetNumOfDraws(Player player){
    if(!player){
        return BAD_INPUT;
    }
    return player->draws;
}
