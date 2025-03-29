# Generic List Library

A lightweight, flexible, and easy-to-use generic list implementation in C. This library provides a dynamic array-based list that can store any type of data through void pointers.

## Installation

Clone the repository and include it in your project:

```bash
curl -o list.h https://raw.githubusercontent.com/DilemaFixer/list/main/logger.h
curl -o list.c https://raw.githubusercontent.com/DilemaFixer/list/main/logger.c
```

Include the header file in your code:

```c
#include "list.h"
```

## API Reference

### Creating and Destroying Lists

```c
// Create a new list with initial capacity
list_t *new_list(size_t capacity);

// Free list and all its elements
void free_list(list_t *list);
```

### Adding Elements

```c
// Add an element to the end of the list
void list_add(list_t *list, void *item);

// Add an element at a specific index
void list_add_at(list_t *list, void *item, size_t index);

// Add an element at the beginning of the list
void list_add_first(list_t *list, void *item);
```

### Removing Elements

```c
// Remove an element at a specific index
void list_remove(list_t *list, size_t index);

// Remove the last element
void list_remove_last(list_t *list);

// Remove the first element
void list_remove_first(list_t *list);
```

### Searching

```c
// Find the first element that matches the selector
void *find(list_t *list, 
           bool (*selector)(const void *item, size_t index, void *context), 
           void *context);

// Find all elements that match the selector
list_t *find_all(list_t *list, 
                 bool (*selector)(const void *item, size_t index, void *context), 
                 void *context);
```

## Usage Examples

### Basic Usage

```c
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Create a new list
    list_t *list = new_list(10);
    
    // Add some integers to the list
    for (int i = 0; i < 5; i++) {
        int *value = malloc(sizeof(int));
        *value = i * 10;
        list_add(list, value);
    }
    
    // Access elements
    for (size_t i = 0; i < list->count; i++) {
        int *value = (int*)list->items[i];
        printf("%d\n", *value);
    }
    
    // Free the list when done
    free_list(list);
    
    return 0;
}
```

### Using Selector Functions

```c
// Define a selector function to find items greater than a threshold
bool greater_than(const void *item, size_t index, void *context) {
    const int *value = (const int*)item;
    const int *threshold = (const int*)context;
    return *value > *threshold;
}

// Using find to get the first matching element
int threshold = 50;
int *found_item = (int*)find(list, greater_than, &threshold);

// Using find_all to get all matching elements
list_t *filtered_list = find_all(list, greater_than, &threshold);
```

## Notes on Memory Management

- The list stores void pointers to items, so it works with any data type
- When using `free_list()`, it frees both the list structure and all stored elements
- If you need to keep the elements, use a custom function to free only the list structure
- If you use `find_all()`, the resulting list contains references to the same elements

## Error Handling

The library uses a logging system for error reporting. Errors will be reported through the `logger.h` interface with appropriate error messages.

## Thread Safety

The library itself is not thread-safe. If you need to use the list in a multi-threaded environment, you need to implement your own synchronization mechanism.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

```
MIT License

Copyright (c) 2025 

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
