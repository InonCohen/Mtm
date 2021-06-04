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
#include "test_utilities.h"
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

void testChessGameAdd(ChessSystem sys) {
    printf("Testing Add...\n");
    int player1 = 1, player2 = 2, player3 = 3, play_time = 30, tour_id = 1;
    ChessResult res = chessAddGame(sys, tour_id, player1, player2, FIRST_PLAYER, play_time);
    if (res != CHESS_SUCCESS) {
        printf("An error occurred. Code: %d\n", res);
    }
    else{
        printf("\nTEST FINISHED SUCCESSFULLY\n\n");
    }
    res = chessAddGame(sys, tour_id, player1, player3, FIRST_PLAYER, play_time);
    if (res != CHESS_SUCCESS) {
        printf("An error occurred. Code: %d\n", res);
    }
    else{
        printf("\nTEST FINISHED SUCCESSFULLY\n\n");
    }
}

void testChessRemovePlayer(ChessSystem sys){
    printf("Testing RemovePlayer...\n");
    ChessResult res = chessRemovePlayer(sys,1);
    if(res != CHESS_SUCCESS){
        printf("An error occurred. Code: %d\n", res);
        return;
    }
    else{
        printf("\nTEST FINISHED SUCCESSFULLY\n\n");
    }
}

void testChessCalcAvgPlayTime(ChessSystem sys){
    printf("Testing RemovePlayer...\n");
    ChessResult res;
    double avg = chessCalculateAveragePlayTime(sys,12, &res);
    if(res != CHESS_PLAYER_NOT_EXIST){
        printf("An error occurred. Code: %d\n", res);
        return;
    }
    avg = chessCalculateAveragePlayTime(sys,2, &res);
    if(res != CHESS_SUCCESS){
        printf("An error occurred. Code: %d\n", res);
    }
    else{
        printf("Player Average Play Time is %f", avg);
        printf("\nTEST FINISHED SUCCESSFULLY\n\n");
    }
}

void testChessPrintPlayersLevels(ChessSystem sys){
    printf("Testing PrintPlayersLevel...\n");
    FILE* file = fopen("LevelsTest.txt", "w");
    ChessResult res = chessSavePlayersLevels(sys, file);
    fclose(file);
    if (res!= CHESS_SUCCESS){
        printf("An error occurred. Code: %d\n", res);
    }
    else{
        printf("\nTEST FINISHED SUCCESSFULLY\n\n");
    }


}

int main(){
    ChessSystem sys1 = chessCreate();


    ASSERT_TEST(chessAddTournament(sys1, 1, 5, "Location one") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys1, 2, 5, "Location two") == CHESS_SUCCESS);


    int player_1 = 1;
    int player_2 = 2;
    int player_3 = 3;
    int player_4 = 4;
    int player_5 = 5;
    int player_6 = 6;

//tournament_1
    ASSERT_TEST(chessAddGame(sys1, 1, player_1, player_5, DRAW, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 1, player_1, player_6, DRAW, 2) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 1, player_1, player_2, FIRST_PLAYER, 3) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 1, player_1, player_3, SECOND_PLAYER, 4) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 1, player_3, player_4, FIRST_PLAYER, 5) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 1, player_3, player_2, SECOND_PLAYER, 6) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 1, player_4, player_5, FIRST_PLAYER, 7) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 1, player_4, player_6, FIRST_PLAYER, 8) == CHESS_SUCCESS);

    ASSERT_TEST(chessEndTournament(sys1, 1) == CHESS_SUCCESS);
    char* file_name = "your_output/winner_of_tour_1.txt";
    FILE* f = fopen("your_output/test_player_score_1.txt", "w");
    ASSERT_TEST(f != NULL);
    ASSERT_TEST(chessSavePlayersLevels(sys1, f) == CHESS_SUCCESS);
    ASSERT_TEST(chessSaveTournamentStatistics(sys1, file_name) == CHESS_SUCCESS);
    fclose(f);

//tournament_2
    ASSERT_TEST(chessAddGame(sys1, 2, player_1, player_5, DRAW, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 2, player_1, player_6, DRAW, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 2, player_1, player_2, FIRST_PLAYER, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 2, player_1, player_3, SECOND_PLAYER, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 2, player_3, player_4, FIRST_PLAYER, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 2, player_3, player_2, SECOND_PLAYER, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 2, player_4, player_5, FIRST_PLAYER, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 2, player_4, player_6, FIRST_PLAYER, 1) == CHESS_SUCCESS);

    ASSERT_TEST(chessRemovePlayer(sys1,3) == CHESS_SUCCESS);//remove winner

    ASSERT_TEST(chessEndTournament(sys1, 2) == CHESS_SUCCESS);
    file_name = "your_output/winner_of_tour_2.txt";
    chessSaveTournamentStatistics(sys1, file_name);
    f = fopen("your_output/test_player_score_2_after_remove.txt", "w");
    ASSERT_TEST(f != NULL);
    ASSERT_TEST(chessSavePlayersLevels(sys1, f) == CHESS_SUCCESS);
    fclose(f);

    chessDestroy(sys1);

    return 0;
}
