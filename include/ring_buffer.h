#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stddef.h>

/** Fixed-size circular buffer with wraparound. */
typedef struct RingBuffer RingBuffer;

/** Creates a ring buffer with fixed capacity. @return RingBuffer or NULL. */
RingBuffer *ring_buffer_create(size_t capacity);

/** Frees all ring buffer memory. */
void ring_buffer_destroy(RingBuffer *rb);

/** Writes element (overwrites oldest if full). @return 0 on success, -1 on error. */
int ring_buffer_write(RingBuffer *rb, int value);

/** Reads element from buffer. @return 0 on success, -1 on error. */
int ring_buffer_read(RingBuffer *rb, int *out_value);

/** Views oldest element without removing. @return 0 on success, -1 on error. */
int ring_buffer_peek(const RingBuffer *rb, int *out_value);

/** Returns number of elements. */
size_t ring_buffer_size(const RingBuffer *rb);

/** Returns total capacity. */
size_t ring_buffer_capacity(const RingBuffer *rb);

/** Checks if buffer is empty. @return 1 if empty, 0 otherwise. */
int ring_buffer_is_empty(const RingBuffer *rb);

/** Checks if buffer is full. @return 1 if full, 0 otherwise. */
int ring_buffer_is_full(const RingBuffer *rb);

/** Clears buffer (resets read/write pointers). */
void ring_buffer_clear(RingBuffer *rb);

/** Prints buffer for debugging. */
void ring_buffer_print(const RingBuffer *rb);

#endif