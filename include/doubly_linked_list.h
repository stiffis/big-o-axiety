#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stddef.h>

typedef struct DoublyLinkedList DoublyLinkedList;

DoublyLinkedList *dlist_create(void);

void dlist_destroy(DoublyLinkedList *list);

int dlist_push_front(DoublyLinkedList *list, int value);

int dlist_push_back(DoublyLinkedList *list, int value);

int dlist_pop_front(DoublyLinkedList *list, int *out_value);

int dlist_pop_back(DoublyLinkedList *list, int *out_value);

int dlist_insert_at(DoublyLinkedList *list, size_t index, int value);

int dlist_remove_at(DoublyLinkedList *list, size_t index, int *out_value);

int dlist_get(const DoublyLinkedList *list, size_t index, int *out_value);

int dlist_set(DoublyLinkedList *list, size_t index, int value);

size_t dlist_size(const DoublyLinkedList *list);

int dlist_is_empty(const DoublyLinkedList *list);

int dlist_find(const DoublyLinkedList *list, int value);

void dlist_clear(DoublyLinkedList *list);

void dlist_reverse(DoublyLinkedList *list);

void dlist_print(const DoublyLinkedList *list);

void dlist_print_reverse(const DoublyLinkedList *list);

#endif // DOUBLY_LINKED_LIST_H
