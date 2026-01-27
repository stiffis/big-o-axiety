#include <stdio.h>
#include <assert.h>
#include "../include/array2d.h"

#define TEST(name) printf("Testing %s... ", name)
#define PASS() printf("✓ PASS\n")

int test_create_destroy(void) {
    TEST("create and destroy");
    
    Array2D *arr = array2d_create(3, 4);
    assert(arr != NULL);
    assert(array2d_rows(arr) == 3);
    assert(array2d_cols(arr) == 4);
    
    array2d_destroy(arr);
    PASS();
    return 0;
}

int test_set_and_get(void) {
    TEST("set and get");
    
    Array2D *arr = array2d_create(3, 3);
    
    array2d_set(arr, 0, 0, 100);
    array2d_set(arr, 1, 1, 200);
    array2d_set(arr, 2, 2, 300);
    
    int val;
    array2d_get(arr, 0, 0, &val);
    assert(val == 100);
    
    array2d_get(arr, 1, 1, &val);
    assert(val == 200);
    
    array2d_get(arr, 2, 2, &val);
    assert(val == 300);
    
    array2d_get(arr, 0, 1, &val);
    assert(val == 0);
    
    array2d_destroy(arr);
    PASS();
    return 0;
}

int test_fill(void) {
    TEST("fill");
    
    Array2D *arr = array2d_create(3, 4);
    
    array2d_fill(arr, 42);
    
    int val;
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 4; j++) {
            array2d_get(arr, i, j, &val);
            assert(val == 42);
        }
    }
    
    array2d_destroy(arr);
    PASS();
    return 0;
}

int test_clear(void) {
    TEST("clear");
    
    Array2D *arr = array2d_create(3, 3);
    
    array2d_fill(arr, 99);
    array2d_clear(arr);
    
    int val;
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            array2d_get(arr, i, j, &val);
            assert(val == 0);
        }
    }
    
    array2d_destroy(arr);
    PASS();
    return 0;
}

int test_fill_row_col(void) {
    TEST("fill row and column");
    
    Array2D *arr = array2d_create(4, 4);
    
    array2d_fill_row(arr, 1, 10);
    array2d_fill_col(arr, 2, 20);
    
    int val;
    for (size_t j = 0; j < 4; j++) {
        array2d_get(arr, 1, j, &val);
        if (j == 2) {
            assert(val == 20);
        } else {
            assert(val == 10);
        }
    }
    
    for (size_t i = 0; i < 4; i++) {
        array2d_get(arr, i, 2, &val);
        assert(val == 20);
    }
    
    array2d_destroy(arr);
    PASS();
    return 0;
}

int test_get_row_col(void) {
    TEST("get row and column");
    
    Array2D *arr = array2d_create(3, 4);
    
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 4; j++) {
            array2d_set(arr, i, j, (int)(i * 10 + j));
        }
    }
    
    int row_buffer[4];
    array2d_get_row(arr, 1, row_buffer, 4);
    assert(row_buffer[0] == 10);
    assert(row_buffer[1] == 11);
    assert(row_buffer[2] == 12);
    assert(row_buffer[3] == 13);
    
    int col_buffer[3];
    array2d_get_col(arr, 2, col_buffer, 3);
    assert(col_buffer[0] == 2);
    assert(col_buffer[1] == 12);
    assert(col_buffer[2] == 22);
    
    array2d_destroy(arr);
    PASS();
    return 0;
}

int test_transpose_square(void) {
    TEST("transpose (square matrix)");
    
    Array2D *arr = array2d_create(3, 3);
    
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            array2d_set(arr, i, j, (int)(i * 3 + j));
        }
    }
    
    array2d_transpose(arr);
    
    int val;
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            array2d_get(arr, i, j, &val);
            assert(val == (int)(j * 3 + i));
        }
    }
    
    array2d_destroy(arr);
    PASS();
    return 0;
}

int test_transpose_copy(void) {
    TEST("transpose copy");
    
    Array2D *arr = array2d_create(2, 3);
    
    array2d_set(arr, 0, 0, 1);
    array2d_set(arr, 0, 1, 2);
    array2d_set(arr, 0, 2, 3);
    array2d_set(arr, 1, 0, 4);
    array2d_set(arr, 1, 1, 5);
    array2d_set(arr, 1, 2, 6);
    
    Array2D *transposed = array2d_transpose_copy(arr);
    assert(transposed != NULL);
    assert(array2d_rows(transposed) == 3);
    assert(array2d_cols(transposed) == 2);
    
    int val;
    array2d_get(transposed, 0, 0, &val);
    assert(val == 1);
    array2d_get(transposed, 1, 0, &val);
    assert(val == 2);
    array2d_get(transposed, 2, 0, &val);
    assert(val == 3);
    array2d_get(transposed, 0, 1, &val);
    assert(val == 4);
    array2d_get(transposed, 1, 1, &val);
    assert(val == 5);
    array2d_get(transposed, 2, 1, &val);
    assert(val == 6);
    
    array2d_destroy(arr);
    array2d_destroy(transposed);
    PASS();
    return 0;
}

int test_find(void) {
    TEST("find");
    
    Array2D *arr = array2d_create(3, 3);
    
    array2d_set(arr, 0, 0, 10);
    array2d_set(arr, 1, 2, 20);
    array2d_set(arr, 2, 1, 30);
    
    size_t row, col;
    
    assert(array2d_find(arr, 10, &row, &col) == 0);
    assert(row == 0 && col == 0);
    
    assert(array2d_find(arr, 20, &row, &col) == 0);
    assert(row == 1 && col == 2);
    
    assert(array2d_find(arr, 30, &row, &col) == 0);
    assert(row == 2 && col == 1);
    
    assert(array2d_find(arr, 99, &row, &col) == -1);
    
    array2d_destroy(arr);
    PASS();
    return 0;
}

int test_copy(void) {
    TEST("copy");
    
    Array2D *arr1 = array2d_create(3, 3);
    Array2D *arr2 = array2d_create(3, 3);
    
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            array2d_set(arr1, i, j, (int)(i * 10 + j));
        }
    }
    
    array2d_copy(arr2, arr1);
    
    int val1, val2;
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            array2d_get(arr1, i, j, &val1);
            array2d_get(arr2, i, j, &val2);
            assert(val1 == val2);
        }
    }
    
    array2d_destroy(arr1);
    array2d_destroy(arr2);
    PASS();
    return 0;
}

int test_bounds_checking(void) {
    TEST("bounds checking");
    
    Array2D *arr = array2d_create(3, 4);
    
    assert(array2d_set(arr, 10, 0, 99) == -1);
    assert(array2d_set(arr, 0, 10, 99) == -1);
    
    int val;
    assert(array2d_get(arr, 10, 0, &val) == -1);
    assert(array2d_get(arr, 0, 10, &val) == -1);
    
    array2d_destroy(arr);
    PASS();
    return 0;
}

int test_zero_dimensions(void) {
    TEST("zero dimensions rejection");
    
    Array2D *arr1 = array2d_create(0, 5);
    assert(arr1 == NULL);
    
    Array2D *arr2 = array2d_create(5, 0);
    assert(arr2 == NULL);
    
    PASS();
    return 0;
}

int test_transpose_non_square(void) {
    TEST("transpose non-square rejection");
    
    Array2D *arr = array2d_create(2, 3);
    
    assert(array2d_transpose(arr) == -1);
    
    array2d_destroy(arr);
    PASS();
    return 0;
}

int main(void) {
    printf("=== Running Array2D Tests ===\n\n");
    
    int failed = 0;
    
    failed += test_create_destroy();
    failed += test_set_and_get();
    failed += test_fill();
    failed += test_clear();
    failed += test_fill_row_col();
    failed += test_get_row_col();
    failed += test_transpose_square();
    failed += test_transpose_copy();
    failed += test_find();
    failed += test_copy();
    failed += test_bounds_checking();
    failed += test_zero_dimensions();
    failed += test_transpose_non_square();
    
    printf("\n");
    if (failed == 0) {
        printf("✓ All tests passed!\n");
    } else {
        printf("✗ %d test(s) failed\n", failed);
    }
    
    return failed;
}
