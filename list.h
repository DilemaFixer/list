#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include "logger.h"

#define BASE_LIST_FACTOR 2

typedef struct list_t {
    void **items;
    void *last_item;
    size_t count;
    size_t capacity;
    size_t factor;
} list_t;

list_t *new_list(size_t capacity);
void free_list(list_t *list);
void list_add(list_t *list , void* item);
void list_remove(list_t *list , size_t index);
void list_remove_last(list_t *list);

#endif
