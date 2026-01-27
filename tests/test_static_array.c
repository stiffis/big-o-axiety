#include <stdio.h>
#include <assert.h>
#include "../include/static_array.h"

#define TEST(name) printf("Testing %s... ", name)
#define PASS() printf("✓ PASS\n")

int test_create_destroy(void) {
    TEST("create and destroy");
    
    StaticArray *arr = static_array_create(10);
    assert(arr != NULL);
    assert(static_array_capacity(arr) == 10);
    
    static_array_destroy(arr);
    PASS();
    return 0;
}

int test_set_and_get(void) {
    TEST("set and get");
    
    StaticArray *arr = static_array_create(5);
    
    static_array_set(arr, 0, 100);
    static_array_set(arr, 2, 200);
    static_array_set(arr, 4, 300);
    
    int val;
    static_array_get(arr, 0, &val);
    assert(val == 100);
    
    static_array_get(arr, 2, &val);
    assert(val == 200);
    
    static_array_get(arr, 4, &val);
    assert(val == 300);
    
    static_array_get(arr, 1, &val);
    assert(val == 0);
    
    static_array_destroy(arr);
    PASS();
    return 0;
}

int test_fill(void) {
    TEST("fill");
    
    StaticArray *arr = static_array_create(5);
    
    static_array_fill(arr, 42);
    
    int val;
    for (size_t i = 0; i < 5; i++) {
        static_array_get(arr, i, &val);
        assert(val == 42);
    }
    
    static_array_destroy(arr);
    PASS();
    return 0;
}

int test_clear(void) {
    TEST("clear");
    
    StaticArray *arr = static_array_create(5);
    
    static_array_fill(arr, 99);
    static_array_clear(arr);
    
    int val;
    for (size_t i = 0; i < 5; i++) {
        static_array_get(arr, i, &val);
        assert(val == 0);
    }
    
    static_array_destroy(arr);
    PASS();
    return 0;
}

int test_find(void) {
    TEST("find");
    
    StaticArray *arr = static_array_create(5);
    
    static_array_set(arr, 0, 10);
    static_array_set(arr, 2, 20);
    static_array_set(arr, 4, 30);
    
    assert(static_array_find(arr, 10) == 0);
    assert(static_array_find(arr, 20) == 2);
    assert(static_array_find(arr, 30) == 4);
    assert(static_array_find(arr, 0) == 1);
    assert(static_array_find(arr, 99) == -1);
    
    static_array_destroy(arr);
    PASS();
    return 0;
}

int test_copy(void) {
    TEST("copy");
    
    StaticArray *arr1 = static_array_create(5);
    StaticArray *arr2 = static_array_create(5);
    
    for (size_t i = 0; i < 5; i++) {
        static_array_set(arr1, i, (int)i * 10);
    }
    
    static_array_copy(arr2, arr1);
    
    int val1, val2;
    for (size_t i = 0; i < 5; i++) {
        static_array_get(arr1, i, &val1);
        static_array_get(arr2, i, &val2);
        assert(val1 == val2);
    }
    
    static_array_destroy(arr1);
    static_array_destroy(arr2);
    PASS();
    return 0;
}

int test_reverse(void) {
    TEST("reverse");
    
    StaticArray *arr = static_array_create(5);
    
    for (size_t i = 0; i < 5; i++) {
        static_array_set(arr, i, (int)i);
    }
    
    static_array_reverse(arr);
    
    int val;
    for (size_t i = 0; i < 5; i++) {
        static_array_get(arr, i, &val);
        assert(val == (int)(4 - i));
    }
    
    static_array_destroy(arr);
    PASS();
    return 0;
}

int test_bounds_checking(void) {
    TEST("bounds checking");
    
    StaticArray *arr = static_array_create(5);
    
    assert(static_array_set(arr, 10, 99) == -1);
    
    int val;
    assert(static_array_get(arr, 10, &val) == -1);
    
    static_array_destroy(arr);
    PASS();
    return 0;
}

int test_capacity(void) {
    TEST("capacity");
    
    StaticArray *arr = static_array_create(100);
    assert(static_array_capacity(arr) == 100);
    
    static_array_destroy(arr);
    PASS();
    return 0;
}

int test_zero_capacity(void) {
    TEST("zero capacity rejection");
    
    StaticArray *arr = static_array_create(0);
    assert(arr == NULL);
    
    PASS();
    return 0;
}

int main(void) {
    printf("=== Running Static Array Tests ===\n\n");
    
    int failed = 0;
    
    failed += test_create_destroy();
    failed += test_set_and_get();
    failed += test_fill();
    failed += test_clear();
    failed += test_find();
    failed += test_copy();
    failed += test_reverse();
    failed += test_bounds_checking();
    failed += test_capacity();
    failed += test_zero_capacity();
    
    printf("\n");
    if (failed == 0) {
        printf("✓ All tests passed!\n");
    } else {
        printf("✗ %d test(s) failed\n", failed);
    }
    
    return failed;
}
