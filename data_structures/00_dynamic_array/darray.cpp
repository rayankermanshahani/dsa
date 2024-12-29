/**
 * darray.cpp
 *
 * A minimal, cache-friendly dynamic array implementation with manual memory
 * management and zero dependencies.
 */

#include "testing.hpp"
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
template <typename T> void darray_set(DArray<T>* arr, size_t idx, T elem) {
  if (idx >= arr->sz || idx < 0) {
    throw std::runtime_error("Index out of bounds");
  }
  arr->data[idx] = elem;
}

// get current size of array
template <typename T> size_t darray_size(const DArray<T>* arr) {
  return arr->sz;
}

int main(void) {
  // test suite
  test::TestSuite suite("Dynamic Array Tests");

  suite.add_test("Creation and destruction", []() {
    auto arr = darray_create<int>();
    test::assert_equal(size_t(0), darray_size(&arr));
    test::assert_equal(size_t(INIT_CAP), arr.cap);

    darray_destroy(&arr);
    test::assert_equal(size_t(0), arr.cap);
  });

  suite.add_test("Push back and size", []() {
    auto arr = darray_create<int>();
    darray_push_back(&arr, 1);
    darray_push_back(&arr, 3);
    darray_push_back(&arr, 3);
    darray_push_back(&arr, 7);

    test::assert_equal(size_t(4), darray_size(&arr));
    test::assert_equal(1, darray_get(&arr, 0));
    test::assert_equal(3, darray_get(&arr, 1));
    test::assert_equal(3, darray_get(&arr, 2));
    test::assert_equal(7, darray_get(&arr, 3));

    darray_destroy(&arr);
  });

  suite.add_test("Pop back and size", []() {
    auto arr = darray_create<int>();
    darray_push_back(&arr, 1);
    darray_push_back(&arr, 3);
    darray_push_back(&arr, 3);
    darray_push_back(&arr, 7);

    test::assert_equal(size_t(4), darray_size(&arr));
    test::assert_equal(7, darray_pop_back(&arr));
    test::assert_equal(3, darray_pop_back(&arr));
    test::assert_equal(3, darray_pop_back(&arr));
    test::assert_equal(1, darray_pop_back(&arr));
    test::assert_equal(size_t(0), darray_size(&arr));

    darray_destroy(&arr);
  });

  suite.add_test("Get and set", []() {
    auto arr = darray_create<int>();
    darray_push_back(&arr, 1);
    darray_push_back(&arr, 3);
    darray_push_back(&arr, 3);
    darray_push_back(&arr, 7);

    darray_set(&arr, 0, 69);
    test::assert_equal(69, darray_get(&arr, 0));

    darray_destroy(&arr);
  });

  suite.add_test("Auto-resize", []() {
    auto arr = darray_create<int>();

    // fill beyond initial capacity
    for (int i = 0; i < INIT_CAP + 1; ++i) {
      darray_push_back(&arr, i);
    }
    test::assert_equal(size_t(INIT_CAP + 1), darray_size(&arr));
    test::assert_equal(size_t(INIT_CAP * GROWTH_FACTOR), arr.cap);

    // fill beyond new capacity
    for (int i = INIT_CAP + 1; i < INIT_CAP * GROWTH_FACTOR + 1; ++i) {
      darray_push_back(&arr, i);
    }
    test::assert_equal(size_t(INIT_CAP * GROWTH_FACTOR + 1), darray_size(&arr));
    test::assert_equal(size_t(INIT_CAP * GROWTH_FACTOR * GROWTH_FACTOR),
                       arr.cap);

    darray_destroy(&arr);
  });

  // error handling tests
  suite.add_test("Pop from empty array", []() {
    auto arr = darray_create<int>();
    bool caught_exception = false;

    try {
      darray_pop_back(&arr);
    } catch (const std::runtime_error& e) {
      caught_exception = true;
    }
    test::assert_true(caught_exception, "Expected exception not thrown");

    darray_destroy(&arr);
  });

  suite.add_test("Out of bounds access", []() {
    auto arr = darray_create<int>();
    darray_push_back(&arr, 7);
    bool caught_exception = false;

    try {
      darray_get(&arr, 2);
    } catch (const std::runtime_error& e) {
      caught_exception = true;
    }
    test::assert_true(caught_exception, "Expected exception not thrown");

    caught_exception = false;
    try {
      darray_get(&arr, -3);
    } catch (const std::runtime_error& e) {
      caught_exception = true;
    }
    test::assert_true(caught_exception, "Expected exception not thrown");

    darray_destroy(&arr);
  });

  // run all tests
  suite.run();

  // benchmarking
  test::Benchmark bench("Dynamic Array Benchmarks");

  bench.add_test("Push back performance", []() {
    auto arr = darray_create<int>();
    for (int i = 0; i < 100000; ++i) {
      darray_push_back(&arr, i);
    }

    darray_destroy(&arr);
  });

  bench.add_test("Push and pop performance", []() {
    auto arr = darray_create<int>();
    for (int i = 0; i < 100000; ++i) {
      darray_push_back(&arr, i);
    }
    while (darray_size(&arr) > 0) {
      darray_pop_back(&arr);
    }

    darray_destroy(&arr);
  });

  bench.add_test("Random access performance", []() {
    auto arr = darray_create<int>();
    test::RandomGenerator gen;

    for (int i = 0; i < 100000; ++i) {
      darray_push_back(&arr, i);
    }

    auto rand_idxs = gen.generate_ints(10000, 0, 99999);
    for (size_t i = 0; i < rand_idxs.size(); ++i) {
      darray_get(&arr, rand_idxs[i]);
    }

    darray_destroy(&arr);
  });

  // run all benchmarks
  bench.run();

  std::cout << "\n" << std::string(50, '=') << std::endl;
  std::cout << "Dynamic array program is complete." << std::endl;
  std::cout << "" << std::string(50, '=') << std::endl;

  return 0;
}
