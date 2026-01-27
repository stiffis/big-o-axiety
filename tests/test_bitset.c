#include <stdio.h>
#include <assert.h>
#include "../include/bitset.h"

#define TEST(name) printf("Testing %s... ", name)
#define PASS() printf("✓ PASS\n")

int test_create_destroy(void) {
    TEST("create and destroy");
    
    Bitset *bs = bitset_create(32);
    assert(bs != NULL);
    assert(bitset_size(bs) == 32);
    assert(bitset_count(bs) == 0);
    assert(bitset_none(bs) == 1);
    
    bitset_destroy(bs);
    PASS();
    return 0;
}

int test_set_and_test(void) {
    TEST("set and test");
    
    Bitset *bs = bitset_create(16);
    
    bitset_set(bs, 0);
    assert(bitset_test(bs, 0) == 1);
    assert(bitset_count(bs) == 1);
    
    bitset_set(bs, 5);
    assert(bitset_test(bs, 5) == 1);
    assert(bitset_count(bs) == 2);
    
    bitset_set(bs, 15);
    assert(bitset_test(bs, 15) == 1);
    assert(bitset_count(bs) == 3);
    
    assert(bitset_test(bs, 1) == 0);
    assert(bitset_test(bs, 10) == 0);
    
    bitset_destroy(bs);
    PASS();
    return 0;
}

int test_clear(void) {
    TEST("clear");
    
    Bitset *bs = bitset_create(16);
    
    bitset_set(bs, 3);
    bitset_set(bs, 7);
    bitset_set(bs, 11);
    assert(bitset_count(bs) == 3);
    
    bitset_clear(bs, 7);
    assert(bitset_test(bs, 7) == 0);
    assert(bitset_count(bs) == 2);
    
    bitset_clear(bs, 3);
    bitset_clear(bs, 11);
    assert(bitset_count(bs) == 0);
    assert(bitset_none(bs) == 1);
    
    bitset_destroy(bs);
    PASS();
    return 0;
}

int test_flip(void) {
    TEST("flip");
    
    Bitset *bs = bitset_create(8);
    
    bitset_flip(bs, 0);
    assert(bitset_test(bs, 0) == 1);
    
    bitset_flip(bs, 0);
    assert(bitset_test(bs, 0) == 0);
    
    bitset_flip(bs, 5);
    assert(bitset_test(bs, 5) == 1);
    assert(bitset_count(bs) == 1);
    
    bitset_destroy(bs);
    PASS();
    return 0;
}

int test_set_all(void) {
    TEST("set_all");
    
    Bitset *bs = bitset_create(10);
    
    bitset_set_all(bs);
    assert(bitset_count(bs) == 10);
    assert(bitset_all(bs) == 1);
    assert(bitset_any(bs) == 1);
    assert(bitset_none(bs) == 0);
    
    for (size_t i = 0; i < 10; i++) {
        assert(bitset_test(bs, i) == 1);
    }
    
    bitset_destroy(bs);
    PASS();
    return 0;
}

int test_clear_all(void) {
    TEST("clear_all");
    
    Bitset *bs = bitset_create(16);
    
    bitset_set_all(bs);
    assert(bitset_count(bs) == 16);
    
    bitset_clear_all(bs);
    assert(bitset_count(bs) == 0);
    assert(bitset_none(bs) == 1);
    assert(bitset_all(bs) == 0);
    assert(bitset_any(bs) == 0);
    
    bitset_destroy(bs);
    PASS();
    return 0;
}

int test_flip_all(void) {
    TEST("flip_all");
    
    Bitset *bs = bitset_create(8);
    
    bitset_set(bs, 0);
    bitset_set(bs, 2);
    bitset_set(bs, 4);
    assert(bitset_count(bs) == 3);
    
    bitset_flip_all(bs);
    assert(bitset_count(bs) == 5);
    assert(bitset_test(bs, 0) == 0);
    assert(bitset_test(bs, 1) == 1);
    assert(bitset_test(bs, 2) == 0);
    assert(bitset_test(bs, 3) == 1);
    
    bitset_destroy(bs);
    PASS();
    return 0;
}

int test_all_any_none(void) {
    TEST("all, any, none");
    
    Bitset *bs = bitset_create(5);
    
    assert(bitset_all(bs) == 0);
    assert(bitset_any(bs) == 0);
    assert(bitset_none(bs) == 1);
    
    bitset_set(bs, 2);
    assert(bitset_all(bs) == 0);
    assert(bitset_any(bs) == 1);
    assert(bitset_none(bs) == 0);
    
    bitset_set_all(bs);
    assert(bitset_all(bs) == 1);
    assert(bitset_any(bs) == 1);
    assert(bitset_none(bs) == 0);
    
    bitset_destroy(bs);
    PASS();
    return 0;
}

int test_and(void) {
    TEST("bitwise AND");
    
    Bitset *bs1 = bitset_create(8);
    Bitset *bs2 = bitset_create(8);
    
    bitset_set(bs1, 0);
    bitset_set(bs1, 2);
    bitset_set(bs1, 4);
    
    bitset_set(bs2, 0);
    bitset_set(bs2, 3);
    bitset_set(bs2, 4);
    
    bitset_and(bs1, bs2);
    
    assert(bitset_test(bs1, 0) == 1);
    assert(bitset_test(bs1, 2) == 0);
    assert(bitset_test(bs1, 3) == 0);
    assert(bitset_test(bs1, 4) == 1);
    assert(bitset_count(bs1) == 2);
    
    bitset_destroy(bs1);
    bitset_destroy(bs2);
    PASS();
    return 0;
}

int test_or(void) {
    TEST("bitwise OR");
    
    Bitset *bs1 = bitset_create(8);
    Bitset *bs2 = bitset_create(8);
    
    bitset_set(bs1, 0);
    bitset_set(bs1, 2);
    
    bitset_set(bs2, 1);
    bitset_set(bs2, 2);
    bitset_set(bs2, 3);
    
    bitset_or(bs1, bs2);
    
    assert(bitset_test(bs1, 0) == 1);
    assert(bitset_test(bs1, 1) == 1);
    assert(bitset_test(bs1, 2) == 1);
    assert(bitset_test(bs1, 3) == 1);
    assert(bitset_count(bs1) == 4);
    
    bitset_destroy(bs1);
    bitset_destroy(bs2);
    PASS();
    return 0;
}

int test_xor(void) {
    TEST("bitwise XOR");
    
    Bitset *bs1 = bitset_create(8);
    Bitset *bs2 = bitset_create(8);
    
    bitset_set(bs1, 0);
    bitset_set(bs1, 2);
    bitset_set(bs1, 4);
    
    bitset_set(bs2, 0);
    bitset_set(bs2, 3);
    bitset_set(bs2, 4);
    
    bitset_xor(bs1, bs2);
    
    assert(bitset_test(bs1, 0) == 0);
    assert(bitset_test(bs1, 2) == 1);
    assert(bitset_test(bs1, 3) == 1);
    assert(bitset_test(bs1, 4) == 0);
    assert(bitset_count(bs1) == 2);
    
    bitset_destroy(bs1);
    bitset_destroy(bs2);
    PASS();
    return 0;
}

int test_equals(void) {
    TEST("equals");
    
    Bitset *bs1 = bitset_create(8);
    Bitset *bs2 = bitset_create(8);
    
    assert(bitset_equals(bs1, bs2) == 1);
    
    bitset_set(bs1, 3);
    assert(bitset_equals(bs1, bs2) == 0);
    
    bitset_set(bs2, 3);
    assert(bitset_equals(bs1, bs2) == 1);
    
    bitset_destroy(bs1);
    bitset_destroy(bs2);
    PASS();
    return 0;
}

int test_error_handling(void) {
    TEST("error handling");
    
    Bitset *bs = bitset_create(8);
    
    assert(bitset_set(bs, 100) == -1);
    assert(bitset_clear(bs, 100) == -1);
    assert(bitset_flip(bs, 100) == -1);
    assert(bitset_test(bs, 100) == -1);
    
    assert(bitset_create(0) == NULL);
    
    bitset_destroy(bs);
    bitset_destroy(NULL);
    
    PASS();
    return 0;
}

int test_non_byte_aligned(void) {
    TEST("non-byte-aligned sizes");
    
    Bitset *bs = bitset_create(13);
    assert(bitset_size(bs) == 13);
    
    bitset_set_all(bs);
    assert(bitset_count(bs) == 13);
    assert(bitset_all(bs) == 1);
    
    for (size_t i = 0; i < 13; i++) {
        assert(bitset_test(bs, i) == 1);
    }
    
    bitset_destroy(bs);
    PASS();
    return 0;
}

int main(void) {
    printf("=== Running Bitset Tests ===\n\n");
    
    int failed = 0;
    
    failed += test_create_destroy();
    failed += test_set_and_test();
    failed += test_clear();
    failed += test_flip();
    failed += test_set_all();
    failed += test_clear_all();
    failed += test_flip_all();
    failed += test_all_any_none();
    failed += test_and();
    failed += test_or();
    failed += test_xor();
    failed += test_equals();
    failed += test_error_handling();
    failed += test_non_byte_aligned();
    
    printf("\n");
    if (failed == 0) {
        printf("✓ All tests passed!\n");
    } else {
        printf("✗ %d test(s) failed\n", failed);
    }
    
    return failed;
}
