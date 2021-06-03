#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

int getListLength(Node list);
bool isListSorted(Node list);
Node mergeSortedLists(Node list1, Node list2, ErrorCode* error_code);
Node createNode(int input);


bool isListSorted(Node list){
    if(!list){
        return false;
    }
    Node iter = list;
    int one_before_last;
    while(iter && iter->next){
        if(iter->x > iter->next->x){
            return false;
        }
        one_before_last=iter->x;
        iter=iter->next;
    }
    if(one_before_last <= iter->x){
        return true;
    }
    return false;
}

Node createNode(int input) {
    Node init_node = malloc(sizeof(*init_node));
    if (init_node == NULL) {
        return NULL;
    }
    init_node->x = input;
    init_node->next = NULL;
    return init_node;
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

void printList(Node list){
    if(!list){
        return;
    }
    Node iter = list;
    printf("Printing List...\n");
    while(iter) {
        printf("%d", iter->x);
        if (iter->next) {
            printf(" -> ");
        }
        iter = iter->next;
    }
    printf("\n");
}

void destroyList(Node list) {
    while (list) {
        Node toDelete = list;
        list = list->next;
        free(toDelete);
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
    Node merged_sorted_list = NULL;
    Node iter1 = list1, iter2 = list2, *iter_merged = &merged_sorted_list;
    while(iter1 && iter2) {
        *iter_merged = malloc(sizeof(**iter_merged));
        if (!(*iter_merged)) {
            destroyList(merged_sorted_list);
            *error_code = MEMORY_ERROR;
            return NULL;
        }
        (*iter_merged)->next = NULL;
        if (iter1->x <= iter2->x) {
            (*iter_merged)->x = iter1->x;
            iter1 = iter1->next;
        } else {
            (*iter_merged)->x = iter2->x;
            iter2 = iter2->next;
        }
        iter_merged = &(*iter_merged)->next;
    }
    Node rest_to_copy = (iter1==NULL) ? iter2 : iter1;
    (*iter_merged) = copyList(rest_to_copy);
    if(!(*iter_merged)) {
        destroyList(merged_sorted_list);
        *error_code = MEMORY_ERROR;
        return NULL;
    }
    *error_code = SUCCESS;
    return merged_sorted_list;
}





// use ctrl+f on "createNode" and replace all with your create_node function name
// use ctrl+f on "destroyList" and replace all with your destroy_list function name

int main(){
    ErrorCode* error_code = malloc(sizeof(*error_code));
    *error_code = SUCCESS;
    Node list1 = createNode(2);
    list1->next = createNode(4);
    list1->next->next=createNode(9);
    Node list2 = createNode(2);
    list2->next = createNode(4);
    list2->next->next=createNode(8);
    Node merged_list = mergeSortedLists(list1,list2,error_code);
    printf("\n%d\n\n", *error_code);
    while(merged_list){
        printf("%d\n",merged_list->x);
        merged_list=merged_list->next;
    }
    destroyList(list1);
    destroyList(list2);
    destroyList(merged_list);
    list1 = createNode(1);
    list1->next = createNode(4);
    list1->next->next=createNode(9);
    list2 = createNode(2);
    list2->next = createNode(5);
    list2->next->next=createNode(8);
    merged_list = mergeSortedLists(list1,list2,error_code);
    printf("\n%d\n\n", *error_code);
    while(merged_list){
        printf("%d\n",merged_list->x);
        merged_list=merged_list->next;
    }
    destroyList(list1);
    destroyList(list2);
    destroyList(merged_list);
    list1 = createNode(1);
    list1->next = createNode(2);
    list1->next->next=createNode(9);
    list1->next->next->next=createNode(9);
    list2 = createNode(2);
    list2->next = createNode(5);
    list2->next->next=createNode(8);
    list2->next->next->next=createNode(8);
    list2->next->next->next->next=createNode(12);
    merged_list = mergeSortedLists(list1,list2,error_code);
    printList(merged_list);
    printf("\n%d\n", *error_code);
    while(merged_list){
        printf("%d\n",merged_list->x);
        merged_list=merged_list->next;
    }
    destroyList(list1);
    destroyList(list2);
    destroyList(merged_list);
    list1 = NULL;
    list2 = createNode(2);
    list2->next = createNode(5);
    list2->next->next=createNode(8);
    merged_list = mergeSortedLists(list1,list2,error_code);
    printf("\n%d\n", *error_code);
    while(merged_list){
        printf("%d\n",merged_list->x);
        merged_list=merged_list->next;
    }
    return 0;
}
