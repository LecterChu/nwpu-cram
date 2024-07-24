#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

// Define the list structure
#define DEFINE_LIST(T) \
    typedef struct { \
        T* elements; \
        size_t size; \
        size_t capacity; \
    } List_##T; \
    \
    void List_##T##_init(List_##T* list) { \
        list->elements = NULL; \
        list->size = 0; \
        list->capacity = 0; \
    } \
    \
    void List_##T##_add(List_##T* list, T element) { \
        if (list->size >= list->capacity) { \
            list->capacity = (list->capacity == 0) ? 1 : list->capacity * 2; \
            list->elements = realloc(list->elements, list->capacity * sizeof(T)); \
        } \
        list->elements[list->size++] = element; \
    } \
    \
    void List_##T##_clear(List_##T* list) { \
        free(list->elements); \
        list->elements = NULL; \
        list->size = 0; \
        list->capacity = 0; \
    }\
    void List_##T##_get(T* element,size_t index){\
        *element = list->elements[index];\
    }
#endif