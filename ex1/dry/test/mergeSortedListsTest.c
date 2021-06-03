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
// add necessary declarations here

int getListLength(Node list) {
    int len=0;
    Node i=list;
    while(i){
        len++;
        i=i->next;
    }
    return len;
}

bool isListSorted(Node list) {
    Node i=list;
    while(i && i->next){
        if ((i->x)>(i->next->x))
        {
            return false;
        }
        i=i->next;
    }
    return true;
}

// add necessary functions here (create_node_func, destroy_list_func...)

Node mergeSortedLists(Node list1, Node list2, ErrorCode* error_code){

    //Enter your code here

}

// use ctrl+f on "insert_create_node_function" and replace all with your create_node function name
// use ctrl+f on "insert_destroy_list_function" and replace all with your destroy_list function name

int main(){
    ErrorCode* error_code = malloc(sizeof(*error_code));
    *error_code = SUCCESS;
    Node list1 = insert_create_node_function(2);
    list1->next = insert_create_node_function(4);
    list1->next->next=insert_create_node_function(9);
    Node list2 = insert_create_node_function(2);
    list2->next = insert_create_node_function(4);
    list2->next->next=insert_create_node_function(8);
    Node merged_list = mergeSortedLists(list1,list2,error_code);
    printf("\n%d\n\n", *error_code);
    while(merged_list){
        printf("%d\n",merged_list->x);
        merged_list=merged_list->next;
    }
    insert_destroy_list_function(list1);
    insert_destroy_list_function(list2);
    insert_destroy_list_function(merged_list);
    list1 = insert_create_node_function(1);
    list1->next = insert_create_node_function(4);
    list1->next->next=insert_create_node_function(9);
    list2 = insert_create_node_function(2);
    list2->next = insert_create_node_function(5);
    list2->next->next=insert_create_node_function(8);
    merged_list = mergeSortedLists(list1,list2,error_code);
    printf("\n%d\n\n", *error_code);
    while(merged_list){
        printf("%d\n",merged_list->x);
        merged_list=merged_list->next;
    }
    insert_destroy_list_function(list1);
    insert_destroy_list_function(list2);
    insert_destroy_list_function(merged_list);
    list1 = insert_create_node_function(5);
    list1->next = insert_create_node_function(4);
    list1->next->next=insert_create_node_function(9);
    list2 = insert_create_node_function(2);
    list2->next = insert_create_node_function(5);
    list2->next->next=insert_create_node_function(8);
    merged_list = mergeSortedLists(list1,list2,error_code);
    printf("\n%d\n", *error_code);
    while(merged_list){
        printf("%d\n",merged_list->x);
        merged_list=merged_list->next;
    }
    insert_destroy_list_function(list1);
    insert_destroy_list_function(list2);
    insert_destroy_list_function(merged_list);
    list1 = NULL;
    list2 = insert_create_node_function(2);
    list2->next = insert_create_node_function(5);
    list2->next->next=insert_create_node_function(8);
    merged_list = mergeSortedLists(list1,list2,error_code);
    printf("\n%d\n", *error_code);
    while(merged_list){
        printf("%d\n",merged_list->x);
        merged_list=merged_list->next;
    }
    return 0;
}