#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../chessGame.h"
#include "../chessPlayerID.h"
#include "../chessMapUtils.h"
#include "../strUtils.h"
#include "../chessSystem.h"
#include "../chessTournament.h"
#define LENGTH_OF_ZERO_STRING 2
#define MORE_LENGTH 3
#define SEP "-"

char* createGameID(unsigned int player1_id, unsigned int player2_id, unsigned int tournament) {
    if (player1_id < 0 || player2_id < 0 || tournament < 0 || player1_id == player2_id) {
        return NULL;
    }
    char *id1, *id2;
    if (player1_id < player2_id) {
        id1 = castIntToString(player1_id);
        id2 = castIntToString(player2_id);
    } else {
        id1 = castIntToString(player2_id);
        id2 = castIntToString(player1_id);
    }
    char *tournament_id_str = castIntToString(tournament);
    int len1, len2, len3;
    len1 = strlen(id1);
    len2 = strlen(id2);
    len3 = strlen(tournament_id_str);
    int id_size = len1 + len2 + len3 + MORE_LENGTH;
    char *game_id = malloc(id_size);
    if (!game_id) {
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

void printGame(ChessGame game){
    printf("Printing Game:\n");
    if(!game){
        printf("INVALID GAME!\n");
    }
    char* game_id =gameGetID(game);
    printf("Game ID: %s\n", game_id);
    PlayerID player1 = gameGetPlayer1ID(game);
    PlayerID player2 = gameGetPlayer2ID(game);
    int id1 = playerIDGetIntID(player1);
    int id2 = playerIDGetIntID(player2);
    int tournament_id = gameGetTournamentID(game);
    int play_time = gameGetPlayTime(game);
    Winner winner = gameGetWinner(game);
    printf("Game tournament: %d\n", tournament_id);
    printf("Game first player: %d\n", id1);
    printf("Game second player: %d\n", id2);
    printf("Game time: %d\n", play_time);
    printf("Game Winner: %d\n", winner);
}

void  testChessGameCreateAndDestroy(){
    printf("Testing Create and Destroy...\n");
    int player1 =12, player2=17, play_time=30, tour_id=1;
    PlayerID id1 = playerIDCreate(player1, 0);
    PlayerID id2 = playerIDCreate(player2, 57);
    ChessGame game = gameCreate(tour_id, id1, id2, play_time, FIRST_PLAYER);
    if(!game){
        playerIDDestroy(id1);
        playerIDDestroy(id2);
        return;
    }
    printGame(game);
    printf("\n\nTesting Copy:\n");
    ChessGame game2 = gameCopy(game);
    gameDestroy(game);
    playerIDDestroy(id1);
    playerIDDestroy(id2);
    printf("\nMaking sure copy is detached from origin:\n");
    printGame(game2);
    gameDestroy(game2);
    printf("\nTEST FINISHED SUCCESSFULLY\n\n");

}

void testChessGameAdd(ChessSystem sys){
    printf("Testing Add...\n");
    int player1 =12, player2=17, play_time=30, tour_id=1;
    ChessResult res = chessAddGame(sys, tour_id, player1, player2, FIRST_PLAYER, play_time);
    if(res!=CHESS_SUCCESS){
        printf("An error occurred. Code: %d\n", res);
    }

static bool tournamentLocationIsValid(const char* tournament_name){
    if (!isupper(tournament_name[0])){
        return false;
    }
    for (int i = 1; i < strlen(tournament_name) ;i++){
        if (!(isspace(tournament_name[i]) || islower(tournament_name[i]))){
            return false;
        }
    }
    return true;
}

bool testTournamentLocationIsValid(){
    char *valid_str = "Belgium";
    char *invalid_str = "belgium";
    ASSERT_TEST(tournamentLocationIsValid(valid_str));
    ASSERT_TEST(!tournamentLocationIsValid(invalid_str));
    return true;
}

>>>>>>> main
}

int main(){
    printf("TESTING CHESS GAME\n\n");
    testChessGameCreateAndDestroy();
    ChessSystem sys = chessCreate();
    if(!sys){
        printf("Couldn't Create sys\n");
        exit(1);
    }
    ChessResult res = chessAddTournament(sys, 1, 50, "Belgium");
    if(res != CHESS_SUCCESS) {
        printf("Adding Tournament to Chess Failed. Error: %d\n", res);
    }
    testChessGameAdd(sys);
    chessDestroy(sys);
    printf("ALL TESTS FINISHED SUCCESSFULLY\n\n");
    return 0;
}
