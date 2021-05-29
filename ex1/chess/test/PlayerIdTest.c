#include <stdlib.h>
#include <stdio.h>
#include "chess/chessPlayerID.h"

void printID(PlayerID id){
    printf("--PRINTING ID--\n");
    char* full = playerIDGetFullID(id);
    printf("ID: %s\n", full);
    char* id_str = playerIDGetStringID(id);
    printf("ID String: %s\n", id_str);
    char* version_str = playerIDGetStringVersion(id);
    printf("Version String: %s\n", version_str);
    int id_int = playerIDGetIntID(id);
    printf("ID int: %d\n", id_int);
    int version_int = playerIDGetIntVersion(id);
    printf("Version int: %d\n\n", version_int);
}

int main(){
    PlayerID id1 = playerIDCreate(12, 3);
    printf("Printing id1\n");
    printID(id1);
    PlayerID id2 = playerIDCopy(id1);
    printf("Printing id2 before deleting id1\n");
    printID(id2);
    playerIDDestroy(id1);
    printf("Printing id2 after deleting id1\n");
    printID(id2);
    playerIDDestroy(id2);
    PlayerID id3 = playerIDCreate(100, 35);
    printID(id3);
    playerIDDestroy(id3);
    return 0;
}
