#include "list.h"
#include "logger.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Функция для печати содержимого списка
void print_list(list_t *list) {
  if (!list) {
    printf("List is NULL\n");
    return;
  }

  printf("List contents (%zu items):\n", list->count);
  for (size_t i = 0; i < list->count; i++) {
    int *value = (int *)list->items[i];
    printf("[%zu]: %d\n", i, *value);
  }
  printf("\n");
}

// Селектор для поиска элемента по значению
bool find_value(const void *item, size_t index, void *context) {
  const int *value = (const int *)item;
  const int *target = (const int *)context;
  return *value == *target;
}

// Селектор для поиска элемента по индексу
bool find_by_index(const void *item, size_t index, void *context) {
  size_t target_index = *(size_t *)context;
  return index == target_index;
}

// Селектор для поиска элементов больше заданного значения
bool greater_than(const void *item, size_t index, void *context) {
  const int *value = (const int *)item;
  const int *threshold = (const int *)context;
  return *value > *threshold;
}

// Функция для освобождения только структуры списка, но не его элементов
void free_list_no_items(list_t *list) {
  if (!list)
    return;
  free(list->items);
  free(list);
}

int main(void) {
  print_time_in_log = true;
  print_where_in_log = true;

  ilog("Starting list test");

  // Создаем и заполняем список
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

  // Тест метода find - поиск по значению
  ilog("Testing find method with value 50");
  int target_value = 50;
  int *found_item = (int *)find(list, find_value, &target_value);
  if (found_item) {
    ilog("Found item with value %d", *found_item);
  } else {
    wlog("Item with value %d not found", target_value);
  }

  // Тест метода find - поиск по индексу
  ilog("Testing find method with index 7");
  size_t target_index = 7;
  found_item = (int *)find(list, find_by_index, &target_index);
  if (found_item) {
    ilog("Found item at index %zu with value %d", target_index, *found_item);
  } else {
    wlog("Item at index %zu not found", target_index);
  }

  // Тест метода find_all
  ilog("Testing find_all method for values > 70");
  int threshold = 70;
  list_t *filtered_list = find_all(list, greater_than, &threshold);
  ilog("Found %zu items greater than %d", filtered_list->count, threshold);
  print_list(filtered_list);

  // Тест с несуществующим значением
  ilog("Testing find with non-existing value 999");
  target_value = 999;
  found_item = (int *)find(list, find_value, &target_value);
  if (found_item) {
    ilog("Found item with value %d", *found_item);
  } else {
    wlog("Item with value %d not found (expected)", target_value);
  }

  // Тест с пустым списком
  ilog("Testing find_all on empty list");
  list_t *empty_list = new_list(5);
  list_t *empty_result = find_all(empty_list, greater_than, &threshold);
  ilog("Result list has %zu items (expected 0)", empty_result->count);

  // Тест list_add_at
  ilog("Testing list_add_at at position 3");
  int *new_value = malloc(sizeof(int));
  *new_value = 345;
  list_add_at(list, new_value, 3);
  print_list(list);

  // Освобождаем память
  ilog("Freeing filtered list (but not its items)");
  free_list_no_items(filtered_list);
  free_list_no_items(empty_result);
  free_list(empty_list);

  ilog("Removing element at index 5");
  list_remove(list, 5);
  print_list(list);

  ilog("Removing last element");
  list_remove_last(list);
  print_list(list);

  int *last_value = (int *)list->last_item;
  ilog("Last item value: %d", *last_value);

  ilog("Freeing list");
  free_list(list);

  ilog("Test completed successfully");
  return 0;
}
