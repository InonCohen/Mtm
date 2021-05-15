#include "chessTournament.h"

struct chessTournament{
    unsigned int tournamentID;
    char* tournamentLocation;
    unsigned int* gameIDs;
    int tournamentWinnerPlayerID = NULL;
};

ChessTournament chessTournamentCreate();

ChessTournament chessTournamentCopy(ChessTournament);

void chessTournamentDestroy(ChessTournament);

int sumPointsOfPlayer(int playerID);

int countLosingGames(int playerID);