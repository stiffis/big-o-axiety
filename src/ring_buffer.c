#include "../include/ring_buffer.h"
#include <stdlib.h>
#include <stdio.h>

struct RingBuffer {
    int *data;
    size_t capacity;
    size_t size;
    size_t read_index;
    size_t write_index;
};

RingBuffer* ring_buffer_create(size_t capacity) {
    if (capacity == 0) {
        return NULL;
    }
    
    RingBuffer *rb = malloc(sizeof(RingBuffer));
    if (!rb) {
        return NULL;
    }
    
    rb->data = malloc(sizeof(int) * capacity);
    if (!rb->data) {
        free(rb);
        return NULL;
    }
    
    rb->capacity = capacity;
    rb->size = 0;
    rb->read_index = 0;
    rb->write_index = 0;
    
    return rb;
}

void ring_buffer_destroy(RingBuffer *rb) {
    if (!rb) {
        return;
    }
    
    free(rb->data);
    free(rb);
}

int ring_buffer_write(RingBuffer *rb, int value) {
    if (!rb) {
        return -1;
    }
    
    if (rb->size == rb->capacity) {
        return -1;
    }
    
    rb->data[rb->write_index] = value;
    rb->write_index = (rb->write_index + 1) % rb->capacity;
    rb->size++;
    
    return 0;
}

int ring_buffer_read(RingBuffer *rb, int *out_value) {
    if (!rb || !out_value) {
        return -1;
    }
    
    if (rb->size == 0) {
        return -1;
    }
    
    *out_value = rb->data[rb->read_index];
    rb->read_index = (rb->read_index + 1) % rb->capacity;
    rb->size--;
    
    return 0;
}

int ring_buffer_peek(const RingBuffer *rb, int *out_value) {
    if (!rb || !out_value) {
        return -1;
    }
    
    if (rb->size == 0) {
        return -1;
    }
    
    *out_value = rb->data[rb->read_index];
    return 0;
}

size_t ring_buffer_size(const RingBuffer *rb) {
    if (!rb) {
        return 0;
    }
    
    return rb->size;
}

size_t ring_buffer_capacity(const RingBuffer *rb) {
    if (!rb) {
        return 0;
    }
    
    return rb->capacity;
}

int ring_buffer_is_empty(const RingBuffer *rb) {
    if (!rb) {
        return 1;
    }
    
    return rb->size == 0;
}

int ring_buffer_is_full(const RingBuffer *rb) {
    if (!rb) {
        return 0;
    }
    
    return rb->size == rb->capacity;
}

void ring_buffer_clear(RingBuffer *rb) {
    if (!rb) {
        return;
    }
    
    rb->size = 0;
    rb->read_index = 0;
    rb->write_index = 0;
}

void ring_buffer_print(const RingBuffer *rb) {
    if (!rb) {
        printf("NULL\n");
        return;
    }
    
    printf("[");
    
    if (rb->size > 0) {
        size_t idx = rb->read_index;
        for (size_t i = 0; i < rb->size; i++) {
            printf("%d", rb->data[idx]);
            if (i < rb->size - 1) {
                printf(", ");
            }
            idx = (idx + 1) % rb->capacity;
        }
    }
    
    printf("] (size: %zu, capacity: %zu)\n", rb->size, rb->capacity);
}
