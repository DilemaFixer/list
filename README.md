# 📋 list

![Build Status](https://img.shields.io/badge/build-passing-brightgreen)
![Version](https://img.shields.io/badge/version-1.0.0-blue)
![License](https://img.shields.io/badge/license-MIT-green)
![Language](https://img.shields.io/badge/language-C-orange)

A lightweight, generic dynamic list implementation in plain C. This library provides a simple, yet efficient way to work with dynamic arrays of any type of data.

## 📥 Installation

### Linux & macOS

```bash
mkdir -p list && cd list

curl -o list.h https://raw.githubusercontent.com/DilemaFixer/list/main/list.h
curl -o list.c https://raw.githubusercontent.com/DilemaFixer/list/main/list.c
curl -o logger.h https://raw.githubusercontent.com/DilemaFixer/list/main/logger.h
curl -o logger.c https://raw.githubusercontent.com/DilemaFixer/list/main/logger.c
```

### Windows

```batch
mkdir list
cd list

curl -o list.h https://raw.githubusercontent.com/DilemaFixer/list/main/list.h
curl -o list.c https://raw.githubusercontent.com/DilemaFixer/list/main/list.c
curl -o logger.h https://raw.githubusercontent.com/DilemaFixer/list/main/logger.h
curl -o logger.c https://raw.githubusercontent.com/DilemaFixer/list/main/logger.c
```

## 🔧 API and Usage Examples

### 📌 List Creation and Management

Functions for creating, freeing, and managing the list structure.

#### Functions

```c
/**
 * Creates a new list with the specified initial capacity
 */
list_t *new_list(size_t capacity);

/**
 * Frees the list and all its items
 */
void free_list(list_t *list);

/**
 * Increases the capacity of the list by the factor specified in the list
 */
void increase_list(list_t *list);
```

#### Example

```c
#include "list.h"
#include "logger.h"

// Create a new list with initial capacity of 10
list_t *my_list = new_list(10);

// When done with the list, free it and all its items
free_list(my_list);
```

### 📌 Adding Items

Functions for adding items to the list at various positions.

#### Functions

```c
/**
 * Adds an item to the end of the list
 */
void list_add(list_t *list, void *item);

/**
 * Adds an item at the specified index
 */
void list_add_at(list_t *list, void *item, size_t index);

/**
 * Adds an item at the beginning of the list
 */
void list_add_first(list_t *list, void *item);
```

#### Example

```c
#include "list.h"
#include "logger.h"
#include <stdlib.h>

// Create some items
int *value1 = malloc(sizeof(int));
int *value2 = malloc(sizeof(int));
int *value3 = malloc(sizeof(int));
*value1 = 10;
*value2 = 20;
*value3 = 30;

// Add to the end of the list
list_add(my_list, value1);

// Add to the beginning of the list
list_add_first(my_list, value2);

// Add at a specific position (index 1)
list_add_at(my_list, value3, 1);
```

### 📌 Removing Items

Functions for removing items from various positions in the list.

#### Functions

```c
/**
 * Removes an item at the specified index
 */
void list_remove(list_t *list, size_t index);

/**
 * Removes the first item from the list
 */
void list_remove_first(list_t *list);

/**
 * Removes the last item from the list
 */
void list_remove_last(list_t *list);
```

#### Example

```c
#include "list.h"
#include "logger.h"

// Remove the item at index 2
list_remove(my_list, 2);

// Remove the first item
list_remove_first(my_list);

// Remove the last item
list_remove_last(my_list);
```

### 📌 Finding Items

Functions for searching items in the list based on custom criteria.

#### Functions

```c
/**
 * Finds the first item that matches the selector criteria
 */
void *find(list_t *list, 
           bool (*selector)(const void *item, size_t index, void *context),
           void *context);

/**
 * Finds all items that match the selector criteria
 */
list_t *find_all(list_t *list, 
                 bool (*selector)(const void *item, size_t index, void *context),
                 void *context);
```

#### Example

```c
#include "list.h"
#include "logger.h"
#include <stdbool.h>

// Selector function for finding an item with a specific value
bool find_value(const void *item, size_t index, void *context) {
    const int *value = (const int *)item;
    const int *target = (const int *)context;
    return *value == *target;
}

// Find an item with value 20
int target_value = 20;
int *found_item = (int *)find(my_list, find_value, &target_value);

// Selector for items greater than a threshold
bool greater_than(const void *item, size_t index, void *context) {
    const int *value = (const int *)item;
    const int *threshold = (const int *)context;
    return *value > *threshold;
}

// Find all items with values greater than 50
int threshold = 50;
list_t *filtered_list = find_all(my_list, greater_than, &threshold);

// Don't forget to free the filtered list when done
// (but not its items, as they're still in the original list)
free(filtered_list->items);
free(filtered_list);
```

## 📚 Dependencies

- [CSL (C Simple Logger)](https://github.com/DilemaFixer/CSL) - Simple logging library for C
