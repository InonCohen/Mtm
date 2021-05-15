#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DLLNode.h"

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
    free((int*)to_free);
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

int compareInts (int* int1, int* int2){
    if(int1 == NULL || int2 == NULL){
        return BAD_KEY;
    }
    return (*int1 - *int2);
}

void printNode(char* name, Node node){
    if(!node || !name){
        printf("Wha wha.. something went wrong while trying to print %s\n", name);
    }
    int* key =(int*) nodeGetKey(node);
    void* general_data = nodeGetData(node);
    char* data= nodeGetData(node);
    printf("Node: %s\n", name);
    printf("Key: %d\n", *key);
    printf("Data: %s\n", data);
}


int main() {
    char* data1 = "Hello World";
    int key1=1;
    Node node1 = nodeCreate(copyString, copyInt, freeInt, freeString, &key1, data1);
    printNode("Node1", node1);
   // Node node2 = nodeCopy(node1);
  //  printNode("Node2", node2);
    nodeDestroy(node1);
    return 0;
}
