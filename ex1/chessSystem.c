#include "chessSystem.h"

struct ChessSystem{
    Map tournaments; // Key: int id,  Data: Tournament tour
    Map Games; // Key: char* id,  Data: Game game
    Map Players; // Key: int id,  Data: Player
};
/*
 * Required to function:
 *              - Tournaments ADT copy, destroy funcs
 *              - Games ADT copy, destroy funcs
 *              - Players ADT copy, destroy funcs
 */
ChessSystem chessCreate(){
    ChessSystem system = malloc(sizeof(*system));
    if(!system){
        return NULL;
    }
    Map tournaments = malloc(sizeof(*tournaments));
    if(!tournaments){
        free(system);
        return NULL;
    }
    Map games = malloc(sizeof(*games));
    if(!games){
        free(tournaments);
        free(system);
        return NULL;
    }
    Map players = malloc (sizeof(*players));
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

ChessResult chessAddTournament (ChessSystem chess, int tournament_id,
                                int max_games_per_player, const char* tournament_location);

ChessResult chessAddGame(ChessSystem chess, int tournament_id, int first_player,
                         int second_player, Winner winner, int play_time);

ChessResult chessRemoveTournament (ChessSystem chess, int tournament_id);

ChessResult chessRemovePlayer(ChessSystem chess, int player_id);

ChessResult chessEndTournament (ChessSystem chess, int tournament_id);

double chessCalculateAveragePlayTime (ChessSystem chess, int player_id, ChessResult* chess_result);

ChessResult chessSavePlayersLevels (ChessSystem chess, FILE* file);

ChessResult chessSaveTournamentStatistics (ChessSystem chess, char* path_file);
