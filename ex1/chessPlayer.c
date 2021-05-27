#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "chessPlayer.h"
#include "chessGameCopy.h"


#define BAD_INPUT -1
#define WIN_WEIGHT 6
#define LOSS_WEIGHT -10
#define DRAW_WEIGHT 2
#define LENGTH_OF_ZERO_STRING 2

struct Player_t{
    int ID;
    Map games;//keys: int tourIDopponentID, data: ChessGame
    int wins;
    int losses;
    int draws;
    double level;
    int total_time;
};

  // Functions for maintaining a Map of Games//

  static inline void nullifyString(char* str, size_t size){
      assert(str != NULL);
      memset(str, '\0', size);
  }

static inline char castDigitToChar(int digit) {
    assert(digit >= 0 && digit <= 9);
    char converted = (char)(digit + '0');
    return converted;
}

//static char* castIntToString(unsigned int num){
//    if(num == 0){
//        char* str=malloc(LENGTH_OF_ZERO_STRING);
//        if (str == NULL){
//            return NULL;
//        }
//        str[0]='0';
//        str[1]='\0';
//        return str;
//    }
//    int numCopy=num, count=0;
//    while (numCopy){//count the number of digits
//        count++;
//        numCopy/=10;
//    }
//    char* str=(char*)malloc((count) + 1);//+1 is for the '\0'
//    if (str==NULL){
//        return NULL;
//    }
//    nullifyString(str,count+1);
//    for(int i=count-1;i>=0;i--){
//        str[i]= castDigitToChar(num % 10);
//        num/=10;
//    }
//    return str;
//}

void gamesMapKeyDestroy(void* to_free){
    if(to_free == NULL){
        return;
    }
    free((char*)to_free);
}

void gamesMapDataDestroy(void* to_free){
    if(to_free == NULL){
        return;
    }
    gameDestroy((ChessGame)to_free);
}

void* gamesMapKeyCopy (void* to_copy){
    if(to_copy == NULL){
        return NULL;
    }
    int size=strlen((char*)(to_copy))+1;
    char* new_key = malloc(size);
    if(!new_key){
        return NULL;
    }
    nullifyString(new_key,size);
    strcpy(new_key,(char*)to_copy);
    return new_key;
}

void* gamesMapDataCopy (void* to_copy) {
    if(to_copy == NULL){
        return NULL;
    }
    ChessGame copy = gameCopy((ChessGame)to_copy);
    if(!copy){
        return NULL;
    }
    return (void*)copy;
}

int compareGamesMapKeys (void* key1, void* key2){
    if(key1 == NULL || key2 == NULL){
        return BAD_INPUT;
    }
    return strcmp((char*)key1, (char*)key2);
}
    //End of Map maintenance Functions//

static void playerUpdateLevel(Player player){
    if(!player){
        return;
    }
    int total_games = mapGetSize(player->games);
    int wins = player->wins;
    int losses = player->losses;
    int draws = player->draws;
    assert(total_games == wins + losses + draws);
    int total_score = WIN_WEIGHT*wins + LOSS_WEIGHT*losses + DRAW_WEIGHT*draws;
    double level = (double)total_score/total_games;
    player->level = level;
}

Player playerCreate(int id){
    Player new_player = malloc(sizeof(*new_player));
    if(!new_player){
        return NULL;
    }
    Map games = mapCreate(gamesMapDataCopy, gamesMapKeyCopy, gamesMapDataDestroy, gamesMapKeyDestroy, compareGamesMapKeys);
    if(!games){
        free (new_player);
        return NULL;
    }
    new_player->ID = id;
    new_player->wins = 0;
    new_player->losses = 0;
    new_player->draws = 0;
    new_player->level = 0;
    new_player->total_time = 0;
    new_player->games = games;
    return new_player;
}

void playerDestroy(Player player){
    if(!player){
        return;
    }
//    if(player->games && mapGetSize(player->games)){
//        MAP_FOREACH(char*, iter, player->games){
//            ChessGame temp = mapGet(player->games, iter);
//            Player player1 = gameGetPlayer1(temp);
//            if(playerGetID(player1) == playerGetID(player)){
//                gameSetWinner(temp, SECOND_PLAYER);
//            }
//            else{
//                gameSetWinner(temp, FIRST_PLAYER);
//            }
//            free(iter);
//        }
//        mapDestroy(player->games);
//    }
    free(player);
}

Player playerCopy(Player player){
    if(!player){
        return NULL;
    }
    Player copy = playerCreate(player->ID);
    if(!copy){
        return NULL;
    }

    if(player->games){
        mapDestroy(copy->games);
        copy->games = mapCopy(player->games);
        if(!copy->games){
            free(copy);
            return NULL;
        }
    }
    else{
        copy->games = NULL;
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
double playerGetLevel(Player player){
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

PlayerResult playerAddGame (Player player, ChessGame game){
    if(!player || !game){
        return PLAYER_NULL_ARGUMENT;
    }
    assert(gameGetPlayer1(game) == playerGetID(player) || gameGetPlayer2(game) == playerGetID(player));
    char* game_id = gameGetID(game);
    if(mapContains(player->games, game_id)){
        return PLAYER_GAME_ALREADY_EXISTS;
    }
    MapResult res = mapPut(player->games, game_id, game);
    if(res !=MAP_SUCCESS){
        return PLAYER_OUT_OF_MEMORY;
    }
    Winner game_winner = gameGetWinner(game);
    if(game_winner == DRAW){
        player->draws++;
    }
    else if(game_winner == FIRST_PLAYER){
        if(gameGetPlayer1(game) == playerGetID(player)){
            player->wins++;
        }
        else{
            player->losses++;
        }
    }
    else {
        if(gameGetPlayer2(game) == playerGetID(player)){
            player->wins++;
        }
        else{
            player->losses++;
        }
    }
    playerUpdateLevel(player);
    return PLAYER_SUCCESS;
}