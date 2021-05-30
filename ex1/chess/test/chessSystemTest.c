#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "chessGameCopy.h"
#define LENGTH_OF_ZERO_STRING 2
#define MORE_LENGTH 3
#define SEP "-"

static inline void nullifyString(char* str, size_t size){
    assert(str != NULL);
    memset(str, '\0', size);
}

static inline char castDigitToChar(int digit) {
    assert(digit >= 0 && digit <= 9);
    char converted = (char)(digit + '0');
    return converted;
}

static char* castIntToString(unsigned int num){
    if(num == 0){
        char* str=malloc(LENGTH_OF_ZERO_STRING);
        if (str == NULL){
            return NULL;
        }
        str[0]='0';
        str[1]='\0';
        return str;
    }
    int numCopy=num, count=0;
    while (numCopy){//count the number of digits
        count++;
        numCopy/=10;
    }
    char* str=(char*)malloc((count) + 1);//+1 is for the '\0'
    if (str==NULL){
        return NULL;
    }
    nullifyString(str,count+1);
    for(int i=count-1;i>=0;i--){
        str[i]= castDigitToChar(num % 10);
        num/=10;
    }
    return str;
}

char* createGameID(unsigned int player1_id, unsigned int player2_id, unsigned int tournament){
    if(player1_id<0 || player2_id<0 || tournament<0 || player1_id == player2_id){
        return NULL;
    }
    char *id1, *id2;
    if(player1_id<player2_id){
        id1 = castIntToString(player1_id);
        id2 = castIntToString(player2_id);
    }
    else{
        id1 = castIntToString(player2_id);
        id2 = castIntToString(player1_id);
    }
    char* tournament_id_str= castIntToString(tournament) ;
    int len1, len2, len3;
    len1=strlen(id1);
    len2=strlen(id2);
    len3=strlen(tournament_id_str);
    int id_size = len1+len2+len3+MORE_LENGTH;
    char* game_id = malloc(id_size);
    if(!game_id){
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
    printf("Game ID: %s\n", gameGetID(game));
    printf("Game tournament: %d\n", gameGetTournament(game));
    printf("Game first player: %d\n", gameGetPlayer1(game));
    printf("Game second player: %d\n", gameGetPlayer2(game));
    printf("Game time: %d\n", gameGetPlayTime(game));
    printf("Game Winner: %d\n", gameGetWinner(game));
}


void  testChessGameCreateAndDestroy(){
    printf("Testing Create and Destroy...");
    int player1 =12, player2=17, play_time=30, tour_id=1;
    char* game_id = createGameID(player1, player2, tour_id);
    if(!game_id){
        return;
    }
    ChessGame game = gameCreate(game_id, tour_id, player1, player2, play_time, FIRST_PLAYER);
    if(!game){
        free(game_id);
        return;
    }
    printGame(game);
    printf("\n\nTesting Copy:\n");
    ChessGame game2 = gameCopy(game);
    gameDestroy(game);
    printf("\nMaking sure copy is detached from origin:\n");
    printGame(game2);
    free(game_id);
    gameDestroy(game2);
    printf("\nTEST FINISHED SUCCESSFULLY\n\n");
}

void testChessGameAdd(){
    printf("Testing Add...");
    int player1 =12, player2=17, play_time=30, tour_id=1;
    char* game_id = createGameID(player1, player2, tour_id);
    if(!game_id){
        return;
    }
//    ChessGame game = gameCreate(game_id, tour_id, player1, player2, play_time, FIRST_PLAYER);
//    if(!game){
//        free(game_id);
//        return;
//    }

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

}

int main(){
    printf("TESTING CHESS GAME\n\n");
    testChessGameCreateAndDestroy();
    testChessGameAdd();
    return 0;
}
