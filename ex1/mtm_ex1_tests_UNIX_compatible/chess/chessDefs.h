#ifndef EX1_CHESSDEFS_H
#define EX1_CHESSDEFS_H

/** Type for representing the victory status of a player in a specific game */
typedef enum {
    WINNER,
    LOSER,
    TIER
}GamePlayerOutcome;

/** Type for representing a chess game in a tournament */
typedef struct chess_game_t* ChessGame;

/** Type for defining the Player */
typedef struct chess_player_t *ChessPlayer;

/** Type for defining a player ID*/
typedef struct chess_player_id *PlayerID;



#endif //EX1_CHESSDEFS_H
