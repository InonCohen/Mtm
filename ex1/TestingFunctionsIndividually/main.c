#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../chess/strUtils.h"

static char* createGameID(char* player1_id, char* player2_id, int tournament_id){
    if(!player1_id || !player2_id || tournament_id <= 0){
        return NULL;
    }
    // TODO: Implement: char* chessSystem->createPlayerID(chessPlayer player)
    char* tournament_id_str = castIntToString((int) tournament_id);
    int len1, len2, len3;
    len1=(int)strlen(player1_id);
    len2=(int)strlen(player2_id);
    len3=(int)strlen(tournament_id_str);
    int size = len1 + strlen(ID_SEP) + len2  + strlen(ID_SEP) + len3 + strlen(ID_SEP);
    char* game_id = malloc(size);
    if(!game_id){
        return NULL;
    }
    nullifyString(game_id, size);
    game_id = strcat(game_id,tournament_id_str);
    game_id = strcat(game_id, ID_SEP);
    game_id = strcat(game_id,strcmp(player1_id,player2_id) < 0 ? player1_id: player2_id);
    game_id = strcat(game_id, ID_SEP);
    game_id = strcat(game_id,strcmp(player1_id,player2_id) > 0 ? player1_id: player2_id);
    return game_id;
}
int main() {
    char* id1 = "10_1";
    char* id2 = "8_0";
    int tour_id = 7;
    char* res = createGameID(id1, id2, tour_id);
    printf("GameKey: %s\n", res);
    free(res);
    return 0;
}