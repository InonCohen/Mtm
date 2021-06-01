#ifndef EX1_CHESSPLAYERID_H
#define EX1_CHESSPLAYERID_H
#include <stdbool.h>
#include "chessDefs.h"

/**
* PlayerID Type
*
* Implements a PlayerID type.
* The PlayerID is made of both an id and a version, at first both of which are integers.
* They are both being casted to strings and the full ID is a string of form id_version.
* Version is the number of times a player with same id was deleted from system.
*
* The following functions are available:
*   playerIDCreate		     - Creates a new PlayerID
*   playerIDDestroy		     - Deletes an existing PlayerID and frees all resources
*   playerIDCopy		     - Copies an existing PlayerID
*   playerIDGetFullID	     - Returns the string of a given PlayerID of form id_version
*   playerIDGetIntID         - Returns the integer of a given PlayerID representing id
*   playerIDGetStringID      - Returns the string of a given PlayerID representing id
*   playerIDGetIntVersion    - Returns the integer of a given PlayerID representing version
*   playerIDGetStringVersion - Returns the string of a given PlayerID representing version
*   playerIDCompare          - Checks if two ids are the same, and if not which is bigger
*/

/**
* playerIDCreate: Allocates a new empty PlayerID.
*
* @param id      - an integer representing a player's id
* @param version - an integer representing a player's version
* @return
* 	NULL - if id is non positive, or version is negative, or allocations failed.
* 	A new PlayerID in case of success.
*/
PlayerID playerIDCreate(int id, int version);

/**
* playerIDDestroy: Deallocates an existing PlayerID.
*
* @param player_id - Target PlayerID to be deallocated. If player_id is NULL nothing
*                  will be done
*/
void playerIDDestroy (PlayerID player_id);

/**
* playerIDCopy: Creates a copy of target PlayerID.
* @param player_id - Target PlayerID.
* @return
* 	NULL if a NULL was sent or a memory allocation failed.
* 	A PlayerID containing the same elements as player_id otherwise.
*/
PlayerID playerIDCopy(PlayerID player_id);

/**
* playerIDGetFullID: Returns actual full id (not a copy) of target PlayerID.
* @param player_id - Target PlayerID of which full id is required.
* @return
* 	NULL if a NULL was sent.
* 	A string containing player_id's full id otherwise.
*/
char* playerIDGetFullID(PlayerID player_id);

/**
* playerIDGetIntID: Returns id of target PlayerID.
* @param player_id - Target PlayerID of which id is required as an integer.
* @return
* 	(-999) if a NULL was sent.
* 	player_id's id value otherwise.
*/
int playerIDGetIntID(PlayerID player_id);

/**
* playerIDGetStringID: Returns actual string id (not a copy) of target PlayerID.
* @param player_id - Target PlayerID of which id is required as a string.
* @return
* 	NULL if a NULL was sent.
* 	A string containing player_id's id otherwise.
*/
char* playerIDGetStringID(PlayerID player_id);

/**
* playerIDGetIntVersion: Returns version of target PlayerID.
* @param player_id - Target PlayerID of which version is required as an integer.
* @return
* 	(-999) if a NULL was sent.
* 	player_id's version value otherwise.
*/
int playerIDGetIntVersion(PlayerID player_id);

/**
* playerIDGetStringVersion: Returns actual string version (not a copy) of target PlayerID.
* @param player_id - Target PlayerID of which version is required as a string.
* @return
* 	NULL if a NULL was sent.
* 	A string containing player_id's version otherwise.
*/
char* playerIDGetStringVersion(PlayerID player_id);

/**
*	playerIDCompare: Compares two PlayerIDs.
*
* @param id1 - The first PlayerID of two PlayerIDs required to be compared to one another.
* @param id2 - The second PlayerID of two PlayerIDs required to be compared to one another.
* @return
*  a negative integer if id1 is greater than id2.
*  a positive integer if id2 is greater than id1.
*  0 if the two nodes are equal
*/
int playerIDCompare(PlayerID id1, PlayerID id2);
#endif //EX1_CHESSPLAYERID_H
