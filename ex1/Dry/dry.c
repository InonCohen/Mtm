#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#define BAD_INPUT (-999)

typedef struct node_t {
    int x;
    struct node_t *next;
} *Node;

typedef enum {
    SUCCESS=0,
    MEMORY_ERROR,
    UNSORTED_LIST,
    NULL_ARGUMENT,
} ErrorCode;

int getListLength(Node list){
    int size = 0;
    while (list){
        list = list->next;
        size++;
    }
    return size;
}

bool isListSorted(Node list){
    while (list->next){
        if(list->x > list->next->x){
            return false;
        }
    }
    return true;
}

Node copyNode(Node node){
    if(!node){
        return NULL;
    }
    Node node_copy = malloc(sizeof (*node_copy));
    if(!node_copy){
        return NULL;
    }
    node_copy->x = node->x;
    node_copy->next = node->next;
    return node_copy;
}

void destroyList(Node list){
    if(!list){
        return;
    }
    int size = getListLength(list);
    for(int i=0;i<size;i++){
        Node next = list->next;
        free(list);
        list = next;
    }
}

void printList(Node list){
    if(!list){
        return;
    }

    Node iter = copyNode(list);
    printf("Printing List...\n");
    while(iter->next){
        printf("Node Data: %d\n", iter->x);
        iter = iter->next;
    }
    printf("\n");
}

Node mergeSortedLists(Node list1, Node list2, ErrorCode *error_code){
    if(!list1 || !list2){
        *error_code = NULL_ARGUMENT;
        return NULL;
    }
    if(!isListSorted(list1) || !isListSorted(list2)){
        *error_code = UNSORTED_LIST;
        return NULL;
    }

//    Node iterator1 = list1, iterator2 = list2;
    Node merged_sorted_list = malloc(sizeof(*merged_sorted_list));
    if(!merged_sorted_list){
        *error_code = MEMORY_ERROR;
        return NULL;
    }
    if(list1->x <= list2->x){
        merged_sorted_list->x = list1->x;
    }
    else{
        merged_sorted_list->x = list2->x;
    }

//    while(iterator1 && iterator2){
//        merged_sorted_list = malloc(sizeof(*merged_sorted_list));
//        if(!merged_sorted_list){
//            *error_code = MEMORY_ERROR;
//            destroyList(merged_sorted_list);
//            return NULL;
//        }
//        if(iterator1->x < iterator2->x){
//            merged_sorted_list->x = iterator1->x;
//            merged_sorted_list->next = iterator1->next;
//        }
//        iterator1 = iterator1->next;
//        iterator2 = iterator2->next;
//    }
    list1 = list1->next;
    list2 = list2->next;
    *error_code = SUCCESS;
    return merged_sorted_list;
}

/**
 * listGeneralTest: Test for creating a list and print it.
 * @return
 *  MEMORY_ERROR if fails, SUCCESS otherwise.
 */
ErrorCode listGeneralTest() {
    int SIZE = 5;

    // Creating Nodes
    Node iter1 = malloc(sizeof(*iter1));
    if (!iter1) {
        return MEMORY_ERROR;
    }
    Node iter2 = malloc(sizeof(*iter2));
    if (!iter2) {
        free(iter1);
        return MEMORY_ERROR;
    }

    // Saves a ptr to list start
    Node list1 = iter1;
    Node list2 = iter2;

    // Init List Node Zero
    Node next1 = NULL;
    Node next2 = NULL;
    iter1->x = 0;
    iter1->next = next1;
    iter2->x = 0;
    iter2->next = next2;

    // Build List
    for (int i = 0; i < SIZE; i++) {

        next1 = malloc(sizeof(*next1));
        if (!next1) {
            destroyList(list1);
            destroyList(list2);
            return MEMORY_ERROR;
        }
        next1->x = (i+1);
        next1->next = NULL;

        next2 = malloc(sizeof(*next2));
        if (!next2) {
            destroyList(list1);
            destroyList(list2);
            return BAD_INPUT;
        }
        next2->x = (i+1) * 2;
        next2->next = NULL;

        iter1->next = next1;
        iter2->next = next2;
        iter1 = iter1->next;
        iter2 = iter2->next;
    }

    printList(list1);
    printList(list2);
    return SUCCESS;
}


int main(){
    listGeneralTest();

}
