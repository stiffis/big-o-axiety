#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>

/** FIFO data structure (First In, First Out) - linked-list based. */
typedef struct Queue Queue;

/** Creates an empty queue. @return Queue or NULL. */
Queue *queue_create(void);

/** Frees all queue memory. */
void queue_destroy(Queue *queue);

/** Adds element to back. @return 0 on success, -1 on error. */
int queue_enqueue(Queue *queue, int value);

/** Removes element from front. @return 0 on success, -1 on error. */
int queue_dequeue(Queue *queue, int *out_value);

/** Views front element. @return 0 on success, -1 on error. */
int queue_peek(const Queue *queue, int *out_value);

/** Returns number of elements. */
size_t queue_size(const Queue *queue);

/** Checks if queue is empty. @return 1 if empty, 0 otherwise. */
int queue_is_empty(const Queue *queue);

/** Removes all elements. */
void queue_clear(Queue *queue);

/** Prints queue for debugging. */
void queue_print(const Queue *queue);

#endif // QUEUE_H