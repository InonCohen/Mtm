#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "chessGame.h"
#include "chessSystem.h"

#define SEP "-"
#define BAD_INPUT -1
#define BAD_KEY -1
#define MORE_LENGTH 3
#define LENGTH_OF_ZERO_STRING 2

struct chess_game_t{
    char* id;
    unsigned int tournament_id;
    unsigned int player1;
    unsigned int player2;
    int play_time;
    Winner game_winner;
};

static inline void nullifyString(char* str, size_t size){
    assert(str != NULL);
    memset(str, '\0', size);
}

static inline char castDigitToChar(int digit) {
    assert(digit >= 0 && digit <= 9);
    char converted = (char)(digit + '0');
    return converted;
}

static char* castIntToString(int num){
    if(num==0){
        char* str=malloc(LENGTH_OF_ZERO_STRING);
        if (str==NULL){
            return NULL;
        }
        str[0]='0';
        str[1]='\0';
        return str;
    }
    int numCopy=num, count=0;
    while (numCopy){//count the number of digits
        count++;
        numCopy/=10;
    }
    char* str=(char*)malloc((count) + 1);//+1 is for the '\0'
    if (str==NULL){
        return NULL;
    }
    nullifyString(str,count+1);
    for(int i=count-1;i>=0;i--){
        str[i]= castDigitToChar(num % 10);
        num/=10;
    }
    return str;
}


static char* createGameID(unsigned int player1, unsigned int player2, unsigned int tournament_id){
    if(!player1 || !player2 || !tournament_id){
        return NULL;
    }
    char* id1 = castIntToString((int) player1);
    char* id2 = castIntToString((int) player2);
    char* tournament_id_str= castIntToString((int) tournament_id) ;
    unsigned long len1, len2, len3;
    len1=strlen(id1);
    len2=strlen(id2);
    len3=strlen(tournament_id_str);
    char* game_id = malloc(len1 + len2 + len3 + MORE_LENGTH);
    if(!game_id){
        return NULL;
    }
    game_id = strcat(game_id,tournament_id_str);
    game_id = strcat(game_id,SEP);
    game_id = strcat(game_id,(player1<player2)? id1: id2);
    game_id = strcat(game_id,SEP);
    game_id = strcat(game_id,(player1<player2)? id2: id1);
    return game_id;
}

ChessGame chessGameCreate(unsigned int tournament_id, unsigned int player1, unsigned int player2,
                          int play_time, Winner winner){
    if(tournament_id<=0||player1<=0||player2 <=0||play_time<0||(winner!=FIRST_PLAYER && winner!=SECOND_PLAYER)){
        return NULL;
    }
    if(player1 == player2){
        return NULL;
    }
    ChessGame result = malloc(sizeof (*result));
    if (!result){
        return NULL;
    }
    result->game_winner = winner;
    result->play_time =  play_time;
    result-> tournament_id = tournament_id;
    result->player1 = player1;
    result->player2 = player2;
    char* game_id = createGameID(player1, player2, tournament_id);
    result->id = game_id;
    return result;
}

ChessGame chessGameCopy(ChessGame game){
    if(game == NULL){
        return NULL;
    }
    ChessGame new_game = malloc(sizeof (*new_game));
    if (new_game == NULL) {
        return NULL;
    }
    new_game->player1 = game->player1;
    new_game->player2 = game->player2;
    new_game->tournament_id = game->tournament_id;
    new_game->play_time = game->play_time;
    new_game->game_winner = game->game_winner;
    unsigned long len_of_id = strlen(game->id);
    char* id_copy = malloc(len_of_id + 1);
    if(!id_copy){
        free(new_game);
        return NULL;
    }

    strcpy(id_copy, game->id);
    new_game->id = id_copy;
    return new_game;
}

void chessGameDestroy(ChessGame game){
    if(!game){
        return;
    }
    free(game);
}

char* getChessGameID(ChessGame chessGame){
    if(!chessGame){
        return NULL;
    }
    return chessGame->id;
}

void freeInt(void* to_free){
    free(to_free);
}

void freeString(void* to_free){
    free((char*)to_free);
}


int compareStrings (char* str1, char* str2){
    if(str1 == NULL || str2 == NULL){
        return BAD_KEY;
    }
    return strcmp(str1, str2);
}

void* copyInt (void* to_copy){
    if(to_copy == NULL){
        return NULL;
    }
    int* new_int = malloc(sizeof(int));
    if(!new_int){
        return NULL;
    }
    new_int = ((int*)to_copy);
    return new_int;
}

int compareInts (void* int1, void* int2){
    if(int1 == NULL || int2 == NULL){
        return BAD_KEY;
    }
    return ((int)int1 - (int)int2);
}