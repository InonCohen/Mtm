#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define BAD_INPUT (-999)
typedef int make_iso_compilers_happy;
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

Node copyList(Node list){
    if(!list){
        return NULL;
    }
    Node list_copy = malloc(sizeof (*list_copy));
    if(!list_copy){
        return NULL;
    }
    list_copy->x = list->x;
    list_copy->next = copyList(list->next);

    return list_copy;
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

    Node iter = list;
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

    Node merged_sorted_list = malloc(sizeof(*merged_sorted_list));
    if(!merged_sorted_list){
        *error_code = MEMORY_ERROR;
        return NULL;
    }
    merged_sorted_list->next = NULL;
    Node iter1 = list1, iter2 = list2, iter_merged = merged_sorted_list;

    if(iter1->x <= iter2->x){
        iter_merged->x = iter1->x;
        iter1 = iter1->next;
    }
    else{
        iter_merged->x = iter2->x;
        iter2 = iter2->next;
    }
    iter_merged = iter_merged->next;
    while(iter1 || iter2){
        iter_merged = malloc(sizeof (*iter_merged));
        if(iter1 == NULL){
            iter_merged = copyList(iter2);
            iter2 = NULL;
            continue;
        }

        if(iter2 == NULL){
            iter_merged = iter1;
            iter1 = NULL;
            continue;
        }

        if(iter1->x < iter2->x){
            merged_sorted_list->x = iter1->x;
            merged_sorted_list->next = iter1->next;
        }


        iter1 = iter1->next;
        iter2 = iter2->next;
    }

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

    Node copy_list = copyList(list1);
    destroyList(list1);
    destroyList(list2);
    destroyList(copy_list);
    return SUCCESS;
}


int main(){
    listGeneralTest();

}
