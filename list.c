#include "logger.h"
#include "list.h"

#include <stdlib.h>

list_t *new_list(size_t capacity){
    if(capacity == 0) elog("Can't create list with zero capacity");

    list_t *list = (list_t*)malloc(sizeof(list_t));
    if(!list) elog("Error allocation memory for list_t struct");

    list->items = malloc(sizeof(void*) * capacity);
    if(!list->items) elog("Error allocation memory for list items ( list_t -> items (void**))");

    list->last_item = list->items;
    list->count = 0;
    list->factor = BASE_LIST_FACTOR;
    list->capacity = capacity;
    return list;
}

void free_list(list_t *list){
    if(!list) return;

    if(list){
        if(list->count > 0){
            for(size_t i = 0; i < list->count; i++){
                free(list->items[i]);
            }
        }
        free(list->items);
    }

    free(list);
}


void increase_list(list_t *list){
    if(!list) elog("Can`t increase list capacity by null ptr on it");
    if(list->factor == 0) elog("Can't increase list capacity , factor is zero");
    if(!list->items) elog("Can't increase list capacity , list itemas arr is null");
    
    size_t new_capacity = list->factor * list->capacity;
    size_t size = sizeof(void*) * new_capacity;

    void *buffer = malloc(size);
    memcpy(buffer , list->items , size);
    free(list->items);

    list->items = buffer;
    list->last_item = (char*)list->items + (sizeof(void*) * list->count);
    list->capacity = new_capacity;
}
void list_add(list_t *list , void* item){
    if(!list) elog("Can't add item to list , ptr is null");
    if(!item) elog("Can't add item to list , item is null");
    if(!list->items) elog("Can't add item to list, list_t -> items is null");
    
    if(list->count + 1 > list->capacity)
        increase_list(list);

    list->items[list->count] = item;
    list->last_item = item;
    list->count++;
}

void list_remove(list_t *list , size_t index){
    if(!list) elog("Can't remove item from list, list ptr is null");
    if(!list->items) elog("Can't remove item from list , list_t -> items is null");
    if(list->count == 0) elog("Can't remove item from list , list is empty");
    if(list->count < index) elog("Can't remove items at index %zu , out of range" , index);

    for(size_t i = index ; i < list->count - 1; i++){
        list->items[i] = list->items[i+1];
    }

    list->count--;
    if(list->count == 0)
        list->last_item = NULL;
    else 
        list->last_item = list->items[list->count - 1];
}

void list_remove_last(list_t *list){
    if(!list) elog("Can't remove last item from list, list ptr is null");
    if(list->count == 0) elog("Can't remove last item from empty list");
    list_remove(list , list->count - 1);
}
