#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "map.h"
#include "../chess/LinkedList.h"

#define BAD_INT -1

struct Map_t{
    copyMapKeyElements copyKeyElemFunc;
    copyMapDataElements copyDataElemFunc;
    freeMapKeyElements freeKeyElemFunc;
    freeMapDataElements freeDataElemFunc;
    compareMapKeyElements compKeyElemsFunc;
    Node nodePrototype;
    DoublyLinkedList list;
    int iterator;
};



Map mapCreate(copyMapDataElements copyDataElement,
              copyMapKeyElements copyKeyElement,
              freeMapDataElements freeDataElement,
              freeMapKeyElements freeKeyElement,
              compareMapKeyElements compareKeyElements){
    if(copyKeyElement == NULL || copyDataElement == NULL ||
    freeDataElement == NULL || freeKeyElement == NULL || compareKeyElements == NULL){
        return NULL;
    }
    Map new_map = malloc(sizeof (*new_map));
    if(new_map == NULL){
        return NULL;
    }
    Node node = nodeCreate(copyDataElement, copyKeyElement, freeDataElement, freeKeyElement, compareKeyElements, 0, NULL);
    if(node == NULL){
        free(new_map);
        return NULL;
    }
    DoublyLinkedList list = listCreate(nodeCopy, nodeDestroy, nodeCompare);
    if(list == NULL){
        nodeDestroy(node);
        free(new_map);
        return NULL;
    }
    new_map->nodePrototype = node;
    new_map->list = list;
    new_map->iterator = 0;
    return new_map;
}

void mapDestroy(Map map){
    if(!map){
        return;
    }
    if(map->nodePrototype){
        nodeDestroy(map->nodePrototype);
    }
   if(map->list){
       listDestroy(map->list);
   }
   free(map);
}

Map mapCopy(Map map){
    if(!map){
        return NULL;
    }
    Map map_copy = malloc(sizeof (*map_copy));
    if(!map_copy){
        return NULL;
    }
    map_copy->copyKeyElemFunc = map->copyKeyElemFunc;
    map_copy->copyDataElemFunc = map->copyDataElemFunc;
    map_copy->freeKeyElemFunc = map->freeKeyElemFunc;
    map_copy->freeDataElemFunc = map->freeDataElemFunc;
    map_copy->compKeyElemsFunc = map->compKeyElemsFunc;
    map_copy->nodePrototype = nodeCopy(map->nodePrototype);
    if(!map_copy->nodePrototype){
        free(map_copy);
        return NULL;
    }
    map_copy->list = listCopy(map->list);
    if(!map_copy->list){
        nodeDestroy(map_copy->nodePrototype);
        free(map_copy);
        return NULL;
    }
    map_copy->iterator = 0;
    return map_copy;
}

int mapGetSize(Map map){
    if(!map){
        return BAD_INT;
    }
    return listGetSize(map->list);
}


bool mapContains(Map map, MapKeyElement element){
    if(!map || !element){
        return false;
    }
    NodeResult res = nodeSetKey(map->nodePrototype, element);
    if(res != NODE_SUCCESS){
        return false;
    }
    return listContains(map->list, map->nodePrototype);
}

/**
*	mapPut: Gives a specified key a specific value.
*  Iterator's value is undefined after this operation.
*
* @param map - The map for which to reassign the data element
* @param keyElement - The key element which need to be reassigned
* @param dataElement - The new data element to associate with the given key.
*      A copy of the element will be inserted as supplied by the copying function
*      which is given at initialization and old data memory would be
*      deleted using the free function given at initialization.
* @return
* 	MAP_NULL_ARGUMENT if a NULL was sent as map or keyElement or dataElement
* 	MAP_OUT_OF_MEMORY if an allocation failed (Meaning the function for copying
* 	an element failed)
* 	MAP_SUCCESS the paired elements had been inserted successfully
*/
MapResult mapPut(Map map, MapKeyElement keyElement, MapDataElement dataElement){
    if(!map || !keyElement || !dataElement){
        return MAP_NULL_ARGUMENT;
    }
    NodeResult res = nodeSetKey(map->nodePrototype, keyElement);
    if(res != NODE_SUCCESS){

        return (MapResult) res;
    }
    res = nodeSetData(map->nodePrototype, dataElement);
    if(res != NODE_SUCCESS){
        return (MapResult) res;
    }
    return (MapResult) listInsert(map->list, map->nodePrototype);
}

/**
*	mapGet: Returns the data associated with a specific key in the map.
*			Iterator status unchanged
*
* @param map - The map for which to get the data element from.
* @param keyElement - The key element which need to be found and whos data
we want to get.
* @return
*  NULL if a NULL pointer was sent or if the map does not contain the requested key.
* 	The data element associated with the key otherwise.
*/
MapDataElement mapGet(Map map, MapKeyElement keyElement){
    if(!map || !keyElement){
        return NULL;
    }
    NodeResult res = nodeSetKey(map->nodePrototype, keyElement);
    if(res != NODE_SUCCESS){
        return NULL;
    }
    if(!(mapContains(map, keyElement))){
        return NULL;
    }

    Node node_of_data = listGetNode(map->list, keyElement);
    if(!node_of_data){
        return NULL;
    }
    return nodeGetData(node_of_data);
}

/**
* 	mapRemove: Removes a pair of key and data elements from the map. The elements
*  are found using the comparison function given at initialization. Once found,
*  the elements are removed and deallocated using the free functions
*  supplied at initialization.
*  Iterator's value is undefined after this operation.
*
* @param map -
* 	The map to remove the elements from.
* @param keyElement
* 	The key element to find and remove from the map. The element will be freed using the
* 	free function given at initialization. The data element associated with this key
*  will also be freed using the free function given at initialization.
* @return
* 	MAP_NULL_ARGUMENT if a NULL was sent to the function
*  MAP_ITEM_DOES_NOT_EXIST if an equal key item does not already exists in the map
* 	MAP_SUCCESS the paired elements had been removed successfully
*/
MapResult mapRemove(Map map, MapKeyElement keyElement) {
    if (!map || !keyElement) {
        return MAP_NULL_ARGUMENT;
    }
    if (!mapContains(map, keyElement)) {
        return MAP_ITEM_DOES_NOT_EXIST;
    }
    NodeResult res1 = nodeSetKey(map->nodePrototype, keyElement);
    if(res1 != NODE_SUCCESS){

        return (MapResult) res1;
    }
    Node to_remove = listGetNode(map->list, keyElement);
    ListResult res2 = listRemove(map->list, to_remove);
    return (MapResult) res2;

}

MapKeyElement mapGetFirst(Map map){
    if(!map){
        return NULL;
    }
   Node first = listGetFirst(map->list);
    return nodeGetKey(first);
}


MapKeyElement mapGetNext(Map map){
    if(!map){
        return NULL;
    }
    Node next = listGetNext(map->list);
    return nodeGetKey(next);
}


/**
* mapClear: Removes all key and data elements from target map.
* The elements are deallocated using the stored free functions.
* @param map
* 	Target map to remove all element from.
* @return
* 	MAP_NULL_ARGUMENT - if a NULL pointer was sent.
* 	MAP_SUCCESS - Otherwise.
*/
MapResult mapClear(Map map){
    if(map == NULL){
        return MAP_NULL_ARGUMENT;
    }

    return (MapResult) listClear(map->list);
}

