#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"
#define INVALID_ARG -1

struct DoublyLinkedList_t{
    copyNodeKeyElement copyKeyFunc;
    freeNodeKeyElement freeKeyFunc;
    copyNodeDataElement copyDataFunc;
    freeNodeDataElement freeDataFunc;
    compareListNodeKeyElements compKeysFunc;
    Node head;
    Node tail;
    int size;
    int iterator;
};

DoublyLinkedList listCreate(copyListNodeDataElements copyDataElement,
                copyListNodeKeyElements copyKeyElement,
                freeListNodeDataElements freeDataElement,
                freeListNodeKeyElements freeKeyElement,
                compareListNodeKeyElements compareKeyElements){
    if(copyDataElement == NULL || copyKeyElement == NULL || freeDataElement == NULL || freeKeyElement == NULL){
        return NULL;
    }
    DoublyLinkedList list = malloc (sizeof(*list));
    if(!list){
        return NULL;
    }
    list->head = nodeCreate(copyDataElement, copyKeyElement, freeDataElement, freeKeyElement, NULL, NULL);
    if(!list->head){
        free(list);
        return NULL;
    }
    list->tail = nodeCreate(copyDataElement, copyKeyElement, freeDataElement, freeKeyElement, NULL, NULL);
    if(!list->tail){
        nodeDestroy(list->head);
        free(list);
        return NULL;
    }
    list->copyKeyFunc = copyKeyElement;
    list->copyDataFunc = copyDataElement;
    list->freeKeyFunc = freeKeyElement;
    list->freeDataFunc = freeDataElement;
    list->compKeysFunc = compareKeyElements;
    list->size = 0;
    list->iterator = 0;
    return list;
}

void listDestroy(DoublyLinkedList list){
    if(!list){
        return;
    }
    int num_of_nodes=list->size;
    for(int i=0;i<num_of_nodes;i++){
        nodeDestroy(nodeGetNext(list->head));
    }
    nodeDestroy(list->head);
    nodeDestroy(list->tail);
    free(list);
}

//DoublyLinkedList listCopy(DoublyLinkedList list){
//    if(!list){
//        return NULL;
//    }
//    DoublyLinkedList list_copy = malloc((sizeof(*list_copy)));
//    if(!list_copy){
//        return NULL;
//    }
//    int size = list->size;
//    Node iter = listGetFirst(list);
//    for(int i=0;i<size;i++){
//        Node current_temp = nodeCopy(nodeGetNext(list));
//    }
//}

int listGetSize(DoublyLinkedList list){
    if(!list){
        return INVALID_ARG;
    }
    return list->size;
}

Node listGetFirst(DoublyLinkedList list){
    if(!list){
        return NULL;
    }
    int size = listGetSize(list);
    Node min_node = nodeGetNext(list->head);
    if(!min_node){
        return NULL;
    }
    ListNodeKeyElement min_key = list->copyKeyFunc(nodeGetKey(min_node));
    if(!min_key){
        nodeDestroy(min_node);
        return NULL;
    }
    Node iter = nodeGetNext(min_node);
    if(!iter){
        list->freeKeyFunc(min_key);
        nodeDestroy(min_node);
    }
    for(int i=1;i<size;i++) {
        Node temp_node = nodeGetNext(iter);
        if (!temp_node) {
            list->freeKeyFunc(min_key);
            nodeDestroy(min_node);
            nodeDestroy(iter);
            return NULL;
        }
        ListNodeKeyElement iter_key = nodeGetKey(temp_node);
        if (!iter_key) {
            nodeDestroy(temp_node);
            list->freeKeyFunc(min_key);
            nodeDestroy(min_node);
            nodeDestroy(iter);
            return NULL;
        }
        if (0 > list->compKeysFunc(iter_key, min_key)) {
            min_key = list->copyKeyFunc(nodeGetKey(iter));
            min_node = iter;
        }
        iter = temp_node;
        nodeDestroy(temp_node);
        list->freeKeyFunc(iter_key);
    }
    return min_node;
}
