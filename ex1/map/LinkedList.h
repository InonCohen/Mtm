#ifndef EX1NEW_LINKEDLIST_H
#define EX1NEW_LINKEDLIST_H

#include <stdbool.h>
#include "DLLNode.h"

/**
* Generic List Container
*
* Implements a list container type.
*
* The following functions are available:
*   listCreate		- Creates a new List
*   listDestroy		- Deletes an existing list and frees all resources
*   listCopy		- Copies an existing list
*   listGetsize     - Returns the size of the list
*   listGetNode     - Returns a pointer to an existing node in the list
*   listInsert      - Puts a new node at the end of the list, or changes data
*                     of an existing node
*   listRemove      - Removes an existing node from the list
*   listContains    - Returns TRUE if a specific key exists in
*   listGetHead     - Returns the pointer of the head node in the list
*   listGetTail     - Returns the pointer of the tail node in the list
*   listGetNext     - Returns the pointer of the next node in the list
*   listGetPrev     - Returns the pointer of the previous node in the list
*   listClear       - Empties the list of all its content

*/

/** Type for defining the Doubly Linked List */
typedef struct DoublyLinkedList_t *DoublyLinkedList;

/** Type used for returning error codes from list functions */
typedef enum ListResult_t {
    LIST_SUCCESS,
    LIST_ERROR,
    LIST_OUT_OF_MEMORY,
    LIST_NULL_ARGUMENT,
    LIST_ITEM_ALREADY_EXISTS,
    LIST_ITEM_DOES_NOT_EXIST
} ListResult;

/** Type of function for copying a node element of the list */
typedef Node (*copyNode)(Node);

/** Type of function for deallocating a Node element of the list */
typedef void(*freeNode)(Node);

/**
* Type of function used by the list to identify equal nodes.
* This function should return:
* 		A positive integer if the first element is greater;
* 		0 if they're equal;
*		A negative integer if the second element is greater.
*/
typedef int(*compareNodes)(Node, Node);

/**
* listCreate: Allocates a new empty list.
*
* @param copyNodeElement - Function pointer to be used for copying Node elements
* @param freeNodeElement - Function pointer to be used for removing Node elements
* 		from the list
* @param compareNodeElements - Function pointer to be used for comparing Node elements
* 		inside the list. Used to check if new elements already exist in the list.
* @return
* 	NULL - if one of the parameters is NULL or allocations failed.
* 	A new List in case of success.
*/
DoublyLinkedList listCreate(copyNode copyNodeElement,
                freeNode freeNodeElement,
                compareNodes compareNodeElements);

/**
* listDestroy: Deallocates an existing list. Clears all elements by using the
* stored free functions.
*
* @param list - Target list to be deallocated. If list is NULL nothing will be
* 		done
*/
void listDestroy(DoublyLinkedList list);

/**
* listCopy: Creates a copy of target list.
* Iterator values for both lists is undefined after this operation.
*
* @param list - Target list.
* @return
* 	NULL if a NULL was sent or a memory allocation failed.
* 	A Doubly Linked List containing the same elements as list otherwise.
*/
DoublyLinkedList listCopy(DoublyLinkedList list);

/**
* listGetSize: Returns the number of elements in a list
* @param list - The list which size is requested
* @return
* 	-1 if a NULL pointer was sent.
* 	Otherwise the number of elements in the list.
*/
int listGetSize(DoublyLinkedList list);

/**
*	listGetFirst: Sets the internal iterator (also called current node) to
*	the first node in the list and returns a copy of it. There doesn't
 *	need to be an internal order of the nodes so the "first" node is the
 *	list's head's next that is available in the list. Use this to start iterating over the list.
*	To continue iteration use listGetNext
*
* @param list - The list for which to set the iterator and return a copy of the first
* 		node.
* @return
* 	NULL if a NULL pointer was sent or the list is empty or allocation fails
* 	The first node of the list otherwise
*/
Node listGetFirst(DoublyLinkedList list);

/**
*	listGetNext: Advances the list iterator to the next node and returns a copy of it.
*	The next node is the smallest node of the nodes that are
*   greater than the current node.
* @param list - The list for which to advance the iterator
* @return
* 	NULL if reached the end of the list, or the iterator is at an invalid state,
* 	or a NULL sent as argument or allocation fails
* 	The next node in the list in case of success
*/
Node listGetNext(DoublyLinkedList list);

/**
*	listInsert: Gives a node to be inserted to the list.
*  Iterator's value is undefined after this operation.
*
* @param list - The list for which to insert the node
* @param node - The node which needs to be inserted
*      A copy of the node will be inserted as supplied by the Node type
* @return
* 	LIST_NULL_ARGUMENT if a NULL was sent as list or node
* 	LIST_OUT_OF_MEMORY if an allocation failed (Meaning the function for copying
* 	a node failed)
* 	LIST_SUCCESS the node had been inserted successfully
*/
ListResult listInsert(DoublyLinkedList list, Node node);

/**
* 	listRemove: Removes a node from the list. The node is found using the
*  comparison function given at initialization. Once found, the node is
*  removed and deallocated using the free function supplied at initialization.
*  Iterator's value is undefined after this operation.
*
* @param list -
* 	The list to remove the node from.
* @param node
* 	The node to find and remove from the list. The node will be freed using the
* 	free function given at initialization.
* @return
* 	LIST_NULL_ARGUMENT if a NULL was sent to the function
*   LIST_ITEM_DOES_NOT_EXIST if an equal node does not already exist in the list
* 	LIST_SUCCESS the node had been removed successfully
*/
ListResult listRemove(DoublyLinkedList list, Node node);

/**
* listContains: Checks if a node exists in the list. The node will be
* considered in the list if one of the nodes in the list is determined equal
* using the comparison function used to initialize the list.
*
* @param list - The map to search in
* @param node - The node to look for. Will be compared using the
* 		comparison function.
* @return
* 	false - if one or more of the inputs is null, or if the node was not found.
* 	true - if the node was found in the map.
*/
bool listContains(DoublyLinkedList list, Node node);

#endif //EX1NEW_LINKEDLIST_H
