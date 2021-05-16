#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DLLNode.h"
#include "LinkedList.h"

#define BAD_KEY -999


void* copyString (void* to_copy){
    if(to_copy == NULL){
        return NULL;
    }
    int size = strlen((char*)to_copy);
    char* new_string = malloc(size+1);
    if(!new_string){
        return NULL;
    }
    strcpy(new_string, (char*)to_copy);
    return new_string;
}

void freeInt(void* to_free){
    free(to_free);
}

void freeString(void* to_free){
    free((char*)to_free);
}


int compareStrings (char* str1, char* str2){
    if(str1 == NULL || str2 == NULL){
        return BAD_KEY;
    }
    return strcmp(str1, str2);
}

void* copyInt (void* to_copy){
    if(to_copy == NULL){
        return NULL;
    }
    int* new_int = malloc(sizeof(int));
    if(!new_int){
        return NULL;
    }
    *new_int = (*(int*)to_copy);
    return new_int;
}

int compareInts (void* int1, void* int2){
    if(int1 == NULL || int2 == NULL){
        return BAD_KEY;
    }
    return (*(int*)int1 - *(int*)int2);
}

void printNode(Node node){
    if(!node){
        printf("Wha wha.. something went wrong while trying to print node\n");
        return;
    }
    int* key =(int*) nodeGetKey(node);
    char* data= nodeGetData(node);
    printf("   Key: %d\n", *key);
    printf("   Data: %s\n", data);
    Node next = nodeGetNext(node);
    if(next){
        NodeKeyElement next_key=nodeGetKey(next);
        printf("   Next Node: %d\n", *(int*)next_key);
        free(next_key);
    }
    Node previous=nodeGetPrev(node);
   if(previous){
       NodeKeyElement prev_key=nodeGetKey(previous);
       printf("   Previous Node: %d\n", *(int*)prev_key);
       free(prev_key);
   }
   free(key);
   free(data);
}

//void printList(DoublyLinkedList list){
//    if(!list){
//        return;
//    }
//    int size=listGetSize(list);
//    printNode(listGetFirst(list));
//    for(int i=1;i<size;i++){
//        Node temp
//        printNode(nodeGetNext(list));
//    }
//}


int main() {
    char* data1 = "Hello World", *data2="Hello New World!";
    int key1 = 1, key2 = 2;
    Node node1 = nodeCreate(copyString, copyInt, freeString, freeInt, &key1, data1);
    Node node2 = nodeCreate(copyString, copyInt, freeString, freeInt, &key2, data2);
    DoublyLinkedList list1 = listCreate(copyString, copyInt, freeString, freeInt, compareInts);
    listDestroy(list1);

    //TODO: check GetFirst, build GetNext, then build copyFunc, then the rest. Estimation: 6 hours
    //TODO: Build the MAP.C. Estimation: 2 hours.

    return 0;
}
