#include <stdbool.h>
#include "test_utilities.h"
#include "../chessTournament.h"


bool testTournamentCreate(){
    int TOURNAMENT_ID = 1;
    int TOURNAMENT_MAX_GAMES_PER_PLAYER = 5;
    char* TOURNAMENT_LOCATION = "Belgium";

    ChessTournament new_tournament = tournamentCreate(TOURNAMENT_ID,
                                                      TOURNAMENT_MAX_GAMES_PER_PLAYER, TOURNAMENT_LOCATION);
    ASSERT_TEST_WITH_FREE(new_tournament, tournamentDestroy);
    return true;
}
/**
 * Using tournamentCreate, tournamentDestroy and should be called after them are tested.
 * @return true if copy action was succeeded, false otherwise.
 */
bool testTournamentCopy(){
    int TOURNAMENT_ID = 1;
    int TOURNAMENT_MAX_GAMES_PER_PLAYER = 5;
    char* TOURNAMENT_LOCATION = "Belgium";

    ChessTournament src_tournament = tournamentCreate(TOURNAMENT_ID,
                                                      TOURNAMENT_MAX_GAMES_PER_PLAYER, TOURNAMENT_LOCATION);
    ASSERT_TEST_WITH_FREE(src_tournament, tournamentDestroy);
    ChessTournament dst_tournament = tournamentCopy(src_tournament);
    ASSERT_TEST_WITH_FREE(dst_tournament, tournamentDestroy);

    return true;
}

bool testTournamentGetSumPointsOfPlayer(){
    return true;
}

bool testTournamentCountLosingGames(){
    return true;
}

int main(){
    ASSERT_TEST(testTournamentCreate);
    ASSERT_TEST(testTournamentCopy);
    ASSERT_TEST(testTournamentGetSumPointsOfPlayer);
    ASSERT_TEST(testTournamentCountLosingGames);

    return 0;
}
