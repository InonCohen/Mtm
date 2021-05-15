#ifndef EX1_CHESSTOURNAMENT_H
#define EX1_CHESSTOURNAMENT_H

/** Type for representing a chess game in a tournament */
typedef struct chess_tournament_t *ChessTournament;

ChessTournament chessTournamentCreate();

ChessTournament chessTournamentCopy(ChessTournament);

void chessTournamentDestroy(ChessTournament);

int sumPointsOfPlayer(int playerID);

int countLosingGames(int playerID);

#endif //EX1_CHESSTOURNAMENT_H
