#ifndef EX1_CHESSMAPUTILS_H
#define EX1_CHESSMAPUTILS_H
#include "../map/map.h"

MapDataElement gamesMapCopyData (MapDataElement to_copy);
MapDataElement tournamentsMapCopyData(MapDataElement data);
MapDataElement playersMapCopyData(MapDataElement data);
MapKeyElement playersMapCopyKey(MapDataElement key);
MapKeyElement intCopyFunc(MapKeyElement key);
MapKeyElement doubleCopyFunc(MapKeyElement key);
MapKeyElement stringCopyFunc (MapKeyElement to_copy);


void gamesMapFreeData(MapDataElement to_free);
void playersMapFreeData(MapDataElement data);
void playersMapFreeKey(MapDataElement key);
void mapFreeStringKey(MapKeyElement to_free);
void intFreeFunc(MapKeyElement key) ;
void doubleFreeFunc(MapKeyElement key);
void tournamentsMapFreeData (MapDataElement data);

int mapCompareStringKeys (MapKeyElement key1, MapKeyElement key2);
int intCompFunc(MapKeyElement key1, MapKeyElement key2);
int playersMapComp(MapKeyElement key1, MapKeyElement key2);
int levelsMapComp(MapKeyElement key1, MapKeyElement key2);

#endif //EX1_CHESSMAPUTILS_H
