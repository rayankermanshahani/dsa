#include "dynamic_array.h"
#include <stdlib.h>
#include <string.h>

#define GROWTH_FACTOR 2
#define MIN_CAP 8 // minimum array capacity

/* resize dynamic array */
static void resize(DynArr *arr, size_t new_cap) {
    int *new_data = realloc(arr->data, new_cap * sizeof(int));
    if (new_data) {
        arr->data = new_data;
        arr->cap = new_cap;
    }
}

/* create dynamic array */
DynArr *arr_create(size_t init_cap) {
    DynArr *arr = malloc(sizeof(DynArr));
    if (!arr)
        return NULL;
    init_cap = init_cap < MIN_CAP ? MIN_CAP : init_cap;
    arr->data = malloc(init_cap * sizeof(int));

    if (!arr->data) {
        free(arr);
        return NULL;
    }

    arr->size = 0;
    arr->cap = init_cap;
    return arr;
}

/* destroy dynamic array */
void arr_destroy(DynArr *arr) {
    if (arr) {
        free(arr->data);
        free(arr);
    }
}

/* get array element at index */
int arr_get(const DynArr *arr, size_t idx) {
    return (arr && idx < arr->size) ? arr->data[idx] : -1;
}

/* set array element at index */
void arr_set(DynArr *arr, size_t idx, int value) {
    if (arr && idx < arr->size) {
        arr->data[idx] = value;
    }
}

/* append element to end of array */
void arr_append(DynArr *arr, int value) {
    if (!arr)
        return;

    // array needs more space
    if (arr->size >= arr->cap) {
        resize(arr, arr->cap * GROWTH_FACTOR);
    }

    if (arr->size < arr->cap) {
        arr->data[arr->size++] = value;
    }
}

/* remove element from array at index */
void arr_remove(DynArr *arr, size_t idx) {
    if (!arr || idx >= arr->size)
        return;

    memmove(&arr->data[idx], &arr->data[idx + 1],
            (arr->size - idx - 1) * sizeof(int));
    arr->size--;

    // shrink if size is less than 1/4 of capacity
    if (arr->size > 0 && arr->size < arr->cap / 4) {
        resize(arr, arr->cap / 2);
    }
}

/* get array size */
size_t arr_size(const DynArr *arr) { return arr ? arr->size : 0; }

/* get array capacity */
size_t arr_cap(const DynArr *arr) { return arr ? arr->cap : 0; }

/* check if array is empty */
int arr_is_empty(const DynArr *arr) { return arr ? arr->size == 0 : 1; }

/* clear all array elements */
void arr_clear(DynArr *arr) {
    if (arr) {
        arr->size = 0;
    }
}
