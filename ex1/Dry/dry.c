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

Node mergeSortedLists(Node list1, Node list2, ErrorCode* error_code){
    if(!list1 || !list2){
        *error_code = NULL_ARGUMENT;
        return NULL;
    }
    if(!isListSorted(list1) || !isListSorted(list2)){
        *error_code = UNSORTED_LIST;
        return NULL;
    }
    Node combined_list = NULL;
    Node iterator1 = list1, iterator2 = list2, combined_list_iterator = combined_list;
    while(list1 && list2){
        combined_list_iterator = malloc(sizeof (*Node));
        if(!combined_list_iterator){
            *error_code = MEMORY_ERROR;
            destroyList(combined_list);
            return NULL;
        }


    }
}
