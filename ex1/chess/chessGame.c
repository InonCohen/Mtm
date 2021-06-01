#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "strUtils.h"
#include "chessGame.h"
#include "chessSystem.h"
#include "chessPlayerID.h"

struct chess_game_t{
    char* id;
    int tournament_id;
    PlayerID player1_id;
    PlayerID player2_id;
    int play_time;
    Winner game_winner;
    bool player_deleted;
};

/**
* createGameID: Created a game ID in accordance to received data.
 *                  The game id is of form tour_id1_id2, where tour is the received tournament_id,
 *                  id1 is player1_id_str, and id2 is player2_id_str
* @param player1_id_str - a string representing game's first player ID.
* @param player2_id_str - a string representing game's second player ID.
* @param tournament_id - an integer representing game's tournament ID.
* @return
* 	NULL if a NULL was sent as either players' ids, or if the tournament id
 * 	is non-positive, or if an allocation failed.
* 	Otherwise the game id.
*/
static char* createGameID(char* player1_id_str, char* player2_id_str, int tournament_id);

ChessGame gameCreate(int tournament_id, PlayerID player1_id, PlayerID player2_id,
                          int play_time, Winner winner){
    if(tournament_id<=0||!player1_id||!player2_id||play_time<0||(winner!=FIRST_PLAYER && winner!=SECOND_PLAYER)){
        return NULL;
    }
    if (!playerIDCompare(player1_id, player2_id)){
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
    result->player1_id = playerIDCopy(player1_id);
    if(!player1_id){
        return NULL;
    }
    result->player2_id = playerIDCopy(player2_id);
    if(!player2_id){
        return NULL;
    }
    char* game_id = createGameID(playerIDGetFullID(player1_id), playerIDGetFullID(player2_id), tournament_id);
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

    new_game->player1_id = playerIDCopy(game->player1_id);
    new_game->player2_id = playerIDCopy(game->player2_id);
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
    playerIDDestroy(game->player1_id);
    playerIDDestroy(game->player2_id);
    free(game);
}

char* gameGetID(ChessGame game){
    if(!game){
        return NULL;
    }
    return game->id;
}

int gameGetTournamentID(ChessGame game){
    if(!game){
        return BAD_INPUT;
    }
    return game->tournament_id;
}

PlayerID gameGetPlayer1ID(ChessGame game){
    if(!game){
        return NULL;
    }
    return game->player1_id;
}

PlayerID gameGetPlayer2ID(ChessGame game){
    if(!game){
        return NULL;
    }
    return game->player2_id;
}

int gameGetPlayTime(ChessGame game){
    if(!game){
        return BAD_INPUT;
    }
    return game->play_time;
}

Winner gameGetWinner(ChessGame game){
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

bool gamePlayerIsDeleted(ChessGame game){
    if(!game){
        return true;
    }
    return game->player_deleted;
}

void gameUpdateLoser(ChessGame game, ChessPlayer loser, ChessPlayer winner){
    assert(game && loser);
    PlayerID loser_id = playerGetID(loser);
    PlayerID game_player1_id = gameGetPlayer1ID(game);
    Winner old_winner = game->game_winner;
    bool loser_is_first = (playerIDCompare(loser_id, game_player1_id)==0) ? true : false;
    Winner new_winner = (loser_is_first) ? SECOND_PLAYER : FIRST_PLAYER;
    if(old_winner == new_winner){
        return;
    }
    if(old_winner == DRAW){
        playerRemoveDraw(loser, game);
        playerAddLose(loser, game);
        playerRemoveDraw(winner, game);
        playerAddWin(winner, game);
    }
    else if((old_winner == FIRST_PLAYER && loser_is_first) || (old_winner == SECOND_PLAYER && !loser_is_first)) {
        if (loser_is_first) {
            playerRemoveWin(loser, game);
            playerAddLose(loser, game);
            playerRemoveLose(winner, game);
            playerAddWin(winner, game);
        }
    }
    game->game_winner = new_winner;
}

void gameMarkDeletedPlayerTrue(ChessGame game){
    if(!game){
        return;
    }
    game->player_deleted= true;
}

static char* createGameID(char* player1_id_str, char* player2_id_str, int tournament_id){
    if(!player1_id_str || ! player2_id_str || tournament_id <= 0){
        return NULL;
    }
    char* tournament_id_str= castIntToString((int) tournament_id);
    int len1, len2, len3;
    len1=(int)strlen(player1_id_str);
    len2=(int)strlen(player2_id_str);
    len3=(int)strlen(tournament_id_str);
    int size = len1 + strlen(ID_SEP) + len2  + strlen(ID_SEP) + len3 + strlen(ID_SEP);
    char* game_id = malloc(size);
    if(!game_id){
        return NULL;
    }
    nullifyString(game_id, size);
    game_id = strcat(game_id,tournament_id_str);
    game_id = strcat(game_id, ID_SEP);
    game_id = strcat(game_id,strcmp(player1_id_str,player2_id_str) < 0 ? player1_id_str: player2_id_str);
    game_id = strcat(game_id, ID_SEP);
    game_id = strcat(game_id,strcmp(player1_id_str,player2_id_str) > 0 ? player1_id_str: player2_id_str);
    free(tournament_id_str);
    return game_id;
}

