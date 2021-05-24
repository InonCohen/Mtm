#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "chessGame.h"
#include "chessSystem.h"

#define SEP "-"
#define MORE_LENGTH 3

struct chess_game_t{
    char* id;
    unsigned int tournament_id;
    unsigned int player1;
    unsigned int player2;
    int play_time;
    Winner game_winner;
};

char* createGameID(unsigned int player1, unsigned int player2, unsigned int tournament){
    if(!id1 || !id2 || !tournament){
        return NULL;
    }
    char* id1, *id2, *tournament_id_str;
    itoa(player1, id1);
    itoa(player2, id2);
    itoa(tournament, tournament_id_str);
    int len1, len2, len3;
    len1=strlen(id1);
    len2=strlen(id2);
    len3=strlen(tournament_id_str);
    char* game_id = malloc(len1+len2+len3+MORE_LENGTH);
    if(!game_id){
        free(result);
        return NULL;
    }
    game_id = strcat(game_id,id1);
    game_id = strcat(game_id,SEP);
    game_id = strcat(game_id,id2);
    game_id = strcat(game_id,SEP);
    game_id = strcat(game_id,tournament_id_str);
    return game_id;
}

ChessGame chessGameCreate(unsigned int tournament_id, unsigned int player1, unsigned int player2, int play_time, Winner winner){
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
    if (newGame == NULL) {
        return NULL;
    }
    return newGame;
}

void chessGameDestroy(ChessGame game){
    if(!game){
        return;
    }
    free(game);
}

int getChessGameID(ChessGame chessGame){
    return itoa(chessGame->tournament_id)+SEP+itoa(chessGame->player1)+SEP+itoa(chessGame->player2);
}