/* dlist.c - a doubly linked list implementation
 *
 * time complexities:
 * - insert (head/tail): O(1)
 * - delete (head/tail): O(1)
 * - search: O(n)
 *
 * space complexity: O(n)
 *
 * practical considerations:
 * - more memory overhead per node relative to singly linked lists
 * - bidirectional traversal
 * - simpler to remove a node given its address
 *
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// node structure
typedef struct Node {
    int data;          // data in current node
    struct Node *prev; // pointer to previous node
    struct Node *next; // pointer to next node
} Node;

// singly linked list structure
typedef struct {
    Node *head;  // head of list
    Node *tail;  // tail of list
    size_t size; // size of list
} List;

/* function declarations */
List *list_create(void);
void list_destroy(List *list);
bool list_insert_head(List *list, int value);
bool list_insert_tail(List *list, int value);
bool list_remove_head(List *list, int *value);
bool list_remove_tail(List *list, int *value);
bool list_is_empty(const List *list);
size_t list_size(const List *list);
void list_print(const List *list);
void list_print_reverse(const List *list);

/* driver function */
int main(void) {
    // create a new list
    List *list = list_create();
    if (!list) {
        fprintf(stderr, "Failed to create list\n");
        return 1;
    }

    // insert nodes
    printf("Inserting nodes...\n");
    list_insert_head(list, 3);
    list_insert_head(list, 1);
    list_insert_tail(list, 3);
    list_insert_tail(list, 7);
    list_print(list);         // expect: NULL <-> 1 <-> 3 <-> 3 <-> 7 <-> NULL
    list_print_reverse(list); // expect: NULL <-> 7 <-> 3 <-> 3 <-> 1 <-> NULL
    printf("\n");

    // remove nodes
    printf("Removing nodes...\n");
    int value;
    if (list_remove_head(list, &value)) {
        printf("Removed head from list: %d\n", value);
    }
    list_print(list);         // expect: NULL <-> 3 <-> 3 <-> 7 <-> NULL
    list_print_reverse(list); // expect: NULL <-> 7 <-> 3 <-> 3 <-> NULL
    printf("\n");

    printf("Removing tail node...\n");
    if (list_remove_tail(list, &value)) {
        printf("Removed tail from list: %d\n", value);
    }
    list_print(list);         // expect: NULL <-> 3 <-> 3 <-> NULL
    list_print_reverse(list); // expect: NULL <-> 3 <-> 3 <-> NULL
    printf("\n");

    printf("Checking if list is empty...\n");
    if (!list_is_empty(list)) {
        printf("List is not empty.\n");
    } else {
        printf("List is empty.\n");
    }
    printf("\n");

    // clean up
    list_destroy(list);
    printf("List destroyed.\n");
    printf("\n");

    printf("DOUBLY LINKED LIST PROGRAM COMPLETE\n");
    return 0;
}

/* create list */
List *list_create(void) {
    List *list = malloc(sizeof(List));
    if (!list)
        return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

/* destroy list */
void list_destroy(List *list) {
    if (!list)
        return;

    // clean up each node
    Node *current = list->head;
    while (current) {
        Node *next = current->next;
        free(current);
        current = next;
    }

    // clean up list
    free(list);
}

/* insert node at head of list */
bool list_insert_head(List *list, int value) {
    // check if list is valid
    if (!list)
        return false;

    // create new node
    Node *new_node = malloc(sizeof(Node));
    if (!new_node)
        return false;
    new_node->data = value;
    new_node->prev = NULL;
    new_node->next = list->head;

    // update list
    if (list->head) {
        list->head->prev = new_node;
    } else {
        list->tail = new_node;
    }

    list->head = new_node;
    list->size++;

    return true;
}

/* insert node at tail of list */
bool list_insert_tail(List *list, int value) {
    // check if list is valid
    if (!list)
        return false;

    // create new node
    Node *new_node = malloc(sizeof(Node));
    if (!new_node)
        return false;
    new_node->data = value;
    new_node->prev = list->tail;
    new_node->next = NULL;

    // update list
    if (list->tail) {
        list->tail->next = new_node;
    } else { // list only had one node
        list->head = new_node;
    }

    list->tail = new_node;
    list->size++;

    return true;
}

/* remove node at head of list */
bool list_remove_head(List *list, int *value) {
    // check if list is valid and has a head node
    if (!list || !list->head)
        return false;

    // get old head's data
    Node *old_head = list->head;
    *value = old_head->data;

    // update list
    list->head = old_head->next;
    if (list->head) {
        list->head->prev = NULL;
    } else { // list only had one node
        list->tail = NULL;
    }

    free(old_head);
    list->size--;

    return true;
}

/* remove node at tail of list */
bool list_remove_tail(List *list, int *value) {
    // check if list is valid and has a tail node
    if (!list || !list->tail)
        return false;

    // get old tail's data
    Node *old_tail = list->tail;
    *value = old_tail->data;

    // update list
    list->tail = old_tail->prev;
    if (list->tail) {
        list->tail->next = NULL;
    } else { // list only had one node
        list->head = NULL;
    }

    free(old_tail);
    list->size--;

    return true;
}

/* check if list is empty */
bool list_is_empty(const List *list) { return !list || list->size == 0; }

/* get size of list */
size_t list_size(const List *list) { return list ? list->size : 0; }

/* print entire list */
void list_print(const List *list) {
    // check if list is valid
    if (!list)
        return;

    // iterate and print every node in list
    printf("List [size=%zu]:\n", list->size);
    printf("NULL <-> ");
    Node *current = list->head;
    while (current) {
        printf("%d <-> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

/* print entire list in reverse */
void list_print_reverse(const List *list) {
    // check if list is valid
    if (!list)
        return;

    // iterate backwards and print every node in list
    printf("List Reverse [size=%zu]:\n", list->size);
    printf("NULL <-> ");
    Node *current = list->tail;
    while (current) {
        printf("%d <-> ", current->data);
        current = current->prev;
    }
    printf("NULL\n");
}
