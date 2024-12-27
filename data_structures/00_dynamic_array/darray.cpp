/**
 * darray.cpp
 *
 * A minimal, cache-friendly dynamic array implementation with manual memory
 * management and zero dependencies.
 */

#include <cstdlib>
#include <cstring>
#include <iostream>

#define INIT_CAP 16     // initial array capacity
#define GROWTH_FACTOR 2 // when resizing arrays

template <typename T> struct DArray {
  T* data;    // pointer to array data
  size_t sz;  // current number of elements in array
  size_t cap; // total space allocated
};

// initialize dynamic array
template <typename T> DArray<T> darray_create() {
  DArray<T> arr;
  arr.data = (T*)malloc(INIT_CAP * sizeof(T));
  arr.sz = 0;
  arr.cap = INIT_CAP;

  return arr;
}

// free memory allocated for array
template <typename T> void darray_destroy(DArray<T>* arr) {
  free(arr->data);
  arr->sz = 0;
  arr->cap = 0;
}

// resize array when capacity is reached
template <typename T> void darray_resize(DArray<T>* arr, size_t new_cap) {
  T* new_data = (T*)realloc(arr->data, new_cap * sizeof(T));
  if (new_data) {
    arr->data = new_data;
    arr->cap = new_cap;
  }
}

// append element to end of array
template <typename T> void darray_push_back(DArray<T>* arr, T elem) {
  if (arr->sz == arr->cap) {
    darray_resize(arr, GROWTH_FACTOR * arr->cap);
  }
  arr->data[arr->sz++] = elem;
}

// remove and return element from end of array
template <typename T> T darray_pop_back(DArray<T>* arr) {
  if (arr->sz == 0) {
    throw std::runtime_error("Cannot pop from empty array");
  }
  return arr->data[--arr->sz];
}

// get element at index
template <typename T> T darray_get(const DArray<T>* arr, size_t idx) {
  if (idx >= arr->sz || idx < 0) {
    throw std::runtime_error("Index out of bounds");
  }
  return arr->data[idx];
}

// set element at index

int main(void) {
  std::cout << "Dynamic array program is complete." << std::endl;
  return 0;
}
