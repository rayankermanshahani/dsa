/**
 * sll.cpp
 *
 * A singly-linked list implementation.
 */

#include "testing.hpp"
#include <cassert>
#include <cstdlib>
#include <iostream>

template <typename T> struct Node {
  T data;
  Node<T>* next; // pointer to next node
};

// initialize new node
template <typename T> Node<T>* node_create(T data) {
  Node<T>* new_node = new Node<T>;
  if (!new_node) {
    std::cerr << "Memory allocation failed\n";
    exit(EXIT_FAILURE);
  }
  new_node->data = data;
  new_node->next = nullptr;

  return new_node;
}

// add node to head of list
template <typename T> Node<T>* prepend(Node<T>* head, T data) {
  Node<T>* new_node = node_create(data);
  new_node->next = head;

  return new_node;
}

// add node to tail of list
template <typename T> Node<T>* append(Node<T>* head, T data) {
  if (!head) { // list is empty (no head)
    return node_create(data);
  }

  Node<T>* current = head;
  while (current->next) { // find tail
    current = current->next;
  }
  current->next = node_create(data);

  return head;
}

// remove first node with given data
template <typename T> Node<T>* node_remove(Node<T>* head, T data) {
  if (!head) {
    return nullptr;
  }

  if (head->data == data) {
    Node<T>* new_head = head->next;
    delete head;
    return new_head;
  }

  Node<T>* current = head;
  while (current->next && current->next->data != data) {
    current = current->next;
  }

  if (current->next) {
    Node<T>* target_node = current->next;
    current->next = target_node->next;
    delete target_node;
  }
  return head;
}

// traverse and print entire list
template <typename T> void traverse(Node<T>* head) {
  std::cout << "List: ";
  Node<T>* current = head;
  while (current) {
    std::cout << current->data << " -> ";
    current = current->next;
  }
  std::cout << "NULL" << std::endl;
}

// free list
template <typename T> void free_list(Node<T>* head) {
  while (head) {
    Node<T>* temp = head;
    head = head->next;
    delete temp;
  }
}

// driver program
int main(void) {
  // test suite
  test::TestSuite suite("Singly-Linked List");

  suite.add_test("Empty list operations", []() {
    Node<int>* list = nullptr;
    test::assert_equal(true, (list == nullptr));

    auto result = node_remove(list, 1);
    test::assert_equal(true, (nullptr == result));

    free_list(list);
  });

  suite.add_test("Basic operations", []() {
    Node<int>* list = nullptr;

    list = append(list, 3);
    test::assert_true(list != nullptr);
    test::assert_equal(3, list->data);

    list = prepend(list, 1);
    list = append(list, 3);
    list = append(list, 7);
    test::assert_equal(1, list->data);
    test::assert_equal(7, list->next->next->next->data);

    list = node_remove(list, 7);
    test::assert_equal(1, list->data);
    test::assert_equal(3, list->next->next->data);

    free_list(list);
  });

  suite.add_test("String operations", []() {
    Node<std::string>* list = nullptr;
    list = append(list, std::string("Plato"));
    list = append(list, std::string("Aristotle"));
    list = append(list, std::string("Alexander the Great"));
    list = prepend(list, std::string("Socrates"));

    free_list(list);
  });

  // benchmarks
  test::Benchmark bench("Singly-Linked List Benchmarks");

  // run all tests and benchmarks
  suite.run();
  bench.run();

  std::cout << "\n" << std::string(50, '=') << std::endl;
  std::cout << "Singly-linked list program is complete." << std::endl;
  std::cout << "" << std::string(50, '=') << std::endl;

  return 0;
}
