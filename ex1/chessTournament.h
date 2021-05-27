#ifndef EX1_CHESSTOURNAMENT_H
#define EX1_CHESSTOURNAMENT_H

/** Type for representing a chess game in a tournament */
typedef struct chess_tournament_t *ChessTournament;

typedef enum {
    TOURNAMENT_OUT_OF_MEMORY,
    TOURNAMENT_NULL_ARGUMENT,
    TOURNAMENT_INVALID_ID,
    TOURNAMENT_INVALID_LOCATION,
    TOURNAMENT_INVALID_MAX_GAMES,
    TOURNAMENT_TOURNAMENT_ALREADY_EXISTS,
    TOURNAMENT_TOURNAMENT_NOT_EXIST,
    TOURNAMENT_GAME_ALREADY_EXISTS,
    TOURNAMENT_INVALID_PLAY_TIME,
    TOURNAMENT_EXCEEDED_GAMES,
    TOURNAMENT_PLAYER_NOT_EXIST,
    TOURNAMENT_TOURNAMENT_ENDED,
    TOURNAMENT_NO_TOURNAMENTS_ENDED,
    TOURNAMENT_NO_GAMES,
    TOURNAMENT_SAVE_FAILURE,
    TOURNAMENT_SUCCESS
} TournamentResult ;

ChessTournament chessTournamentCreate();

ChessTournament chessTournamentCopy(ChessTournament);

void chessTournamentDestroy(ChessTournament);

int sumPointsOfPlayer(int playerID);

TournamentResult tournamentAddGame(Tournament tournament, int first_player, int second_player,int play_time, Winner winner);

int countLosingGames(int playerID);

#endif //EX1_CHESSTOURNAMENT_H
