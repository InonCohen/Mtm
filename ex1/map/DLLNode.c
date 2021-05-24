#include <stdio.h>
#include <stdlib.h>


#include "DLLNode.h"

struct Node_t{
    copyNodeKeyElement copyKeyFunc;
    freeNodeKeyElement freeKeyFunc;
    copyNodeDataElement copyDataFunc;
    freeNodeDataElement freeDataFunc;
    compareNodeKeyElements compKeysFunc;
    void* key;
    void* data;
    Node next;
    Node prev;
};

Node nodeCreate(copyNodeDataElement copyDataElement,
                copyNodeKeyElement copyKeyElement,
                freeNodeDataElement freeDataElement,
                freeNodeKeyElement freeKeyElement,
                compareNodeKeyElements compKeyElements, void* key, void* data){
    if(copyDataElement == NULL || copyKeyElement == NULL || freeDataElement == NULL ||
    freeKeyElement == NULL || compKeyElements == NULL){
        return NULL;
    }
    Node new_node = malloc(sizeof(*new_node));
    if(!new_node){
        return NULL;
    }
    new_node->copyDataFunc = copyDataElement;
    new_node->copyKeyFunc = copyKeyElement;
    new_node->freeDataFunc = freeDataElement;
    new_node->freeKeyFunc = freeKeyElement;
    new_node->compKeysFunc = compKeyElements;
    if(!key){
        new_node->key=NULL;
    }
    else{
        void* new_key = copyKeyElement(key);
        if(new_key == NULL){
            free(new_node);
            return NULL;
        }
        new_node->key = new_key;
    }
    if(!data){
        new_node->data=NULL;
    }
    else {
        void *new_data = copyDataElement(data);
        if (new_data == NULL) {
            free(new_node->key);
            free(new_node);
            return NULL;
        }
        new_node->data = new_data;
    }
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

void nodeDestroy(Node node){
    if(node == NULL){
        return;
    }
    node->freeKeyFunc(node->key);
    node->freeDataFunc(node->data);
    free(node);
}

Node nodeCopy (Node node){
    if (node == NULL){
        return NULL;
    }
    Node node_copy = malloc (sizeof(*node_copy));
    if(node_copy == NULL){
        return NULL;
    }
    node_copy->copyKeyFunc = node->copyKeyFunc;
    node_copy->copyDataFunc = node->copyDataFunc;
    node_copy->freeKeyFunc = node->freeKeyFunc;
    node_copy->freeDataFunc = node->freeDataFunc;
    node_copy->compKeysFunc = node->compKeysFunc;
    node_copy->key = node->copyKeyFunc(node->key);
    if (node->key != NULL && node_copy->key == NULL){
        free(node_copy);
        return NULL;
    }
    node_copy->data = node_copy->copyDataFunc(node->data);
    if (node->data != NULL && node_copy->data == NULL){
        node_copy->freeKeyFunc(node_copy->key);
        free(node_copy);
        return NULL;
    }
    node_copy->next = NULL;
    node_copy->prev = NULL;
    return node_copy;
}

NodeKeyElement nodeGetKey(Node node){
    if(node == NULL){
        return NULL;
    }
    if(node->key == NULL){
        return NULL;
    }
    NodeKeyElement key_copy = (node->copyKeyFunc)(node->key);
    if(!key_copy){
        return NULL;
    }
    return key_copy;
}

NodeDataElement nodeGetData(Node node){
    if(!node){
        return NULL;
    }
    return node->data;
}

NodeResult nodeSetKey(Node node, NodeKeyElement keyElement){
    if(!node || !keyElement){
        return NODE_NULL_ARGUMENT;
    }
    NodeKeyElement new_key=node->copyKeyFunc(keyElement);
    if(!new_key){
        return NODE_OUT_OF_MEMORY;
    }
    node->freeKeyFunc(node->key);
    node->key=new_key;
    return NODE_SUCCESS;
}

NodeResult nodeSetData(Node node, NodeDataElement dataElement){
    if(!node || !dataElement){
        return NODE_NULL_ARGUMENT;
    }
    NodeDataElement new_data=node->copyDataFunc(dataElement);
    if(!new_data){
        return NODE_OUT_OF_MEMORY;
    }
    node->freeDataFunc(node->data);
    node->data=new_data;
    return NODE_SUCCESS;
}

Node nodeGetNext(Node node){
    if(node == NULL){
        return NULL;
    }
    return node->next;
}

Node nodeGetPrev(Node node){
    if(!node){
        return NULL;
    }
    if(!node->prev){
        return NULL;
    }
    return node->prev;
}

NodeResult nodeSetNext(Node node, Node next_node){
    if(!node){
        return NODE_NULL_ARGUMENT;
    }
    if(!next_node){
        node->next=NULL;
    }
    else{
        node->next=next_node;
    }
    return NODE_SUCCESS;
}

NodeResult nodeSetPrev(Node node, Node prev_node){
    if(!node){
        return NODE_NULL_ARGUMENT;
    }
    if(!prev_node){
        node->prev=NULL;
    }
    else{
        node->prev=prev_node;
    }
    return NODE_SUCCESS;
}

int nodeCompare (Node node1, Node node2){
    if(node1 == NULL || node2 == NULL){
        return -1;
    }
    NodeKeyElement key1 = nodeGetKey(node1);
    if(!key1){
        return -1;
    }
    NodeKeyElement key2 = nodeGetKey(node2);
    if(!key2){
        node1->freeKeyFunc(key1);
        return -1;
    }
    int res = node1->compKeysFunc(key1,key2);
    node1->freeKeyFunc(key1);
    node2->freeKeyFunc(key2);
    return res;
}

void nodeFreeKey(Node node, NodeKeyElement key){
    node->freeKeyFunc(key);
}