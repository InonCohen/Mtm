#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../DLLNode.h"
#include "../LinkedList.h"
#include "../map.h"

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

void printMap(Map map){
    int size = mapGetSize(map);
    MapKeyElement iter = mapGetFirst(map);
    for(int i=0;i<size;i++){
        int key = *(int*)iter;
        printf("Key: %d, ", key);
        MapDataElement data_iter=mapGet(map, iter);
        char* data = (char*)data_iter;
        printf("Data: %s\n", data);
        freeInt(iter);
        iter = mapGetNext(map);
    }
    freeInt(iter);
}


int main() {
    Map map1 = mapCreate(copyString, copyInt, freeString, freeInt, compareInts);
    if(!map1){
        printf("map1 creation failed\n");
        return 1;
    }
    int key1 = 1, key2 = 2, key3 = 3;
    char* data1 = "hello", *data2 = "new", *data3 = "world";
    MapResult res = mapPut(map1, &key1, data1);
    if(res != MAP_SUCCESS){
        printf("insert1 failed with code %d\n", res);
    }
    res = mapPut(map1, &key2, data2);
    if(res != MAP_SUCCESS){
        printf("insert 2 failed with code %d\n", res);
    }
    res = mapPut(map1, &key3, data3);
    if(res != MAP_SUCCESS){
        printf("insert 3 failed with code %d\n", res);
    }
    printf("\n\n--PRINTING MAP1--\n\n");
    printMap(map1);
    Map map2 = mapCopy(map1);
    if(!map2){
        printf("map2 creation failed\n");
        return 1;
    }
    printf("\n\n--PRINTING MAP2 BEFORE CLEARING MAP1--\n\n");
    printMap(map2);
    printf("\n\n--PRINTING MAP1 AFTER REMOVING HEAD--\n\n");
    mapRemove(map1,&key1);
    printMap(map1);
    printf("\n\n--PRINTING MAP2 AFTER CLEARING MAP1--\n\n");
    printMap(map2);

    mapDestroy(map1);
    mapDestroy(map2);
    return 0;
}
