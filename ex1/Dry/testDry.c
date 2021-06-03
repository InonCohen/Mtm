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
Node createNode(int input); // creates new node with “input” in x field
int finishCopy(Node list, Node* head); //copies remaining list (that is not NULL yet)
int addToList(Node list, Node* head); // adds the x value of list to end of list
void destroyNode(Node Node);// destroys given node
void destroyList(Node list); // destroys list

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
Node createNode(int input) {
    Node init_node = malloc(sizeof(*init_node));
    if (init_node == NULL) {
        return NULL;
    }
    init_node->x = input;
    init_node->next = NULL;
    return init_node;
}



int addToList(Node list, Node* src_head) {
    Node new_node = createNode((list)->x);
    if (new_node == NULL) {
        destroyNode(new_node);
        return 0;
    }
    Node head = *src_head;
    while (head->next != NULL) {
        head = head->next;
    } // head points to the last node of src_head
    head->next = new_node;
    return 1;
}

int finishCopy(Node list, Node* head) { // while list is not null, copy remainder to list
    for (; (list) != NULL; list = list->next) {
        int add_remain = addToList(list, head);
        if (!add_remain) {
            return 0;
        }
    }
    return 1;
}

void destroyNode(Node Node) {
    free(Node);
}

void destroyList(Node list) {
    while (list) {
        Node toDelete = list;
        list = list->next;
        free(toDelete);
    }
}
Node mergeSortedLists(Node list1, Node list2, ErrorCode* error_code) {
    if (list1 == NULL || list2 == NULL) {
        *error_code = NULL_ARGUMENT;
        return NULL;
    }
    if (!isListSorted(list1) || !isListSorted(list2)) {
        *error_code = UNSORTED_LIST;
        return NULL;
    }
    Node merged_out = malloc(sizeof (*merged_out));
    if(!merged_out){
        *error_code = MEMORY_ERROR;
        return NULL;
    }
    Node iter1 = list1, iter2 = list2, merged_iter = merged_out;
    int add_element;
    while (iter1 && iter2)
    {
        merged_iter = malloc()
        if ((iter1->x) <= (iter2->x))
        {
            add_element = addToList(merged_out, &head);
            list1 = list1->next;
        }
        else
        {
            add_element = addToList(list2, &head);
            list2 = list2->next;
        }
        if (!add_element) {
            destroyList(head);
            return MEMORY_ERROR;
        }
    }
    Node list = NULL;
    if (!list1) {
        list = list2;
    }
    else {
        list = list1;
    }
    if (!finishCopy(list, &head)) {
        destroyList(head);
        return MEMORY_ERROR;
    }
    *merged_out = (*temp)->next; //skips the first node
    return SUCCESS;
}
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