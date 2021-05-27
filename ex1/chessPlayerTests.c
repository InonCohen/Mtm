#include <stdio.h>
#include "chessPlayer.h"
#include "chessGame.h"

void testMemoryOfCreateAndDestroy(){
    printf("Testing No Memory problems in basic Allocations and Destruction...\n ");
    Player player1 = playerCreate(12);
    Player player2 = playerCopy(player1);
    ChessGame game = chessGameCreate(1, player1, player2, 30, FIRST_PLAYER);
    if(game){
        printf("[GAME CREATE FAILURE]\n");
        return;
    }
    playerDestroy(player2);
    Player player3 = playerCreate(17);
    game = chessGameCreate(1, player1, player3, 30, FIRST_PLAYER);
    if(!game){
        printf("[GAME CREATE FAILURE]\n");
    }
    else{
        printf("[GAME CREATE OK]\n");
    }
    playerDestroy(player1);
    playerDestroy(player3);
//    playerDestroy(player1);
//    Winner winner = chessGameGetWinner(game);
//    if(winner!=SECOND_PLAYER){
//        printf("[GAME UPDATE WHEN DELETING PLAYER FAILURE]\n");
//    }
//    else{
//        printf("[GAME UPDATE WHEN DELETING PLAYER OK]\n");
//    }
    chessGameDestroy(game);

}

int main(){
    testMemoryOfCreateAndDestroy();
    return 0;
}

