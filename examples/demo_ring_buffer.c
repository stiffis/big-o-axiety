#include <stdio.h>
#include "../include/ring_buffer.h"

int main(void) {
    printf("=== Ring Buffer (Circular Queue) Demo ===\n\n");
    
    printf("1. Creating ring buffer with capacity 5:\n");
    RingBuffer *rb = ring_buffer_create(5);
    printf("Empty buffer: ");
    ring_buffer_print(rb);
    printf("\n");
    
    printf("2. Writing elements:\n");
    ring_buffer_write(rb, 10);
    printf("After write(10): ");
    ring_buffer_print(rb);
    
    ring_buffer_write(rb, 20);
    printf("After write(20): ");
    ring_buffer_print(rb);
    
    ring_buffer_write(rb, 30);
    printf("After write(30): ");
    ring_buffer_print(rb);
    printf("\n");
    
    printf("3. Reading elements (FIFO):\n");
    int val;
    ring_buffer_read(rb, &val);
    printf("Read: %d, Buffer now: ", val);
    ring_buffer_print(rb);
    
    ring_buffer_read(rb, &val);
    printf("Read: %d, Buffer now: ", val);
    ring_buffer_print(rb);
    printf("\n");
    
    printf("4. Demonstrating wraparound:\n");
    printf("Current state: ");
    ring_buffer_print(rb);
    
    printf("Writing 40, 50, 60, 70\n");
    ring_buffer_write(rb, 40);
    ring_buffer_write(rb, 50);
    ring_buffer_write(rb, 60);
    ring_buffer_write(rb, 70);
    
    printf("After writes: ");
    ring_buffer_print(rb);
    printf("Buffer is full: %s\n\n", ring_buffer_is_full(rb) ? "yes" : "no");
    
    printf("5. Peek operation:\n");
    ring_buffer_peek(rb, &val);
    printf("Peek: %d (buffer unchanged)\n", val);
    printf("Buffer: ");
    ring_buffer_print(rb);
    printf("\n");
    
    printf("6. Full buffer behavior:\n");
    printf("Attempting to write to full buffer...\n");
    if (ring_buffer_write(rb, 99) == -1) {
        printf("Write failed (buffer is full)\n");
    }
    printf("Buffer: ");
    ring_buffer_print(rb);
    printf("\n");
    
    printf("7. Reading all elements:\n");
    printf("Reading in FIFO order: ");
    while (!ring_buffer_is_empty(rb)) {
        ring_buffer_read(rb, &val);
        printf("%d ", val);
    }
    printf("\n");
    printf("Buffer after reading all: ");
    ring_buffer_print(rb);
    printf("\n");
    
    printf("8. Multiple wraparounds:\n");
    printf("Writing and reading 10 times...\n");
    for (int i = 1; i <= 10; i++) {
        ring_buffer_write(rb, i * 100);
        ring_buffer_read(rb, &val);
        printf("Write %d, Read %d\n", i * 100, val);
    }
    printf("Buffer state: ");
    ring_buffer_print(rb);
    printf("\n");
    
    printf("9. Clear operation:\n");
    ring_buffer_write(rb, 1);
    ring_buffer_write(rb, 2);
    ring_buffer_write(rb, 3);
    printf("Before clear: ");
    ring_buffer_print(rb);
    
    ring_buffer_clear(rb);
    printf("After clear:  ");
    ring_buffer_print(rb);
    printf("\n");
    
    printf("10. Circular buffer use case (data streaming):\n");
    printf("Simulating a 3-element buffer with continuous data flow...\n");
    ring_buffer_destroy(rb);
    rb = ring_buffer_create(3);
    
    printf("Initial: ");
    ring_buffer_print(rb);
    
    printf("\nStep 1: Write 1, 2, 3 (fill buffer)\n");
    ring_buffer_write(rb, 1);
    ring_buffer_write(rb, 2);
    ring_buffer_write(rb, 3);
    ring_buffer_print(rb);
    
    printf("Step 2: Read one (1), Write one (4)\n");
    ring_buffer_read(rb, &val);
    printf("  Read: %d\n", val);
    ring_buffer_write(rb, 4);
    ring_buffer_print(rb);
    
    printf("Step 3: Read one (2), Write one (5)\n");
    ring_buffer_read(rb, &val);
    printf("  Read: %d\n", val);
    ring_buffer_write(rb, 5);
    ring_buffer_print(rb);
    
    printf("Step 4: Read one (3), Write one (6)\n");
    ring_buffer_read(rb, &val);
    printf("  Read: %d\n", val);
    ring_buffer_write(rb, 6);
    ring_buffer_print(rb);
    
    printf("\nNotice: Indices wrapped around but FIFO order maintained!\n");
    printf("Reading remaining: ");
    while (!ring_buffer_is_empty(rb)) {
        ring_buffer_read(rb, &val);
        printf("%d ", val);
    }
    printf("\n");
    
    ring_buffer_destroy(rb);
    
    printf("\n=== Demo Complete ===\n");
    return 0;
}
