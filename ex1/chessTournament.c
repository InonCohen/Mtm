#include <stdio.h>
#include <stdlib.h>

#include "chessTournament.h"
#include "chessGameCopy.h"
#include "chessPlayer.h"
#define MORE_LENGTH 4
#define BAD_INPUT -1

struct chess_tournament_t{
    int tournament_id;
    int max_games_per_player;
    int tournament_winner_player_id;
    char* tournament_location;
    Map games;
};

void freeAll(void* elem1, void* elem2, void* elem3, void* elem4){
    free(elem1);
    free(elem2);
    free(elem3);
    free(elem4);
}

char* createGameID(int player1_id, int player2_id, int tournament, int identifier){
    if(player1_id<0 || player2_id<0 || tournament<0 || player1_id == player2_id){
        return NULL;
    }
    char *id1, *id2, *identifier_str;
    if(player1_id<player2_id){
        id1 = (player1_id<player2_id)? castIntToString(player1_id): castIntToString(player2_id);
        if(!id1){
            return NULL;
        }
        id2 = (player1_id>player2_id)? castIntToString(player1_id): castIntToString(player2_id);
        if(!id2){
            free(id1);
            return NULL;
        }
    }
    identifier_str = castIntToString(identifier);
    if(!identifier_str){
        free(id1);
        free(id2);
        return NULL;
    }
    char* tournament_id_str= castIntToString(tournament) ;
    if(!tournament_id_str){
        freeAll(id1, id2, identifier_str, NULL)
        return NULL;
    }
    int len1, len2, len3, len4;
    len1=strlen(id1);
    len2=strlen(id2);
    len3=strlen(tournament_id_str);
    len4= strlen(identifier_str);
    int id_size = len1+len2+len3+len4+MORE_LENGTH;
    char* game_id = malloc(id_size);
    if(!game_id){
        freeAll(id1, id2, identifier_str, tournament_id_str);
        return NULL;
    }
    nullifyString(game_id,id_size);
    game_id = strcat(game_id,tournament_id_str);
    game_id = strcat(game_id,SEP);
    game_id = strcat(game_id, id1);
    game_id = strcat(game_id,SEP);
    game_id = strcat(game_id,id2);
    game_id = strcat(game_id,SEP);
    game_id = strcat(game_id,identifier_str);
    freeAll(id1, id2, identifier_str, tournament_id_str);
    return game_id;
}

bool gameSamePlayers(ChessGame game, int player1, int player2){
    if(!game){
        return false;
    }
    int id1 = gameGetPlayer1(game);
    int id2 = gameGetPlayer2(game);
    if(player1 == id1){
        if(player2 == id2){
            return true;
        }
    }
    if(player1 == id2){
        if(player2 == id1){
            return true;
        }
    }
    return false;
}

int getGameIdentifier(ChessTournament tournament, int player1, int player2){
    if(!tournament){
        return BAD_INPUT;
    }
    int count =0;
    MAP_FOREACH(char*, iter, tournament->games){
        if(gameSamePlayers(mapGet(tournament->games, player1, player2))){
            count++;
        }
        free(iter);
    }
    return count;
}

ChessTournament chessTournamentCreate();

ChessTournament chessTournamentCopy(ChessTournament);

void chessTournamentDestroy(ChessTournament);

int sumPointsOfPlayer(int playerID);

int countLosingGames(int playerID);

TournamentResult tournamentAddGame(ChessTournament tournament, int first_player,
                                   int second_player,int play_time, Winner winner){
    if(!tournament){
        return TOURNAMENT_NULL_ARGUMENT;
    }
    if(tournament->tournament_id <= 0 || first_player<=0 || second_player<=0 || first_player == second_player){
        return CHESS_INVALID_ID;
    }
    int identifier = getGameIdentifier(tournament, first_player, second_player);
    char* game_id = createGameID(first_player, second_player, tournament->tournament_id, identifier);
    if(!game_id){
        return TOURNAMENT_OUT_OF_MEMORY;
    }
    if(mapContains(tournament->games, game_id){
       ChessGame game = mapGet(tournament->games, game_id);
       if (!(gamePlayerIsDeleted(game))){
           return TOURNAMENT_GAME_ALREADY_EXIST;
       }
    }
    if(play_time<0){
        return TOURNAMENT_INVALID_PLAY_TIME;
    }
    if(mapContains(tournament->players, player1) || mapContains(tournament->players, player2) ){
        Player player1_ptr = mapGet(tournament->players, player1);
        Player player2_ptr = mapGet(tournament->players, player2);
        if(player1_ptr && tournament->max_games_per_player = mapGetSize(playerGetGames(player1_ptr))){
            return TOURNAMENT_EXCEEDED_GAMES;
        }
        if(player2_ptr && tournament->max_games_per_player = mapGetSize(playerGetGames(player2_ptr))){
            return TOURNAMENT_EXCEEDED_GAMES;
        }
    }
    ChessGame to_add = gameCreate(game_id, tournament->tournament_id, player1, player2, play_time, winner);
    if(!to_add){
        free(game_id);
        return TOURNAMENT_OUT_OF_MEMORY;
    }
    free(game_id);
    MapResult res = mapPut(tournament->games, to_add);
    gameDestroy(to_add);
    if(res != MAP_SUCCESS){
        return TOURNAMENT_OUT_OF_MEMORY;
    }
    return TOURNAMENT_SUCCESS;
}