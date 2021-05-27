#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chessGame.h"
#include "chessSystem.h"
#include "chessPlayer.h"

#define SEP "-"
#define SEP_CHAR '-'
#define BAD_INPUT -1
#define MORE_LENGTH 3
#define LENGTH_OF_ZERO_STRING 2

struct chess_game_t{
    char* id;
    unsigned int tournament_id;
    Player player1;
    Player player2;
    int play_time;
    Winner game_winner;
};


//TODO: ELIMINATE CODE DUPLICATION OF THE FOUR FOLLOWING FUNCTIONS
static inline void nullifyString(char* str, size_t size){
    assert(str != NULL);
    memset(str, '\0', size);
}

static inline char castDigitToChar(int digit) {
    assert(digit >= 0 && digit <= 9);
    char converted = (char)(digit + '0');
    return converted;
}

static char* castIntToString(unsigned int num){
    if(num == 0){
        char* str=malloc(LENGTH_OF_ZERO_STRING);
        if (str == NULL){
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


char* createGameID(unsigned int player1_id, unsigned int player2_id, unsigned int tournament){
    if(player1_id<0 || player2_id<0 || tournament<0 || player1_id == player2_id){
        return NULL;
    }
    char *id1, *id2;
    if(player1_id<player2_id){
        id1 = castIntToString(player1_id);
        id2 = castIntToString(player2_id);
    }
    else{
        id1 = castIntToString(player2_id);
        id2 = castIntToString(player1_id);
    }
    char* tournament_id_str= castIntToString(tournament) ;
    int len1, len2, len3;
    len1=strlen(id1);
    len2=strlen(id2);
    len3=strlen(tournament_id_str);
    int id_size = len1+len2+len3+MORE_LENGTH;
    char* game_id = malloc(id_size);
    if(!game_id){
        free(tournament_id_str);
        return NULL;
    }
    nullifyString(game_id,id_size);
    game_id = strcat(game_id,tournament_id_str);
    game_id = strcat(game_id,SEP);
    game_id = strcat(game_id, id1);
    game_id = strcat(game_id,SEP);
    game_id = strcat(game_id,id2);
    free(id1);
    free(id2);
    free(tournament_id_str);
    return game_id;
}

ChessGame chessGameCreate(unsigned int tournament_id, Player player1, Player player2, int play_time, Winner winner){
    if(tournament_id <=0|| !player1 || !player2 || play_time<0 || (winner!=FIRST_PLAYER && winner!=SECOND_PLAYER )){
        return NULL;
    }
    if(playerGetID(player1) == playerGetID(player2)){
        return NULL;
    }
    ChessGame result = malloc(sizeof (*result));
    if (!result){
        return NULL;
    }
    result->game_winner = winner;
    result->play_time =  play_time;
    result-> tournament_id = tournament_id;
    result->player1 = playerCopy(player1);
    result->player2 = playerCopy(player2);
    char* game_id = createGameID(playerGetID(player1), playerGetID(player2), tournament_id);
    if(!game_id){
        free(result);
        return NULL;
    }
    result->id = game_id;
    PlayerResult res = playerAddGame(player1, result);
    if(res!=PLAYER_SUCCESS){
        free(game_id);
        chessGameDestroy(result);
        return NULL;
    }
    playerAddGame(player1, result);
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
    new_game->player1 = playerCopy(game->player1);
    new_game->player2 = playerCopy(game->player2);
    new_game->tournament_id = game->tournament_id;
    new_game->play_time = game->play_time;
    new_game->game_winner = game->game_winner;
    int len_of_id = strlen(game->id);
    char* id_copy = malloc(len_of_id+1);
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
    playerDestroy(game->player1);
    playerDestroy(game->player2);
    free(game->id);
    free(game);
}

char* getChessGameID(ChessGame chessGame){
    if(!chessGame){
        return NULL;
    }
    return chessGame->id;
}

Player chessGameGetPlayer1(ChessGame game){
    if(!game){
        return NULL;
    }
    return game->player1;
}

Player chessGameGetPlayer2(ChessGame game){
    if(!game){
        return NULL;
    }
    return game->player2;
}

char* chessGameGetID(ChessGame game){
    if(!game){
        return NULL;
    }
    return game->id;
}

Winner chessGameGetWinner(ChessGame game){
    if(!game){
        return BAD_INPUT;
    }
    return game->game_winner;
}
//static GameResult getIDsFromGameID(char* game_id, int* id1, int* id2){
//    if(!game_id || !id1 || !id2){
//        return GAME_NULL_ARGUMENT;
//    }
//    int size = strlen(game_id);
//    char* id1_str = malloc(size);
//    if(!id1_str){
//        return GAME_OUT_OF_MEMORY;
//    }
//    char* id2_str = malloc(size);
//    if(!id2_str){
//        free(id1_str);
//        return GAME_OUT_OF_MEMORY;
//    }
//    nullifyString(id1_str, size);
//    nullifyString(id2_str, size);
//    int id2_flag = 0;
//    for(int i=0;i<size;i++){
//        if(game_id[i]==SEP_CHAR){
//            id2_flag++;
//            continue;
//        }
//        if(id2_flag>1){
//            break;
//        }
//        if(!id2_flag){
//            strcat(id1_str,game_id[i]);
//        }
//        strcat(id2_str,game_id[i]);
//    }
//    *id1 = atoi(id1_str);
//    *id2 = atoi(id2_str);
//    free(id1_str);
//    free(id2_str);
//}

void chessGameSetWinner(ChessGame game, Winner winner){
    if(!game || (winner!= FIRST_PLAYER && winner!= SECOND_PLAYER)){
        return;
    }
    game->game_winner = winner;
}

//GameResult chessGameUpdateLoser(char* game_id, Player player){
//    if(!game_id || !player){
//        return GAME_NULL_ARGUMENT;
//    }
//    int loser_id = playerGetID(player);
//    int* id1, *id2;
//    getIDsFromGameID(game_id, id1, id2);
//    if(*id1 != loser_id && *id2 != loser_id){
//        return GAME_PLAYER_NOT_EXIST;
//    }
//    ChessGame game = mapGet(playerGetGames(player),game_id);
//    if(!game){
//        return GAME_OUT_OF_MEMORY;
//    }
//    if(*id1 == loser_id){
//        game->game_winner = SECOND_PLAYER;
//    }
//    else{
//        game->game_winner = FIRST_PLAYER;
//    }
//    return GAME_SUCCESS;
//}