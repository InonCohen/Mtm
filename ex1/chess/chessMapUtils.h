#ifndef EX1_CHESSMAPUTILS_H
#define EX1_CHESSMAPUTILS_H
#include "../map/map.h"
MapDataElement gamesMapCopyData (MapDataElement to_copy);
void gamesMapFreeData(MapDataElement to_free);
MapKeyElement mapCopyStringKey (MapKeyElement to_copy);
void mapFreeStringKey(MapKeyElement to_free);
int mapCompareStringKeys (MapKeyElement key1, MapKeyElement key2);
MapKeyElement intCopyFunc(MapKeyElement key);
void intFreeFunc(MapKeyElement key) ;
int intCompFunc(MapKeyElement key1, MapKeyElement key2);
MapDataElement tournamentsMapCopyData(MapDataElement data);
void tournamentsMapDestroyData (MapDataElement data);

#endif //EX1_CHESSMAPUTILS_H
