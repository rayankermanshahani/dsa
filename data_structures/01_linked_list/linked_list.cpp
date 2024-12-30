/**
 * darray.cpp
 *
 * A minimal, cache-friendly dynamic array implementation with manual memory
 * management and zero dependencies.
 */

#include "testing.hpp"
#include <cstdlib>
#include <iostream>

template <typename T> struct Node {
  T data;
  Node<T>* next; // pointer to next node
};

// initialize new node
template <typename T> Node<T> node_create(T data) {
  Node<T> new_node = new Node<T>;
  if (!new_node) {
    std::cerr << "Memory allocation failed\n";
    exit(EXIT_FAILURE);
  }
  new_node->data = data;
  new_node->next = nullptr;

  return new_node;
}

// add node to head of list
template <typename T> Node<T> prepend(Node<T>* head, T data) {
  Node<T> new_node = node_create(data);
  new_node.next = head;

  return new_node;
}

// add node to tail of list
template <typename T> Node<T> append(Node<T>* head, T data) {
  if (!head) { // list is empty (no head)
    return create_node(data);
  }

  Node<T>* current = head;
  while (current->next) { // find tail
    current = current->next;
  }
  current->next = create_node(data);

  return head;
}

// remove first node with given data
template <typename T> Node<T> node_remove(Node<T>* head, T data) {
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
  if (!head) {
    std::cout << "List: ";
    Node<T>* current = head;
    while (current) {
      std::cout << current->data << " -> ";
      current = current->next;
    }
    std::cout << "NULL" << std::endl;
  }
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
  test::TestSuite suite("");

  // benchmarks

  std::cout << "\n" << std::string(50, '=') << std::endl;
  std::cout << "Singly-linked list program is complete." << std::endl;
  std::cout << "" << std::string(50, '=') << std::endl;

  return 0;
}
