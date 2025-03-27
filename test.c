#include "logger.h"
#include "list.h"
#include <stdio.h>

void print_list(list_t *list) {
    if (!list) {
        printf("List is NULL\n");
        return;
    }
    
    printf("List contents (%zu items):\n", list->count);
    for (size_t i = 0; i < list->count; i++) {
        int *value = (int*)list->items[i];
        printf("[%zu]: %d\n", i, *value);
    }
    printf("\n");
}

int main(void) {
    print_time_in_log = true;
    print_where_in_log = true;
    
    ilog("Starting list test");
    
    list_t *list = new_list(10);
    ilog("Created new list with capacity %zu", list->capacity);
    
    for (int i = 0; i < 15; i++) {
        int *value = malloc(sizeof(int));
        *value = i * 10;
        list_add(list, value);
        dlog("Added value %d to list", *value);
    }
    
    ilog("List capacity after additions: %zu", list->capacity);
    print_list(list);
    
    ilog("Removing element at index 5");
    list_remove(list, 5);
    print_list(list);
    
    ilog("Removing last element");
    list_remove_last(list);
    print_list(list);
    
    int *last_value = (int*)list->last_item;
    ilog("Last item value: %d", *last_value);
    
    ilog("Freeing list");
    free_list(list);
    
    ilog("Test completed successfully");
    return 0;
}
