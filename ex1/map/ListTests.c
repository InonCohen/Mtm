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

int compareListNodes(Node node1, Node node2){
    if(!node1 || !node2){
        return BAD_KEY;
    }
    int* key1 = (int*)nodeGetKey(node1);
    int* key2 = (int*)nodeGetKey(node2);
    int res =  compareInts(key1, key2);
    free(key1);
    free(key2);
    return res;
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

void printList(DoublyLinkedList list){
    if(!list){
        return;
    }
    int size=listGetSize(list);
    Node iter = listGetFirst(list);
    for(int i=0;i<size;i++){
        if(i==0){
            printf("\n\nHEAD\n\n");
        }
        if(i==size-1){
            printf("\n\nTAIL\n\n");
        }
        printNode(iter);
        iter= nodeGetNext(iter);
    }
}


int main() {
    char* data1 = "Hello World", *data2="Hello New World!", *data3 ="A whole new world!!!";
    int key1 = 1, key2 = 2;
    Node node1 = nodeCreate(copyString, copyInt, freeString, freeInt, &key1, data1);
    Node node2 = nodeCreate(copyString, copyInt, freeString, freeInt, &key2, data2);
    DoublyLinkedList list1 = listCreate(nodeCopy, nodeDestroy, compareListNodes);
    ListResult res1 = listInsert(list1, node1);
    printf("Insert1 outcome: %d\n", res1);
    res1 = listInsert(list1, node2);
    printf("Insert2 outcome: %d\n", res1);
    nodeDestroy(node1);
    nodeDestroy(node2);
    printList(list1);
    Node node3 = nodeCreate(copyString, copyInt, freeString, freeInt, &key2, data3);
    res1=listInsert(list1, node3);
    printf("\nReplace outcome: %d\n", res1);
    printList(list1);
    DoublyLinkedList list2 = listCopy(list1);
    printf("\nPrinting list2\n");
    printList(list2);
    listDestroy(list1);
    printf("\nPrinting list2 AGAIN\n");
    printList(list2);
    nodeDestroy(node3);
    listDestroy(list2);
    return 0;
}
