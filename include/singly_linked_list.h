#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <stddef.h>

typedef struct SinglyLinkedList SinglyLinkedList;

SinglyLinkedList *slist_create(void);

void slist_destroy(SinglyLinkedList *list);

int slist_push_front(SinglyLinkedList *list, int value);

int slist_push_back(SinglyLinkedList *list, int value);

int slist_pop_front(SinglyLinkedList *list, int *out_value);

int slist_pop_back(SinglyLinkedList *list, int *out_value);

int slist_insert_after(SinglyLinkedList *list, size_t index, int value);

int slist_remove_at(SinglyLinkedList *list, size_t index, int *out_value);

int slist_get(const SinglyLinkedList *list, size_t index, int *out_value);

int slist_set(SinglyLinkedList *list, size_t index, int value);

size_t slist_size(const SinglyLinkedList *list);

int slist_is_empty(const SinglyLinkedList *list);

int slist_find(const SinglyLinkedList *list, int value);

void slist_clear(SinglyLinkedList *list);

void slist_reverse(SinglyLinkedList *list);

void slist_print(const SinglyLinkedList *list);

#endif // SINGLY_LINKED_LIST_H
