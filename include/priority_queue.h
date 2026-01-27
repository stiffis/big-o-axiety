#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stddef.h>

typedef struct PriorityQueue PriorityQueue;

PriorityQueue *pqueue_create(size_t capacity);

void pqueue_destroy(PriorityQueue *pq);

int pqueue_push(PriorityQueue *pq, int value);

int pqueue_pop(PriorityQueue *pq, int *out_value);

int pqueue_peek(const PriorityQueue *pq, int *out_value);

size_t pqueue_size(const PriorityQueue *pq);

size_t pqueue_capacity(const PriorityQueue *pq);

int pqueue_is_empty(const PriorityQueue *pq);

void pqueue_clear(PriorityQueue *pq);

void pqueue_print(const PriorityQueue *pq);

#endif
