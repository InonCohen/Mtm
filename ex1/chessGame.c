#include "chessGame.h"
#include "chessSystem.h"
#include "assert.h"
#include "stdlib.h"

struct ChessGame{
    unsigned int gameID;
    unsigned int* playersIDs;
    int playTime;
    Winner gameWinner;
};

ChessGame chessGameCreate(unsigned int gameID, unsigned int* playersIDs, int playTime, Winner gameWinner){
    ChessGame result = malloc(sizeof (*result));
    if (!result){
        return NULL;
    }
    re
    ChessGame result = {gameID, playersIDs, playTime, gameWinner};
    return result;
}

ChessGame chessGameCopy(ChessGame game){
    assert (game != NULL);
    ChessGame newGame;
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