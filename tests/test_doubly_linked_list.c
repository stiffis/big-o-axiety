#include <stdio.h>
#include <assert.h>
#include "../include/doubly_linked_list.h"

#define TEST(name) printf("Testing %s... ", name)
#define PASS() printf("✓ PASS\n")

int test_create_destroy(void) {
    TEST("create and destroy");
    
    DoublyLinkedList *list = dlist_create();
    assert(list != NULL);
    assert(dlist_size(list) == 0);
    assert(dlist_is_empty(list) == 1);
    
    dlist_destroy(list);
    PASS();
    return 0;
}

int test_push_front(void) {
    TEST("push_front");
    
    DoublyLinkedList *list = dlist_create();
    
    dlist_push_front(list, 10);
    dlist_push_front(list, 20);
    dlist_push_front(list, 30);
    
    assert(dlist_size(list) == 3);
    
    int val;
    dlist_get(list, 0, &val);
    assert(val == 30);
    dlist_get(list, 1, &val);
    assert(val == 20);
    dlist_get(list, 2, &val);
    assert(val == 10);
    
    dlist_destroy(list);
    PASS();
    return 0;
}

int test_push_back(void) {
    TEST("push_back");
    
    DoublyLinkedList *list = dlist_create();
    
    dlist_push_back(list, 10);
    dlist_push_back(list, 20);
    dlist_push_back(list, 30);
    
    assert(dlist_size(list) == 3);
    
    int val;
    dlist_get(list, 0, &val);
    assert(val == 10);
    dlist_get(list, 1, &val);
    assert(val == 20);
    dlist_get(list, 2, &val);
    assert(val == 30);
    
    dlist_destroy(list);
    PASS();
    return 0;
}

int test_pop_front(void) {
    TEST("pop_front");
    
    DoublyLinkedList *list = dlist_create();
    
    dlist_push_back(list, 10);
    dlist_push_back(list, 20);
    dlist_push_back(list, 30);
    
    int val;
    dlist_pop_front(list, &val);
    assert(val == 10);
    assert(dlist_size(list) == 2);
    
    dlist_pop_front(list, &val);
    assert(val == 20);
    
    dlist_pop_front(list, &val);
    assert(val == 30);
    assert(dlist_is_empty(list) == 1);
    
    dlist_destroy(list);
    PASS();
    return 0;
}

int test_pop_back(void) {
    TEST("pop_back");
    
    DoublyLinkedList *list = dlist_create();
    
    dlist_push_back(list, 10);
    dlist_push_back(list, 20);
    dlist_push_back(list, 30);
    
    int val;
    dlist_pop_back(list, &val);
    assert(val == 30);
    assert(dlist_size(list) == 2);
    
    dlist_pop_back(list, &val);
    assert(val == 20);
    
    dlist_pop_back(list, &val);
    assert(val == 10);
    assert(dlist_is_empty(list) == 1);
    
    dlist_destroy(list);
    PASS();
    return 0;
}

int test_insert_at(void) {
    TEST("insert_at");
    
    DoublyLinkedList *list = dlist_create();
    
    dlist_push_back(list, 10);
    dlist_push_back(list, 30);
    
    dlist_insert_at(list, 1, 20);
    
    int val;
    dlist_get(list, 0, &val);
    assert(val == 10);
    dlist_get(list, 1, &val);
    assert(val == 20);
    dlist_get(list, 2, &val);
    assert(val == 30);
    
    assert(dlist_size(list) == 3);
    
    dlist_destroy(list);
    PASS();
    return 0;
}

int test_remove_at(void) {
    TEST("remove_at");
    
    DoublyLinkedList *list = dlist_create();
    
    dlist_push_back(list, 10);
    dlist_push_back(list, 20);
    dlist_push_back(list, 30);
    dlist_push_back(list, 40);
    
    int val;
    dlist_remove_at(list, 2, &val);
    assert(val == 30);
    assert(dlist_size(list) == 3);
    
    dlist_get(list, 0, &val);
    assert(val == 10);
    dlist_get(list, 1, &val);
    assert(val == 20);
    dlist_get(list, 2, &val);
    assert(val == 40);
    
    dlist_destroy(list);
    PASS();
    return 0;
}

int test_get_set(void) {
    TEST("get and set");
    
    DoublyLinkedList *list = dlist_create();
    
    dlist_push_back(list, 10);
    dlist_push_back(list, 20);
    dlist_push_back(list, 30);
    
    int val;
    dlist_get(list, 1, &val);
    assert(val == 20);
    
    dlist_set(list, 1, 99);
    dlist_get(list, 1, &val);
    assert(val == 99);
    
    dlist_destroy(list);
    PASS();
    return 0;
}

int test_find(void) {
    TEST("find");
    
    DoublyLinkedList *list = dlist_create();
    
    dlist_push_back(list, 10);
    dlist_push_back(list, 20);
    dlist_push_back(list, 30);
    
    assert(dlist_find(list, 10) == 0);
    assert(dlist_find(list, 20) == 1);
    assert(dlist_find(list, 30) == 2);
    assert(dlist_find(list, 99) == -1);
    
    dlist_destroy(list);
    PASS();
    return 0;
}

int test_clear(void) {
    TEST("clear");
    
    DoublyLinkedList *list = dlist_create();
    
    dlist_push_back(list, 10);
    dlist_push_back(list, 20);
    dlist_push_back(list, 30);
    
    assert(dlist_size(list) == 3);
    
    dlist_clear(list);
    
    assert(dlist_size(list) == 0);
    assert(dlist_is_empty(list) == 1);
    
    dlist_destroy(list);
    PASS();
    return 0;
}

int test_reverse(void) {
    TEST("reverse");
    
    DoublyLinkedList *list = dlist_create();
    
    dlist_push_back(list, 10);
    dlist_push_back(list, 20);
    dlist_push_back(list, 30);
    dlist_push_back(list, 40);
    
    dlist_reverse(list);
    
    int val;
    dlist_get(list, 0, &val);
    assert(val == 40);
    dlist_get(list, 1, &val);
    assert(val == 30);
    dlist_get(list, 2, &val);
    assert(val == 20);
    dlist_get(list, 3, &val);
    assert(val == 10);
    
    dlist_destroy(list);
    PASS();
    return 0;
}

int test_bidirectional_access(void) {
    TEST("bidirectional access");
    
    DoublyLinkedList *list = dlist_create();
    
    for (int i = 0; i < 10; i++) {
        dlist_push_back(list, i);
    }
    
    int val;
    dlist_get(list, 2, &val);
    assert(val == 2);
    
    dlist_get(list, 8, &val);
    assert(val == 8);
    
    dlist_destroy(list);
    PASS();
    return 0;
}

int test_error_handling(void) {
    TEST("error handling");
    
    DoublyLinkedList *list = dlist_create();
    
    int val;
    assert(dlist_pop_front(list, &val) == -1);
    assert(dlist_pop_back(list, &val) == -1);
    assert(dlist_get(list, 0, &val) == -1);
    assert(dlist_set(list, 0, 99) == -1);
    assert(dlist_remove_at(list, 0, &val) == -1);
    
    dlist_push_back(list, 10);
    assert(dlist_get(list, 10, &val) == -1);
    
    dlist_destroy(list);
    dlist_destroy(NULL);
    
    PASS();
    return 0;
}

int main(void) {
    printf("=== Running Doubly Linked List Tests ===\n\n");
    
    int failed = 0;
    
    failed += test_create_destroy();
    failed += test_push_front();
    failed += test_push_back();
    failed += test_pop_front();
    failed += test_pop_back();
    failed += test_insert_at();
    failed += test_remove_at();
    failed += test_get_set();
    failed += test_find();
    failed += test_clear();
    failed += test_reverse();
    failed += test_bidirectional_access();
    failed += test_error_handling();
    
    printf("\n");
    if (failed == 0) {
        printf("✓ All tests passed!\n");
    } else {
        printf("✗ %d test(s) failed\n", failed);
    }
    
    return failed;
}
