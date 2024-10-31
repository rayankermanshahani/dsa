/* main.c */
#include "dynamic_array.h"
#include <stdio.h>

/* function declarations */
void arr_print(const DynArr *arr);

/* driver program */
int main(void) {
    // create array
    DynArr *arr = arr_create(10);
    printf("created dynamic array\n");
    arr_print(arr);
    printf("\n");

    // append elements
    printf("appending elements...\n");
    for (int i = 0; i < 10; ++i) {
        arr_append(arr, i * 2);
        arr_print(arr);
    }
    printf("\n");

    // modify elements
    printf("modifying elements...\n");
    arr_set(arr, 9, 99);
    arr_set(arr, 0, 333);
    arr_set(arr, 5, 1337);
    arr_print(arr);
    printf("\n");

    // remove elements
    printf("removing elements at index 2, 7, and 4...\n");
    arr_remove(arr, 2);
    arr_print(arr);
    arr_remove(arr, 7);
    arr_print(arr);
    arr_remove(arr, 4);
    arr_print(arr);
    printf("\n");

    // get elements
    printf("first element of array is: %d\n", arr_get(arr, 0));
    printf("last element of array is: %d\n", arr_get(arr, arr->size - 1));
    printf("\n");

    // clear array
    printf("clearing array...\n");
    arr_clear(arr);
    arr_print(arr);
    printf("\n");

    // clean up
    arr_destroy(arr);
    printf("array destroyed.\n");
    printf("\n");

    printf("DYNAMIC ARRAY PROGRAM COMPLETE\n");
    return 0;
}

/* print a dynamic array */
void arr_print(const DynArr *arr) {
    printf("array (size=%zu, capacity=%zu): ", arr->size, arr->cap);
    for (size_t i = 0; i < arr->size; ++i) {
        printf("%d ", arr->data[i]);
    }
    printf("\n");
}
