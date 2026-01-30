#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stddef.h>

/** Bidirectional linked list with prev/next pointers. */
typedef struct DoublyLinkedList DoublyLinkedList;

/** Creates an empty list. @return List pointer or NULL. */
DoublyLinkedList *dlist_create(void);

/** Frees all list memory. */
void dlist_destroy(DoublyLinkedList *list);

/** Adds element to front. @return 0 on success, -1 on error. */
int dlist_push_front(DoublyLinkedList *list, int value);

/** Adds element to back. @return 0 on success, -1 on error. */
int dlist_push_back(DoublyLinkedList *list, int value);

/** Removes and returns front element. @return 0 on success, -1 on error. */
int dlist_pop_front(DoublyLinkedList *list, int *out_value);

/** Removes and returns back element. @return 0 on success, -1 on error. */
int dlist_pop_back(DoublyLinkedList *list, int *out_value);

/** Inserts element at index. @return 0 on success, -1 on error. */
int dlist_insert_at(DoublyLinkedList *list, size_t index, int value);

/** Removes element at index. @return 0 on success, -1 on error. */
int dlist_remove_at(DoublyLinkedList *list, size_t index, int *out_value);

/** Gets element at index. @return 0 on success, -1 on error. */
int dlist_get(const DoublyLinkedList *list, size_t index, int *out_value);

/** Sets element at index. @return 0 on success, -1 on error. */
int dlist_set(DoublyLinkedList *list, size_t index, int value);

/** Returns number of elements. */
size_t dlist_size(const DoublyLinkedList *list);

/** Checks if list is empty. @return 1 if empty, 0 otherwise. */
int dlist_is_empty(const DoublyLinkedList *list);

/** Finds first occurrence of value. @return Index or -1. */
int dlist_find(const DoublyLinkedList *list, int value);

/** Removes all elements (keeps list structure). */
void dlist_clear(DoublyLinkedList *list);

/** Reverses list in-place. */
void dlist_reverse(DoublyLinkedList *list);

/** Prints list for debugging. */
void dlist_print(const DoublyLinkedList *list);

/** Prints list in reverse order. */
void dlist_print_reverse(const DoublyLinkedList *list);

#endif // DOUBLY_LINKED_LIST_H