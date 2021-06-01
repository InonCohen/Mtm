
#ifndef EX1NEW_DLLNODE_H
#define EX1NEW_DLLNODE_H

/**
* Generic Node Container
*
* Implements a node container type.
*
* The following functions are available:
*   nodeCreate		- Creates a new empty node
*   nodeDestroy		- Deletes an existing node and frees all resources
*   nodeCopy		- Copies an existing node
*   nodeGetKey      - Returns the key of an existing node
*   nodeGetData     - Returns the data of an existing node
*   nodeSetKey      - Changes the key of an existing node
*   nodeSetData     - Changes the data of an existing node
*   nodeGetNext     - Returns the pointer of the next node in the list
*   nodeGetPrev     - Returns the pointer of the previous node in the list
*   nodeSetNext     - Changes the pointer of the next node in the list
*   nodeSetPrev     - Changes the pointer of the previous node in the list
*   nodeCompare     - Indicates whether two nodes have equal keys,
*                      and if not, which one's bigger according to the sign
*   nodeFreeKey     - Frees a given key
*/


/** Type for defining the node */
typedef struct Node_t *Node;

/** Type used for returning error codes from node functions */
    typedef enum NodeResult_t {
    NODE_SUCCESS,
    NODE_ERROR,
    NODE_OUT_OF_MEMORY,
    NODE_NULL_ARGUMENT,
    NODE_ITEM_ALREADY_EXISTS,
    NODE_ITEM_DOES_NOT_EXIST
} NodeResult;

/** Data element data type for node container */
typedef void *NodeDataElement;

/** Key element data type for node container */
typedef void *NodeKeyElement;

/** Type of function for copying a data element of the node */
typedef NodeDataElement(*copyNodeDataElement)(NodeDataElement);

/** Type of function for copying a key element of the node */
typedef NodeKeyElement(*copyNodeKeyElement)(NodeKeyElement);

/** Type of function for deallocating a data element of the node */
typedef void(*freeNodeDataElement)(NodeDataElement);

/** Type of function for deallocating a key element of the node */
typedef void(*freeNodeKeyElement)(NodeKeyElement);

/**
* Type of function used by the node to identify equal key elements.
* This function should return:
* 		A positive integer if the first element is greater;
* 		0 if they're equal;
*		A negative integer if the second element is greater.
*/
typedef int(*compareNodeKeyElements)(NodeKeyElement, NodeKeyElement);

/**
* nodeCreate: Allocates a new empty node.
*
* @param copyDataElement - Function pointer to be used for copying data elements into
*                       	the node or when copying the node.
* @param copyKeyElement  - Function pointer to be used for copying key elements into
*  	                        the node or when copying the node.
* @param freeDataElement - Function pointer to be used for removing data elements from
* 		                    the node
* @param freeKeyElement  - Function pointer to be used for removing key elements from
* 		                    the node
* @param key             - Pointer to the key element of the new node
* @param data            - Pointer to the data element of the new node
* @return
* 	NULL - if one of the function parameters is NULL or allocations failed.
* 	A new Node in case of success.
*/
Node nodeCreate(copyNodeDataElement copyDataElement,
              copyNodeKeyElement copyKeyElement,
              freeNodeDataElement freeDataElement,
              freeNodeKeyElement freeKeyElement,
              compareNodeKeyElements compKeyElements, void* key, void* data);

/**
* nodeDestroy: Deallocates an existing node. Clears all elements by using the
*               stored free functions.
*
* @param node   - Target node to be deallocated. If node is NULL nothing
* 	            	will be done
*/
void nodeDestroy(Node node);


/**
* nodeCopy: Creates a copy of the target node.
*
* @param node    - Target node.
* @return
* 	NULL if a NULL was sent or a memory allocation failed.
* 	A Node containing the same elements as node otherwise.
*/
Node nodeCopy(Node node);


/**
*	nodeGetKey: Returns a copy of the node's key.
*
* @param node - The node for which to get the key element from.
* @return
*  NULL if a NULL pointer was sent or if the allocation failed.
* 	A copy of the node's key element otherwise.
*/
NodeKeyElement nodeGetKey(Node node);


/**
*	nodeGetData: Returns the node's data.
*
* @param node - The node for which to get the data element from.
* @return
*   NULL if a NULL pointer was sent.
* 	The node's data element otherwise.
*/
NodeKeyElement nodeGetData(Node node);


/**
*	nodeSetKey: Changes the node's key to keyElement.
*
* @param node - The node for which the key element is to be changed.
* @param keyElement - The node's to be new key element.
* @return
* 	NODE_NULL_ARGUMENT if a NULL was sent as node or keyElement.
* 	NODE_OUT_OF_MEMORY if an allocation failed (meaning the function for copying
* 	an element failed)
* 	NODE_SUCCESS the new key element had been inserted successfully
*/
NodeResult nodeSetKey(Node node, NodeKeyElement keyElement);


/**
*	nodeSetData: Changes the node's data to dataElement.
*
* @param node - The node for which the data element is to be changed.
* @param dataElement - The node's to be new data element.
* @return
* 	NODE_NULL_ARGUMENT if a NULL was sent as node or dataElement.
* 	NODE_OUT_OF_MEMORY if an allocation failed (meaning the function for copying
* 	an element failed)
* 	NODE_SUCCESS the new data element had been inserted successfully
*/
NodeResult nodeSetData(Node node, NodeDataElement dataElement);


/**
*	nodeGetNext: Returns a pointer to the next node in the list.
*
* @param node - The node of which to get the next node.
* @return
*  NULL if a NULL pointer was sent or if the previous node is NULL.
* 	A pointer to node's next node.
*/
Node nodeGetNext(Node node);


/**
*	nodeGetPrev: Returns a pointer to the previous node in the list.
*
* @param node - The node of which to get the previous node.
* @return
*  NULL if a NULL pointer was sent or if the next node is NULL.
* 	A pointer to the node's previous node.
*/
Node nodeGetPrev(Node node);


/**
*	nodeSetNext: Changes the pointer to the next node in the list.
*
* @param node - The node of which to change the next node.
* @param next_node - The new next node.
* @return
*  NODE_NULL_ARGUMENT if a NULL pointer was sent as node
*  NODE_OUT_OF_MEMORY if the allocation failed.
*  NODE_SUCCESS otherwise.
*/
NodeResult nodeSetNext(Node node, Node next_node);


/**
*	nodeSetPrev: Returns a pointer to the previous node in the list.
*
* @param node - The node of which to change the previous node.
* @param prev_node - The new previous node.
* @return
*  NODE_NULL_ARGUMENT if a NULL pointer was sent as node
*  NODE_SUCCESS otherwise.
*/
NodeResult nodeSetPrev(Node node, Node prev_node);

/**
*	nodeCompare: Compares two nodes using the built in Compare function.
*
* @param node1 - The first node of two nodes required to be compared to one another.
* @param node2 - The second node of two nodes required to be compared to one another.
* @return
*  a negative integer if node1 is greater than node2.
*  a positive integer if node2 is greater than node1.
*  0 if the two nodes are equal
*/
int nodeCompare (Node node1, Node node2);

/**
*	nodeFreeKey: Destroys key using node's built in FreeKeyFunc.
*
* @param node - The node of which the built in FreeKeyFunc is to be used.
* @param key - The key to be destroyed.
*/
void nodeFreeKey(Node node, NodeKeyElement key);


#endif //EX1NEW_DLLNODE_H
