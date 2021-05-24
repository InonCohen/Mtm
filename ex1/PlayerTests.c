#include <stdio.h>
#include "Player.h"

void testMemoryOfCreateAndDestroy(){
    Player player1 = playerCreate(12);
    playerDestroy(player1);
}

int main(){
    printf("\n\nTesting No Memory problems in basic Allocations and Destruction\n\n ");
    testMemoryOfCreateAndDestroy();
    return 0;
};

