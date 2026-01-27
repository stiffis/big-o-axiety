#include <stdio.h>
#include <assert.h>
#include "../include/priority_queue.h"

#define TEST(name) printf("Testing %s... ", name)
#define PASS() printf("✓ PASS\n")

int test_create_destroy(void) {
    TEST("create and destroy");
    
    PriorityQueue *pq = pqueue_create(10);
    assert(pq != NULL);
    assert(pqueue_size(pq) == 0);
    assert(pqueue_is_empty(pq) == 1);
    
    pqueue_destroy(pq);
    PASS();
    return 0;
}

int test_push_and_peek(void) {
    TEST("push and peek");
    
    PriorityQueue *pq = pqueue_create(10);
    
    pqueue_push(pq, 30);
    pqueue_push(pq, 10);
    pqueue_push(pq, 20);
    
    assert(pqueue_size(pq) == 3);
    
    int val;
    pqueue_peek(pq, &val);
    assert(val == 10);
    assert(pqueue_size(pq) == 3);
    
    pqueue_destroy(pq);
    PASS();
    return 0;
}

int test_pop_min_order(void) {
    TEST("pop in min order");
    
    PriorityQueue *pq = pqueue_create(10);
    
    pqueue_push(pq, 50);
    pqueue_push(pq, 30);
    pqueue_push(pq, 70);
    pqueue_push(pq, 10);
    pqueue_push(pq, 40);
    
    int val;
    pqueue_pop(pq, &val);
    assert(val == 10);
    
    pqueue_pop(pq, &val);
    assert(val == 30);
    
    pqueue_pop(pq, &val);
    assert(val == 40);
    
    pqueue_pop(pq, &val);
    assert(val == 50);
    
    pqueue_pop(pq, &val);
    assert(val == 70);
    
    assert(pqueue_is_empty(pq) == 1);
    
    pqueue_destroy(pq);
    PASS();
    return 0;
}

int test_heap_property(void) {
    TEST("heap property maintained");
    
    PriorityQueue *pq = pqueue_create(10);
    
    pqueue_push(pq, 5);
    pqueue_push(pq, 3);
    pqueue_push(pq, 7);
    pqueue_push(pq, 1);
    
    int val;
    pqueue_peek(pq, &val);
    assert(val == 1);
    
    pqueue_pop(pq, &val);
    assert(val == 1);
    
    pqueue_peek(pq, &val);
    assert(val == 3);
    
    pqueue_destroy(pq);
    PASS();
    return 0;
}

int test_auto_resize(void) {
    TEST("auto resize");
    
    PriorityQueue *pq = pqueue_create(2);
    assert(pqueue_capacity(pq) == 2);
    
    pqueue_push(pq, 10);
    pqueue_push(pq, 20);
    assert(pqueue_size(pq) == 2);
    
    pqueue_push(pq, 5);
    assert(pqueue_size(pq) == 3);
    assert(pqueue_capacity(pq) >= 3);
    
    int val;
    pqueue_pop(pq, &val);
    assert(val == 5);
    
    pqueue_destroy(pq);
    PASS();
    return 0;
}

int test_clear(void) {
    TEST("clear");
    
    PriorityQueue *pq = pqueue_create(10);
    
    pqueue_push(pq, 30);
    pqueue_push(pq, 10);
    pqueue_push(pq, 20);
    
    assert(pqueue_size(pq) == 3);
    
    pqueue_clear(pq);
    
    assert(pqueue_size(pq) == 0);
    assert(pqueue_is_empty(pq) == 1);
    
    pqueue_push(pq, 5);
    assert(pqueue_size(pq) == 1);
    
    int val;
    pqueue_peek(pq, &val);
    assert(val == 5);
    
    pqueue_destroy(pq);
    PASS();
    return 0;
}

int test_duplicate_values(void) {
    TEST("duplicate values");
    
    PriorityQueue *pq = pqueue_create(10);
    
    pqueue_push(pq, 10);
    pqueue_push(pq, 5);
    pqueue_push(pq, 10);
    pqueue_push(pq, 5);
    
    int val;
    pqueue_pop(pq, &val);
    assert(val == 5);
    
    pqueue_pop(pq, &val);
    assert(val == 5);
    
    pqueue_pop(pq, &val);
    assert(val == 10);
    
    pqueue_pop(pq, &val);
    assert(val == 10);
    
    pqueue_destroy(pq);
    PASS();
    return 0;
}

int test_single_element(void) {
    TEST("single element");
    
    PriorityQueue *pq = pqueue_create(10);
    
    pqueue_push(pq, 42);
    
    int val;
    pqueue_peek(pq, &val);
    assert(val == 42);
    
    pqueue_pop(pq, &val);
    assert(val == 42);
    assert(pqueue_is_empty(pq) == 1);
    
    pqueue_destroy(pq);
    PASS();
    return 0;
}

int test_error_handling(void) {
    TEST("error handling");
    
    PriorityQueue *pq = pqueue_create(10);
    
    int val;
    assert(pqueue_pop(pq, &val) == -1);
    assert(pqueue_peek(pq, &val) == -1);
    
    pqueue_destroy(pq);
    pqueue_destroy(NULL);
    
    PASS();
    return 0;
}

int test_large_dataset(void) {
    TEST("large dataset");
    
    PriorityQueue *pq = pqueue_create(10);
    
    for (int i = 100; i > 0; i--) {
        pqueue_push(pq, i);
    }
    
    assert(pqueue_size(pq) == 100);
    
    int val;
    for (int i = 1; i <= 100; i++) {
        pqueue_pop(pq, &val);
        assert(val == i);
    }
    
    assert(pqueue_is_empty(pq) == 1);
    
    pqueue_destroy(pq);
    PASS();
    return 0;
}

int test_negative_values(void) {
    TEST("negative values");
    
    PriorityQueue *pq = pqueue_create(10);
    
    pqueue_push(pq, -10);
    pqueue_push(pq, 5);
    pqueue_push(pq, -30);
    pqueue_push(pq, 0);
    pqueue_push(pq, -5);
    
    int val;
    pqueue_pop(pq, &val);
    assert(val == -30);
    
    pqueue_pop(pq, &val);
    assert(val == -10);
    
    pqueue_pop(pq, &val);
    assert(val == -5);
    
    pqueue_pop(pq, &val);
    assert(val == 0);
    
    pqueue_pop(pq, &val);
    assert(val == 5);
    
    pqueue_destroy(pq);
    PASS();
    return 0;
}

int main(void) {
    printf("=== Running Priority Queue Tests ===\n\n");
    
    int failed = 0;
    
    failed += test_create_destroy();
    failed += test_push_and_peek();
    failed += test_pop_min_order();
    failed += test_heap_property();
    failed += test_auto_resize();
    failed += test_clear();
    failed += test_duplicate_values();
    failed += test_single_element();
    failed += test_error_handling();
    failed += test_large_dataset();
    failed += test_negative_values();
    
    printf("\n");
    if (failed == 0) {
        printf("✓ All tests passed!\n");
    } else {
        printf("✗ %d test(s) failed\n", failed);
    }
    
    return failed;
}
