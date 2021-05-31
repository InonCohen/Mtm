#ifndef EX1_CHESSPLAYERID_H
#define EX1_CHESSPLAYERID_H
#include <stdbool.h>
#include "chessDefs.h"

PlayerID playerIDCreate(int id, int version);

void playerIDDestroy (PlayerID player_id);
PlayerID playerIDCopy(PlayerID player_id);
char* playerIDGetFullID(PlayerID player_id);
int playerIDGetIntID(PlayerID player_id);
char* playerIDGetStringID(PlayerID player_id);
int playerIDGetIntVersion(PlayerID player_id);
char* playerIDGetStringVersion(PlayerID player_id);
int playerIDCompare(PlayerID id1, PlayerID id2);
#endif //EX1_CHESSPLAYERID_H
