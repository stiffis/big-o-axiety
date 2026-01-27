#include <stdio.h>
#include <assert.h>
#include "../include/avl.h"

#define TEST(name) printf("Testing %s... ", name)
#define PASS() printf("✓ PASS\n")

static void collect_keys(int key, void *user_data) {
    int **arr_ptr = (int **)user_data;
    **arr_ptr = key;
    (*arr_ptr)++;
}

int test_create_destroy(void) {
    TEST("create and destroy");
    
    AVL *tree = avl_create();
    assert(tree != NULL);
    assert(avl_is_empty(tree));
    assert(avl_size(tree) == 0);
    assert(avl_height(tree) == 0);
    
    avl_destroy(tree);
    PASS();
    return 0;
}

int test_insert_and_search(void) {
    TEST("insert and search");
    
    AVL *tree = avl_create();
    
    assert(avl_insert(tree, 10) == 0);
    assert(avl_insert(tree, 20) == 0);
    assert(avl_insert(tree, 5) == 0);
    
    assert(avl_size(tree) == 3);
    assert(avl_search(tree, 10));
    assert(avl_search(tree, 20));
    assert(avl_search(tree, 5));
    assert(!avl_search(tree, 99));
    
    avl_destroy(tree);
    PASS();
    return 0;
}

int test_duplicate_insert(void) {
    TEST("duplicate insert rejection");
    
    AVL *tree = avl_create();
    
    assert(avl_insert(tree, 10) == 0);
    assert(avl_insert(tree, 10) == -1);
    assert(avl_size(tree) == 1);
    
    avl_destroy(tree);
    PASS();
    return 0;
}

int test_delete(void) {
    TEST("delete");
    
    AVL *tree = avl_create();
    
    avl_insert(tree, 10);
    avl_insert(tree, 20);
    avl_insert(tree, 5);
    avl_insert(tree, 15);
    
    assert(avl_delete(tree, 20) == 0);
    assert(avl_size(tree) == 3);
    assert(!avl_search(tree, 20));
    assert(avl_search(tree, 10));
    
    assert(avl_delete(tree, 99) == -1);
    
    avl_destroy(tree);
    PASS();
    return 0;
}

int test_min_max(void) {
    TEST("min and max");
    
    AVL *tree = avl_create();
    
    avl_insert(tree, 50);
    avl_insert(tree, 30);
    avl_insert(tree, 70);
    avl_insert(tree, 20);
    avl_insert(tree, 90);
    
    int min, max;
    assert(avl_min(tree, &min) == 0);
    assert(min == 20);
    
    assert(avl_max(tree, &max) == 0);
    assert(max == 90);
    
    avl_destroy(tree);
    PASS();
    return 0;
}

int test_balancing(void) {
    TEST("self-balancing (LL rotation)");
    
    AVL *tree = avl_create();
    
    avl_insert(tree, 30);
    avl_insert(tree, 20);
    avl_insert(tree, 10);
    
    assert(avl_is_balanced(tree));
    assert(avl_height(tree) == 2);
    
    avl_destroy(tree);
    PASS();
    return 0;
}

int test_balancing_rr(void) {
    TEST("self-balancing (RR rotation)");
    
    AVL *tree = avl_create();
    
    avl_insert(tree, 10);
    avl_insert(tree, 20);
    avl_insert(tree, 30);
    
    assert(avl_is_balanced(tree));
    assert(avl_height(tree) == 2);
    
    avl_destroy(tree);
    PASS();
    return 0;
}

int test_balancing_lr(void) {
    TEST("self-balancing (LR rotation)");
    
    AVL *tree = avl_create();
    
    avl_insert(tree, 30);
    avl_insert(tree, 10);
    avl_insert(tree, 20);
    
    assert(avl_is_balanced(tree));
    assert(avl_height(tree) == 2);
    
    avl_destroy(tree);
    PASS();
    return 0;
}

int test_balancing_rl(void) {
    TEST("self-balancing (RL rotation)");
    
    AVL *tree = avl_create();
    
    avl_insert(tree, 10);
    avl_insert(tree, 30);
    avl_insert(tree, 20);
    
    assert(avl_is_balanced(tree));
    assert(avl_height(tree) == 2);
    
    avl_destroy(tree);
    PASS();
    return 0;
}

int test_inorder_traversal(void) {
    TEST("in-order traversal");
    
    AVL *tree = avl_create();
    
    avl_insert(tree, 50);
    avl_insert(tree, 30);
    avl_insert(tree, 70);
    avl_insert(tree, 20);
    avl_insert(tree, 40);
    
    int expected[] = {20, 30, 40, 50, 70};
    int result[5];
    int *ptr = result;
    
    avl_inorder(tree, collect_keys, &ptr);
    
    for (int i = 0; i < 5; i++) {
        assert(result[i] == expected[i]);
    }
    
    avl_destroy(tree);
    PASS();
    return 0;
}

int test_to_array(void) {
    TEST("to array conversion");
    
    AVL *tree = avl_create();
    
    avl_insert(tree, 50);
    avl_insert(tree, 30);
    avl_insert(tree, 70);
    avl_insert(tree, 20);
    avl_insert(tree, 90);
    
    int array[5];
    int count = avl_to_array(tree, array, 5);
    
    assert(count == 5);
    assert(array[0] == 20);
    assert(array[1] == 30);
    assert(array[2] == 50);
    assert(array[3] == 70);
    assert(array[4] == 90);
    
    avl_destroy(tree);
    PASS();
    return 0;
}

int test_clear(void) {
    TEST("clear");
    
    AVL *tree = avl_create();
    
    avl_insert(tree, 10);
    avl_insert(tree, 20);
    avl_insert(tree, 30);
    
    assert(avl_size(tree) == 3);
    
    avl_clear(tree);
    
    assert(avl_is_empty(tree));
    assert(avl_size(tree) == 0);
    
    avl_destroy(tree);
    PASS();
    return 0;
}

int test_complex_operations(void) {
    TEST("complex insert/delete sequence");
    
    AVL *tree = avl_create();
    
    for (int i = 1; i <= 100; i++) {
        avl_insert(tree, i);
    }
    
    assert(avl_size(tree) == 100);
    assert(avl_is_balanced(tree));
    
    for (int i = 1; i <= 50; i++) {
        avl_delete(tree, i);
    }
    
    assert(avl_size(tree) == 50);
    assert(avl_is_balanced(tree));
    
    for (int i = 51; i <= 100; i++) {
        assert(avl_search(tree, i));
    }
    
    avl_destroy(tree);
    PASS();
    return 0;
}

int test_empty_operations(void) {
    TEST("operations on empty tree");
    
    AVL *tree = avl_create();
    
    int val;
    assert(avl_min(tree, &val) == -1);
    assert(avl_max(tree, &val) == -1);
    assert(avl_delete(tree, 10) == -1);
    assert(!avl_search(tree, 10));
    assert(avl_is_balanced(tree));
    
    avl_destroy(tree);
    PASS();
    return 0;
}

int main(void) {
    printf("=== Running AVL Tree Tests ===\n\n");
    
    int failed = 0;
    
    failed += test_create_destroy();
    failed += test_insert_and_search();
    failed += test_duplicate_insert();
    failed += test_delete();
    failed += test_min_max();
    failed += test_balancing();
    failed += test_balancing_rr();
    failed += test_balancing_lr();
    failed += test_balancing_rl();
    failed += test_inorder_traversal();
    failed += test_to_array();
    failed += test_clear();
    failed += test_complex_operations();
    failed += test_empty_operations();
    
    printf("\n");
    if (failed == 0) {
        printf("✓ All tests passed!\n");
    } else {
        printf("✗ %d test(s) failed\n", failed);
    }
    
    return failed;
}
