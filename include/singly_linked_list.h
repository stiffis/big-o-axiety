#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <stddef.h>

/** Single-direction linked list with O(1) front operations. */
typedef struct SinglyLinkedList SinglyLinkedList;

/** Creates an empty list. @return List pointer or NULL. */
SinglyLinkedList *slist_create(void);

/** Frees all list memory. */
void slist_destroy(SinglyLinkedList *list);

/** Adds element to front. @return 0 on success, -1 on error. */
int slist_push_front(SinglyLinkedList *list, int value);

/** Adds element to back. @return 0 on success, -1 on error. */
int slist_push_back(SinglyLinkedList *list, int value);

/** Removes and returns front element. @return 0 on success, -1 on error. */
int slist_pop_front(SinglyLinkedList *list, int *out_value);

/** Removes and returns back element. @return 0 on success, -1 on error. */
int slist_pop_back(SinglyLinkedList *list, int *out_value);

/** Inserts element after index. @return 0 on success, -1 on error. */
int slist_insert_after(SinglyLinkedList *list, size_t index, int value);

/** Removes element at index. @return 0 on success, -1 on error. */
int slist_remove_at(SinglyLinkedList *list, size_t index, int *out_value);

/** Gets element at index. @return 0 on success, -1 on error. */
int slist_get(const SinglyLinkedList *list, size_t index, int *out_value);

/** Sets element at index. @return 0 on success, -1 on error. */
int slist_set(SinglyLinkedList *list, size_t index, int value);

/** Returns number of elements. */
size_t slist_size(const SinglyLinkedList *list);

/** Checks if list is empty. @return 1 if empty, 0 otherwise. */
int slist_is_empty(const SinglyLinkedList *list);

/** Finds first occurrence of value. @return Index or -1. */
int slist_find(const SinglyLinkedList *list, int value);

/** Removes all elements (keeps list structure). */
void slist_clear(SinglyLinkedList *list);

/** Reverses list in-place. */
void slist_reverse(SinglyLinkedList *list);

/** Prints list for debugging. */
void slist_print(const SinglyLinkedList *list);

#endif // SINGLY_LINKED_LIST_H