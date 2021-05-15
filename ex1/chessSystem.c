#include "chessSystem.h"

struct ChessSystem{
    unsigned int openTournamentsIDs;
    unsigned int* playersIDs;
};

ChessSystem chessCreate();

void chessDestroy(ChessSystem chess);

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
