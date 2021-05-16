#ifndef EX1NEW_LINKEDLIST_H
#define EX1NEW_LINKEDLIST_H
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

/** Data element data type for list node container */
typedef void *ListNodeDataElement;

/** Key element data type for list node container */
typedef void *ListNodeKeyElement;

/** Type of function for copying a data element of the list node */
typedef ListNodeDataElement(*copyListNodeDataElements)(ListNodeDataElement);

/** Type of function for copying a key element of the list node */
typedef ListNodeKeyElement(*copyListNodeKeyElements)(ListNodeKeyElement);

/** Type of function for deallocating a data element of the list node */
typedef void(*freeListNodeDataElements)(ListNodeDataElement);

/** Type of function for deallocating a key element of the list node */
typedef void(*freeListNodeKeyElements)(ListNodeKeyElement);


/**
* Type of function used by the list to identify equal key elements.
* This function should return:
* 		A positive integer if the first element is greater;
* 		0 if they're equal;
*		A negative integer if the second element is greater.
*/
typedef int(*compareListNodeKeyElements)(ListNodeKeyElement, ListNodeKeyElement);

/**
* listCreate: Allocates a new empty list.
*
* @param copyDataElement - Function pointer to be used for copying data elements into
*  	a node or when copying the list.
* @param copyKeyElement - Function pointer to be used for copying key elements into
*  	a node or when copying the list.
* @param freeDataElement - Function pointer to be used for removing data elements from
* 		a node in the list
* @param freeKeyElement - Function pointer to be used for removing key elements from
* 		a node in the list
* @param compareKeyElements - Function pointer to be used for comparing key elements
* 		inside the list. Used to check if new elements already exist in the list.
* @return
* 	NULL - if one of the parameters is NULL or allocations failed.
* 	A new List in case of success.
*/
DoublyLinkedList listCreate(copyListNodeDataElements copyDataElement,
                copyListNodeKeyElements copyKeyElement,
                freeListNodeDataElements freeDataElement,
                freeListNodeKeyElements freeKeyElement,
                compareListNodeKeyElements compareKeyElements);

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



#endif //EX1NEW_LINKEDLIST_H
