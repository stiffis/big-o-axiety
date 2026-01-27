#include <stdio.h>
#include <assert.h>
#include "../include/ring_buffer.h"

#define TEST(name) printf("Testing %s... ", name)
#define PASS() printf("✓ PASS\n")

int test_create_destroy(void) {
    TEST("create and destroy");
    
    RingBuffer *rb = ring_buffer_create(5);
    assert(rb != NULL);
    assert(ring_buffer_size(rb) == 0);
    assert(ring_buffer_capacity(rb) == 5);
    assert(ring_buffer_is_empty(rb) == 1);
    assert(ring_buffer_is_full(rb) == 0);
    
    ring_buffer_destroy(rb);
    PASS();
    return 0;
}

int test_write_and_read(void) {
    TEST("write and read");
    
    RingBuffer *rb = ring_buffer_create(5);
    
    ring_buffer_write(rb, 10);
    ring_buffer_write(rb, 20);
    ring_buffer_write(rb, 30);
    
    assert(ring_buffer_size(rb) == 3);
    
    int val;
    ring_buffer_read(rb, &val);
    assert(val == 10);
    
    ring_buffer_read(rb, &val);
    assert(val == 20);
    
    ring_buffer_read(rb, &val);
    assert(val == 30);
    
    assert(ring_buffer_is_empty(rb) == 1);
    
    ring_buffer_destroy(rb);
    PASS();
    return 0;
}

int test_peek(void) {
    TEST("peek");
    
    RingBuffer *rb = ring_buffer_create(5);
    
    ring_buffer_write(rb, 10);
    ring_buffer_write(rb, 20);
    
    int val;
    ring_buffer_peek(rb, &val);
    assert(val == 10);
    assert(ring_buffer_size(rb) == 2);
    
    ring_buffer_peek(rb, &val);
    assert(val == 10);
    assert(ring_buffer_size(rb) == 2);
    
    ring_buffer_destroy(rb);
    PASS();
    return 0;
}

int test_full_buffer(void) {
    TEST("full buffer");
    
    RingBuffer *rb = ring_buffer_create(3);
    
    ring_buffer_write(rb, 10);
    ring_buffer_write(rb, 20);
    ring_buffer_write(rb, 30);
    
    assert(ring_buffer_is_full(rb) == 1);
    assert(ring_buffer_write(rb, 40) == -1);
    
    int val;
    ring_buffer_read(rb, &val);
    assert(val == 10);
    assert(ring_buffer_is_full(rb) == 0);
    
    ring_buffer_destroy(rb);
    PASS();
    return 0;
}

int test_wraparound(void) {
    TEST("wraparound");
    
    RingBuffer *rb = ring_buffer_create(3);
    
    ring_buffer_write(rb, 10);
    ring_buffer_write(rb, 20);
    ring_buffer_write(rb, 30);
    
    int val;
    ring_buffer_read(rb, &val);
    assert(val == 10);
    
    ring_buffer_read(rb, &val);
    assert(val == 20);
    
    ring_buffer_write(rb, 40);
    ring_buffer_write(rb, 50);
    
    assert(ring_buffer_size(rb) == 3);
    assert(ring_buffer_is_full(rb) == 1);
    
    ring_buffer_read(rb, &val);
    assert(val == 30);
    
    ring_buffer_read(rb, &val);
    assert(val == 40);
    
    ring_buffer_read(rb, &val);
    assert(val == 50);
    
    assert(ring_buffer_is_empty(rb) == 1);
    
    ring_buffer_destroy(rb);
    PASS();
    return 0;
}

int test_fifo_order(void) {
    TEST("FIFO order");
    
    RingBuffer *rb = ring_buffer_create(5);
    
    for (int i = 1; i <= 5; i++) {
        ring_buffer_write(rb, i * 10);
    }
    
    assert(ring_buffer_is_full(rb) == 1);
    
    int val;
    ring_buffer_read(rb, &val);
    assert(val == 10);
    
    ring_buffer_read(rb, &val);
    assert(val == 20);
    
    ring_buffer_read(rb, &val);
    assert(val == 30);
    
    ring_buffer_destroy(rb);
    PASS();
    return 0;
}

int test_clear(void) {
    TEST("clear");
    
    RingBuffer *rb = ring_buffer_create(5);
    
    ring_buffer_write(rb, 10);
    ring_buffer_write(rb, 20);
    ring_buffer_write(rb, 30);
    
    assert(ring_buffer_size(rb) == 3);
    
    ring_buffer_clear(rb);
    
    assert(ring_buffer_size(rb) == 0);
    assert(ring_buffer_is_empty(rb) == 1);
    
    ring_buffer_write(rb, 40);
    assert(ring_buffer_size(rb) == 1);
    
    ring_buffer_destroy(rb);
    PASS();
    return 0;
}

int test_multiple_wraparounds(void) {
    TEST("multiple wraparounds");
    
    RingBuffer *rb = ring_buffer_create(3);
    
    for (int i = 0; i < 10; i++) {
        ring_buffer_write(rb, i);
        
        int val;
        ring_buffer_read(rb, &val);
        assert(val == i);
    }
    
    assert(ring_buffer_is_empty(rb) == 1);
    
    ring_buffer_destroy(rb);
    PASS();
    return 0;
}

int test_error_handling(void) {
    TEST("error handling");
    
    RingBuffer *rb = ring_buffer_create(3);
    
    int val;
    assert(ring_buffer_read(rb, &val) == -1);
    assert(ring_buffer_peek(rb, &val) == -1);
    
    ring_buffer_write(rb, 10);
    ring_buffer_write(rb, 20);
    ring_buffer_write(rb, 30);
    
    assert(ring_buffer_write(rb, 40) == -1);
    
    ring_buffer_destroy(rb);
    ring_buffer_destroy(NULL);
    
    PASS();
    return 0;
}

int test_capacity_edge_cases(void) {
    TEST("capacity edge cases");
    
    RingBuffer *rb1 = ring_buffer_create(1);
    assert(rb1 != NULL);
    assert(ring_buffer_capacity(rb1) == 1);
    
    ring_buffer_write(rb1, 42);
    assert(ring_buffer_is_full(rb1) == 1);
    
    int val;
    ring_buffer_read(rb1, &val);
    assert(val == 42);
    assert(ring_buffer_is_empty(rb1) == 1);
    
    ring_buffer_destroy(rb1);
    
    RingBuffer *rb2 = ring_buffer_create(0);
    assert(rb2 == NULL);
    
    PASS();
    return 0;
}

int main(void) {
    printf("=== Running Ring Buffer Tests ===\n\n");
    
    int failed = 0;
    
    failed += test_create_destroy();
    failed += test_write_and_read();
    failed += test_peek();
    failed += test_full_buffer();
    failed += test_wraparound();
    failed += test_fifo_order();
    failed += test_clear();
    failed += test_multiple_wraparounds();
    failed += test_error_handling();
    failed += test_capacity_edge_cases();
    
    printf("\n");
    if (failed == 0) {
        printf("✓ All tests passed!\n");
    } else {
        printf("✗ %d test(s) failed\n", failed);
    }
    
    return failed;
}
