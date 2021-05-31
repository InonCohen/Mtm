#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "strUtils.h"
#include "chessGame.h"
#include "chessTournament.h"
#include "chessMapUtils.h"
#include "chessPlayer.h"
#include "chessPlayerID.h"

#define EPSILON (0.01)

/**
 *
 * @param to_copy
 * @return
 */
void* gamesMapCopyData (void* to_copy) {
    if(to_copy == NULL){
        return NULL;
    }
    ChessGame copy = gameCopy((ChessGame)to_copy);
    if(!copy){
        return NULL;
    }
    return (void*)copy;
}
/**
 *
 * @param to_free
 */
void gamesMapFreeData(void* to_free){
    if(to_free == NULL){
        return;
    }
    gameDestroy((ChessGame)to_free);
}
/**
 *
 * @param to_copy
 * @return
 */
void mapFreeStringKey(void* to_free){
    if(to_free == NULL){
        return;
    }
    free((char*)to_free);
}
void tournamentsMapFreeData(void* to_free){
    if(to_free == NULL){
        return;
    }
    tournamentDestroy((ChessTournament)to_free);
}

/**
 *
 * @param key1
 * @param key2
 * @return
 */
int mapCompareStringKeys (void* key1, void* key2){
    if(key1 == NULL || key2 == NULL){
        return BAD_INPUT;
    }
    return strcmp((char*)key1, (char*)key2);
}

MapKeyElement intCopyFunc(MapKeyElement key) {
    if(!key) {
        return NULL;
    }
    int* new_key = malloc(sizeof(*new_key));
    if(!new_key) {
        return NULL;
    }
    *new_key = *(int*)key;
    return (void*)new_key;
}

MapKeyElement doubleCopyFunc(MapKeyElement key){
    if(!key) {
        return NULL;
    }
    double* new_key = malloc(sizeof(*new_key));
    if(!new_key) {
        return NULL;
    }
    *new_key = *(double*)key;
    return (void*)new_key;
}

void intFreeFunc(MapKeyElement key) {
    free((int*)key);
}

void doubleFreeFunc(MapKeyElement key) {
    free((double*)key);
}

int intCompFunc(MapKeyElement key1, MapKeyElement key2) {
    if(!key1 || !key2) {
        return BAD_INPUT;
    }
    return *(int*)key1-*(int*)key2;
}

MapDataElement tournamentsMapCopyData(MapDataElement data){
    if(!data){
        return NULL;
    }
    return tournamentCopy((ChessTournament)data);
}

MapDataElement playersMapCopyData(MapDataElement data){
    if(!data){
        return NULL;
    }
    return playerCopy((ChessPlayer)data);
}

MapKeyElement stringCopyFunc (MapKeyElement to_copy){
    if(!to_copy){
        return NULL;
    }
    int length = strlen((char*)to_copy);
    char* to_return = malloc(length+1);
    if(!to_return){
        return NULL;
    }
    strcpy(to_return, to_copy);
    return (void*)to_return;
}

MapKeyElement playersMapCopyKey(MapDataElement key){
    if(!key){
        return NULL;
    }
    return playerIDCopy((PlayerID)key);
}

void playersMapFreeData(MapDataElement data){
    if(!data){
        return;
    }
    playerDestroy((ChessPlayer)data);
}

void playersMapFreeKey(MapDataElement key){
    if(!key){
        return;
    }
    playerIDDestroy((PlayerID)key);
}

int playersMapComp(MapKeyElement key1, MapKeyElement key2){
    if(!key1 || !key2){
        return BAD_INPUT;
    }
    return playerIDCompare((PlayerID)key1, (PlayerID)key2);
}

int levelsMapComp(MapKeyElement key1, MapKeyElement key2) {
    if (!key1 || !key2) {
        return BAD_INPUT;
    }
    bool res = (fabs(*(double *) key1 - *(double *) key2)<EPSILON);
    if(res == true){
        return 0;
    }
    else{
        return 1;
    }
}

/*End: Internal map's utility functions of mapElement */
