#include "chessGame.h"
#include "chessSystem.h"

struct ChessGame{
    unsigned int* gameID;
    unsigned int* playersIDS;
    int playTime;
    Winner gameWinner;
};

ChessGame chessGameCreate();

ChessGame chessGameCopy(ChessGame);

void chessGameDestroy(ChessGame);