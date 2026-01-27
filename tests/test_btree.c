#include <stdio.h>
#include <assert.h>
#include "../include/btree.h"

#define TEST(name) printf("Testing %s... ", name)
#define PASS() printf("✓ PASS\n")

static void collect_keys(int key, void *user_data) {
    int **arr_ptr = (int **)user_data;
    **arr_ptr = key;
    (*arr_ptr)++;
}

int test_create_destroy(void) {
    TEST("create and destroy");
    
    BTree *tree = btree_create(3);
    assert(tree != NULL);
    assert(btree_is_empty(tree));
    assert(btree_size(tree) == 0);
    assert(btree_height(tree) == 0);
    assert(btree_min_degree(tree) == 3);
    
    btree_destroy(tree);
    PASS();
    return 0;
}

int test_invalid_min_degree(void) {
    TEST("invalid min degree rejection");
    
    BTree *tree = btree_create(1);
    assert(tree == NULL);
    
    PASS();
    return 0;
}

int test_insert_and_search(void) {
    TEST("insert and search");
    
    BTree *tree = btree_create(3);
    
    assert(btree_insert(tree, 10) == 0);
    assert(btree_insert(tree, 20) == 0);
    assert(btree_insert(tree, 5) == 0);
    assert(btree_insert(tree, 15) == 0);
    
    assert(btree_size(tree) == 4);
    assert(btree_search(tree, 10));
    assert(btree_search(tree, 20));
    assert(btree_search(tree, 5));
    assert(btree_search(tree, 15));
    assert(!btree_search(tree, 99));
    
    btree_destroy(tree);
    PASS();
    return 0;
}

int test_duplicate_insert(void) {
    TEST("duplicate insert rejection");
    
    BTree *tree = btree_create(3);
    
    assert(btree_insert(tree, 10) == 0);
    assert(btree_insert(tree, 10) == -1);
    assert(btree_size(tree) == 1);
    
    btree_destroy(tree);
    PASS();
    return 0;
}

int test_delete(void) {
    TEST("delete");
    
    BTree *tree = btree_create(3);
    
    btree_insert(tree, 10);
    btree_insert(tree, 20);
    btree_insert(tree, 5);
    btree_insert(tree, 15);
    btree_insert(tree, 25);
    
    assert(btree_delete(tree, 20) == 0);
    assert(btree_size(tree) == 4);
    assert(!btree_search(tree, 20));
    assert(btree_search(tree, 10));
    
    assert(btree_delete(tree, 99) == -1);
    
    btree_destroy(tree);
    PASS();
    return 0;
}

int test_min_max(void) {
    TEST("min and max");
    
    BTree *tree = btree_create(3);
    
    btree_insert(tree, 50);
    btree_insert(tree, 30);
    btree_insert(tree, 70);
    btree_insert(tree, 20);
    btree_insert(tree, 90);
    
    int min, max;
    assert(btree_min(tree, &min) == 0);
    assert(min == 20);
    
    assert(btree_max(tree, &max) == 0);
    assert(max == 90);
    
    btree_destroy(tree);
    PASS();
    return 0;
}

int test_node_splitting(void) {
    TEST("node splitting (t=2)");
    
    BTree *tree = btree_create(2);
    
    for (int i = 1; i <= 10; i++) {
        btree_insert(tree, i * 10);
    }
    
    assert(btree_size(tree) == 10);
    assert(btree_height(tree) >= 2);
    
    for (int i = 1; i <= 10; i++) {
        assert(btree_search(tree, i * 10));
    }
    
    btree_destroy(tree);
    PASS();
    return 0;
}

int test_traversal(void) {
    TEST("in-order traversal");
    
    BTree *tree = btree_create(3);
    
    btree_insert(tree, 50);
    btree_insert(tree, 30);
    btree_insert(tree, 70);
    btree_insert(tree, 20);
    btree_insert(tree, 40);
    btree_insert(tree, 60);
    btree_insert(tree, 80);
    
    int expected[] = {20, 30, 40, 50, 60, 70, 80};
    int result[7];
    int *ptr = result;
    
    btree_traverse(tree, collect_keys, &ptr);
    
    for (int i = 0; i < 7; i++) {
        assert(result[i] == expected[i]);
    }
    
    btree_destroy(tree);
    PASS();
    return 0;
}

int test_to_array(void) {
    TEST("to array conversion");
    
    BTree *tree = btree_create(3);
    
    btree_insert(tree, 50);
    btree_insert(tree, 30);
    btree_insert(tree, 70);
    btree_insert(tree, 20);
    btree_insert(tree, 90);
    
    int array[5];
    int count = btree_to_array(tree, array, 5);
    
    assert(count == 5);
    assert(array[0] == 20);
    assert(array[1] == 30);
    assert(array[2] == 50);
    assert(array[3] == 70);
    assert(array[4] == 90);
    
    btree_destroy(tree);
    PASS();
    return 0;
}

int test_clear(void) {
    TEST("clear");
    
    BTree *tree = btree_create(3);
    
    btree_insert(tree, 10);
    btree_insert(tree, 20);
    btree_insert(tree, 30);
    
    assert(btree_size(tree) == 3);
    
    btree_clear(tree);
    
    assert(btree_is_empty(tree));
    assert(btree_size(tree) == 0);
    
    btree_destroy(tree);
    PASS();
    return 0;
}

int test_sequential_insert(void) {
    TEST("sequential insert (1-50)");
    
    BTree *tree = btree_create(3);
    
    for (int i = 1; i <= 50; i++) {
        btree_insert(tree, i);
    }
    
    assert(btree_size(tree) == 50);
    
    for (int i = 1; i <= 50; i++) {
        assert(btree_search(tree, i));
    }
    
    int min, max;
    btree_min(tree, &min);
    btree_max(tree, &max);
    assert(min == 1);
    assert(max == 50);
    
    btree_destroy(tree);
    PASS();
    return 0;
}

int test_complex_operations(void) {
    TEST("complex insert/delete sequence");
    
    BTree *tree = btree_create(3);
    
    for (int i = 1; i <= 100; i++) {
        btree_insert(tree, i);
    }
    
    assert(btree_size(tree) == 100);
    
    for (int i = 1; i <= 50; i++) {
        btree_delete(tree, i);
    }
    
    assert(btree_size(tree) == 50);
    
    for (int i = 51; i <= 100; i++) {
        assert(btree_search(tree, i));
    }
    
    for (int i = 1; i <= 50; i++) {
        assert(!btree_search(tree, i));
    }
    
    btree_destroy(tree);
    PASS();
    return 0;
}

int test_delete_all(void) {
    TEST("delete all keys");
    
    BTree *tree = btree_create(2);
    
    for (int i = 1; i <= 20; i++) {
        btree_insert(tree, i);
    }
    
    for (int i = 1; i <= 20; i++) {
        assert(btree_delete(tree, i) == 0);
    }
    
    assert(btree_is_empty(tree));
    assert(btree_size(tree) == 0);
    
    btree_destroy(tree);
    PASS();
    return 0;
}

int test_empty_operations(void) {
    TEST("operations on empty tree");
    
    BTree *tree = btree_create(3);
    
    int val;
    assert(btree_min(tree, &val) == -1);
    assert(btree_max(tree, &val) == -1);
    assert(btree_delete(tree, 10) == -1);
    assert(!btree_search(tree, 10));
    assert(btree_is_valid(tree));
    
    btree_destroy(tree);
    PASS();
    return 0;
}

int main(void) {
    printf("=== Running B-Tree Tests ===\n\n");
    
    int failed = 0;
    
    failed += test_create_destroy();
    failed += test_invalid_min_degree();
    failed += test_insert_and_search();
    failed += test_duplicate_insert();
    failed += test_delete();
    failed += test_min_max();
    failed += test_node_splitting();
    failed += test_traversal();
    failed += test_to_array();
    failed += test_clear();
    failed += test_sequential_insert();
    failed += test_complex_operations();
    failed += test_delete_all();
    failed += test_empty_operations();
    
    printf("\n");
    if (failed == 0) {
        printf("✓ All tests passed!\n");
    } else {
        printf("✗ %d test(s) failed\n", failed);
    }
    
    return failed;
}
