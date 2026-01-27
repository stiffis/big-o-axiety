#include <stdio.h>
#include <assert.h>
#include "../include/array.h"

#define TEST(name) printf("Testing %s... ", name)
#define PASS() printf("✓ PASS\n")
#define FAIL(msg) do { printf("✗ FAIL: %s\n", msg); return 1; } while(0)

int test_create_destroy(void) {
    TEST("create and destroy");
    
    DynamicArray *arr = array_create(10);
    assert(arr != NULL);
    assert(array_size(arr) == 0);
    assert(array_capacity(arr) == 10);
    assert(array_is_empty(arr) == 1);
    
    array_destroy(arr);
    PASS();
    return 0;
}

int test_push_and_get(void) {
    TEST("push and get");
    
    DynamicArray *arr = array_create(2);
    
    array_push(arr, 100);
    array_push(arr, 200);
    array_push(arr, 300);
    
    assert(array_size(arr) == 3);
    
    int val;
    array_get(arr, 0, &val);
    assert(val == 100);
    
    array_get(arr, 1, &val);
    assert(val == 200);
    
    array_get(arr, 2, &val);
    assert(val == 300);
    
    array_destroy(arr);
    PASS();
    return 0;
}

int test_resize(void) {
    TEST("automatic resize");
    
    DynamicArray *arr = array_create(2);
    
    array_push(arr, 1);
    array_push(arr, 2);
    assert(array_capacity(arr) == 2);
    
    array_push(arr, 3);
    assert(array_capacity(arr) == 4);
    
    array_push(arr, 4);
    array_push(arr, 5);
    assert(array_capacity(arr) == 8);
    
    assert(array_size(arr) == 5);
    
    array_destroy(arr);
    PASS();
    return 0;
}

int test_pop(void) {
    TEST("pop");
    
    DynamicArray *arr = array_create(4);
    array_push(arr, 10);
    array_push(arr, 20);
    array_push(arr, 30);
    
    int val;
    array_pop(arr, &val);
    assert(val == 30);
    assert(array_size(arr) == 2);
    
    array_pop(arr, &val);
    assert(val == 20);
    
    array_pop(arr, &val);
    assert(val == 10);
    assert(array_is_empty(arr) == 1);
    
    array_destroy(arr);
    PASS();
    return 0;
}

int test_insert(void) {
    TEST("insert");
    
    DynamicArray *arr = array_create(5);
    array_push(arr, 1);
    array_push(arr, 2);
    array_push(arr, 4);
    
    array_insert(arr, 2, 3);
    
    int val;
    array_get(arr, 0, &val);
    assert(val == 1);
    array_get(arr, 1, &val);
    assert(val == 2);
    array_get(arr, 2, &val);
    assert(val == 3);
    array_get(arr, 3, &val);
    assert(val == 4);
    
    array_insert(arr, 0, 0);
    array_get(arr, 0, &val);
    assert(val == 0);
    assert(array_size(arr) == 5);
    
    array_destroy(arr);
    PASS();
    return 0;
}

int test_remove(void) {
    TEST("remove");
    
    DynamicArray *arr = array_create(5);
    array_push(arr, 10);
    array_push(arr, 20);
    array_push(arr, 30);
    array_push(arr, 40);
    
    int val;
    array_remove(arr, 1, &val);
    assert(val == 20);
    assert(array_size(arr) == 3);
    
    array_get(arr, 0, &val);
    assert(val == 10);
    array_get(arr, 1, &val);
    assert(val == 30);
    array_get(arr, 2, &val);
    assert(val == 40);
    
    array_destroy(arr);
    PASS();
    return 0;
}

int test_set(void) {
    TEST("set");
    
    DynamicArray *arr = array_create(3);
    array_push(arr, 1);
    array_push(arr, 2);
    array_push(arr, 3);
    
    array_set(arr, 1, 999);
    
    int val;
    array_get(arr, 1, &val);
    assert(val == 999);
    
    array_destroy(arr);
    PASS();
    return 0;
}

int test_find(void) {
    TEST("find");
    
    DynamicArray *arr = array_create(5);
    array_push(arr, 10);
    array_push(arr, 20);
    array_push(arr, 30);
    
    assert(array_find(arr, 20) == 1);
    assert(array_find(arr, 30) == 2);
    assert(array_find(arr, 10) == 0);
    assert(array_find(arr, 99) == -1);
    
    array_destroy(arr);
    PASS();
    return 0;
}

int test_clear(void) {
    TEST("clear");
    
    DynamicArray *arr = array_create(5);
    array_push(arr, 1);
    array_push(arr, 2);
    array_push(arr, 3);
    
    assert(array_size(arr) == 3);
    
    array_clear(arr);
    
    assert(array_size(arr) == 0);
    assert(array_is_empty(arr) == 1);
    assert(array_capacity(arr) == 5);
    
    array_destroy(arr);
    PASS();
    return 0;
}

int test_error_handling(void) {
    TEST("error handling");
    
    DynamicArray *arr = array_create(2);
    array_push(arr, 1);
    
    int val;
    assert(array_get(arr, 10, &val) == -1);
    assert(array_set(arr, 10, 99) == -1);
    assert(array_remove(arr, 10, &val) == -1);
    assert(array_insert(arr, 10, 99) == -1);
    
    array_clear(arr);
    assert(array_pop(arr, &val) == -1);
    
    array_destroy(arr);
    PASS();
    return 0;
}

int main(void) {
    printf("=== Running Dynamic Array Tests ===\n\n");
    
    int failed = 0;
    
    failed += test_create_destroy();
    failed += test_push_and_get();
    failed += test_resize();
    failed += test_pop();
    failed += test_insert();
    failed += test_remove();
    failed += test_set();
    failed += test_find();
    failed += test_clear();
    failed += test_error_handling();
    
    printf("\n");
    if (failed == 0) {
        printf("✓ All tests passed!\n");
    } else {
        printf("✗ %d test(s) failed\n", failed);
    }
    
    return failed;
}
