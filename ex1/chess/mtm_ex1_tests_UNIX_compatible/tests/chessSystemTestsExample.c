#include <stdlib.h>
#include "../../chessSystem.h"
#include "../../test_utilities.h"
#include <string.h>
#include <math.h>
#define ARE_FLOATS_EQUAL(d1,d2) (fabs(d1-d2) < 0.000001)

static long NumTestsPassed = 0;

static void red () {
  printf("\033[1;31m");
  fflush(stdout);
}

static void green() {
  printf("\033[0;32m");
  fflush(stdout);
}

static void purple() {
  printf("\033[0;35m");
}

static void yellow () {
  printf("\033[0;33m");
  fflush(stdout);
}

static void reset () {
  printf("\033[0m");
  fflush(stdout);
}

static void printIfSuccess(long num_tests)
{
    if (0 == NumTestsPassed)
    {
        red();
    }
    if (num_tests == NumTestsPassed)
    {
        green();
    }
    else
    {
        yellow();
    }
    
    printf("####  Summary: Passed %ld out of %ld ####\n" ,NumTestsPassed, num_tests);
    reset();
}


#define RUN_COLORFULL_TEST(test, name, id)                  \
    do {                                 \
purple();      printf("Running test# %ld %s ... ", id + 1, name);  reset(); \
      fflush(stdout); \
        if (test()) {                    \
            green();\
            printf("[OK]\n");            \
            reset();\
            ++NumTestsPassed;   \
        } else {    \
            red();\
            printf("[Failed]\n");        \
            reset();\
        }                                \
    } while (0)

/*************************************************************************/


/*return true if same*/
static bool compareFiles(FILE *fp1, FILE *fp2)
{
    bool isOk = true;
    if (fp1 == NULL)
    {
        isOk =  false;
    }
    if(fp2 == NULL)
    {
        if (fp1)
        {
            fclose(fp1);
        }
        isOk =  false;
    }

    if (!isOk)
    {
        return false;
    }

    int ch1 = getc(fp1);
    int ch2 = getc(fp2);
    
    int pos = 0, line = 1;
  
    while (ch1 != EOF && ch2 != EOF)
    {
        pos++;
        if (ch1 == '\n' && ch2 == '\n')
        {
            line++;
            pos = 0;
        }
        if (ch1 != ch2)
        {
            return false;
        }
        ch1 = getc(fp1);
        ch2 = getc(fp2);
    }

    return (ch1 == EOF && ch2 == EOF);
}


static bool openFilesCompareAndDelete(const char* expected, const char* actual)
{
    FILE* file_expected = fopen(expected, "r");
    FILE* file_meine = fopen(actual, "r");
    ASSERT_TEST(compareFiles(file_expected, file_meine));
    ASSERT_TEST(0 == fclose(file_expected));
    ASSERT_TEST(0 == fclose(file_meine));

    size_t length_file_name_plus_one = strlen(actual);
    ASSERT_TEST(length_file_name_plus_one >0); 
    ++length_file_name_plus_one;
    char* rm_command = (char*)malloc(length_file_name_plus_one + 3u);  
    ASSERT_TEST(NULL != strncpy(rm_command,"rm ", 4));
    ASSERT_TEST(NULL != strncpy(rm_command+3u, actual, length_file_name_plus_one));
    ASSERT_TEST(0 == system(rm_command));
    free(rm_command);
    return true;
}

/*************************************************************************/

static bool updatePlayerInLoop(ChessSystem chess, int tour, int player_id, int _win, int _lose, int _draw, int time)
{
    int start_from = 123456;
    int win1 = _win/2;
    int win2 = _win - win1;
    int lose1 = _lose/2;
    int lose2 = _lose - lose1;
    int draw1 = _draw/2;
    int draw2 = _draw - draw1;
    for (int i = start_from; i < start_from + win1; i++)
    {
        ASSERT_TEST(chessAddGame(chess, tour, player_id, i, FIRST_PLAYER, time) == CHESS_SUCCESS);      
    }
    for (int i = start_from + win1; i <start_from + win1 + lose1; i++)
    {
        ASSERT_TEST(chessAddGame(chess, tour, player_id, i, SECOND_PLAYER, time) == CHESS_SUCCESS);
    }
    for (int i = start_from + win1 + lose1; i < start_from + win1 + lose1 + draw1; i++)
    {
        ASSERT_TEST(chessAddGame(chess, tour, player_id, i, DRAW, time ) == CHESS_SUCCESS);
    }

    start_from *= 2;
    for (int i = start_from + win2; i > start_from; i--)
    {
        ASSERT_TEST(chessAddGame(chess, tour, i, player_id, SECOND_PLAYER, time ) == CHESS_SUCCESS);
    }

    for (int i = start_from + win2 + lose2; i > start_from + win2 ; i--)
    {
        ASSERT_TEST(chessAddGame(chess, tour, i, player_id, FIRST_PLAYER, time ) == CHESS_SUCCESS);
    }
    for (int i = start_from + win2 + lose2 + draw2; i > start_from + win2 + lose2; i--)
    {
        ASSERT_TEST(chessAddGame(chess, tour, i, player_id, DRAW, time ) == CHESS_SUCCESS);
    }
    return true;
}


static bool testAddTournament_Shimon()
{
    ASSERT_TEST(chessAddTournament(NULL, 2, 5, "London") == CHESS_NULL_ARGUMENT);
    ChessSystem chess = chessCreate();
    ASSERT_TEST(chessAddTournament(chess, 1, 5, NULL) == CHESS_NULL_ARGUMENT);
    ASSERT_TEST(chessAddTournament(chess, 1, 4, "Akko") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, 2, 5, "London") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, 1, 10, "Paris") == CHESS_TOURNAMENT_ALREADY_EXISTS);
    ASSERT_TEST(chessAddTournament(chess, 2, 10, "!!!") == CHESS_TOURNAMENT_ALREADY_EXISTS);
    ASSERT_TEST(chessAddTournament(chess, 3, 10, "!!!") == CHESS_INVALID_LOCATION);
    ASSERT_TEST(chessAddTournament(chess, 3, -19, " @Jerusalem") == CHESS_INVALID_LOCATION);
    ASSERT_TEST(chessAddTournament(chess, 3, -19, "Jerusalem") == CHESS_INVALID_MAX_GAMES);
    ASSERT_TEST(chessAddTournament(chess, 2, 14, "Barcelona") == CHESS_TOURNAMENT_ALREADY_EXISTS);
    ASSERT_TEST(chessAddTournament(chess, 3, 14, "Barcelona") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, 3, 14, "Barcelona") == CHESS_TOURNAMENT_ALREADY_EXISTS);
    ASSERT_TEST(chessAddTournament(chess, 0, 10, "Madrid") == CHESS_INVALID_ID);

    for (int i = -100; i < 1; i++)
    {
        ASSERT_TEST(chessAddTournament(chess, i, 999, "Losangeles") == CHESS_INVALID_ID);
    }

    for (int i = 4; i < 300; i++)
    {
        ASSERT_TEST(chessAddTournament(chess, i, i+13, "Afganistan") == CHESS_SUCCESS);
    }
    
    ASSERT_TEST(chessAddTournament(chess, 300, 0, "Munich") == CHESS_INVALID_MAX_GAMES);
    ASSERT_TEST(chessAddTournament(chess, 300, 937, "TelAviv") == CHESS_INVALID_LOCATION);
    ASSERT_TEST(chessAddTournament(chess, 300, 937, "Tel aviv") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, 301, 937, "los") == CHESS_INVALID_LOCATION);
    ASSERT_TEST(chessAddTournament(chess, 301, 937, "One day it will success") == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(chess, 301) == CHESS_NO_GAMES);
    ASSERT_TEST(chessAddGame(chess, 301, 133, 135, SECOND_PLAYER, 55 ) == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(chess, 301) == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(chess, 301) == CHESS_TOURNAMENT_ENDED);
    ASSERT_TEST(chessAddTournament(chess, 301, 3516, "Maybe today") == CHESS_TOURNAMENT_ALREADY_EXISTS);
    ASSERT_TEST(chessAddTournament(chess, 301, 6165, " Starts with space") == CHESS_TOURNAMENT_ALREADY_EXISTS);
    ASSERT_TEST(chessAddTournament(chess, 305, 6165, " Starts with space") == CHESS_INVALID_LOCATION);

    chessDestroy(chess);
    return true;
}

static bool testAddGame_Shimon()
{
    int tournament_id = 1, first_player = 222, second_player = 333, play_time = 1000, invalid = -999;
    Winner winner = DRAW;

    ASSERT_TEST(chessAddGame(NULL, invalid, first_player, second_player, winner, play_time) == CHESS_NULL_ARGUMENT);
    ASSERT_TEST(chessAddGame(NULL, tournament_id, invalid, second_player, winner, play_time) == CHESS_NULL_ARGUMENT);
    ASSERT_TEST(chessAddGame(NULL, tournament_id, first_player, invalid, winner, play_time) == CHESS_NULL_ARGUMENT);
    ASSERT_TEST(chessAddGame(NULL, tournament_id, first_player, second_player, invalid, play_time) == CHESS_NULL_ARGUMENT);
    ASSERT_TEST(chessAddGame(NULL, tournament_id, first_player, second_player, winner, invalid) == CHESS_NULL_ARGUMENT);

    ChessSystem chess = chessCreate();
    ASSERT_TEST(chessAddGame(chess, invalid, first_player, second_player, invalid, invalid) == CHESS_INVALID_ID);
    ASSERT_TEST(chessAddGame(chess, tournament_id, invalid, second_player, invalid, invalid) == CHESS_INVALID_ID);
    ASSERT_TEST(chessAddGame(chess, tournament_id, first_player, invalid, invalid, invalid) == CHESS_INVALID_ID);
    ASSERT_TEST(chessAddGame(chess, tournament_id, first_player, first_player, invalid, invalid) == CHESS_INVALID_ID);
    ASSERT_TEST(chessAddGame(chess, tournament_id, first_player, second_player, winner, play_time) == CHESS_TOURNAMENT_NOT_EXIST);
    ASSERT_TEST(chessAddTournament(chess, tournament_id, 4, "Akko") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tournament_id, first_player, second_player, winner, play_time) == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(chess, tournament_id) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tournament_id, first_player +5, second_player+5, winner, play_time) == CHESS_TOURNAMENT_ENDED);


    ++tournament_id;
    ASSERT_TEST(chessAddTournament(chess, tournament_id, 14, "Barcelona") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tournament_id, first_player, second_player, winner, invalid) == CHESS_INVALID_PLAY_TIME);
    ASSERT_TEST(chessAddGame(chess, tournament_id, first_player, second_player, winner, 0) == CHESS_SUCCESS);


    ++tournament_id;
    ASSERT_TEST(chessAddTournament(chess, tournament_id, 14, "Somalia") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tournament_id, first_player, second_player, winner, play_time) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tournament_id, second_player, first_player, winner, play_time) == CHESS_GAME_ALREADY_EXISTS);
    ASSERT_TEST(chessAddGame(chess, tournament_id, first_player, second_player, winner, play_time) == CHESS_GAME_ALREADY_EXISTS);


    ++tournament_id;
    int max_games_in_tour = 16;
    ASSERT_TEST(chessAddTournament(chess, tournament_id, max_games_in_tour, "Isla bonita") == CHESS_SUCCESS);    
    for (int i = 0; i < max_games_in_tour / 2 ; i++)
    {
        ASSERT_TEST(chessAddGame(chess, tournament_id, first_player, second_player++, winner, play_time) == CHESS_SUCCESS);
        ASSERT_TEST(chessAddGame(chess, tournament_id, second_player++, first_player, winner, play_time) == CHESS_SUCCESS);
    }
    ASSERT_TEST(chessAddGame(chess, tournament_id, second_player++, first_player, winner, play_time) == CHESS_EXCEEDED_GAMES);

    chessDestroy(chess);
    return true;
}                         


static bool testRemoveTournament_Shimon()
{
    ASSERT_TEST(chessRemoveTournament(NULL, 1) == CHESS_NULL_ARGUMENT);
    ASSERT_TEST(chessRemoveTournament(NULL, -15) == CHESS_NULL_ARGUMENT);
    ChessSystem chess = chessCreate();
    ASSERT_TEST(chess!=NULL);
    ASSERT_TEST(chessRemoveTournament(chess, 1) == CHESS_TOURNAMENT_NOT_EXIST);
    ASSERT_TEST(chessRemoveTournament(chess, 2) == CHESS_TOURNAMENT_NOT_EXIST);
    ASSERT_TEST(chessAddTournament(chess, 1, 4, "Eilat") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, 2, 4, "Annapurna") == CHESS_SUCCESS);
    ASSERT_TEST(chessRemoveTournament(chess, -1) == CHESS_INVALID_ID);
    ASSERT_TEST(chessRemoveTournament(chess, 3) == CHESS_TOURNAMENT_NOT_EXIST);
    ASSERT_TEST(chessRemoveTournament(chess, 2) == CHESS_SUCCESS);
    ASSERT_TEST(chessRemoveTournament(chess, 0) == CHESS_INVALID_ID);
    int tournament_id = 1, first_player = 222, second_player = 333;
    ASSERT_TEST(chessAddGame(chess, tournament_id, first_player, second_player, SECOND_PLAYER, 0) == CHESS_SUCCESS);
    ASSERT_TEST(chessRemoveTournament(chess, 1) == CHESS_SUCCESS);

    chessDestroy(chess);
    return true;
}

static bool testRemovePlayer_Shimon()
{
    ASSERT_TEST(chessRemovePlayer(NULL, 1) == CHESS_NULL_ARGUMENT);
    ChessSystem chess = chessCreate();
    ASSERT_TEST(chess != NULL);
    ASSERT_TEST(chessAddTournament(chess, 1, 4, "Eilat") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, 2, 4, "Annapurna") == CHESS_SUCCESS);
    
    int tournament_id = 1, first_player = 222, second_player = 333;
    ASSERT_TEST(chessAddGame(chess, tournament_id, first_player, second_player++, SECOND_PLAYER, 15) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tournament_id, first_player, second_player++, SECOND_PLAYER, 15) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tournament_id, first_player, second_player++, SECOND_PLAYER, 15) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tournament_id, first_player, second_player++, SECOND_PLAYER, 15) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tournament_id, first_player, 17, SECOND_PLAYER, 15) == CHESS_EXCEEDED_GAMES);

    ++tournament_id;
    second_player = 333;
    ASSERT_TEST(chessAddGame(chess, tournament_id, first_player, second_player++, SECOND_PLAYER, 15) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tournament_id, first_player, second_player++, SECOND_PLAYER, 15) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tournament_id, first_player, 17, SECOND_PLAYER, 15) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tournament_id, first_player, second_player++, SECOND_PLAYER, 15) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tournament_id, first_player, 13, SECOND_PLAYER, 15) == CHESS_EXCEEDED_GAMES);
    ASSERT_TEST(chessAddGame(chess, tournament_id, 1537, second_player++, SECOND_PLAYER, 15) == CHESS_SUCCESS);
    
    ASSERT_TEST(chessRemovePlayer(chess, 17) == CHESS_SUCCESS);
    ASSERT_TEST(chessRemovePlayer(chess, 17) == CHESS_PLAYER_NOT_EXIST);
    ASSERT_TEST(chessRemovePlayer(chess, 335) == CHESS_SUCCESS);
    ASSERT_TEST(chessRemovePlayer(chess, 335) == CHESS_PLAYER_NOT_EXIST);
    ASSERT_TEST(chessRemovePlayer(chess, 18) == CHESS_PLAYER_NOT_EXIST);
    ASSERT_TEST(chessRemovePlayer(chess, 0) == CHESS_INVALID_ID);
    ASSERT_TEST(chessRemovePlayer(chess, -999) == CHESS_INVALID_ID);

    ASSERT_TEST(chessRemoveTournament(chess, tournament_id) == CHESS_SUCCESS);
    ASSERT_TEST(chessRemovePlayer(chess, 1537) == CHESS_SUCCESS);
    ASSERT_TEST(chessRemovePlayer(chess, 1537) == CHESS_PLAYER_NOT_EXIST);
    ASSERT_TEST(chessRemovePlayer(chess, 222) == CHESS_SUCCESS);
    ASSERT_TEST(chessRemovePlayer(chess, 222) == CHESS_PLAYER_NOT_EXIST);

    chessDestroy(chess);
    return true;
}

static bool testEndTournament_Shimon()
{
    ASSERT_TEST(chessEndTournament(NULL, 1) == CHESS_NULL_ARGUMENT);
    ASSERT_TEST(chessEndTournament(NULL, -156) == CHESS_NULL_ARGUMENT);
    ChessSystem chess = chessCreate();
    ASSERT_TEST(chess != NULL);
    ASSERT_TEST(chessEndTournament(chess, 0) == CHESS_INVALID_ID);
    ASSERT_TEST(chessEndTournament(chess, -235) == CHESS_INVALID_ID);
    ASSERT_TEST(chessEndTournament(chess, 1) == CHESS_TOURNAMENT_NOT_EXIST);
    ASSERT_TEST(chessEndTournament(chess, 15) == CHESS_TOURNAMENT_NOT_EXIST);
    ASSERT_TEST(chessEndTournament(chess, 19) == CHESS_TOURNAMENT_NOT_EXIST);


    ASSERT_TEST(chessAddTournament(chess, 1, 4, "Eilat") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, 2, 4, "Annapurna") == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(chess, 1) == CHESS_NO_GAMES);
    ASSERT_TEST(chessAddGame(chess, 2, 1111, 2222, SECOND_PLAYER, 15) == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(chess, 2) == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(chess, 2) == CHESS_TOURNAMENT_ENDED);
    ASSERT_TEST(chessRemoveTournament(chess, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(chess, 1) == CHESS_TOURNAMENT_NOT_EXIST);
    ASSERT_TEST(chessRemoveTournament(chess, 2) == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(chess, 2) == CHESS_TOURNAMENT_NOT_EXIST);

    chessDestroy(chess);
    return true;
}

static const int abraham = 1111, ben = 2222, caroline = 3333, david = 4444, emily = 5555;

static bool averageTest(ChessSystem chess, double a, double b, double c,double d, double e, bool is_emily)  
{
    double arr[5];
    int players_id[5] = {abraham, ben, caroline, david, emily};
    arr[0] = a;
    arr[1] = b;
    arr[2] = c;
    arr[3] = d;
    arr[4] = e;
    for (int i = 0; i < 5; i++)
    {
        ChessResult res = -1;
        double average = chessCalculateAveragePlayTime(chess, players_id[i], &res);
        if ( (4 == i) && !is_emily)
        {
            ASSERT_TEST(res == CHESS_PLAYER_NOT_EXIST);
        }
        else
        {
            ASSERT_TEST(res == CHESS_SUCCESS);
            ASSERT_TEST(ARE_FLOATS_EQUAL(average, arr[i]));
        }
    }
    return true;
}

static bool testCalculateAveragePlayTime_Shimon()
{
    ChessResult res;
    chessCalculateAveragePlayTime(NULL, -15, &res);
    ASSERT_TEST(res == CHESS_NULL_ARGUMENT);
    ChessSystem chess = chessCreate();
    ASSERT_TEST(chess != NULL);
    
    res = CHESS_SUCCESS;
    chessCalculateAveragePlayTime(chess, 0, &res);
    ASSERT_TEST(res == CHESS_INVALID_ID);
    
    res = CHESS_SUCCESS;
    chessCalculateAveragePlayTime(chess, -15, &res);
    ASSERT_TEST(res == CHESS_INVALID_ID);

    res = CHESS_SUCCESS;
    chessCalculateAveragePlayTime(chess, 1, &res);
    ASSERT_TEST(res == CHESS_PLAYER_NOT_EXIST);


    ASSERT_TEST(chessAddTournament(chess, 11, 10, "London") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, 22, 10, "Tel aviv") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, 33, 10, "Ibiza") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, 44, 10, "Napoli") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, 22, 10, "Haifa") == CHESS_TOURNAMENT_ALREADY_EXISTS);
    
    int tour = 11;
    ASSERT_TEST(chessAddGame(chess, tour, abraham, ben, FIRST_PLAYER, 5000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tour, ben, caroline, SECOND_PLAYER, 2000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tour, caroline, david, DRAW, 3000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tour, abraham, david, FIRST_PLAYER, 6000) == CHESS_SUCCESS);

    ASSERT_TEST(averageTest(chess, 5500,3500,2500,4500,0, false));

    tour = 22;
    ASSERT_TEST(chessAddGame(chess, tour, abraham, ben, FIRST_PLAYER, 500) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tour, ben, caroline, SECOND_PLAYER, 200) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tour, caroline, david, DRAW, 300) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tour, abraham, david, FIRST_PLAYER, 600) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tour, emily, 6666, FIRST_PLAYER, 700) == CHESS_SUCCESS);
    ASSERT_TEST(averageTest(chess, 3025,1925,1375,2475,700,true));

    tour = 33;
    ASSERT_TEST(chessAddGame(chess, tour, abraham, ben, FIRST_PLAYER, 50) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tour, ben, caroline, SECOND_PLAYER, 20) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tour, caroline, david, DRAW, 30) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tour, abraham, david, FIRST_PLAYER, 60) == CHESS_SUCCESS);

    ASSERT_TEST(averageTest(chess, 2035, 1295,925,1665,700, true));

    tour = 44;
    ASSERT_TEST(chessAddGame(chess, tour, abraham, ben, FIRST_PLAYER, 5) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tour, ben, caroline, SECOND_PLAYER, 2) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tour, caroline, david, DRAW, 3) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tour, abraham, david, FIRST_PLAYER, 6) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tour,  6666, emily, FIRST_PLAYER, 900) == CHESS_SUCCESS);
    ASSERT_TEST(averageTest(chess,1527.625,972.125,694.375,1249.875, 800, true));


    ASSERT_TEST(chessEndTournament(chess, 33) == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(chess, 44) == CHESS_SUCCESS);
    ASSERT_TEST(averageTest(chess,1527.625,972.125,694.375,1249.875, 800, true));
    
    ASSERT_TEST(chessRemoveTournament(chess, 11) == CHESS_SUCCESS);
    ASSERT_TEST(averageTest(chess,203.5,129.5,92.5,166.5, 800, true));
    
    ASSERT_TEST(chessRemoveTournament(chess, 33) == CHESS_SUCCESS);
    ASSERT_TEST(averageTest(chess,277.75,176.75,126.25,227.25, 800, true));

    ASSERT_TEST(chessRemoveTournament(chess, 33) == CHESS_TOURNAMENT_NOT_EXIST);
    ASSERT_TEST(chessRemoveTournament(chess, 22) == CHESS_SUCCESS);
    ASSERT_TEST(chessRemoveTournament(chess, 44) == CHESS_SUCCESS);
   
    chessDestroy(chess);
    return true;
}


static bool testSavePlayersLevels_Shimon()
{
    FILE* file_levels = fopen("./actual_output/testSavePlayersLevels_temp.txt", "w");
    ASSERT_TEST(file_levels != NULL);
    ASSERT_TEST(chessSavePlayersLevels(NULL, file_levels) == CHESS_NULL_ARGUMENT);
    ChessSystem chess = chessCreate();
    ASSERT_TEST(chessSavePlayersLevels(chess, NULL) == CHESS_NULL_ARGUMENT);

    ASSERT_TEST(chessSavePlayersLevels(chess, file_levels) == CHESS_SUCCESS);
    ASSERT_TEST(chessSavePlayersLevels(chess, file_levels) == CHESS_SUCCESS);
    fclose(file_levels);
    ASSERT_TEST(0 == system("rm ./actual_output/testSavePlayersLevels_temp.txt"));

    FILE* file_levels0 = fopen("./actual_output/level0.txt", "w");
    ASSERT_TEST(file_levels0 != NULL);
    ASSERT_TEST(chessSavePlayersLevels(chess, file_levels0) == CHESS_SUCCESS);
    fclose(file_levels0);
    ASSERT_TEST(0 == system("rm ./actual_output/level0.txt"));

    chessDestroy(chess);
    return true;
}

static bool testSaveTournamentStatistics_Shimon()
{
    ASSERT_TEST(chessSaveTournamentStatistics(NULL, "This_is_mr_NULL_here.txt") == CHESS_NULL_ARGUMENT);
    ChessSystem chess = chessCreate();
    ASSERT_TEST(chess!= NULL);
    ASSERT_TEST(chessSaveTournamentStatistics(chess, NULL) == CHESS_NULL_ARGUMENT);
    ASSERT_TEST(chessSaveTournamentStatistics(chess,"empty_chess.txt") == CHESS_NO_TOURNAMENTS_ENDED);

    int tournament_id = 1, first_player = 222, second_player = 333, play_time = 1000;
    Winner winner = DRAW;

    ASSERT_TEST(chessAddTournament(chess, tournament_id, 4, "Afula") == CHESS_SUCCESS);
    ASSERT_TEST(chessSaveTournamentStatistics(chess,"./actual_output/try1.txt") == CHESS_NO_TOURNAMENTS_ENDED);
    ASSERT_TEST(chessAddGame(chess, tournament_id, first_player, second_player, winner, play_time) == CHESS_SUCCESS);
    ASSERT_TEST(chessSaveTournamentStatistics(chess,"./actual_output/try2.txt") == CHESS_NO_TOURNAMENTS_ENDED);
    
    ASSERT_TEST(chessAddTournament(chess, tournament_id +1 , 4, "Atlit") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tournament_id + 1 , first_player, second_player, winner, play_time) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tournament_id + 1 , first_player + 1, second_player +1 , winner, play_time) == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(chess, tournament_id + 1) == CHESS_SUCCESS);    
    ASSERT_TEST(chessSaveTournamentStatistics(chess,"./actual_output/try3.txt") == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(chess, tournament_id) == CHESS_SUCCESS);    
    ASSERT_TEST(chessSaveTournamentStatistics(chess,"./actual_output/try4.txt") == CHESS_SUCCESS);

    ASSERT_TEST(chessRemoveTournament(chess, tournament_id + 1) == CHESS_SUCCESS);    
    ASSERT_TEST(chessSaveTournamentStatistics(chess,"./actual_output/try5.txt") == CHESS_SUCCESS);
    ASSERT_TEST(chessRemoveTournament(chess, tournament_id) == CHESS_SUCCESS);    
    ASSERT_TEST(chessSaveTournamentStatistics(chess,"./actual_output/try6.txt") == CHESS_NO_TOURNAMENTS_ENDED);
    
    ASSERT_TEST(0 == system("rm ./actual_output/try3.txt"));
    ASSERT_TEST(0 == system("rm ./actual_output/try4.txt"));
    ASSERT_TEST(0 == system("rm ./actual_output/try5.txt"));
    chessDestroy(chess);
    return true;
}

static bool addPlayersShortLoop(ChessSystem chess, int tour)
{
    int game_time = 50;
    for (int i = 0; i < 1; i++)
    {
        ASSERT_TEST(chessAddGame(chess, tour, abraham, ben, FIRST_PLAYER, game_time) == CHESS_SUCCESS);
        ASSERT_TEST(chessAddGame(chess, tour, ben, caroline, SECOND_PLAYER, game_time) == CHESS_SUCCESS);
        ASSERT_TEST(chessAddGame(chess, tour, caroline, david, DRAW, game_time) == CHESS_SUCCESS);
        ASSERT_TEST(chessAddGame(chess, tour, abraham, david, SECOND_PLAYER, game_time) == CHESS_SUCCESS);
        ASSERT_TEST(chessAddGame(chess, tour, emily, caroline, FIRST_PLAYER, game_time) == CHESS_SUCCESS);    
    }
    return true;    
}


bool testLevelAndStatsShort_Shimon()
{

    FILE* file_levels = fopen("./actual_output/levelShort.txt", "w");
    if(!file_levels)
    {
        printf("test failed to open file, make sure you have the folder tests in the same folder with chessSystem"
               "excutable file and you have write permissions for the file /actual_output/levelShort.txt");
    }

    ChessSystem chess = chessCreate();
    int tournament_removed_a = 11111111;
    int tournament_removed_b = 22222222;

    int tournament_active_a = 33333333;
    int tournament_active_b = 44444444;

    int tournament_ended_a = 55555555;
    int tournament_ended_b = 66666666;

    int tournament_empty = 7777777;


    //adding tournaments
    int max_games = 4;
    ASSERT_TEST(chessAddTournament(chess, tournament_removed_a, max_games, "Removed a") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, tournament_removed_b, max_games, "Removed b") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, tournament_active_a, max_games, "Active a") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, tournament_active_b, max_games, "Active b") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, tournament_ended_a, max_games, "Ended a") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, tournament_ended_b, max_games, "Ended b") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, tournament_empty, 0, "Empty") == CHESS_INVALID_MAX_GAMES);    
    ASSERT_TEST(chessAddTournament(chess, tournament_empty, max_games - 3, "Empty") == CHESS_SUCCESS);    

    int tour;
    
    // adding games to tournaments
    tour = tournament_removed_a;
    int john = 6666;
    ASSERT_TEST(addPlayersShortLoop(chess, tour));
    ASSERT_TEST(chessAddGame(chess, tour, john, david, FIRST_PLAYER, 60) == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(chess, tour) == CHESS_SUCCESS);    
    ASSERT_TEST(chessRemoveTournament(chess, tour) == CHESS_SUCCESS);

    tour = tournament_removed_b;
    ASSERT_TEST(addPlayersShortLoop(chess, tour));
    ASSERT_TEST(chessRemoveTournament(chess, tour) == CHESS_SUCCESS);
    
    tour =  tournament_active_a;
    ASSERT_TEST(addPlayersShortLoop(chess, tour));

    tour = tournament_active_b;
    ASSERT_TEST(addPlayersShortLoop(chess, tour));    

    tour = tournament_ended_a;
    int longest_game_time = 99999;
    int gabriela = 8888;
    ASSERT_TEST(addPlayersShortLoop(chess, tour));
    ASSERT_TEST(chessAddGame(chess, tour, gabriela, emily, FIRST_PLAYER, ++longest_game_time) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tour, emily, gabriela, SECOND_PLAYER, ++longest_game_time) == CHESS_GAME_ALREADY_EXISTS);
    ASSERT_TEST(chessAddGame(chess, tour, gabriela, emily, FIRST_PLAYER, ++longest_game_time) == CHESS_GAME_ALREADY_EXISTS);
    ASSERT_TEST(chessEndTournament(chess, tour) == CHESS_SUCCESS);

    tour = tournament_ended_b;
    longest_game_time = 999999;
    int frank = 7777;
    ASSERT_TEST(addPlayersShortLoop(chess, tour));
    //removing frank and putting him back
    ASSERT_TEST(chessAddGame(chess, tour, frank, abraham, DRAW, longest_game_time) == CHESS_SUCCESS);
    ASSERT_TEST(chessRemovePlayer(chess, frank) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tour, ben, frank, SECOND_PLAYER, ++longest_game_time) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tour, caroline, frank, FIRST_PLAYER, ++longest_game_time) == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(chess, tour) == CHESS_SUCCESS);


    tour = tournament_empty; // do nothing
    ASSERT_TEST(chessRemovePlayer(chess, emily) == CHESS_SUCCESS);
    
    ASSERT_TEST(chessSavePlayersLevels(chess, file_levels) == CHESS_SUCCESS);
    ASSERT_TEST(chessSaveTournamentStatistics(chess, "./actual_output/statsShort.txt") == CHESS_SUCCESS);
    chessDestroy(chess);
    fclose(file_levels);

    ASSERT_TEST(openFilesCompareAndDelete("./expected_output/statsShort.txt", "./actual_output/statsShort.txt"));
    ASSERT_TEST(openFilesCompareAndDelete("./expected_output/levelShort.txt", "./actual_output/levelShort.txt"));
    return true;    
}

bool testLevelAndStats_Shimon()
{
    FILE* file_levels = fopen("./actual_output/level.txt", "w");
    if(!file_levels)
    {
        printf("test failed to open file, make sure you have the folder tests in the same folder with chessSystem"
               "excutable file and you have write permissions for the file /actual_output/level.txt");
    }
    ChessSystem chess = chessCreate();
    ASSERT_TEST(chessEndTournament(chess, 9) == CHESS_TOURNAMENT_NOT_EXIST);
    ASSERT_TEST(chessAddTournament(chess, 9, 500, "London") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, 5, 500, "Tel aviv") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, 44, 3, "New Mexico") == CHESS_INVALID_LOCATION);
    ASSERT_TEST(chessAddTournament(chess, 3, 500, "Ibiza") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, 9, 5, "Morocco") == CHESS_TOURNAMENT_ALREADY_EXISTS);
    ASSERT_TEST(chessAddTournament(chess, 12, 6, "") == CHESS_INVALID_LOCATION);
    ASSERT_TEST(chessAddTournament(chess, 12, 500, "Napoli") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, 3, 10, "Haifa") == CHESS_TOURNAMENT_ALREADY_EXISTS);
    ASSERT_TEST(chessAddTournament(chess, 14, 2, "Eilat") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, 65, 15, "New-York") == CHESS_INVALID_LOCATION);
    ASSERT_TEST(chessRemoveTournament(chess, 14) == CHESS_SUCCESS);
    ASSERT_TEST(chessRemoveTournament(chess, 14) == CHESS_TOURNAMENT_NOT_EXIST);
    int tour = 19;
    ASSERT_TEST(chessAddTournament(chess, tour, 2, "Washington d c ") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tour, 1, 2, FIRST_PLAYER, 5000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tour, 2, 1, FIRST_PLAYER, 2000) == CHESS_GAME_ALREADY_EXISTS);
    ASSERT_TEST(chessAddGame(chess, tour, 1, 2, FIRST_PLAYER, 3000) == CHESS_GAME_ALREADY_EXISTS);
    ASSERT_TEST(chessAddGame(chess, tour, 3, 2, SECOND_PLAYER, 7500) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tour, 4, 1, SECOND_PLAYER, 1000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tour, 2, 4, FIRST_PLAYER, 3500) == CHESS_EXCEEDED_GAMES);
    ASSERT_TEST(chessAddGame(chess, tour, 3, 4, DRAW, 400) == CHESS_SUCCESS);
    ASSERT_TEST(chessRemoveTournament(chess, tour) == CHESS_SUCCESS);
    int t= 15;
    tour = 9;

    ASSERT_TEST(chessAddGame(chess, tour, 1, 2, FIRST_PLAYER, 5000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tour, 2, 1, FIRST_PLAYER, 2000) == CHESS_GAME_ALREADY_EXISTS);
    ASSERT_TEST(chessAddGame(chess, tour, 1, 2, FIRST_PLAYER, 3000) == CHESS_GAME_ALREADY_EXISTS);
    ASSERT_TEST(chessAddGame(chess, tour, 3, 2, SECOND_PLAYER, 7500) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tour, 4, 1, SECOND_PLAYER, 1000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tour, 2, 4, FIRST_PLAYER, 3500) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tour, 3, 4, DRAW, 400) == CHESS_SUCCESS);

    ASSERT_TEST(updatePlayerInLoop(chess, tour,99999,	45,	0,	0,++t));
    ASSERT_TEST(updatePlayerInLoop(chess, tour,88888,	4,	0,	82,++t));
    ASSERT_TEST(updatePlayerInLoop(chess, tour,77777,	40,	0,	0,++t));
    ASSERT_TEST(updatePlayerInLoop(chess, tour,2222,	18,	5,	18,++t));
    ASSERT_TEST(updatePlayerInLoop(chess, tour,7777,	13,	8,	15,++t));
    ASSERT_TEST(updatePlayerInLoop(chess, tour,5555,	11,	5,	11,++t));
    ASSERT_TEST(updatePlayerInLoop(chess, tour,9999,	0,	18,	19,++t));
    ASSERT_TEST(updatePlayerInLoop(chess, tour,4444,	5,	1,	1,++t));
    ASSERT_TEST(updatePlayerInLoop(chess, tour,3333,	4,	15,	3,--t));
    ASSERT_TEST(updatePlayerInLoop(chess, tour,6666,	2,	4,	5,--t));
    ASSERT_TEST(updatePlayerInLoop(chess, tour,1111,	0,	12,	3,--t));
    ASSERT_TEST(chessEndTournament(chess, tour) == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(chess, tour) == CHESS_TOURNAMENT_ENDED);
    tour = 5;
    ASSERT_TEST(updatePlayerInLoop(chess, tour,99999,	89,	60,	54,t));
    ASSERT_TEST(updatePlayerInLoop(chess, tour,77777,	61,	5	,54,t));
    ASSERT_TEST(updatePlayerInLoop(chess, tour,4444,	37,	52	,50,t));
    ASSERT_TEST(updatePlayerInLoop(chess, tour,2222,	15,	10,	90,t));
    ASSERT_TEST(updatePlayerInLoop(chess, tour,88888,	37,	51,	46,t));
    ASSERT_TEST(updatePlayerInLoop(chess, tour,5555,	45,	75,	76,t));
    ASSERT_TEST(updatePlayerInLoop(chess, tour,7777,	57,	73,	74,t));
    ASSERT_TEST(updatePlayerInLoop(chess, tour,6666,	66,	73,	72,t));
    ASSERT_TEST(updatePlayerInLoop(chess, tour,9999,	79,	78,	59,t));
    ASSERT_TEST(updatePlayerInLoop(chess, tour,3333,	45,	41,	87,t));
    ASSERT_TEST(updatePlayerInLoop(chess, tour,1111,    24,	18,	69,t));
    ASSERT_TEST(chessRemoveTournament(chess, tour) == CHESS_SUCCESS);
    tour = 3;
    t=17;
    ASSERT_TEST(chessAddTournament(chess, tour, 1, "Ibiza") == CHESS_TOURNAMENT_ALREADY_EXISTS);
    ASSERT_TEST(updatePlayerInLoop(chess, tour,99999,	35,	46	,24,t));
    ASSERT_TEST(updatePlayerInLoop(chess, tour,77777,	94,	46	,58,t));
    ASSERT_TEST(updatePlayerInLoop(chess, tour,4444,	22,	7	,69,t));
    ASSERT_TEST(updatePlayerInLoop(chess, tour,2222,	1,	39,	8,t));
    ASSERT_TEST(updatePlayerInLoop(chess, tour,88888,	53,	77,	47,t));
    ASSERT_TEST(updatePlayerInLoop(chess, tour,5555,	89,	48,	82,t));
    ASSERT_TEST(updatePlayerInLoop(chess, tour,7777	,55,	21,	29,t));
    ASSERT_TEST(updatePlayerInLoop(chess, tour,6666	,90	,30,	95,t));
    ASSERT_TEST(updatePlayerInLoop(chess, tour,9999,	31,	33,	14,t));
    ASSERT_TEST(updatePlayerInLoop(chess, tour,3333,	66,	38,	14,t));
    ASSERT_TEST(updatePlayerInLoop(chess, tour,1111,	20,	32,	1,t));
    ASSERT_TEST(chessEndTournament(chess, tour) == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(chess, tour) == CHESS_TOURNAMENT_ENDED);
    tour = 12;  
    ASSERT_TEST(chessAddGame(chess, tour, 9999999, 1111111, FIRST_PLAYER, 5000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tour, 9999999, 1111112, SECOND_PLAYER, 5000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tour, 1111113, 9999999, FIRST_PLAYER, 5000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tour, 1111117, 9999999, FIRST_PLAYER, 5000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tour, 93, 456, FIRST_PLAYER, 2000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tour, 1456, 18, FIRST_PLAYER, 3000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tour, 1156, 2, SECOND_PLAYER, 7500) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, tour, -17, 7, SECOND_PLAYER, 1000) == CHESS_INVALID_ID);
    ASSERT_TEST(chessAddGame(chess, -15, 13517, 156, SECOND_PLAYER, 1000) == CHESS_INVALID_ID);
    ASSERT_TEST(chessAddGame(chess, tour, 15, -1, FIRST_PLAYER, 3500) == CHESS_INVALID_ID);
    
    
    ASSERT_TEST(chessSavePlayersLevels(chess, file_levels) == CHESS_SUCCESS);
    ASSERT_TEST(chessSaveTournamentStatistics(chess, "./actual_output/stats.txt") == CHESS_SUCCESS);
    chessDestroy(chess);
    fclose(file_levels);

    ASSERT_TEST(openFilesCompareAndDelete("./expected_output/stats.txt", "./actual_output/stats.txt"));
    ASSERT_TEST(openFilesCompareAndDelete("./expected_output/level.txt", "./actual_output/level.txt"));
    return true;
}

//segel tests
bool testChessAddTournament_segel() {
    ChessSystem chess = chessCreate();
    ASSERT_TEST(chessAddTournament(chess, 1, 4, "London") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, 2, 5, "London") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, 1, 10, "Paris") == CHESS_TOURNAMENT_ALREADY_EXISTS);

    chessDestroy(chess);
    return true;
}

bool testChessRemoveTournament_segel() {
    ChessSystem chess = chessCreate();
    ASSERT_TEST(chessAddTournament(chess, 1, 4, "London") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, 2, 4, "London") == CHESS_SUCCESS);
    ASSERT_TEST(chessRemoveTournament(chess, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessRemoveTournament(chess, 1) == CHESS_TOURNAMENT_NOT_EXIST);
    ASSERT_TEST(chessAddTournament(chess, 1, 4, "Paris") == CHESS_SUCCESS);

    chessDestroy(chess);
    return true;
}

bool testChessAddGame_segel(){
    ChessSystem chess = chessCreate();
    ASSERT_TEST(chessAddGame(chess, 1, 1, 2, FIRST_PLAYER, 2000) == CHESS_TOURNAMENT_NOT_EXIST);
    ASSERT_TEST(chessAddTournament(chess, 1, 4, "London") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, 1, 1, 2, FIRST_PLAYER, 2000) == CHESS_SUCCESS);

    chessDestroy(chess);
    return true;
}

bool testChessPrintLevelsAndTournamentStatistics_segel(){
    FILE* file_levels = fopen("actual_output/player_levels_actual_output.txt", "w");
    if(!file_levels){
        printf("test failed to open file, make sure you have the folder tests in the same folder with chessSystem"
               "excutable file and you have write permissions for the file /actual_output/player_levels_actual_output.txt");
        return false;
    }
    ChessSystem chess = chessCreate();
    ASSERT_TEST(chessAddTournament(chess, 1, 4, "London") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, 1, 1, 2, FIRST_PLAYER, 2000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, 1, 1, 3, FIRST_PLAYER, 3000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, 1, 3, 2, SECOND_PLAYER, 3000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, 1, 4, 1, SECOND_PLAYER, 1000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, 1, 2, 4, FIRST_PLAYER, 3500) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, 1, 3, 4, DRAW, 400) == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(chess, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessSavePlayersLevels(chess, file_levels) == CHESS_SUCCESS);
    ASSERT_TEST(chessSaveTournamentStatistics(chess, "actual_output/tournament_statistics_actual_output.txt") == CHESS_SUCCESS);
    fclose(file_levels);


    ASSERT_TEST(openFilesCompareAndDelete("./expected_output/player_levels_expected_output.txt", "./actual_output/player_levels_actual_output.txt"));
    ASSERT_TEST(openFilesCompareAndDelete("./expected_output/tournament_statistics_expected_output.txt", "./actual_output/tournament_statistics_actual_output.txt"));
    chessDestroy(chess);
    
    return true;
}

//maaroof the ashkiller tests:
bool testChessDestroy_maaroof() {
    chessDestroy(NULL);

    ChessSystem sys1 = chessCreate();
    chessDestroy(sys1);

    ChessSystem sys2 = chessCreate();
    ASSERT_TEST(chessAddTournament(sys2, 1, 1, "Location one") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys2, 2, 1, "Location two") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys2, 3, 1, "Location three") == CHESS_SUCCESS);
    chessDestroy(sys2);

    ChessSystem sys3 = chessCreate();
    ASSERT_TEST(chessAddTournament(sys3, 1, 1, "Location one") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys3, 2, 1, "Location two") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys3, 3, 1, "Location three") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys3, 1, 01, 02, FIRST_PLAYER, 5) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys3, 2, 01, 02, FIRST_PLAYER, 5) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys3, 3, 01, 02, FIRST_PLAYER, 5) == CHESS_SUCCESS);
    chessDestroy(sys3);

    return true;
}

bool testChessAddTournamentAndEndTournament_maaroof() {
    ChessSystem sys1 = chessCreate();
    ASSERT_TEST(chessAddTournament(sys1, 1, 1, NULL) == CHESS_NULL_ARGUMENT);
    ASSERT_TEST(chessAddTournament(NULL, 1, 1, "Location one") == CHESS_NULL_ARGUMENT);

    ASSERT_TEST(chessAddTournament(sys1, 1, 1, "Location one") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys1, 2, 1, "Location two") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys1, 3, 1, "Location three") == CHESS_SUCCESS);
    
    ASSERT_TEST(chessEndTournament(sys1, 1) == CHESS_NO_GAMES);
    ASSERT_TEST(chessEndTournament(NULL, -1) == CHESS_NULL_ARGUMENT);
    ASSERT_TEST(chessEndTournament(sys1, -1) == CHESS_INVALID_ID);
    
    ASSERT_TEST(chessAddTournament(sys1, 1, 1, "Location one") == CHESS_TOURNAMENT_ALREADY_EXISTS);
    ASSERT_TEST(chessAddTournament(sys1, 1, 1, "invalid location") == CHESS_TOURNAMENT_ALREADY_EXISTS);
    ASSERT_TEST(chessAddTournament(sys1, 4, -1, "invalid location") == CHESS_INVALID_LOCATION);
    ASSERT_TEST(chessAddTournament(sys1, 4, -1, "London") == CHESS_INVALID_MAX_GAMES);

    ASSERT_TEST(chessAddTournament(sys1, -2, -1, "invalid location") == CHESS_INVALID_ID);
    ASSERT_TEST(chessAddTournament(sys1, 2, -1, "invalid location") == CHESS_TOURNAMENT_ALREADY_EXISTS);
    ASSERT_TEST(chessAddTournament(sys1, 5, 1, "invalid location") == CHESS_INVALID_LOCATION);
    ASSERT_TEST(chessAddTournament(sys1, 5, 1, " Invalid location") == CHESS_INVALID_LOCATION);
    ASSERT_TEST(chessAddTournament(sys1, 10, 1, "L") == CHESS_SUCCESS);
    
    int player_1 = 1;
    int player_2 = 2;
    ASSERT_TEST(chessAddGame(sys1, 1, player_1, player_2, FIRST_PLAYER, 10) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 2, player_1, player_2, SECOND_PLAYER, 10) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 3, player_1, player_2, SECOND_PLAYER, 10) == CHESS_SUCCESS);

    ASSERT_TEST(chessEndTournament(sys1, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(sys1, 2) == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(sys1, 3) == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(sys1, 3) == CHESS_TOURNAMENT_ENDED);
    ASSERT_TEST(chessEndTournament(sys1, 4) == CHESS_TOURNAMENT_NOT_EXIST);
    ASSERT_TEST(chessEndTournament(sys1, -1) == CHESS_INVALID_ID);

   
    ASSERT_TEST(chessAddGame(sys1, 1, 4, 5, FIRST_PLAYER, 10) == CHESS_TOURNAMENT_ENDED);
    ASSERT_TEST(chessSaveTournamentStatistics(sys1, "actual_output/test_add_tournament_end_tournament.txt") == CHESS_SUCCESS);


    ASSERT_TEST(openFilesCompareAndDelete("./expected_output/test_add_tournament_end_tournament.txt", "./actual_output/test_add_tournament_end_tournament.txt"));

    ChessSystem sys2 = chessCreate();
    ASSERT_TEST(chessAddTournament(sys2, 1, 1, "Location one") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys2, 2, 1, "Location two") == CHESS_SUCCESS);
    ASSERT_TEST(chessSaveTournamentStatistics(sys2, "document.txt") == CHESS_NO_TOURNAMENTS_ENDED);

    chessDestroy(sys2);
    chessDestroy(sys1);
    
    return true;
}

bool testChessAddGame_maaroof()
{
    ChessSystem sys1 = chessCreate();
    ASSERT_TEST(chessAddTournament(sys1, 1, 1, "Location one") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys1, 2, 1, "Location two") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys1, 3, 1, "Location three") == CHESS_SUCCESS);
    
    int player_1 = 1;
    int player_2 = 2;
    int player_3 = 3;
    int player_4 = 4;

    ASSERT_TEST(chessAddGame(sys1, 1, player_1, player_2, FIRST_PLAYER, 10) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 1, player_1, player_2, FIRST_PLAYER, 10) == CHESS_GAME_ALREADY_EXISTS);
    ASSERT_TEST(chessAddGame(sys1, 1, player_2, player_1, FIRST_PLAYER, 10) == CHESS_GAME_ALREADY_EXISTS);
    ASSERT_TEST(chessAddGame(sys1, 2, player_1, player_2, FIRST_PLAYER, 10) == CHESS_SUCCESS);

    ASSERT_TEST(chessAddGame(sys1, 1, player_3, player_3, FIRST_PLAYER, 10) == CHESS_INVALID_ID);
    ASSERT_TEST(chessAddGame(sys1, 1, player_3, player_4, FIRST_PLAYER, -1) == CHESS_INVALID_PLAY_TIME);
    //not sure about ZERO as play time
    //ASSERT_TEST(chessAddGame(sys1, 1, player_1, player_2, FIRST_PLAYER, 0) == CHESS_INVALID_PLAY_TIME);
    ASSERT_TEST(chessAddGame(sys1, -1, player_1, player_2, FIRST_PLAYER, -1) == CHESS_INVALID_ID);
    ASSERT_TEST(chessAddGame(sys1, 1, -8, player_2, FIRST_PLAYER, -1) == CHESS_INVALID_ID);

    ASSERT_TEST(chessAddGame(sys1, 1, player_1, player_3, SECOND_PLAYER, 10) == CHESS_EXCEEDED_GAMES);
    ASSERT_TEST(chessAddGame(sys1, 1, player_3, player_2, FIRST_PLAYER, 10) == CHESS_EXCEEDED_GAMES);
    ASSERT_TEST(chessAddGame(sys1, 1, player_3, player_1, FIRST_PLAYER, 10) == CHESS_EXCEEDED_GAMES);
    ASSERT_TEST(chessAddGame(sys1, 1, player_1, player_4, SECOND_PLAYER, 10) == CHESS_EXCEEDED_GAMES);
    ASSERT_TEST(chessAddGame(sys1, 3, player_1, player_2, FIRST_PLAYER, 10) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 4, player_1, player_2, FIRST_PLAYER, 10) == CHESS_TOURNAMENT_NOT_EXIST);

    ASSERT_TEST(chessAddTournament(sys1, 4, 2, "Location four") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 4, player_1, player_2, FIRST_PLAYER, 10) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 4, player_3, player_2, SECOND_PLAYER, 10) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 4, player_3, player_2, FIRST_PLAYER, 10) == CHESS_GAME_ALREADY_EXISTS);
    ASSERT_TEST(chessAddGame(sys1, 4, player_4, player_2, FIRST_PLAYER, 10) == CHESS_EXCEEDED_GAMES);
    
    ASSERT_TEST(chessAddGame(sys1, 4, player_3, player_4, FIRST_PLAYER, 10) == CHESS_SUCCESS);
    ASSERT_TEST(chessRemovePlayer(sys1,player_3) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 4, player_3, player_4, FIRST_PLAYER, 10) == CHESS_SUCCESS);

    chessDestroy(sys1);
    return true;
}

bool testRemoveTournament_maaroof() 
{
    ChessSystem sys1 = chessCreate();
    ASSERT_TEST(chessAddTournament(sys1, 1, 3, "Location one") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys1, 2, 3, "Location two") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys1, 3, 3, "Location three") == CHESS_SUCCESS);
    ASSERT_TEST(chessRemoveTournament(sys1, 3) == CHESS_SUCCESS);

    int player_1 = 1;
    int player_2 = 2;
    int player_3 = 3;
    //int player_4 = 4;

    ASSERT_TEST(chessAddGame(sys1, 3, player_1, player_2, FIRST_PLAYER, 10) == CHESS_TOURNAMENT_NOT_EXIST);
    ASSERT_TEST(chessAddGame(sys1, 2, player_1, player_2, FIRST_PLAYER, 10) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 2, player_3, player_2, FIRST_PLAYER, 10) == CHESS_SUCCESS);
    ASSERT_TEST(chessRemoveTournament(sys1, 2) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 2, player_1, player_2, FIRST_PLAYER, 10) == CHESS_TOURNAMENT_NOT_EXIST);
    ASSERT_TEST(chessAddGame(sys1, 2, -1, player_2, FIRST_PLAYER, 10) == CHESS_INVALID_ID);
    ASSERT_TEST(chessAddGame(sys1, -1, player_1, player_2, FIRST_PLAYER, -10) == CHESS_INVALID_ID);

    ASSERT_TEST(chessAddGame(sys1, 1, player_1, player_2, FIRST_PLAYER, 10) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 1, player_3, player_2, FIRST_PLAYER, 10) == CHESS_SUCCESS);

    ASSERT_TEST(chessSaveTournamentStatistics(sys1,"actual_output/test_tournament_remove.txt") == CHESS_NO_TOURNAMENTS_ENDED);

    ASSERT_TEST(chessEndTournament(sys1, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessSaveTournamentStatistics(sys1, "actual_output/test_tournament_remove.txt") == CHESS_SUCCESS);



    ASSERT_TEST(openFilesCompareAndDelete("./expected_output/test_tournament_remove.txt", "./actual_output/test_tournament_remove.txt"));

    chessDestroy(sys1);
    
    return true;
}

bool testChessRemovePlayer_maaroof() {
    ChessSystem sys1 = chessCreate();
    ASSERT_TEST(chessAddTournament(sys1, 1, 3, "Location one") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys1, 2, 3, "Location two") == CHESS_SUCCESS);
    
    int player_1 = 1;
    int player_2 = 2;
    int player_3 = 3;
    
    ASSERT_TEST(chessAddGame(sys1, 1, player_1, player_2, FIRST_PLAYER, 6) == CHESS_SUCCESS); //tour 1: add 1,2
    ASSERT_TEST(chessAddGame(sys1, 1, player_3, player_2, FIRST_PLAYER, 4) == CHESS_SUCCESS); //tour 1: add 3,2
    ASSERT_TEST(chessAddGame(sys1, 2, player_1, player_2, FIRST_PLAYER, 10) == CHESS_SUCCESS);//tour 2: add 1,2
    
    FILE* file_levels = fopen("actual_output/player_levels_all.txt", "w");
    ASSERT_TEST(chessSavePlayersLevels(sys1, file_levels) == CHESS_SUCCESS);
    fclose(file_levels);

    ASSERT_TEST(openFilesCompareAndDelete("./expected_output/player_levels_all.txt", "./actual_output/player_levels_all.txt"));
    
    ASSERT_TEST(chessRemovePlayer(sys1, player_1) == CHESS_SUCCESS);//remove 1
    ASSERT_TEST(chessEndTournament(sys1, 1) == CHESS_SUCCESS);//end 1
    ASSERT_TEST(chessEndTournament(sys1, 2) == CHESS_SUCCESS);//end 2
    
    FILE* file_levels_2 = fopen("actual_output/remove_player_1.txt", "w");
    ASSERT_TEST(chessSavePlayersLevels(sys1, file_levels_2) == CHESS_SUCCESS);//print
    ASSERT_TEST(chessRemovePlayer(sys1, player_1) == CHESS_PLAYER_NOT_EXIST);
    fclose(file_levels_2);


    ASSERT_TEST(openFilesCompareAndDelete("./expected_output/remove_player_1.txt", "./actual_output/remove_player_1.txt"));

    chessDestroy(sys1);
    
    return true;
}

bool testChessRemovePlayer_2_maaroof() {
    ChessSystem sys1 = chessCreate();
    ASSERT_TEST(chessAddTournament(sys1, 1, 3, "Location one") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys1, 2, 3, "Location two") == CHESS_SUCCESS);

    int player_1 = 1;
    int player_2 = 2;

    ASSERT_TEST(chessAddGame(sys1, 1, player_1, player_2, FIRST_PLAYER, 6) == CHESS_SUCCESS); //tour 1: add 1,2
    
    FILE* file1 = fopen("actual_output/before_remove.txt", "w");
    ASSERT_TEST(chessSavePlayersLevels(sys1, file1) == CHESS_SUCCESS);
    fclose(file1);
    
    ASSERT_TEST(openFilesCompareAndDelete("./expected_output/before_remove.txt", "./actual_output/before_remove.txt"));

    ASSERT_TEST(chessRemovePlayer(sys1, player_1) == CHESS_SUCCESS);//remove 1

    file1 = fopen("actual_output/after_remove.txt", "w");
    ASSERT_TEST(chessSavePlayersLevels(sys1, file1) == CHESS_SUCCESS);
    fclose(file1);

    ASSERT_TEST(openFilesCompareAndDelete("./expected_output/after_remove.txt", "./actual_output/after_remove.txt"));

    ASSERT_TEST(chessAddGame(sys1, 1, player_1, player_2, FIRST_PLAYER, 6) == CHESS_SUCCESS); //tour 1: add 1,2
    
    file1 = fopen("actual_output/add_same_game_after_remove.txt", "w");
    ASSERT_TEST(chessSavePlayersLevels(sys1, file1) == CHESS_SUCCESS);
    fclose(file1);

    ASSERT_TEST(openFilesCompareAndDelete("./expected_output/add_same_game_after_remove.txt", "./actual_output/add_same_game_after_remove.txt"));
    chessDestroy(sys1);
    
    return true;
}

bool testAvgGameTime_maaroof() 
{
    ChessSystem sys1 = chessCreate();
    ASSERT_TEST(chessAddTournament(sys1, 1, 3, "Location one") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys1, 2, 3, "Location two") == CHESS_SUCCESS);

    int player_1 = 1;
    int player_2 = 2;
    int player_3 = 3;
    int player_4 = 4;

    ChessResult* chess_result = malloc(sizeof(*chess_result));
    ASSERT_TEST(chessAddGame(sys1, 1, player_1, player_2, FIRST_PLAYER, 6) == CHESS_SUCCESS); //tour 1: add 1,2
    double avg1 = chessCalculateAveragePlayTime(sys1, player_1, chess_result);
    ASSERT_TEST(*chess_result == CHESS_SUCCESS);
    double avg2 = chessCalculateAveragePlayTime(sys1, player_2, chess_result);
    ASSERT_TEST(*chess_result == CHESS_SUCCESS);
    ASSERT_TEST(avg1 == avg2);
    ASSERT_TEST(avg1 == 6);
    
    ASSERT_TEST(chessAddGame(sys1, 1, player_1, player_3, FIRST_PLAYER, 14) == CHESS_SUCCESS);
    avg1 = chessCalculateAveragePlayTime(sys1, player_1, chess_result);
    ASSERT_TEST(*chess_result == CHESS_SUCCESS);
    ASSERT_TEST(avg1 == 10);

    avg1 = chessCalculateAveragePlayTime(sys1, player_3, chess_result);
    ASSERT_TEST(*chess_result == CHESS_SUCCESS);
    ASSERT_TEST(avg1 == 14);

    ASSERT_TEST(chessAddGame(sys1, 2, player_1, player_3, FIRST_PLAYER, 20) == CHESS_SUCCESS);
    avg1 = chessCalculateAveragePlayTime(sys1, player_1, chess_result);
    ASSERT_TEST(*chess_result == CHESS_SUCCESS);
    ASSERT_TEST(avg1 == 40.0/3.0);

    avg1 = chessCalculateAveragePlayTime(sys1, player_3, chess_result);
    ASSERT_TEST(*chess_result == CHESS_SUCCESS);
    ASSERT_TEST(avg1 == 17);

    chessCalculateAveragePlayTime(sys1, player_4, chess_result);
    ASSERT_TEST(*chess_result == CHESS_PLAYER_NOT_EXIST);

    chessCalculateAveragePlayTime(sys1, -1, chess_result);
    ASSERT_TEST(*chess_result == CHESS_INVALID_ID);

    chessCalculateAveragePlayTime(NULL, player_4, chess_result);
    ASSERT_TEST(*chess_result == CHESS_NULL_ARGUMENT);

    chessCalculateAveragePlayTime(NULL, -1, chess_result);
    ASSERT_TEST(*chess_result == CHESS_NULL_ARGUMENT);

    ASSERT_TEST(chessRemovePlayer(sys1, player_1) == CHESS_SUCCESS);
    chessCalculateAveragePlayTime(sys1, player_1, chess_result);
    ASSERT_TEST(*chess_result == CHESS_PLAYER_NOT_EXIST);
    
    avg1 = chessCalculateAveragePlayTime(sys1, player_3, chess_result);
    ASSERT_TEST(*chess_result == CHESS_SUCCESS);
    ASSERT_TEST(avg1 == 17);

    ASSERT_TEST(chessAddGame(sys1, 2, player_1, player_3, FIRST_PLAYER, 20) == CHESS_SUCCESS);
    avg1 = chessCalculateAveragePlayTime(sys1, player_1, chess_result);
    ASSERT_TEST(*chess_result == CHESS_SUCCESS);
    ASSERT_TEST(avg1 == 20);

    avg1 = chessCalculateAveragePlayTime(sys1, player_3, chess_result);
    ASSERT_TEST(*chess_result == CHESS_SUCCESS);
    ASSERT_TEST(avg1 == 18);

    free(chess_result);
    chessDestroy(sys1);
    return true;
}

bool testSavePlayerLevelsAndTournamentStatistics_maaroof() 
{
    ChessSystem sys1 = chessCreate();
    ASSERT_TEST(chessAddTournament(sys1, 1, 3, "Location one") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys1, 2, 3, "Location two") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys1, 3, 3, "Location three") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys1, 4, 3, "Location four") == CHESS_SUCCESS);

    int player_1 = 1;
    int player_2 = 2;
    //int player_3 = 3;
    //int player_4 = 4;
    //int player_5 = 5;

    char* fileName = "";
   // FILE* file;

    ASSERT_TEST(chessAddGame(sys1, 4, player_1, player_2, FIRST_PLAYER, 6) == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(sys1, 4) == CHESS_SUCCESS);
    fileName = "actual_output/tournament_statistics_1.txt";
    ASSERT_TEST(chessSaveTournamentStatistics(sys1, fileName) == CHESS_SUCCESS);
    
    ASSERT_TEST(openFilesCompareAndDelete("./expected_output/tournament_statistics_1.txt", "./actual_output/tournament_statistics_1.txt"));

    ASSERT_TEST(chessAddGame(sys1, 3, player_1, player_2, FIRST_PLAYER, 6) == CHESS_SUCCESS);
    ASSERT_TEST(chessRemovePlayer(sys1, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(sys1, 3) == CHESS_SUCCESS);
    fileName = "actual_output/tournament_statistics_2.txt";
    ASSERT_TEST(chessSaveTournamentStatistics(sys1, fileName) == CHESS_SUCCESS);


    ASSERT_TEST(openFilesCompareAndDelete("./expected_output/tournament_statistics_2.txt", "./actual_output/tournament_statistics_2.txt"));

    ASSERT_TEST(chessAddGame(sys1, 2, player_1, player_2, FIRST_PLAYER, 6) == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(sys1, 2) == CHESS_SUCCESS);
    fileName = "actual_output/tournament_statistics_3.txt";
    ASSERT_TEST(chessSaveTournamentStatistics(sys1, fileName) == CHESS_SUCCESS);

    ASSERT_TEST(openFilesCompareAndDelete("./expected_output/tournament_statistics_3.txt", "./actual_output/tournament_statistics_3.txt"));
    chessDestroy(sys1);
   
    return true;
}

bool oneMoreTestJustYouKnowToMakeSureEveryThingWorksFine_maaroof() {
    ChessSystem sys1 = chessCreate();
    ASSERT_TEST(chessAddTournament(sys1, 1, 5, "Location one") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys1, 2, 5, "Location two") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys1, 3, 5, "Location three") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys1, 4, 5, "Location four") == CHESS_SUCCESS);

    int player_1 = 1;
    int player_2 = 2;
    int player_3 = 3;
    int player_4 = 4;
    int player_5 = 5;

    //tournament_1
    ASSERT_TEST(chessAddGame(sys1, 1, player_2, player_1, FIRST_PLAYER, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 1, player_2, player_3, SECOND_PLAYER, 2) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 1, player_2, player_4, SECOND_PLAYER, 3) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 1, player_2, player_5, FIRST_PLAYER, 4) == CHESS_SUCCESS);
    
    ASSERT_TEST(chessEndTournament(sys1, 1) == CHESS_SUCCESS);
    char* file_name = "actual_output/tour1.txt";
    chessSaveTournamentStatistics(sys1, file_name);
    ASSERT_TEST(openFilesCompareAndDelete("./expected_output/tour1.txt", "./actual_output/tour1.txt"));

    ASSERT_TEST(chessRemovePlayer(sys1, 2) == CHESS_SUCCESS);
    file_name = "actual_output/tour1_remove_while_ended.txt";
    chessSaveTournamentStatistics(sys1, file_name);

    ASSERT_TEST(openFilesCompareAndDelete("./expected_output/tour1_remove_while_ended.txt", "./actual_output/tour1_remove_while_ended.txt"));
    
    //tournament_2
    ASSERT_TEST(chessAddGame(sys1, 2, player_2, player_1, FIRST_PLAYER, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 2, player_2, player_3, SECOND_PLAYER, 2) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 2, player_2, player_4, SECOND_PLAYER, 3) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 2, player_2, player_5, FIRST_PLAYER, 4) == CHESS_SUCCESS);

    ASSERT_TEST(chessRemovePlayer(sys1, 2) == CHESS_SUCCESS);//remove winner
       
    file_name = "actual_output/tour2_remove_winner.txt";
    ASSERT_TEST(chessEndTournament(sys1, 2) == CHESS_SUCCESS);
    chessSaveTournamentStatistics(sys1, file_name);
    ASSERT_TEST(openFilesCompareAndDelete("./expected_output/tour2_remove_winner.txt", "./actual_output/tour2_remove_winner.txt"));


    //tournament_3
    ASSERT_TEST(chessAddGame(sys1, 3, player_2, player_1, FIRST_PLAYER, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 3, player_2, player_3, SECOND_PLAYER, 2) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 3, player_2, player_4, SECOND_PLAYER, 3) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 3, player_2, player_5, FIRST_PLAYER, 4) == CHESS_SUCCESS);

    ASSERT_TEST(chessRemovePlayer(sys1, 2) == CHESS_SUCCESS);//remove winner


    ASSERT_TEST(chessAddGame(sys1, 3, player_2, player_1, FIRST_PLAYER, 5) == CHESS_SUCCESS);
    
    file_name = "actual_output/tour3_add_same_game.txt";
    ASSERT_TEST(chessEndTournament(sys1, 3) == CHESS_SUCCESS);
    chessSaveTournamentStatistics(sys1, file_name);
    ASSERT_TEST(openFilesCompareAndDelete("./expected_output/tour3_add_same_game.txt", "./actual_output/tour3_add_same_game.txt"));


    chessDestroy(sys1);
   
    return true;
}

bool testPlayerLevelsAdvanced_maaroof() {
    //add game
    //remove player
    //add game
    //print players
    //see if the first game applies
    ChessSystem sys1 = chessCreate();
    ASSERT_TEST(chessAddTournament(sys1, 1, 5, "Location one") == CHESS_SUCCESS);
    int player_1 = 1;
    int player_2 = 2;
    ASSERT_TEST(chessAddGame(sys1, 1, player_1, player_2, FIRST_PLAYER, 3) == CHESS_SUCCESS);
    //ASSERT_TEST(chessRemovePlayer(sys1, player_1) == CHESS_SUCCESS);
    FILE* f = fopen("actual_output/test_player_level_advanced.txt", "w");
    ASSERT_TEST(f != NULL);
    ASSERT_TEST(chessSavePlayersLevels(sys1, f) == CHESS_SUCCESS);
    fclose(f);

    ASSERT_TEST(chessRemovePlayer(sys1, player_1) == CHESS_SUCCESS);

    f = fopen("actual_output/test_player_level_advanced_after_remove.txt", "w");
    ASSERT_TEST(f != NULL);
    ASSERT_TEST(chessSavePlayersLevels(sys1, f) == CHESS_SUCCESS);
    fclose(f);

    ASSERT_TEST(chessAddGame(sys1, 1, player_1, player_2, FIRST_PLAYER, 3) == CHESS_SUCCESS);
    f = fopen("actual_output/test_player_level_advanced_add_same_game.txt", "w");
    ASSERT_TEST(f != NULL);
    ASSERT_TEST(chessSavePlayersLevels(sys1, f) == CHESS_SUCCESS);
    fclose(f);
    ASSERT_TEST(openFilesCompareAndDelete("./expected_output/test_player_level_advanced.txt", "./actual_output/test_player_level_advanced.txt"));    
    ASSERT_TEST(openFilesCompareAndDelete("./expected_output/test_player_level_advanced_after_remove.txt", "./actual_output/test_player_level_advanced_after_remove.txt"));    
    ASSERT_TEST(openFilesCompareAndDelete("./expected_output/test_player_level_advanced_add_same_game.txt", "./actual_output/test_player_level_advanced_add_same_game.txt"));        

    chessDestroy(sys1);
   
    return true;
}

bool testTournamentWinner_maaroof() {
    ChessSystem sys1 = chessCreate();
    ChessSystem sys2 = chessCreate();

    ASSERT_TEST(chessAddTournament(sys1, 1, 5, "Location one") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys1, 2, 5, "Location two") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys1, 3, 5, "Location three") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys1, 4, 5, "Location four") == CHESS_SUCCESS);

    ASSERT_TEST(chessAddTournament(sys2, 2, 5, "Location two") == CHESS_SUCCESS);//to sys2

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
    char* file_name = "actual_output/winner_of_tour_1.txt";
    ASSERT_TEST(chessSaveTournamentStatistics(sys1, file_name) == CHESS_SUCCESS);
    ASSERT_TEST(openFilesCompareAndDelete("./expected_output/winner_of_tour_1.txt", "./actual_output/winner_of_tour_1.txt"));        

    FILE* f = fopen("actual_output/test_player_score_1.txt", "w");
    ASSERT_TEST(f != NULL);
    ASSERT_TEST(chessSavePlayersLevels(sys1, f) == CHESS_SUCCESS);
    fclose(f);
    ASSERT_TEST(openFilesCompareAndDelete("./expected_output/test_player_score_1.txt", "./actual_output/test_player_score_1.txt"));        
    
    //tournament_2
    ASSERT_TEST(chessAddGame(sys1, 2, player_1, player_5, DRAW, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 2, player_1, player_6, DRAW, 2) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 2, player_1, player_2, FIRST_PLAYER, 3) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 2, player_1, player_3, SECOND_PLAYER, 4) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 2, player_3, player_4, FIRST_PLAYER, 5) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 2, player_3, player_2, SECOND_PLAYER, 6) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 2, player_4, player_5, FIRST_PLAYER, 7) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 2, player_4, player_6, FIRST_PLAYER, 8) == CHESS_SUCCESS);

    ASSERT_TEST(chessRemovePlayer(sys1,3) == CHESS_SUCCESS);//remove winner

    ASSERT_TEST(chessEndTournament(sys1, 2) == CHESS_SUCCESS);
    file_name = "actual_output/winner_of_tour_2.txt";
    chessSaveTournamentStatistics(sys1, file_name);
    f = fopen("actual_output/test_player_score_2_after_remove.txt", "w");
    ASSERT_TEST(f != NULL);
    ASSERT_TEST(chessSavePlayersLevels(sys1, f) == CHESS_SUCCESS);
    fclose(f);
    ASSERT_TEST(openFilesCompareAndDelete("./expected_output/winner_of_tour_2.txt", "./actual_output/winner_of_tour_2.txt"));        
    ASSERT_TEST(openFilesCompareAndDelete("./expected_output/test_player_score_2_after_remove.txt", "./actual_output/test_player_score_2_after_remove.txt"));        

    //sys2:
    ASSERT_TEST(chessAddGame(sys2, 2, player_1, player_5, DRAW, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys2, 2, player_1, player_6, DRAW, 2) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys2, 2, player_1, player_2, FIRST_PLAYER, 3) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys2, 2, player_1, player_3, SECOND_PLAYER, 4) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys2, 2, player_3, player_4, FIRST_PLAYER, 5) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys2, 2, player_3, player_2, SECOND_PLAYER, 6) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys2, 2, player_4, player_5, FIRST_PLAYER, 7) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys2, 2, player_4, player_6, FIRST_PLAYER, 8) == CHESS_SUCCESS);

    ASSERT_TEST(chessRemovePlayer(sys2, 3) == CHESS_SUCCESS);//remove winner

    ASSERT_TEST(chessEndTournament(sys2, 2) == CHESS_SUCCESS);
    file_name = "actual_output/winner_of_tour_2_sys2.txt";
    chessSaveTournamentStatistics(sys2, file_name);
    f = fopen("actual_output/test_player_score_2_after_remove_sys2.txt", "w");
    ASSERT_TEST(f != NULL);
    ASSERT_TEST(chessSavePlayersLevels(sys2, f) == CHESS_SUCCESS);
    fclose(f);
    ASSERT_TEST(openFilesCompareAndDelete("./expected_output/winner_of_tour_2_sys2.txt", "./actual_output/winner_of_tour_2_sys2.txt"));        
    ASSERT_TEST(openFilesCompareAndDelete("./expected_output/test_player_score_2_after_remove_sys2.txt", "./actual_output/test_player_score_2_after_remove_sys2.txt"));        

    chessDestroy(sys2);
    chessDestroy(sys1);
    
   
    return true;
}



bool testPlayerAfterRemoveTournament_Shimon()
{
    ChessSystem chess = chessCreate();
    ASSERT_TEST(NULL != chess);
    int tour_paris = 135;
    int tour_vegas = 778;
    int play_time_paris = 165156; //even number
    int play_time_vegas = 123680; // even number
    ChessResult res;
    ASSERT_TEST(chessAddTournament(chess, tour_paris, 1, "Paris Hilton") == CHESS_INVALID_LOCATION);
    ASSERT_TEST(chessAddTournament(chess, tour_paris, 1, "Paris hilton street") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, tour_vegas, 1, "Vegas") == CHESS_SUCCESS);
    
    // add game in nparis
    ASSERT_TEST(chessAddGame(chess, tour_paris, emily, ben, FIRST_PLAYER, play_time_paris) == CHESS_SUCCESS);

    double average_ben = chessCalculateAveragePlayTime(chess, ben, &res);
    ASSERT_TEST(res == CHESS_SUCCESS);
    ASSERT_TEST(ARE_FLOATS_EQUAL(average_ben, play_time_paris));   

    double average_emily = chessCalculateAveragePlayTime(chess, emily, &res);
    ASSERT_TEST(res == CHESS_SUCCESS);
    ASSERT_TEST(ARE_FLOATS_EQUAL(average_emily, play_time_paris));

    // add game in vegas
    ASSERT_TEST(chessAddGame(chess, tour_vegas, emily, abraham, SECOND_PLAYER, play_time_vegas) == CHESS_SUCCESS);
    average_emily = chessCalculateAveragePlayTime(chess, emily, &res);
    ASSERT_TEST(res == CHESS_SUCCESS);
    ASSERT_TEST(ARE_FLOATS_EQUAL(average_emily, (float)(play_time_paris/2 + play_time_vegas/2))); 

    average_ben = chessCalculateAveragePlayTime(chess, ben, &res);
    ASSERT_TEST(res == CHESS_SUCCESS);
    ASSERT_TEST(ARE_FLOATS_EQUAL(average_ben, play_time_paris));

    // remove tournament
    ASSERT_TEST(chessRemoveTournament(chess,tour_paris) == CHESS_SUCCESS);

    average_ben = chessCalculateAveragePlayTime(chess, ben, &res);
    ASSERT_TEST(res == CHESS_SUCCESS);
    ASSERT_TEST(ARE_FLOATS_EQUAL(average_ben, 0.0f));   

    average_emily = chessCalculateAveragePlayTime(chess, emily, &res);
    ASSERT_TEST(res == CHESS_SUCCESS);
    ASSERT_TEST(ARE_FLOATS_EQUAL(average_emily, (float)play_time_vegas));    

    chessDestroy(chess);
    return true;
}



/*The functions for the tests should be added here*/
bool (*tests[]) (void) = {
        testAddTournament_Shimon,
        testAddGame_Shimon,
        testRemoveTournament_Shimon,
        testRemovePlayer_Shimon,
        testEndTournament_Shimon, 
        testCalculateAveragePlayTime_Shimon,
        testSavePlayersLevels_Shimon,
        testSaveTournamentStatistics_Shimon,
        testLevelAndStatsShort_Shimon,
        testPlayerAfterRemoveTournament_Shimon,
        //testLevelAndStats_Shimon, /*uncomment this and string below - only if you want long test*/
        testChessAddTournament_segel,
        testChessRemoveTournament_segel,
        testChessAddGame_segel,
        testChessPrintLevelsAndTournamentStatistics_segel,
        testChessDestroy_maaroof,
        testChessAddTournamentAndEndTournament_maaroof,
        testChessAddGame_maaroof,
        testRemoveTournament_maaroof,
        testChessRemovePlayer_maaroof,
        testChessRemovePlayer_2_maaroof,
        testAvgGameTime_maaroof,
        testSavePlayerLevelsAndTournamentStatistics_maaroof,
        oneMoreTestJustYouKnowToMakeSureEveryThingWorksFine_maaroof,
        testTournamentWinner_maaroof,
        testPlayerLevelsAdvanced_maaroof,
};

#define NUMBER_TESTS ((long)(sizeof(tests)/sizeof(*tests)))

/*The names of the test functions should be added here*/
const char* testNames[NUMBER_TESTS] = {
        "testAddTournament_Shimon",
        "testAddGame_Shimon",
        "testRemoveTournament_Shimon",
        "testRemovePlayer_Shimon",
        "testEndTournament_Shimon", 
        "testCalculateAveragePlayTime_Shimon",
        "testSavePlayersLevels_Shimon",
        "testSaveTournamentStatistics_Shimon",
        "testLevelAndStatsShort_Shimon",
        "testPlayerAfterRemoveTournament_Shimon",
       // "testLevelAndStats_Shimon" /*uncomment this if you want long test*/
        "testChessAddTournament_segel",
        "testChessRemoveTournament_segel",
        "testChessAddGame_segel",
        "testChessPrintLevelsAndTournamentStatistics_segel",
        "testChessDestroy_maaroof",
        "testChessAddTournamentAndEndTournament_maaroof",
        "testChessAddGame_maaroof",
        "testRemoveTournament_maaroof",
        "testChessRemovePlayer_maaroof",
        "testChessRemovePlayer_2_maaroof",
        "testAvgGameTime_maaroof",
        "testSavePlayerLevelsAndTournamentStatistics_maaroof",
        "oneMoreTestJustYouKnowToMakeSureEveryThingWorksFine_maaroof",
        "testTournamentWinner_maaroof",
        "testPlayerLevelsAdvanced_maaroof",
};


int main(int argc, char *argv[]) 
{
    long number_tests = NUMBER_TESTS;
    if (argc == 1)
    {
        system("mkdir -p actual_output");
        fprintf(stdout, "Running %ld tests:\n", number_tests);
        for (long test_idx = 0; test_idx < number_tests; test_idx++)
        {
            RUN_COLORFULL_TEST(tests[test_idx], testNames[test_idx], test_idx);
        }
        printIfSuccess(number_tests);
    }
    else if (argc != 2) 
    {
        fprintf(stdout, "Usage: chessSystem <test index>\n");
        return 0;
    }
    else
    {
        long test_idx = strtol(argv[1], NULL, 10);
        if (test_idx < 1 || test_idx > NUMBER_TESTS) 
        {
            fprintf(stderr, "Invalid test index %ld\n", test_idx);
            return 0;
        }
        system("mkdir -p actual_output");
        number_tests = 1;
        RUN_COLORFULL_TEST(tests[test_idx - 1], testNames[test_idx - 1], test_idx - 1);
    }

    return 0;
}
