#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stddef.h>

/** Binary min-heap (O(log n) push/pop, stack-safe iterative heapify). */
typedef struct PriorityQueue PriorityQueue;

/** Creates a priority queue. @return Queue or NULL. */
PriorityQueue *pqueue_create(size_t capacity);

/** Frees all queue memory. */
void pqueue_destroy(PriorityQueue *pq);

/** Pushes element. @return 0 on success, -1 on error. */
int pqueue_push(PriorityQueue *pq, int value);

/** Removes min element. @return 0 on success, -1 on error. */
int pqueue_pop(PriorityQueue *pq, int *out_value);

/** Views min element. @return 0 on success, -1 on error. */
int pqueue_peek(const PriorityQueue *pq, int *out_value);

/** Returns number of elements. */
size_t pqueue_size(const PriorityQueue *pq);

/** Returns total capacity. */
size_t pqueue_capacity(const PriorityQueue *pq);

/** Checks if empty. @return 1 if empty, 0 otherwise. */
int pqueue_is_empty(const PriorityQueue *pq);

/** Removes all elements. */
void pqueue_clear(PriorityQueue *pq);

/** Prints queue for debugging. */
void pqueue_print(const PriorityQueue *pq);

#endif