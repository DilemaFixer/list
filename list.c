#include "list.h"
#include "logger.h"

#include <stdlib.h>

list_t *new_list(size_t capacity) {
  if (capacity == 0)
    elog("Can't create list with zero capacity");

  list_t *list = (list_t *)malloc(sizeof(list_t));
  if (!list)
    elog("Error allocation memory for list_t struct");

  list->items = malloc(sizeof(void *) * capacity);
  if (!list->items)
    elog("Error allocation memory for list items ( list_t -> items (void**))");

  list->last_item = list->items;
  list->count = 0;
  list->factor = BASE_LIST_FACTOR;
  list->capacity = capacity;
  return list;
}

void free_list(list_t *list) {
  if (!list)
    return;

  if (list) {
    if (list->count > 0) {
      for (size_t i = 0; i < list->count; i++) {
        free(list->items[i]);
      }
    }
    free(list->items);
  }

  free(list);
}

void increase_list(list_t *list) {
  if (!list)
    elog("Can`t increase list capacity by null ptr on it");
  if (list->factor == 0)
    elog("Can't increase list capacity , factor is zero");
  if (!list->items)
    elog("Can't increase list capacity , list itemas arr is null");

  size_t new_capacity = list->factor * list->capacity;
  size_t size = sizeof(void *) * new_capacity;

  void *buffer = malloc(size);
  memcpy(buffer, list->items, size);
  free(list->items);

  list->items = buffer;
  list->last_item = (char *)list->items + (sizeof(void *) * list->count);
  list->capacity = new_capacity;
}

void list_add(list_t *list, void *item) {
  if (!list)
    elog("Can't add item to list , ptr is null");
  if (!item)
    elog("Can't add item to list , item is null");
  if (!list->items)
    elog("Can't add item to list, list_t -> items is null");

  if (list->count + 1 > list->capacity)
    increase_list(list);

  list->items[list->count] = item;
  list->last_item = item;
  list->count++;
}

void list_remove(list_t *list, size_t index) {
  if (!list)
    elog("Can't remove item from list, list ptr is null");
  if (!list->items)
    elog("Can't remove item from list , list_t -> items is null");
  if (list->count == 0)
    elog("Can't remove item from list , list is empty");
  if (list->count < index)
    elog("Can't remove items at index %zu , out of range", index);

  for (size_t i = index; i < list->count - 1; i++) {
    list->items[i] = list->items[i + 1];
  }

  list->count--;
  if (list->count == 0)
    list->last_item = NULL;
  else
    list->last_item = list->items[list->count - 1];
}

void list_remove_first(list_t *list) {
  if (!list)
    elog("Can't remove first at empty list");
  if (list->count == 0)
    elog("Can't remove first element at empty list");
  list_remove(list, 0);
}

void list_remove_last(list_t *list) {
  if (!list)
    elog("Can't remove last item from list, list ptr is null");
  if (list->count == 0)
    elog("Can't remove last item from empty list");
  list_remove(list, list->count - 1);
}

void list_add_at(list_t *list, void *item, size_t index) {
  if (!list)
    elog("Can't add element at %zu in null list", index);
  if (!item)
    elog("Can't add element at %zu in list , item is null", index);
  if (list->capacity < index + 1)
    elog("Can't add element at %zu , index was out of range", index);

  if (list->count + 1 > list->capacity)
    increase_list(list);

  void *from = (char *)list->items + (sizeof(void *) * index);
  void *to = (char *)list->items + (sizeof(void *) * (index + 1));

  memmove(to, from, (list->count - index) * sizeof(void *));
  list->items[index] = item;
  list->count++;
}

void list_add_first(list_t *list, void *item) {
  if (!list)
    elog("Can't add element as first , list is null");
  if (!item)
    elog("Can't add element as first , element is null");

  list_add_at(list, item, 0);
}

void *find(list_t *list,
           bool (*selector)(const void *item, size_t index, void *context),
           void *context) {
  if (!list || !selector)
    return NULL;

  for (size_t i = 0; i < list->count; i++) {
    void *item = list->items[i];
    if (selector(item, i, context)) {
      return item;
    }
  }

  return NULL;
}

list_t *find_all(list_t *list, bool (*selector)(const void *item, size_t index, void *context),
                 void *context) {
  if (!list || !selector)
    return NULL;

list_t *result = new_list(list->count > 0 ? list->count / 2 : 5);

  for (size_t i = 0; i < list->count; i++) {
    void *item = list->items[i];
    if (selector(item, i, context))
      list_add(result, item);
  }

  return result;
}
