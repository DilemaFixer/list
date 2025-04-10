#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    LEVEL_FATAL = 0,
    LEVEL_WARN  = 1,
    LEVEL_DEBUG = 2,
    LEVEL_TODO  = 3,
    LEVEL_UNIMPLEMENTED = 4
} LogLevel;

static const char* const LEVEL_NAMES[] = {
    "FATAL", "WARN", "DEBUG", "TODO", "UNIMPLEMENTED"
};

static inline void lmessage(LogLevel level, const char* format, ...) {
    fprintf(stderr, "[%s] ", LEVEL_NAMES[level]);

    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);

    fprintf(stderr, "\n");

    if (level == LEVEL_FATAL || level == LEVEL_UNIMPLEMENTED) {
        exit(1);
    }
}

#define lfatal(...) lmessage(LEVEL_FATAL, __VA_ARGS__)
#define lwarn(...)  lmessage(LEVEL_WARN, __VA_ARGS__)
#define ldebug(...) lmessage(LEVEL_DEBUG, __VA_ARGS__)
#define ltodo(...)  lmessage(LEVEL_TODO, __VA_ARGS__)
#define lunimp(...) lmessage(LEVEL_UNIMPLEMENTED, "Not implemented: " __VA_ARGS__)

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

void list_add_at(list_t *list , void* item , size_t index);
void list_add(list_t *list , void* item);
void list_add_first(list_t *list , void *item);

void list_remove(list_t *list , size_t index);
void list_remove_last(list_t *list);
void list_remove_first(list_t *list);
void *find(list_t *list, bool (*selector)(const void *item, size_t index, void *context), void *context);
list_t *find_all(list_t *list , bool(*selector)(const void *item , size_t index, void *context) , void *context);
#endif
