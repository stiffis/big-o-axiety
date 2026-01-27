#include <stdio.h>
#include <assert.h>
#include "../include/stack.h"

#define TEST(name) printf("Testing %s... ", name)
#define PASS() printf("✓ PASS\n")

int test_create_destroy(void) {
    TEST("create and destroy");
    
    Stack *stack = stack_create();
    assert(stack != NULL);
    assert(stack_size(stack) == 0);
    assert(stack_is_empty(stack) == 1);
    
    stack_destroy(stack);
    PASS();
    return 0;
}

int test_push_and_peek(void) {
    TEST("push and peek");
    
    Stack *stack = stack_create();
    
    stack_push(stack, 10);
    stack_push(stack, 20);
    stack_push(stack, 30);
    
    assert(stack_size(stack) == 3);
    
    int val;
    stack_peek(stack, &val);
    assert(val == 30);
    assert(stack_size(stack) == 3);
    
    stack_destroy(stack);
    PASS();
    return 0;
}

int test_pop(void) {
    TEST("pop");
    
    Stack *stack = stack_create();
    
    stack_push(stack, 10);
    stack_push(stack, 20);
    stack_push(stack, 30);
    
    int val;
    stack_pop(stack, &val);
    assert(val == 30);
    assert(stack_size(stack) == 2);
    
    stack_pop(stack, &val);
    assert(val == 20);
    
    stack_pop(stack, &val);
    assert(val == 10);
    assert(stack_is_empty(stack) == 1);
    
    stack_destroy(stack);
    PASS();
    return 0;
}

int test_lifo_order(void) {
    TEST("LIFO order");
    
    Stack *stack = stack_create();
    
    for (int i = 1; i <= 5; i++) {
        stack_push(stack, i * 10);
    }
    
    assert(stack_size(stack) == 5);
    
    int val;
    stack_pop(stack, &val);
    assert(val == 50);
    
    stack_pop(stack, &val);
    assert(val == 40);
    
    stack_pop(stack, &val);
    assert(val == 30);
    
    stack_destroy(stack);
    PASS();
    return 0;
}

int test_resize(void) {
    TEST("automatic resize");
    
    Stack *stack = stack_create_with_capacity(2);
    
    stack_push(stack, 1);
    stack_push(stack, 2);
    assert(stack_capacity(stack) == 2);
    
    stack_push(stack, 3);
    assert(stack_capacity(stack) == 4);
    
    stack_push(stack, 4);
    stack_push(stack, 5);
    assert(stack_capacity(stack) == 8);
    
    assert(stack_size(stack) == 5);
    
    stack_destroy(stack);
    PASS();
    return 0;
}

int test_clear(void) {
    TEST("clear");
    
    Stack *stack = stack_create();
    
    stack_push(stack, 10);
    stack_push(stack, 20);
    stack_push(stack, 30);
    
    assert(stack_size(stack) == 3);
    
    size_t old_capacity = stack_capacity(stack);
    
    stack_clear(stack);
    
    assert(stack_size(stack) == 0);
    assert(stack_is_empty(stack) == 1);
    assert(stack_capacity(stack) == old_capacity);
    
    stack_destroy(stack);
    PASS();
    return 0;
}

int test_peek_after_push(void) {
    TEST("peek after push");
    
    Stack *stack = stack_create();
    
    int val;
    
    stack_push(stack, 10);
    stack_peek(stack, &val);
    assert(val == 10);
    
    stack_push(stack, 20);
    stack_peek(stack, &val);
    assert(val == 20);
    
    stack_push(stack, 30);
    stack_peek(stack, &val);
    assert(val == 30);
    
    stack_destroy(stack);
    PASS();
    return 0;
}

int test_error_handling(void) {
    TEST("error handling");
    
    Stack *stack = stack_create();
    
    int val;
    assert(stack_pop(stack, &val) == -1);
    assert(stack_peek(stack, &val) == -1);
    
    stack_destroy(stack);
    stack_destroy(NULL);
    
    PASS();
    return 0;
}

int main(void) {
    printf("=== Running Stack Tests ===\n\n");
    
    int failed = 0;
    
    failed += test_create_destroy();
    failed += test_push_and_peek();
    failed += test_pop();
    failed += test_lifo_order();
    failed += test_resize();
    failed += test_clear();
    failed += test_peek_after_push();
    failed += test_error_handling();
    
    printf("\n");
    if (failed == 0) {
        printf("✓ All tests passed!\n");
    } else {
        printf("✗ %d test(s) failed\n", failed);
    }
    
    return failed;
}
