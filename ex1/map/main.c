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

int compareInts (int* int1, int* int2){
    if(int1 == NULL || int2 == NULL){
        return BAD_KEY;
    }
    return (*int1 - *int2);
}

void printNode(char* name, Node node){
    if(!node || !name){
        printf("Wha wha.. something went wrong while trying to print %s\n", name);
        return;
    }
    int* key =(int*) nodeGetKey(node);
    char* data= nodeGetData(node);
    printf("Node: %s\n", name);
    printf("Key: %d\n", *key);
    printf("Data: %s\n", data);
    Node next = nodeGetNext(node);
    if(next){
        NodeKeyElement next_key=nodeGetKey(next);
        printf("Next Node: %d\n", *(int*)next_key);
        free(next_key);
    }
    Node previous=nodeGetPrev(node);
   if(previous){
       NodeKeyElement prev_key=nodeGetKey(previous);
       printf("Previous Node: %d\n", *(int*)prev_key);
       free(prev_key);
   }
   free(key);
   free(data);
}


int main() {
    char* data1 = "Hello World", *data2="Hello New World!";
    int key1 = 1, key2 = 2;
    Node node1 = nodeCreate(copyString, copyInt, freeString, freeInt, &key1, data1);
    printf("\n\nFIRST PRINTING\n\n");
    printNode("Node1", node1);
    Node node2 = nodeCopy(node1);
    printNode("Node2", node2);
    NodeResult res1 = nodeSetKey(node2, &key2);
    if(res1!=NODE_SUCCESS){
        return -1;
    }
    NodeResult res2 = nodeSetData(node2, data2);
    if(res2!=NODE_SUCCESS){
        return -1;
    }
    printf("\n\nSECOND PRINTING\n\n");
    printNode("Node1", node1);
    printNode("Node2", node2);
    int* get_key1 = nodeGetKey(node1);
    int* get_key2 = nodeGetKey(node2);
    char* get_data1 = nodeGetData(node1);
    char* get_data2 = nodeGetData(node2);
    printf("\n\nTHIRD PRINTING\n\n");
    printNode("Node1", node1);
    printNode("Node2", node2);
    printf("First key: %d, First data: %s\n", *get_key1, get_data1);
    printf("Second key: %d, Second data: %s\n", *get_key2, get_data2);
    NodeResult res3=nodeSetNext(node1, node2);
    NodeResult res4=nodeSetPrev(node1, node2);
    NodeResult res5=nodeSetNext(node2, node1);
    NodeResult res6=nodeSetPrev(node2, node1);
    if(res3!=NODE_SUCCESS||res4!=NODE_SUCCESS||res5!=NODE_SUCCESS||res6!=NODE_SUCCESS){
        return -1;
    }
    printf("\n\nFOURTH PRINTING\n\n");
    printf("First key: %d, First data: %s\n", *get_key1, get_data1);
    printf("Second key: %d, Second data: %s\n", *get_key2, get_data2);
    int new_key1=7, new_key2=13;
    NodeResult res7=nodeSetKey(node1, &new_key1);
    NodeResult res8=nodeSetKey(node2, &new_key2);
    if(res7!=NODE_SUCCESS||res8!=NODE_SUCCESS){
        return -1;
    }
    printf("\n\nFIFTH PRINTING\n\n");
    printNode("Node1", node1);
    printNode("Node2", node2);
    nodeDestroy(node1);
    nodeDestroy(node2);
    free(get_key1);
    free(get_key2);
    free(get_data1);
    free(get_data2);

    return 0;
}
