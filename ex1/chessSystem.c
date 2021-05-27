#include "chessSystem.h"
#include "map.h"
#include "chessPlayer.h"
#include "chessGameCopy.h"
#include "chessTournament.h"

struct ChessSystem{
    Map tournaments; // Key: int id,  Data: Tournament tour
//    Map Games; // Key: char* id,  Data: Game game
    Map Players; // Key: int id,  Data: Player
};
/*
 * Required to function:
 *              - Tournaments ADT copy, destroy funcs
 *              - Games ADT copy, destroy funcs
 *              - Players ADT copy, destroy funcs
 */


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

ChessSystem chessCreate(){
    ChessSystem system = malloc(sizeof(*system));
    if(!system){
        return NULL;
    }
    Map tournaments = mapCreate(tournamentCreate, tournamentMapKeyCopy, tournamentDestroy, tournamentMapKeyFree, tournamentMapKeyComp);
    if(!tournaments){
        free(system);
        return NULL;
    }
//    Map games = malloc(sizeof(*games));
//    if(!games){
//        free(tournaments);
//        free(system);
//        return NULL;
//    }
    Map players = mapCreate(playerCopy, );
    if(!players){
        free(games);
        free(tournaments);
        free(system);
        return NULL;
    }
    system->tournaments = tournaments;
    system->games = games;
    system->players = players;
    return system;
}

void chessDestroy(ChessSystem chess){
    if(!chess){
        return;
    }
    if(chess->tournaments){
        mapDestroy(chess->tournaments);
    }
    if(chess->games){
        mapDestroy(chess->games);
    }
    if(chess->players){
        mapDestroy(chess->players);
    }
    free(chess);
}

static bool chessGameInTournament(Tournament tournament, char* game_id){
    if(!tournament || !game_id){
        return false;
    }
    if(mapContains(games,game_id)){
        if (!gamePlayerIsDeleted(game)) {
            return true;
        }
        else{
            return false;
        }
    }
    return false;
}

ChessResult chessAddTournament (ChessSystem chess, int tournament_id,
                                int max_games_per_player, const char* tournament_location);

ChessResult chessAddGame(ChessSystem chess, int tournament_id, int first_player,
                         int second_player, Winner winner, int play_time){
    if(!chess){
        return CHESS_NULL_ARGUMENT;
    }
    if(tournament_id<=0 || first_player<=0 || second_player<=0 || first_player == second_player){
        return CHESS_INVALID_ID;
    }
    assert(chess->tournaments);
    if(!mapContains(chess->tournaments, tournament_id)){
        return CHESS_TOURNAMENT_NOT_EXIST;
    }
    Tournament tournament = mapGet(chess->tournaments, tournament_id);
    if(tournamentIsOver(tournament)){
        return CHESS_TOURNAMENT_ENDED;
    }
    return tournamentAddGame(tournament, first_player, second_player,play_time, winner);
}

ChessResult chessRemoveTournament (ChessSystem chess, int tournament_id);

ChessResult chessRemovePlayer(ChessSystem chess, int player_id);

ChessResult chessEndTournament (ChessSystem chess, int tournament_id);

double chessCalculateAveragePlayTime (ChessSystem chess, int player_id, ChessResult* chess_result);

ChessResult chessSavePlayersLevels (ChessSystem chess, FILE* file);

ChessResult chessSaveTournamentStatistics (ChessSystem chess, char* path_file);
