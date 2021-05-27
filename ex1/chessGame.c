#include <stdlib.h>
#include <string.h>
#include "strUtils.h"
#include "chessGame.h"
#include "chessSystem.h"

#define ID_SEP "-"

struct chess_game_t{
    char* id;
    int tournament_id;
    int player1;
    int player2;
    int play_time;
    Winner game_winner;
};

static char* createGameID(int player1, int player2, int tournament_id){
    if(!player1 || !player2 || !tournament_id){
        return NULL;
    }
    char* id1 = castIntToString((int) player1);
    char* id2 = castIntToString((int) player2);
    char* tournament_id_str= castIntToString((int) tournament_id) ;
    int len1, len2, len3;
    len1=(int)strlen(id1);
    len2=(int)strlen(id2);
    len3=(int)strlen(tournament_id_str);
    char* game_id = malloc(len1 + strlen(ID_SEP) + len2  + strlen(ID_SEP) + len3 + 1);
    if(!game_id){
        return NULL;
    }
    game_id = strcat(game_id,tournament_id_str);
    game_id = strcat(game_id, ID_SEP);
    game_id = strcat(game_id,(player1<player2)? id1: id2);
    game_id = strcat(game_id, ID_SEP);
    game_id = strcat(game_id,(player1<player2)? id2: id1);
    return game_id;
}

ChessGame gameCreate(int tournament_id, int player1, int player2,
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
    if(!game_id){
        return NULL;
    }
    result->id = game_id;
    return result;
}

ChessGame gameCopy(ChessGame game){
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
    int len_of_id = (int)strlen(game->id);
    char* id_copy = malloc(len_of_id + 1);
    if(!id_copy){
        free(new_game);
        return NULL;
    }

    strcpy(id_copy, game->id);
    new_game->id = id_copy;
    return new_game;
}

void gameDestroy(ChessGame game){
    if(!game){
        return;
    }
    free(game->id);
    free(game);
}

char* gameGetID(ChessGame chessGame){
    if(!chessGame){
        return NULL;
    }
    return chessGame->id;
}
