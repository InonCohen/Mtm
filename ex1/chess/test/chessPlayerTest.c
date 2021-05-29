#include <stdio.h>
#include "../chessPlayer.h"
#include "../chessPlayerID.h"

void printPlayer(ChessPlayer player){
    if(!player){
        printf("Error, cannot print player");
    }
    printf("--PRINTING PLAYER--\n");
    char* id = playerGetIDString(player);
    printf("ID: %s\n", id);
    printf("Total games: %d\n", playerGetNumOfGames(player));
    printf("Wins: %d\n", playerGetNumOfWins(player));
    printf("Losses: %d\n", playerGetNumOfLosses(player));
    printf("Draws: %d\n", playerGetNumOfDraws(player));
    printf("Level: %f\n", playerGetLevel(player));
    printf("Total play time: %d\n", playerGetPlayingTime(player));
}

void testMemoryOfCreateAndDestroy(){
    PlayerID id1 = playerIDCreate(12, 0);
    ChessPlayer player1 = playerCreate(id1);
    playerIDDestroy(id1);
    printPlayer(player1);
    ChessPlayer player2 = playerCopy(player1);
    printf("Printing player2 before deleting player1\n");
    printPlayer(player2);
    playerDestroy(player1);
    printf("Printing player2 after deleting player1\n");
    printPlayer(player2);
    playerDestroy(player2);
    PlayerID id2 = playerIDCreate(135, 135);
    ChessPlayer player3 = playerCreate(id2);
    playerIDDestroy(id2);
    printPlayer(player3);
    ChessPlayer player4 = playerCopy(player3);
    printf("Printing player4 before deleting player3\n");
    printPlayer(player4);
    playerDestroy(player3);
    printf("Printing player4 after deleting player3\n");
    printPlayer(player4);
    playerDestroy(player4);
}

int main(){
    printf("\n\nTesting No Memory problems in basic Allocations and Destruction\n\n ");
    testMemoryOfCreateAndDestroy();
    return 0;
}

