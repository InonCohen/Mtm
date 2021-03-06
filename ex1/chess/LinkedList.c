#include <stdio.h>
#include <stdlib.h>

#include <assert.h>
#include "LinkedList.h"
#define INVALID_ARG -1

struct DoublyLinkedList_t{
    copyNode copyNodeFunc;
    freeNode freeNodeFunc;
    compareNodes compNodesFunc;
    Node head;
    Node tail;
    int size;
    int iterator;
};

static ListResult listReplace(DoublyLinkedList list, Node node);

DoublyLinkedList listCreate(copyNode copyNodeElement,
                            freeNode freeNodeElement,
                            compareNodes compareNodeElements){
    if(copyNodeElement == NULL || freeNodeElement == NULL || compareNodeElements == NULL){
        return NULL;
    }
    DoublyLinkedList list = malloc (sizeof(*list));
    if(!list){
        return NULL;
    }
    list->copyNodeFunc = copyNodeElement;
    list->freeNodeFunc = freeNodeElement;
    list->compNodesFunc = compareNodeElements;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->iterator = 0;
    return list;
}


void listDestroy(DoublyLinkedList list){
    if(!list){
        return;
    }
    listClear(list);
    free(list);
}

DoublyLinkedList listCopy(DoublyLinkedList list){
    if(!list){
        return NULL;
    }
    DoublyLinkedList list_copy = malloc((sizeof(*list_copy)));
    if(!list_copy){
        return NULL;
    }
    list_copy->copyNodeFunc=list->copyNodeFunc;
    list_copy->freeNodeFunc=list->freeNodeFunc;
    list_copy->compNodesFunc=list->compNodesFunc;
    list_copy->size=0;
    int size = list->size;
    Node iter = listGetHead(list);
    ListResult res;
    for(int i=0;i<size;i++){
        res = listInsert(list_copy, iter);
        if(res!=LIST_SUCCESS){
            listDestroy(list_copy);
            return NULL;
        }
        iter= nodeGetNext(iter);
    }
    return list_copy;
}

int listGetSize(DoublyLinkedList list){
    if(!list){
        return INVALID_ARG;
    }
    return list->size;
}

Node listGetHead (DoublyLinkedList list){
    if(!list){
        return NULL;
    }
    return list->head;
}

Node listGetTail (DoublyLinkedList list){
    if(!list){
        return NULL;
    }
    return list->tail;
}

Node listGetNode (DoublyLinkedList list, NodeKeyElement keyElement){
    if(!list || !keyElement){
        return NULL;
    }
    Node iter = listGetHead(list);
    Node to_compare = nodeCopy(iter);
    if(!to_compare){
        return NULL;
    }
    nodeSetKey(to_compare,keyElement);
    while(iter){
        if(list->compNodesFunc(iter,to_compare)==0){
            nodeDestroy(to_compare);
            return iter;
        }
        iter = nodeGetNext(iter);
    }
    return NULL;
}

Node findAntecedent(DoublyLinkedList list, Node node){
    if(list == NULL || node == NULL){
        return NULL;
    }
    Node following = findFollowing(list, node);
    if(following == list->head){
        return NULL;
    }
    return (following == NULL)? list->tail: nodeGetPrev(following);
}

Node findFollowing(DoublyLinkedList list, Node node){
    if(list == NULL || node == NULL){
        return NULL;
    }
    int diff = list->compNodesFunc(list->head, node);
    assert(diff != 0);
    if(diff>0){
        return listGetHead(list);
    }
    Node iter = list->head;
    while(iter!=NULL){
        if(list->compNodesFunc(iter, node) < 0){
            iter = nodeGetNext(iter);
            continue;
        }
        break;
    }
    return iter;
}

ListResult listInsert(DoublyLinkedList list, Node node){
    if(!list || !node){
        return LIST_NULL_ARGUMENT;
    }
    int size = list->size;
    Node to_insert = list->copyNodeFunc(node);
    if(!to_insert){
        return LIST_OUT_OF_MEMORY;
    }
    nodeSetNext(to_insert, NULL);
    nodeSetPrev(to_insert, NULL);
    if(size==0){
        list->head=to_insert;
        list->tail=to_insert;
        list->size++;
        return LIST_SUCCESS;
    }
    if(listContains(list, node)){
        nodeDestroy(to_insert);
        return listReplace(list, node);
    }
    Node antecedent = findAntecedent(list, node);
    Node following = findFollowing(list, node);
    assert(antecedent != NULL || following != NULL);
    if(antecedent != NULL && following != NULL){
        nodeSetNext(antecedent, to_insert);
        nodeSetPrev(following, to_insert);
        nodeSetNext(to_insert, following);
        nodeSetPrev(to_insert, antecedent);
    }
    else if(antecedent == NULL){ // if to_insert needs to be inserted at the beginning
        nodeSetPrev(following, to_insert);
        nodeSetNext(to_insert, following);
        list->head=to_insert;
    }
    else {
        nodeSetNext(antecedent, to_insert);
        nodeSetPrev(to_insert, antecedent);
        list->tail = to_insert;
    }
    list->size++;
    return LIST_SUCCESS;
}

ListResult listRemove(DoublyLinkedList list, Node node){
    if(!list || !node){
        return LIST_NULL_ARGUMENT;
    }
    if(!listContains(list, node)){
        return LIST_ITEM_DOES_NOT_EXIST;
    }
    Node iter = listGetHead(list);
    while(iter!=NULL){
        if(list->compNodesFunc(iter, node) == 0){
            if(iter==list->head){
                list->head = nodeGetNext(list->head);
            }
            if(iter==list->tail){
                list->tail= nodeGetPrev(list->tail);
            }
            Node previous = nodeGetPrev(iter);
            Node following = nodeGetNext(iter);
            nodeSetPrev(following, previous);
            nodeSetNext(previous, following);
            list->freeNodeFunc(iter);
            list->size--;
            return LIST_SUCCESS;
        }
        iter= nodeGetNext(iter);
    }
    return LIST_ITEM_DOES_NOT_EXIST;
}

bool listContains(DoublyLinkedList list, Node node){
    if(!list || !node){
        return false;
    }
    int size=list->size;
    Node iter = list->head;
    for(int i=0;i<size;i++){
        if(0==list->compNodesFunc(iter, node)){
            return true;
        }
        iter= nodeGetNext(iter);
    }
    return false;
}

ListResult listClear (DoublyLinkedList list){
    if(list == NULL){
        return LIST_NULL_ARGUMENT;
    }
    int size = listGetSize(list);
    for(int i=0;i<size;i++){

        listRemove(list, list->head);
    }
    if(list->size!=0){
        return LIST_ERROR;
    }
    return LIST_SUCCESS;
}

Node listGetFirst(DoublyLinkedList list){
    if(!list){
        return NULL;
    }
    list->iterator=1;
    return list->head;
}

Node listGetNext(DoublyLinkedList list){
    if(!list){
        return NULL;
    }
    Node iter = list->head;
    for(int i=0;i<list->iterator;i++){
        iter = nodeGetNext(iter);
    }
    (list->iterator)++;
    return iter;
}

/**
*	listReplace: Gives a node in the list a different data.
*   Iterator's value is undefined after this operation.
*
* @param list - The list in which exists a node with key equal to given node,
*               and which needs to be replaced by the given node.
* @param node - The node to be inserted to the list, after removing a node
*               with an equal key.
*               A copy of the node containing the new data will be inserted
* @return
* 	LIST_NULL_ARGUMENT if a NULL was sent as list or node
* 	LIST_OUT_OF_MEMORY if an allocation failed (meaning the function for copying
* 	a node failed)
* 	LIST_SUCCESS the node had been inserted successfully
*/
static ListResult listReplace(DoublyLinkedList list, Node node) {
    if (list == NULL || node == NULL) {
        return LIST_NULL_ARGUMENT;
    }
    NodeKeyElement key = nodeGetKey(node);
    Node to_replace = listGetNode(list, key);
    nodeFreeKey(node, key);
    ListResult res = listRemove(list, to_replace);
    if(res != LIST_SUCCESS){
        return res;
    }
    return listInsert(list, node);
}

