#include <stdlib.h>
#include <string.h>
#include "strUtils.h"
#include "chessGame.h"
#include "chessTournament.h"
#include "chessMapUtils.h"

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
void* mapCopyStringKey (void* to_copy){
    if(to_copy == NULL){
        return NULL;
    }
    int size=(int)strlen((char*)(to_copy))+1;
    char* new_key = malloc(size);
    if(!new_key){
        return NULL;
    }
    nullifyString(new_key,size);
    strcpy(new_key, (char*)to_copy);
    return new_key;
}
/**
 *
 * @param to_free
 */
void mapFreeStringKey(void* to_free){
    if(to_free == NULL){
        return;
    }
    free((char*)to_free);
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

void intFreeFunc(MapKeyElement key) {
    free((int*)key);
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

void tournamentsMapDestroyData (MapDataElement data){
    if(!data){
        return;
    }
    tournamentDestroy((ChessTournament)(data));
}
/*End: Internal map's utility functions of mapElement */