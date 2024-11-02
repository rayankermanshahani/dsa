/* slist.c - a singly linked list implementation
 *
 * time complexities:
 * - insert (head): O(1)
 * - insert (tail): O(1)
 * - delete (head): O(1)
 * - delete (tail): O(n)
 * - search: O(n)
 *
 * space complexity: O(n)
 *
 * practical considerations:
 * - simple implementation
 * - no backward traversal
 * - inefficent tail operations
 *
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* node structure */
typedef struct Node {
    int data;          // data in current node
    struct Node *next; // pointer to next node
} Node;

/* singly linked list structure */
typedef struct {
    Node *head;  // head of list
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
    list_print(list); // expect: 1 -> 3 -> 3 -> 7 -> NULL
    printf("\n");

    // remove nodes
    printf("Removing nodes...\n");
    int value;
    if (list_remove_head(list, &value)) {
        printf("Removed head from list: %d\n", value);
    }
    list_print(list); // expect: 3 -> 3 -> 7 -> NULL
    printf("\n");

    printf("Removing tail node...\n");
    if (list_remove_tail(list, &value)) {
        printf("Removed tail from list: %d\n", value);
    }
    list_print(list); // expect: 3 -> 3 -> NULL
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

    printf("SINGLY LINKED LIST PROGRAM COMPLETE\n");

    return 0;
}

/* create list */
List *list_create(void) {
    List *list = malloc(sizeof(List));
    if (!list)
        return NULL;

    list->head = NULL;
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
    new_node->next = list->head;

    // update list
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
    new_node->next = NULL;

    // update list
    if (!list->head) {
        list->head = new_node;
    } else {
        // find tail node
        Node *current = list->head;
        while (current->next) {
            current = current->next;
        }
        current->next = new_node;
    }
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
    free(old_head);
    list->size--;

    return true;
}

/* remove node at tail of list */
bool list_remove_tail(List *list, int *value) {
    // check if list is valid and has a head node
    if (!list || !list->head)
        return false;

    // there is only one node in list (ie. head is tail)
    if (!list->head->next) {
        *value = list->head->data;
        // update list
        free(list->head);
        list->head = NULL;
        list->size--;

        return true;
    }

    // find tail node
    Node *current = list->head;
    while (current->next->next)
        current = current->next;

    // update list
    *value = current->next->data;
    free(current->next);
    current->next = NULL;
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
    Node *current = list->head;
    while (current) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}
