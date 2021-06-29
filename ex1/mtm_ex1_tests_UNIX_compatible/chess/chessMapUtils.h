#ifndef EX1_CHESSMAPUTILS_H
#define EX1_CHESSMAPUTILS_H
#include "map.h"

/**
* chessMapUtils is an Auxiliary Class that holds functions which are used by multiple ADTs
* in order to create and manage generic maps.
*
* The maps are as followed:
*
* gamesMap:         consists keys of type char* (game_id) and data of type ChessGame.
* tournamentsMap:  consists keys of type int* (tournament_id) and data of type ChessTournament.
* playersMap:       consists keys of type PlayerID and data of type ChessPlayer.
*
* The following functions are for each map, where ### is either games, tournaments, or players:
*   ###MapCopyData		- copies a given data element.
*   ###MapFreeData		- deallocates a given data element.
*   ###MapCopyKey		- copies a given key element.
*   ###MapFreeKey		- deallocates a given key element.
*
*
* In addition to the mentioned maps, there are maps of which key and/or data are of basic type,
* aka int*, double*, or strings. Thus, the following functions are provided:
* intCopyFunc          - copies a given int.
* doubleCopyFunc       - copies a given double.
* stringCopyFunc       - copies a given string.
* intFreeFunc		    - deallocates a given int.
* doubleFreeFunc		- deallocates a given double.
* stringFreeFunc		- deallocates a given string.
* intCompFunc	    	- compares two whole numbers.
* doubleCompFunc	    - compares two real numbers.
*
*/


/**
* gamesMapCopyData: Creates a copy of target MapDataElement.
* @param to_copy - Target MapDataElement. Real type: ChessGame .
* @return
* 	NULL if a NULL was sent or a memory allocation failed.
* 	A ChessGame identical to to_copy otherwise.
*/
MapDataElement gamesMapCopyData (MapDataElement to_copy);

/**
* tournamentsMapCopyData: Creates a copy of target MapDataElement.
* @param to_copy - Target MapDataElement. Real type: ChessTournament .
* @return
* 	NULL if a NULL was sent or a memory allocation failed.
* 	A ChessTournament identical to to_copy otherwise.
*/
MapDataElement tournamentsMapCopyData(MapDataElement data);

/**
* playersMapCopyData: Creates a copy of target MapDataElement.
* @param to_copy - Target MapDataElement. Real type: ChessPlayer .
* @return
* 	NULL if a NULL was sent or a memory allocation failed.
* 	A ChessPlayer identical to to_copy otherwise.
*/
MapDataElement playersMapCopyData(MapDataElement data);

/**
* playersMapCopyKey: Creates a copy of target MapKeyElement.
* @param to_copy - Target MapKeyElement. Real type: PlayerID.
* @return
* 	NULL if a NULL was sent or a memory allocation failed.
* 	A PlayerID identical to to_copy otherwise.
*/
MapKeyElement playersMapCopyKey(MapKeyElement to_copy);

/**
* intCopyFunc: Creates a copy of target MapKeyElement.
* @param to_copy - Target MapKeyElement. Real type: int*.
* @return
* 	NULL if a NULL was sent or a memory allocation failed.
* 	A int* identical to to_copy otherwise.
*/
MapKeyElement intCopyFunc(MapKeyElement to_copy);

/**
* doubleCopyFunc: Creates a copy of target MapKeyElement.
* @param to_copy - Target MapKeyElement. Real type: double*.
* @return
* 	NULL if a NULL was sent or a memory allocation failed.
* 	A double* identical to to_copy otherwise.
*/
MapKeyElement doubleCopyFunc(MapKeyElement to_copy);

/**
* stringCopyFunc: Creates a copy of target MapKeyElement.
* @param to_copy - Target MapKeyElement. Real type: char*.
* @return
* 	NULL if a NULL was sent or a memory allocation failed.
* 	A string identical to to_copy otherwise.
*/
MapKeyElement stringCopyFunc (MapKeyElement to_copy);

/**
* gamesMapFreeData: Deallocates target MapDataElement.
* @param to_free - Target MapDataElement. Real type: ChessGame.
*/

void gamesMapFreeData(MapDataElement to_free);

/**
* tournamentsMapFreeData: Deallocates target MapDataElement.
* @param to_free - Target MapDataElement. Real type: ChessTournament.
*/
void tournamentsMapFreeData (MapDataElement to_free);

/**
* gamesMapFreeData: Deallocates target MapDataElement.
* @param to_free - Target MapDataElement. Real type: ChessPlayer.
*/
void playersMapFreeData(MapDataElement to_free);

/**
* gamesMapFreeKey: Deallocates target MapKeyElement.
* @param to_free - Target MapKeyElement. Real type: PlayerID.
*/
void playersMapFreeKey(MapKeyElement to_free);

/**
* mapFreeStringKey: Deallocates target MapKeyElement.
* @param to_free - Target MapKeyElement. Real type: string.
*/
void mapFreeStringKey(MapKeyElement to_free);

/**
* intFreeFunc: Deallocates target MapKeyElement.
* @param to_free - Target MapKeyElement. Real type: int*.
*/
void intFreeFunc(MapKeyElement to_free) ;

/**
* doubleFreeFunc: Deallocates target MapKeyElement.
* @param to_free - Target MapKeyElement. Real type: double*.
*/
void doubleFreeFunc(MapKeyElement to_free);

/**
*	playersMapComp: Compares two keys of players map. Real type of keys: PlayerID.
*
* @param key1 - The first key of two keys required to be compared to one another.
* @param key2 - The second key of two keys required to be compared to one another.
* @return
*  a negative integer if key1 is greater than key2.
*  a positive integer if key2 is greater than key1.
*  0 if the two nodes are equal
*/
int playersMapComp(MapKeyElement key1, MapKeyElement key2);

/**
*	intCompFunc: Compares two keys of map. Real type of keys: int*.
*
* @param key1 - The first key of two keys required to be compared to one another.
* @param key2 - The second key of two keys required to be compared to one another.
* @return
*  a negative integer if key1 is greater than key2.
*  a positive integer if key2 is greater than key1.
*  0 if the two nodes are equal
*/
int intCompFunc(MapKeyElement key1, MapKeyElement key2);

/**
*	doubleCompFunc: Compares two keys of map. Real type of keys: double*.
*
* @param key1 - The first key of two keys required to be compared to one another.
* @param key2 - The second key of two keys required to be compared to one another.
* @return
*  a negative integer if key1 is greater than key2.
*  a positive integer if key2 is greater than key1.
*  0 if the two nodes are equal
*/
int doubleCompFunc(MapKeyElement key1, MapKeyElement key2);

/**
*	mapCompareStringKeys: Compares two keys of map. Real type of keys: string.
*
* @param key1 - The first key of two keys required to be compared to one another.
* @param key2 - The second key of two keys required to be compared to one another.
* @return
*  a negative integer if key1 is greater than key2.
*  a positive integer if key2 is greater than key1.
*  0 if the two nodes are equal
*/
int mapCompareStringKeys (MapKeyElement key1, MapKeyElement key2);

#endif //EX1_CHESSMAPUTILS_H
