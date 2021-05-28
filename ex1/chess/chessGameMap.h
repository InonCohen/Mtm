#ifndef EX1_CHESSGAMEMAP_H
#define EX1_CHESSGAMEMAP_H

void* gamesMapCopyData (void* to_copy);
void gamesMapFreeData(void* to_free);
void* mapCopyStringKey (void* to_copy);
void mapFreeStringKey(void* to_free);
int mapCompareStringKeys (void* key1, void* key2);

#endif //EX1_CHESSGAMEMAP_H
