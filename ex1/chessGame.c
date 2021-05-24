#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "chessGame.h"
#include "chessSystem.h"

#define SEP "-"

struct ChessGame{
    unsigned int tournament_id;
    unsigned int player1;
    unsigned int player2;
    int playTime;
    Winner gameWinner;
};

ChessGame chessGameCreate(unsigned int gameID, unsigned int* playersIDs, int playTime, Winner gameWinner){
    ChessGame result = malloc(sizeof (*result));
    if (!result){
        return NULL;
    }

    ChessGame result = {gameID, playersIDs, playTime, gameWinner};
    return result;
}

ChessGame chessGameCopy(ChessGame game){
    assert (game != NULL);
    ChessGame newGame = chessGameCreate(game->gameID, game->playersIDs, game->playTime, game->gameWinner);
    if (newGame == NULL) {
        return NULL;
    }

    if (addAllOrDestroy(newChessGame, chessGame) == CHESS_OUT_OF_MEMORY) {
        return NULL;
    }
    newGame->iterator = chessGame->iterator;
    return newGame;
}

void chessGameDestroy(ChessGame);

int getChessGameID(ChessGame chessGame){
    return itoa(chessGame->tournament_id)+SEP+itoa(chessGame->player1)+SEP+itoa(chessGame->player2);
}