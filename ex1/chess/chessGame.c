#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strUtils.h"
#include "chessGame.h"
#include "chessSystem.h"
#include "chessPlayer.h"

struct chess_game_t{
    char* id;
    int tournament_id;
    char* player1_id;
    char* player2_id;
    int play_time;
    Winner game_winner;
    bool player_deleted;
};



static char* createGameID(char* player1_id, char* player2_id, int tournament_id){
    if(!player1_id || !player2_id || tournament_id <= 0){
        return NULL;
    }
    // TODO: Implement: char* chessSystem->createPlayerID(chessPlayer player)
    char* tournament_id_str= castIntToString((int) tournament_id);
    int len1, len2, len3;
    len1=(int)strlen(player1_id);
    len2=(int)strlen(player2_id);
    len3=(int)strlen(tournament_id_str);
    int size = len1 + strlen(ID_SEP) + len2  + strlen(ID_SEP) + len3 + strlen(ID_SEP);
    char* game_id = malloc(size);
    if(!game_id){
        return NULL;
    }
    nullifyString(game_id, size);
    game_id = strcat(game_id,tournament_id_str);
    game_id = strcat(game_id, ID_SEP);
    game_id = strcat(game_id,strcmp(player1_id,player2_id) < 0 ? player1_id: player2_id);
    game_id = strcat(game_id, ID_SEP);
    game_id = strcat(game_id,strcmp(player1_id,player2_id) > 0 ? player1_id: player2_id);
    return game_id;
}

ChessGame gameCreate(int tournament_id, char* player1_id, char* player2_id,
                          int play_time, Winner winner){
    if(tournament_id<=0||!player1_id||!player2_id||play_time<0||(winner!=FIRST_PLAYER && winner!=SECOND_PLAYER)){
        return NULL;
    }
    //TODO: Add check for: "chessPlayer.c->extractNumericID(char* player_id) <= 0"
    if(player1_id == player2_id){
        return NULL;
    }
    ChessGame result = malloc(sizeof (*result));
    if (!result){
        return NULL;
    }
    result->game_winner = winner;
    result->play_time =  play_time;
    result-> tournament_id = tournament_id;
    result->player_deleted = false;
    result->player1_id = malloc(strlen(player1_id) + 1);
    if(!result->player1_id) {
        free(result);
        return NULL;
    }

    result->player2_id = malloc(strlen(player1_id) + 1);
    if(!result->player2_id){
        free(result->player1_id);
        free(result);
        return NULL;
    }
    strcpy(result->player1_id, player1_id);
    strcpy(result->player2_id, player2_id);
    char* game_id = createGameID(player1_id, player2_id, tournament_id);
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

    new_game->player1_id = game->player1_id;
    new_game->player2_id = game->player2_id;
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

int gameGetTournamentID(ChessGame game){
    if(!game){
        return BAD_INPUT;
    }
    return game->tournament_id;
}

char* gameGetPlayer1ID(ChessGame game){
    if(!game){
        return NULL;
    }
    return game->player1_id;
}

char* gameGetPlayer2ID(ChessGame game){
    if(!game){
        return NULL;
    }
    return game->player2_id;
}

char* chessGameGetID(ChessGame game){
    if(!game){
        return NULL;
    }
    return game->id;
}

int gameGetPlayTime(ChessGame game){
    if(!game){
        return BAD_INPUT;
    }
    return game->play_time;
}

Winner chessGameGetWinner(ChessGame game){
    if(!game){
        return BAD_INPUT;
    }
    return game->game_winner;
}

void gameSetWinner(ChessGame game, Winner winner){
    if(!game || (winner!= FIRST_PLAYER && winner!= SECOND_PLAYER)){
        return;
    }
    game->game_winner = winner;
}
/**
 * extractPlayersIDsFromGameID
 * @param game_id
 * @param player1_id: An empty <int> pointer to which player1_id is to be input.
 * @param player2_id: An empty <int> pointer to which player2_id is to be input.
 * @return
 */
// TODO: Update extractPlayersIDsFromGameID by the new player ID structure.
//static GameResult extractPlayersIDsFromGameID(char* game_id, int* player1_id, int* player2_id){
//    if(!game_id || !player1_id || !player2_id){
//        return GAME_NULL_ARGUMENT;
//    }
//    int size = (int)strlen(game_id);
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
//    int i=0;
//
//    // Goto the first char after ID_SEP
//    while(game_id[i++] != ID_SEP[0]);
//    // Fill player1_id &&player2_id
//    for(;i<size;i++){
//        if(game_id[i] == ID_SEP[0]){
//            id2_flag++;
//            continue;
//        }
//        if(id2_flag>1){
//            break;
//        }
//        if(!id2_flag){
//            strncat(id1_str, &game_id[i], 1);
//        }
//        strncat(id2_str, &game_id[i], 1);
//    }
//    *player1_id = atoi(id1_str);
//    *player2_id = atoi(id2_str);
//    free(id1_str);
//    free(id2_str);
//    return GAME_SUCCESS;
//}

void chessGameSetWinner(ChessGame game, Winner winner){
    if(!game || (winner!= FIRST_PLAYER && winner!= SECOND_PLAYER)){
        return;
    }
    game->game_winner = winner;
}

bool gamePlayerIsDeleted(ChessGame game){
    return game->player_deleted;
}

// TODO: Update chessGameUpdateLoser by the new player ID structure.
//GameResult chessGameUpdateLoser(char* game_id, ChessPlayer player){
//    if(!game_id || !player){
//        return GAME_NULL_ARGUMENT;
//    }
//    int loser_id = playerGetID(player);
//    char **id1, **id2;
//    extractPlayersIDsFromGameID(game_id, id1, id2);
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

