#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chessPlayerID.h"
#include "strUtils.h"
#include "chessSystem.h"

struct chess_player_id{
    char* full_id;
    int id_int;
    char* id_str;
    int version_int;
    char* version_str;
};

PlayerID playerIDCreate(int id, int version){
    if(id <= 0 || version < 0){
        return NULL;
    }
    PlayerID new_id = malloc(sizeof(*new_id));
    if(!new_id){
        return NULL;
    }
    char* id_str = castIntToString(id);
    if(!id_str){
        return NULL;
    }
    char* version_str = castIntToString(version);
    if(!version_str){
        return NULL;
    }
    int id_length = strlen(id_str);
    int version_length = strlen(id_str);
    char* combined = createEmptyString(id_length+strlen(ID_SEP)+version_length+1);
    strcat(combined, id_str);
    strcat(combined, ID_SEP);
    strcat(combined, version_str);
    new_id->full_id = combined;
    new_id->id_int = id;
    new_id->version_int = version;
    new_id->id_str = id_str;
    new_id->version_str = version_str;
    return new_id;
}

void playerIDDestroy (PlayerID player_id){
    if(!player_id){
        return;
    }
    freeAll(player_id->full_id, player_id->version_str, player_id->id_str, player_id);
}

PlayerID playerIDCopy(PlayerID player_id){
    if(!player_id){
        return NULL;
    }
    if(player_id->id_int <= 0 || player_id->id_int < 0){
        return NULL;
    }
    PlayerID player_id_copy = playerIDCreate(player_id->id_int, player_id->version_int);
    if(!player_id_copy){
        return NULL;
    }
    return player_id_copy;
}

char* playerIDGetFullID(PlayerID player_id){
    if(!player_id){
        return NULL;
    }
    return player_id->full_id;
}
int playerIDGetIntID(PlayerID player_id){
    if(!player_id){
        return BAD_INPUT;
    }
    return player_id->id_int;
}
char* playerIDGetStringID(PlayerID player_id){
    if(!player_id){
        return NULL;
    }
    return player_id->id_str;
}
int playerIDGetIntVersion(PlayerID player_id){
    if(!player_id){
        return BAD_INPUT;
    }
    return player_id->version_int;
}
char* playerIDGetStringVersion(PlayerID player_id){
    if(!player_id){
        return NULL;
    }
    return player_id->version_str;
}
