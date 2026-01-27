#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>

typedef struct Queue Queue;

Queue *queue_create(void);

void queue_destroy(Queue *queue);

int queue_enqueue(Queue *queue, int value);

int queue_dequeue(Queue *queue, int *out_value);

int queue_peek(const Queue *queue, int *out_value);

size_t queue_size(const Queue *queue);

int queue_is_empty(const Queue *queue);

void queue_clear(Queue *queue);

void queue_print(const Queue *queue);

#endif // QUEUE_H
