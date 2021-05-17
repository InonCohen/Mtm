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

ListResult listRemove(DoublyLinkedList list, Node node){
    if(!list || !node){
        return LIST_NULL_ARGUMENT;
    }
    if(!listContains(list, node)){
        return LIST_ITEM_DOES_NOT_EXIST;
    }
    Node iter = listGetFirst(list);
    while(iter!=NULL){
        if(list->compNodesFunc(iter, node) == 0){
            if(iter==list->head){
                list->head= nodeGetNext(list->head);
            }
            if(iter==list->tail){
                list->tail= nodeGetPrev(list->tail);
            }
            list->freeNodeFunc(iter);
            list->size--;
            return LIST_SUCCESS;
        }
        iter= nodeGetNext(iter);
    }
    return LIST_ITEM_DOES_NOT_EXIST;
}

void listDestroy(DoublyLinkedList list){
    if(!list){
        return;
    }
    int num_of_nodes=list->size;
    for(int i=0;i<num_of_nodes;i++){

        listRemove(list, list->head);
    }
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
    Node iter = listGetFirst(list);
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

Node listGetFirst(DoublyLinkedList list){
    if(!list){
        return NULL;
    }
    list->iterator=1;
    return list->head;
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

Node findFollowing(DoublyLinkedList list, Node node){
    if(list == NULL || node == NULL){
        return NULL;
    }
    int diff = list->compNodesFunc(list->head, node);
    assert(diff != 0);
    if(diff>0){
        return listGetFirst(list);
    }
    Node iter = list->head;
    while(iter!=NULL){
        if(list->compNodesFunc(iter, node) < 0){
            iter = nodeGetNext(iter);
        }
        break;
    }
    return iter;
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

Node listGet (DoublyLinkedList list, Node node){
    if(!list || !node){
        return NULL;
    }
    Node iter = listGetFirst(list);
    while(iter){
        if(list->compNodesFunc(iter,node)==0){
            return iter;
        }
        iter= nodeGetNext(iter);
    }
    return NULL;
}

static ListResult listReplace(DoublyLinkedList list, Node node) {
    if (list == NULL || node == NULL) {
        return LIST_NULL_ARGUMENT;
    }
    Node to_replace = listGet(list, node);
    ListResult res = listRemove(list, to_replace);
    if(res != LIST_SUCCESS){
        return res;
    }
    return listInsert(list, node);
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




