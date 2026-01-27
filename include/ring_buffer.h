#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stddef.h>

typedef struct RingBuffer RingBuffer;

RingBuffer *ring_buffer_create(size_t capacity);

void ring_buffer_destroy(RingBuffer *rb);

int ring_buffer_write(RingBuffer *rb, int value);

int ring_buffer_read(RingBuffer *rb, int *out_value);

int ring_buffer_peek(const RingBuffer *rb, int *out_value);

size_t ring_buffer_size(const RingBuffer *rb);

size_t ring_buffer_capacity(const RingBuffer *rb);

int ring_buffer_is_empty(const RingBuffer *rb);

int ring_buffer_is_full(const RingBuffer *rb);

void ring_buffer_clear(RingBuffer *rb);

void ring_buffer_print(const RingBuffer *rb);

#endif
