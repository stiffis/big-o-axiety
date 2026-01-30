#ifndef DEQUE_H
#define DEQUE_H

#include <stddef.h>

/** Double-ended queue (operations at both ends in O(1)). */
typedef struct Deque Deque;

/** Creates an empty deque. @return Deque or NULL. */
Deque *deque_create(void);

/** Frees all deque memory. */
void deque_destroy(Deque *deque);

/** Adds element to front. @return 0 on success, -1 on error. */
int deque_push_front(Deque *deque, int value);

/** Adds element to back. @return 0 on success, -1 on error. */
int deque_push_back(Deque *deque, int value);

/** Removes element from front. @return 0 on success, -1 on error. */
int deque_pop_front(Deque *deque, int *out_value);

/** Removes element from back. @return 0 on success, -1 on error. */
int deque_pop_back(Deque *deque, int *out_value);

/** Views front element. @return 0 on success, -1 on error. */
int deque_peek_front(const Deque *deque, int *out_value);

/** Views back element. @return 0 on success, -1 on error. */
int deque_peek_back(const Deque *deque, int *out_value);

/** Returns number of elements. */
size_t deque_size(const Deque *deque);

/** Checks if deque is empty. @return 1 if empty, 0 otherwise. */
int deque_is_empty(const Deque *deque);

/** Removes all elements. */
void deque_clear(Deque *deque);

/** Prints deque for debugging. */
void deque_print(const Deque *deque);

#endif