#include <stdbool.h>
#include "test_utilities.h"
#include "../chessTournament.h"

int TOURNAMENT_ID = 1;
int TOURNAMENT_MAX_GAMES_PER_PLAYER = 5;
char* TOURNAMENT_LOCATION = "Belgium";
int PLAYER_DEFAULT_VERSION = 0;
int PLAYER1_ID = 1;
int PLAYER2_ID = 2;
int play_time = 30;
Winner winner = SECOND_PLAYER;

bool testTournamentCreate(){
    ChessTournament new_tournament = tournamentCreate(TOURNAMENT_ID,
                                                      TOURNAMENT_MAX_GAMES_PER_PLAYER, TOURNAMENT_LOCATION);
    ASSERT_TEST(new_tournament);
    tournamentDestroy(new_tournament);
    return true;
}
/**
 * Using tournamentCreate, tournamentDestroy and should be called after them are tested.
 * @return true if copy action was succeeded, false otherwise.
 */
bool testTournamentCopy(){
    ChessTournament src_tournament = tournamentCreate(TOURNAMENT_ID,
                                                      TOURNAMENT_MAX_GAMES_PER_PLAYER, TOURNAMENT_LOCATION);
    ASSERT_TEST(src_tournament);
    ChessTournament dst_tournament = tournamentCopy(src_tournament);
    ASSERT_TEST(dst_tournament);

    tournamentDestroy(src_tournament);
    tournamentDestroy(dst_tournament);
    return true;
}

bool testTournamentAddGame(){
    ChessTournament tournament = tournamentCreate(TOURNAMENT_ID, TOURNAMENT_MAX_GAMES_PER_PLAYER, TOURNAMENT_LOCATION);
    PlayerID player1_id = playerIDCreate(PLAYER1_ID,PLAYER_DEFAULT_VERSION);
    PlayerID player2_id = playerIDCreate(PLAYER2_ID,PLAYER_DEFAULT_VERSION);
    ChessGame game = gameCreate(tournamentGetID(tournament), player1_id, player2_id, play_time, winner);

    ChessResult tournament_result = tournamentAddGame(tournament, game);
    ASSERT_TEST(tournament_result == CHESS_SUCCESS);

    playerIDDestroy(player1_id);
    playerIDDestroy(player2_id);
    gameDestroy(game);
    tournamentDestroy(tournament);
    return true;
}

bool testTournamentEndTournament(){
    // TODO: GENERATE MORE COMPLEX DATA
    ChessTournament tournament = tournamentCreate(TOURNAMENT_ID, TOURNAMENT_MAX_GAMES_PER_PLAYER, TOURNAMENT_LOCATION);
    PlayerID player1_id = playerIDCreate(PLAYER1_ID,PLAYER_DEFAULT_VERSION);
    PlayerID player2_id = playerIDCreate(PLAYER2_ID,PLAYER_DEFAULT_VERSION);
    ChessGame game = gameCreate(tournamentGetID(tournament), player1_id, player2_id, play_time, winner);

    ChessResult tournament_result = tournamentAddGame(tournament, game);
    ASSERT_TEST(tournament_result == CHESS_SUCCESS);
    ChessResult tournament_end_result = tournamentEndTournament(tournament);
    ASSERT_TEST(tournament_end_result == CHESS_SUCCESS);

    playerIDDestroy(player1_id);
    playerIDDestroy(player2_id);
    gameDestroy(game);
    tournamentDestroy(tournament);
    return true;
}

int main(){
    RUN_TEST(testTournamentCreate, "testTournamentCreate");
    RUN_TEST(testTournamentCopy, "testTournamentCopy");
    RUN_TEST(testTournamentAddGame, "testTournamentAddGame");
    RUN_TEST(testTournamentEndTournament, "testTournamentEndTournament");
    return 0;
}
