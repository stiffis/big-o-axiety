#include <stdio.h>
#include <assert.h>
#include "../include/singly_linked_list.h"

#define TEST(name) printf("Testing %s... ", name)
#define PASS() printf("✓ PASS\n")

int test_create_destroy(void) {
    TEST("create and destroy");
    
    SinglyLinkedList *list = slist_create();
    assert(list != NULL);
    assert(slist_size(list) == 0);
    assert(slist_is_empty(list) == 1);
    
    slist_destroy(list);
    PASS();
    return 0;
}

int test_push_front(void) {
    TEST("push_front");
    
    SinglyLinkedList *list = slist_create();
    
    slist_push_front(list, 10);
    slist_push_front(list, 20);
    slist_push_front(list, 30);
    
    assert(slist_size(list) == 3);
    
    int val;
    slist_get(list, 0, &val);
    assert(val == 30);
    
    slist_get(list, 1, &val);
    assert(val == 20);
    
    slist_get(list, 2, &val);
    assert(val == 10);
    
    slist_destroy(list);
    PASS();
    return 0;
}

int test_push_back(void) {
    TEST("push_back");
    
    SinglyLinkedList *list = slist_create();
    
    slist_push_back(list, 10);
    slist_push_back(list, 20);
    slist_push_back(list, 30);
    
    assert(slist_size(list) == 3);
    
    int val;
    slist_get(list, 0, &val);
    assert(val == 10);
    
    slist_get(list, 1, &val);
    assert(val == 20);
    
    slist_get(list, 2, &val);
    assert(val == 30);
    
    slist_destroy(list);
    PASS();
    return 0;
}

int test_pop_front(void) {
    TEST("pop_front");
    
    SinglyLinkedList *list = slist_create();
    
    slist_push_back(list, 10);
    slist_push_back(list, 20);
    slist_push_back(list, 30);
    
    int val;
    slist_pop_front(list, &val);
    assert(val == 10);
    assert(slist_size(list) == 2);
    
    slist_pop_front(list, &val);
    assert(val == 20);
    
    slist_pop_front(list, &val);
    assert(val == 30);
    assert(slist_is_empty(list) == 1);
    
    slist_destroy(list);
    PASS();
    return 0;
}

int test_pop_back(void) {
    TEST("pop_back");
    
    SinglyLinkedList *list = slist_create();
    
    slist_push_back(list, 10);
    slist_push_back(list, 20);
    slist_push_back(list, 30);
    
    int val;
    slist_pop_back(list, &val);
    assert(val == 30);
    assert(slist_size(list) == 2);
    
    slist_pop_back(list, &val);
    assert(val == 20);
    
    slist_pop_back(list, &val);
    assert(val == 10);
    assert(slist_is_empty(list) == 1);
    
    slist_destroy(list);
    PASS();
    return 0;
}

int test_insert_after(void) {
    TEST("insert_after");
    
    SinglyLinkedList *list = slist_create();
    
    slist_push_back(list, 10);
    slist_push_back(list, 30);
    
    slist_insert_after(list, 0, 20);
    
    int val;
    slist_get(list, 0, &val);
    assert(val == 10);
    slist_get(list, 1, &val);
    assert(val == 20);
    slist_get(list, 2, &val);
    assert(val == 30);
    
    assert(slist_size(list) == 3);
    
    slist_destroy(list);
    PASS();
    return 0;
}

int test_remove_at(void) {
    TEST("remove_at");
    
    SinglyLinkedList *list = slist_create();
    
    slist_push_back(list, 10);
    slist_push_back(list, 20);
    slist_push_back(list, 30);
    slist_push_back(list, 40);
    
    int val;
    slist_remove_at(list, 1, &val);
    assert(val == 20);
    assert(slist_size(list) == 3);
    
    slist_get(list, 0, &val);
    assert(val == 10);
    slist_get(list, 1, &val);
    assert(val == 30);
    slist_get(list, 2, &val);
    assert(val == 40);
    
    slist_destroy(list);
    PASS();
    return 0;
}

int test_get_set(void) {
    TEST("get and set");
    
    SinglyLinkedList *list = slist_create();
    
    slist_push_back(list, 10);
    slist_push_back(list, 20);
    slist_push_back(list, 30);
    
    int val;
    slist_get(list, 1, &val);
    assert(val == 20);
    
    slist_set(list, 1, 99);
    slist_get(list, 1, &val);
    assert(val == 99);
    
    slist_destroy(list);
    PASS();
    return 0;
}

int test_find(void) {
    TEST("find");
    
    SinglyLinkedList *list = slist_create();
    
    slist_push_back(list, 10);
    slist_push_back(list, 20);
    slist_push_back(list, 30);
    
    assert(slist_find(list, 10) == 0);
    assert(slist_find(list, 20) == 1);
    assert(slist_find(list, 30) == 2);
    assert(slist_find(list, 99) == -1);
    
    slist_destroy(list);
    PASS();
    return 0;
}

int test_clear(void) {
    TEST("clear");
    
    SinglyLinkedList *list = slist_create();
    
    slist_push_back(list, 10);
    slist_push_back(list, 20);
    slist_push_back(list, 30);
    
    assert(slist_size(list) == 3);
    
    slist_clear(list);
    
    assert(slist_size(list) == 0);
    assert(slist_is_empty(list) == 1);
    
    slist_destroy(list);
    PASS();
    return 0;
}

int test_reverse(void) {
    TEST("reverse");
    
    SinglyLinkedList *list = slist_create();
    
    slist_push_back(list, 10);
    slist_push_back(list, 20);
    slist_push_back(list, 30);
    slist_push_back(list, 40);
    
    slist_reverse(list);
    
    int val;
    slist_get(list, 0, &val);
    assert(val == 40);
    slist_get(list, 1, &val);
    assert(val == 30);
    slist_get(list, 2, &val);
    assert(val == 20);
    slist_get(list, 3, &val);
    assert(val == 10);
    
    slist_destroy(list);
    PASS();
    return 0;
}

int test_error_handling(void) {
    TEST("error handling");
    
    SinglyLinkedList *list = slist_create();
    
    int val;
    assert(slist_pop_front(list, &val) == -1);
    assert(slist_pop_back(list, &val) == -1);
    assert(slist_get(list, 0, &val) == -1);
    assert(slist_set(list, 0, 99) == -1);
    assert(slist_remove_at(list, 0, &val) == -1);
    
    slist_push_back(list, 10);
    assert(slist_get(list, 10, &val) == -1);
    
    slist_destroy(list);
    slist_destroy(NULL);
    
    PASS();
    return 0;
}

int main(void) {
    printf("=== Running Singly Linked List Tests ===\n\n");
    
    int failed = 0;
    
    failed += test_create_destroy();
    failed += test_push_front();
    failed += test_push_back();
    failed += test_pop_front();
    failed += test_pop_back();
    failed += test_insert_after();
    failed += test_remove_at();
    failed += test_get_set();
    failed += test_find();
    failed += test_clear();
    failed += test_reverse();
    failed += test_error_handling();
    
    printf("\n");
    if (failed == 0) {
        printf("✓ All tests passed!\n");
    } else {
        printf("✗ %d test(s) failed\n", failed);
    }
    
    return failed;
}
