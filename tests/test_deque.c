#include <stdio.h>
#include <assert.h>
#include "../include/deque.h"

#define TEST(name) printf("Testing %s... ", name)
#define PASS() printf("✓ PASS\n")

int test_create_destroy(void) {
    TEST("create and destroy");
    
    Deque *deque = deque_create();
    assert(deque != NULL);
    assert(deque_size(deque) == 0);
    assert(deque_is_empty(deque) == 1);
    
    deque_destroy(deque);
    PASS();
    return 0;
}

int test_push_front(void) {
    TEST("push front");
    
    Deque *deque = deque_create();
    
    deque_push_front(deque, 10);
    deque_push_front(deque, 20);
    deque_push_front(deque, 30);
    
    assert(deque_size(deque) == 3);
    
    int val;
    deque_peek_front(deque, &val);
    assert(val == 30);
    
    deque_peek_back(deque, &val);
    assert(val == 10);
    
    deque_destroy(deque);
    PASS();
    return 0;
}

int test_push_back(void) {
    TEST("push back");
    
    Deque *deque = deque_create();
    
    deque_push_back(deque, 10);
    deque_push_back(deque, 20);
    deque_push_back(deque, 30);
    
    assert(deque_size(deque) == 3);
    
    int val;
    deque_peek_front(deque, &val);
    assert(val == 10);
    
    deque_peek_back(deque, &val);
    assert(val == 30);
    
    deque_destroy(deque);
    PASS();
    return 0;
}

int test_pop_front(void) {
    TEST("pop front");
    
    Deque *deque = deque_create();
    
    deque_push_back(deque, 10);
    deque_push_back(deque, 20);
    deque_push_back(deque, 30);
    
    int val;
    deque_pop_front(deque, &val);
    assert(val == 10);
    assert(deque_size(deque) == 2);
    
    deque_pop_front(deque, &val);
    assert(val == 20);
    
    deque_pop_front(deque, &val);
    assert(val == 30);
    assert(deque_is_empty(deque) == 1);
    
    deque_destroy(deque);
    PASS();
    return 0;
}

int test_pop_back(void) {
    TEST("pop back");
    
    Deque *deque = deque_create();
    
    deque_push_back(deque, 10);
    deque_push_back(deque, 20);
    deque_push_back(deque, 30);
    
    int val;
    deque_pop_back(deque, &val);
    assert(val == 30);
    assert(deque_size(deque) == 2);
    
    deque_pop_back(deque, &val);
    assert(val == 20);
    
    deque_pop_back(deque, &val);
    assert(val == 10);
    assert(deque_is_empty(deque) == 1);
    
    deque_destroy(deque);
    PASS();
    return 0;
}

int test_mixed_operations(void) {
    TEST("mixed operations");
    
    Deque *deque = deque_create();
    
    deque_push_back(deque, 10);
    deque_push_front(deque, 5);
    deque_push_back(deque, 20);
    deque_push_front(deque, 1);
    
    assert(deque_size(deque) == 4);
    
    int val;
    deque_peek_front(deque, &val);
    assert(val == 1);
    
    deque_peek_back(deque, &val);
    assert(val == 20);
    
    deque_pop_front(deque, &val);
    assert(val == 1);
    
    deque_pop_back(deque, &val);
    assert(val == 20);
    
    assert(deque_size(deque) == 2);
    
    deque_destroy(deque);
    PASS();
    return 0;
}

int test_peek_operations(void) {
    TEST("peek operations");
    
    Deque *deque = deque_create();
    
    deque_push_back(deque, 10);
    deque_push_back(deque, 20);
    
    int val;
    deque_peek_front(deque, &val);
    assert(val == 10);
    assert(deque_size(deque) == 2);
    
    deque_peek_back(deque, &val);
    assert(val == 20);
    assert(deque_size(deque) == 2);
    
    deque_destroy(deque);
    PASS();
    return 0;
}

int test_clear(void) {
    TEST("clear");
    
    Deque *deque = deque_create();
    
    deque_push_back(deque, 10);
    deque_push_back(deque, 20);
    deque_push_back(deque, 30);
    
    assert(deque_size(deque) == 3);
    
    deque_clear(deque);
    
    assert(deque_size(deque) == 0);
    assert(deque_is_empty(deque) == 1);
    
    deque_push_back(deque, 40);
    assert(deque_size(deque) == 1);
    
    deque_destroy(deque);
    PASS();
    return 0;
}

int test_fifo_behavior(void) {
    TEST("FIFO behavior");
    
    Deque *deque = deque_create();
    
    for (int i = 1; i <= 5; i++) {
        deque_push_back(deque, i * 10);
    }
    
    assert(deque_size(deque) == 5);
    
    int val;
    deque_pop_front(deque, &val);
    assert(val == 10);
    
    deque_pop_front(deque, &val);
    assert(val == 20);
    
    deque_pop_front(deque, &val);
    assert(val == 30);
    
    deque_destroy(deque);
    PASS();
    return 0;
}

int test_lifo_behavior(void) {
    TEST("LIFO behavior");
    
    Deque *deque = deque_create();
    
    for (int i = 1; i <= 5; i++) {
        deque_push_back(deque, i * 10);
    }
    
    assert(deque_size(deque) == 5);
    
    int val;
    deque_pop_back(deque, &val);
    assert(val == 50);
    
    deque_pop_back(deque, &val);
    assert(val == 40);
    
    deque_pop_back(deque, &val);
    assert(val == 30);
    
    deque_destroy(deque);
    PASS();
    return 0;
}

int test_error_handling(void) {
    TEST("error handling");
    
    Deque *deque = deque_create();
    
    int val;
    assert(deque_pop_front(deque, &val) == -1);
    assert(deque_pop_back(deque, &val) == -1);
    assert(deque_peek_front(deque, &val) == -1);
    assert(deque_peek_back(deque, &val) == -1);
    
    deque_destroy(deque);
    deque_destroy(NULL);
    
    PASS();
    return 0;
}

int test_single_element(void) {
    TEST("single element operations");
    
    Deque *deque = deque_create();
    
    deque_push_front(deque, 42);
    
    int val;
    deque_peek_front(deque, &val);
    assert(val == 42);
    
    deque_peek_back(deque, &val);
    assert(val == 42);
    
    deque_pop_back(deque, &val);
    assert(val == 42);
    assert(deque_is_empty(deque) == 1);
    
    deque_push_back(deque, 99);
    deque_pop_front(deque, &val);
    assert(val == 99);
    assert(deque_is_empty(deque) == 1);
    
    deque_destroy(deque);
    PASS();
    return 0;
}

int main(void) {
    printf("=== Running Deque Tests ===\n\n");
    
    int failed = 0;
    
    failed += test_create_destroy();
    failed += test_push_front();
    failed += test_push_back();
    failed += test_pop_front();
    failed += test_pop_back();
    failed += test_mixed_operations();
    failed += test_peek_operations();
    failed += test_clear();
    failed += test_fifo_behavior();
    failed += test_lifo_behavior();
    failed += test_error_handling();
    failed += test_single_element();
    
    printf("\n");
    if (failed == 0) {
        printf("✓ All tests passed!\n");
    } else {
        printf("✗ %d test(s) failed\n", failed);
    }
    
    return failed;
}
