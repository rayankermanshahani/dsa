/* dynamic_array.h */
#ifndef DYN_ARR_H
#define DYN_ARR_H

#include <stddef.h>
typedef struct {
    int *data;   // pointer to array elements
    size_t size; // number of elements
    size_t cap;  // capacity of array
} DynArr;

/* core operations */
DynArr *arr_create(size_t init_cap);
void arr_destroy(DynArr *arr);
int arr_get(const DynArr *arr, size_t idx);
void arr_set(DynArr *arr, size_t idx, int value);
void arr_append(DynArr *arr, int value);
void arr_remove(DynArr *arr, size_t idx);

/* utiilty functions */
size_t arr_size(const DynArr *arr);
size_t arr_cap(const DynArr *arr);
int arr_is_empty(const DynArr *arr);
void arr_clear(DynArr *arr);

#endif // DYN_ARR_H
