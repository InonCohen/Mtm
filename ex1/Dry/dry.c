#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

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
    while(list){
        printf("%d", list->x);
    }
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


int main(){
    int SIZE=5;
    Node begin1, begin2;
    Node next1 = NULL, next2 = NULL;
    begin1 = malloc(sizeof (*begin1));
    if(!begin1){
        return 0;
    }
    begin2 = malloc(sizeof (*begin2));
    if(!begin2){
        free(begin1);
        return 0;
    }
    begin1->x = 0;
    begin1->next = next1;
    begin2->x = 0;
    begin1->next = next2;

    for(int i=0;i<SIZE;i++){
        next1->x = i;
        next2->x = i*2;

        next1 = malloc(sizeof (*next1));
        if(!next1){
            destroyList(begin1);
            return 0;
        }
        next2 = malloc(sizeof (*next2));
        if(!next2){
            destroyList(begin1);
            destroyList(begin2);
            return 0;
        }

        next1->next = next1;
        begin2->next = next2;
    }

    return 0;
}
