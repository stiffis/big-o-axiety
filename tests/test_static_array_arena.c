#include <stdio.h>
#include <assert.h>
#include "../include/static_array_arena.h"

#define TEST(name) printf("Testing %s... ", name)
#define PASS() printf("✓ PASS\n")

void test_arena_create_destroy(void) {
    TEST("arena create and destroy");
    
    Arena *arena = arena_create(1024);
    assert(arena != NULL);
    assert(arena_capacity(arena) == 1024);
    assert(arena_used(arena) == 0);
    
    arena_destroy(arena);
    PASS();
}

void test_arena_reset(void) {
    TEST("arena reset");
    
    Arena *arena = arena_create(1024);
    assert(arena != NULL);
    
    StaticArrayArena *arr = static_array_arena_create(arena, 10);
    assert(arr != NULL);
    assert(arena_used(arena) > 0);
    
    size_t used = arena_used(arena);
    arena_reset(arena);
    assert(arena_used(arena) == 0);
    
    StaticArrayArena *arr2 = static_array_arena_create(arena, 10);
    assert(arr2 != NULL);
    assert(arena_used(arena) == used);
    
    arena_destroy(arena);
    PASS();
}

void test_create_and_capacity(void) {
    TEST("create and capacity");
    
    Arena *arena = arena_create(4096);
    assert(arena != NULL);
    
    StaticArrayArena *arr = static_array_arena_create(arena, 100);
    assert(arr != NULL);
    assert(static_array_arena_capacity(arr) == 100);
    
    arena_destroy(arena);
    PASS();
}

void test_set_and_get(void) {
    TEST("set and get");
    
    Arena *arena = arena_create(4096);
    StaticArrayArena *arr = static_array_arena_create(arena, 10);
    assert(arr != NULL);
    
    assert(static_array_arena_set(arr, 0, 42) == 0);
    assert(static_array_arena_set(arr, 5, 100) == 0);
    
    int value;
    assert(static_array_arena_get(arr, 0, &value) == 0);
    assert(value == 42);
    
    assert(static_array_arena_get(arr, 5, &value) == 0);
    assert(value == 100);
    
    arena_destroy(arena);
    PASS();
}

void test_fill(void) {
    TEST("fill");
    
    Arena *arena = arena_create(4096);
    StaticArrayArena *arr = static_array_arena_create(arena, 10);
    assert(arr != NULL);
    
    assert(static_array_arena_fill(arr, 7) == 0);
    
    int value;
    for (size_t i = 0; i < 10; i++) {
        assert(static_array_arena_get(arr, i, &value) == 0);
        assert(value == 7);
    }
    
    arena_destroy(arena);
    PASS();
}

void test_clear(void) {
    TEST("clear");
    
    Arena *arena = arena_create(4096);
    StaticArrayArena *arr = static_array_arena_create(arena, 10);
    assert(arr != NULL);
    
    static_array_arena_fill(arr, 42);
    static_array_arena_clear(arr);
    
    int value;
    for (size_t i = 0; i < 10; i++) {
        assert(static_array_arena_get(arr, i, &value) == 0);
        assert(value == 0);
    }
    
    arena_destroy(arena);
    PASS();
}

void test_find(void) {
    TEST("find");
    
    Arena *arena = arena_create(4096);
    StaticArrayArena *arr = static_array_arena_create(arena, 10);
    assert(arr != NULL);
    
    static_array_arena_set(arr, 3, 42);
    static_array_arena_set(arr, 7, 100);
    
    assert(static_array_arena_find(arr, 42) == 3);
    assert(static_array_arena_find(arr, 100) == 7);
    assert(static_array_arena_find(arr, 999) == -1);
    
    arena_destroy(arena);
    PASS();
}

void test_multiple_arrays(void) {
    TEST("multiple arrays in same arena");
    
    Arena *arena = arena_create(4096);
    assert(arena != NULL);
    
    StaticArrayArena *arr1 = static_array_arena_create(arena, 10);
    assert(arr1 != NULL);
    
    StaticArrayArena *arr2 = static_array_arena_create(arena, 20);
    assert(arr2 != NULL);
    
    static_array_arena_set(arr1, 0, 42);
    static_array_arena_set(arr2, 0, 100);
    
    int value;
    assert(static_array_arena_get(arr1, 0, &value) == 0);
    assert(value == 42);
    
    assert(static_array_arena_get(arr2, 0, &value) == 0);
    assert(value == 100);
    
    arena_destroy(arena);
    PASS();
}

void test_arena_exhaustion(void) {
    TEST("arena exhaustion");
    
    Arena *arena = arena_create(256);
    assert(arena != NULL);
    
    StaticArrayArena *arr1 = static_array_arena_create(arena, 10);
    assert(arr1 != NULL);
    
    StaticArrayArena *arr2 = static_array_arena_create(arena, 100);
    assert(arr2 == NULL);
    
    arena_destroy(arena);
    PASS();
}

void test_error_handling(void) {
    TEST("error handling");
    
    Arena *arena = arena_create(4096);
    StaticArrayArena *arr = static_array_arena_create(arena, 10);
    assert(arr != NULL);
    
    assert(static_array_arena_set(arr, 10, 42) == -1);
    assert(static_array_arena_set(arr, 100, 42) == -1);
    
    int value;
    assert(static_array_arena_get(arr, 10, &value) == -1);
    assert(static_array_arena_get(arr, 100, &value) == -1);
    assert(static_array_arena_get(arr, 0, NULL) == -1);
    
    arena_destroy(arena);
    PASS();
}

int main(void) {
    printf("=== Running Static Array Arena Tests ===\n\n");
    
    test_arena_create_destroy();
    test_arena_reset();
    test_create_and_capacity();
    test_set_and_get();
    test_fill();
    test_clear();
    test_find();
    test_multiple_arrays();
    test_arena_exhaustion();
    test_error_handling();
    
    printf("\n✓ All tests passed!\n");
    return 0;
}
