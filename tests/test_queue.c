#include <stdio.h>
#include <assert.h>
#include "../include/queue.h"

#define TEST(name) printf("Testing %s... ", name)
#define PASS() printf("✓ PASS\n")

int test_create_destroy(void) {
    TEST("create and destroy");
    
    Queue *queue = queue_create();
    assert(queue != NULL);
    assert(queue_size(queue) == 0);
    assert(queue_is_empty(queue) == 1);
    
    queue_destroy(queue);
    PASS();
    return 0;
}

int test_enqueue_and_peek(void) {
    TEST("enqueue and peek");
    
    Queue *queue = queue_create();
    
    queue_enqueue(queue, 10);
    queue_enqueue(queue, 20);
    queue_enqueue(queue, 30);
    
    assert(queue_size(queue) == 3);
    
    int val;
    queue_peek(queue, &val);
    assert(val == 10);
    assert(queue_size(queue) == 3);
    
    queue_destroy(queue);
    PASS();
    return 0;
}

int test_dequeue(void) {
    TEST("dequeue");
    
    Queue *queue = queue_create();
    
    queue_enqueue(queue, 10);
    queue_enqueue(queue, 20);
    queue_enqueue(queue, 30);
    
    int val;
    queue_dequeue(queue, &val);
    assert(val == 10);
    assert(queue_size(queue) == 2);
    
    queue_dequeue(queue, &val);
    assert(val == 20);
    
    queue_dequeue(queue, &val);
    assert(val == 30);
    assert(queue_is_empty(queue) == 1);
    
    queue_destroy(queue);
    PASS();
    return 0;
}

int test_fifo_order(void) {
    TEST("FIFO order");
    
    Queue *queue = queue_create();
    
    for (int i = 1; i <= 5; i++) {
        queue_enqueue(queue, i * 10);
    }
    
    assert(queue_size(queue) == 5);
    
    int val;
    queue_dequeue(queue, &val);
    assert(val == 10);
    
    queue_dequeue(queue, &val);
    assert(val == 20);
    
    queue_dequeue(queue, &val);
    assert(val == 30);
    
    queue_destroy(queue);
    PASS();
    return 0;
}

int test_clear(void) {
    TEST("clear");
    
    Queue *queue = queue_create();
    
    queue_enqueue(queue, 10);
    queue_enqueue(queue, 20);
    queue_enqueue(queue, 30);
    
    assert(queue_size(queue) == 3);
    
    queue_clear(queue);
    
    assert(queue_size(queue) == 0);
    assert(queue_is_empty(queue) == 1);
    
    queue_destroy(queue);
    PASS();
    return 0;
}

int test_peek_consistency(void) {
    TEST("peek consistency");
    
    Queue *queue = queue_create();
    
    int val;
    
    queue_enqueue(queue, 10);
    queue_peek(queue, &val);
    assert(val == 10);
    
    queue_enqueue(queue, 20);
    queue_peek(queue, &val);
    assert(val == 10);
    
    queue_enqueue(queue, 30);
    queue_peek(queue, &val);
    assert(val == 10);
    
    queue_destroy(queue);
    PASS();
    return 0;
}

int test_enqueue_after_dequeue(void) {
    TEST("enqueue after dequeue");
    
    Queue *queue = queue_create();
    
    queue_enqueue(queue, 10);
    queue_enqueue(queue, 20);
    
    int val;
    queue_dequeue(queue, &val);
    assert(val == 10);
    
    queue_enqueue(queue, 30);
    
    queue_dequeue(queue, &val);
    assert(val == 20);
    
    queue_dequeue(queue, &val);
    assert(val == 30);
    
    assert(queue_is_empty(queue) == 1);
    
    queue_destroy(queue);
    PASS();
    return 0;
}

int test_error_handling(void) {
    TEST("error handling");
    
    Queue *queue = queue_create();
    
    int val;
    assert(queue_dequeue(queue, &val) == -1);
    assert(queue_peek(queue, &val) == -1);
    
    queue_destroy(queue);
    queue_destroy(NULL);
    
    PASS();
    return 0;
}

int main(void) {
    printf("=== Running Queue Tests ===\n\n");
    
    int failed = 0;
    
    failed += test_create_destroy();
    failed += test_enqueue_and_peek();
    failed += test_dequeue();
    failed += test_fifo_order();
    failed += test_clear();
    failed += test_peek_consistency();
    failed += test_enqueue_after_dequeue();
    failed += test_error_handling();
    
    printf("\n");
    if (failed == 0) {
        printf("✓ All tests passed!\n");
    } else {
        printf("✗ %d test(s) failed\n", failed);
    }
    
    return failed;
}
