#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../include/dyn_string.h"

#define TEST(name) printf("Testing %s... ", name)
#define PASS() printf("✓ PASS\n")
#define FAIL(msg) do { printf("✗ FAIL: %s\n", msg); return 1; } while(0)

int test_create_destroy(void) {
    TEST("create and destroy");
    
    String *str = string_create();
    assert(str != NULL);
    assert(string_length(str) == 0);
    assert(string_capacity(str) >= 32);
    assert(string_is_empty(str) == 1);
    assert(strcmp(string_cstr(str), "") == 0);
    
    string_destroy(str);
    PASS();
    return 0;
}

int test_create_from(void) {
    TEST("create from C-string");
    
    String *str = string_create_from("Hello, World!");
    assert(str != NULL);
    assert(string_length(str) == 13);
    assert(strcmp(string_cstr(str), "Hello, World!") == 0);
    
    string_destroy(str);
    PASS();
    return 0;
}

int test_push_and_get(void) {
    TEST("push and get");
    
    String *str = string_create();
    
    string_push(str, 'H');
    string_push(str, 'i');
    string_push(str, '!');
    
    assert(string_length(str) == 3);
    assert(strcmp(string_cstr(str), "Hi!") == 0);
    
    char ch;
    string_get(str, 0, &ch);
    assert(ch == 'H');
    
    string_get(str, 1, &ch);
    assert(ch == 'i');
    
    string_get(str, 2, &ch);
    assert(ch == '!');
    
    string_destroy(str);
    PASS();
    return 0;
}

int test_pop(void) {
    TEST("pop");
    
    String *str = string_create_from("ABC");
    
    char ch;
    string_pop(str, &ch);
    assert(ch == 'C');
    assert(string_length(str) == 2);
    assert(strcmp(string_cstr(str), "AB") == 0);
    
    string_pop(str, &ch);
    assert(ch == 'B');
    
    string_pop(str, &ch);
    assert(ch == 'A');
    assert(string_is_empty(str) == 1);
    
    string_destroy(str);
    PASS();
    return 0;
}

int test_append(void) {
    TEST("append");
    
    String *str = string_create_from("Hello");
    
    string_append(str, ", ");
    string_append(str, "World!");
    
    assert(string_length(str) == 13);
    assert(strcmp(string_cstr(str), "Hello, World!") == 0);
    
    string_destroy(str);
    PASS();
    return 0;
}

int test_concat(void) {
    TEST("concat");
    
    String *str1 = string_create_from("Hello");
    String *str2 = string_create_from(" World");
    
    string_concat(str1, str2);
    
    assert(string_length(str1) == 11);
    assert(strcmp(string_cstr(str1), "Hello World") == 0);
    
    string_destroy(str1);
    string_destroy(str2);
    PASS();
    return 0;
}

int test_insert(void) {
    TEST("insert");
    
    String *str = string_create_from("Hello World");
    
    string_insert(str, 5, ",");
    assert(strcmp(string_cstr(str), "Hello, World") == 0);
    
    string_insert(str, 0, ">>> ");
    assert(strcmp(string_cstr(str), ">>> Hello, World") == 0);
    
    string_insert_char(str, string_length(str), '!');
    assert(strcmp(string_cstr(str), ">>> Hello, World!") == 0);
    
    string_destroy(str);
    PASS();
    return 0;
}

int test_set(void) {
    TEST("set");
    
    String *str = string_create_from("Hello");
    
    string_set(str, 0, 'h');
    assert(strcmp(string_cstr(str), "hello") == 0);
    
    string_set(str, 4, '!');
    assert(strcmp(string_cstr(str), "hell!") == 0);
    
    string_destroy(str);
    PASS();
    return 0;
}

int test_find_char(void) {
    TEST("find_char");
    
    String *str = string_create_from("Hello World");
    
    assert(string_find_char(str, 'H') == 0);
    assert(string_find_char(str, 'W') == 6);
    assert(string_find_char(str, 'o') == 4);
    assert(string_find_char(str, 'z') == -1);
    
    string_destroy(str);
    PASS();
    return 0;
}

int test_find(void) {
    TEST("find substring");
    
    String *str = string_create_from("Hello World");
    
    assert(string_find(str, "Hello") == 0);
    assert(string_find(str, "World") == 6);
    assert(string_find(str, "o W") == 4);
    assert(string_find(str, "xyz") == -1);
    assert(string_find(str, "") == 0);
    
    string_destroy(str);
    PASS();
    return 0;
}

int test_compare_and_equals(void) {
    TEST("compare and equals");
    
    String *str1 = string_create_from("apple");
    String *str2 = string_create_from("banana");
    
    assert(string_compare(str1, "apple") == 0);
    assert(string_compare(str1, "banana") < 0);
    assert(string_compare(str2, "apple") > 0);
    
    assert(string_equals(str1, "apple") == 1);
    assert(string_equals(str1, "banana") == 0);
    
    string_destroy(str1);
    string_destroy(str2);
    PASS();
    return 0;
}

int test_substring(void) {
    TEST("substring");
    
    String *str = string_create_from("Hello World");
    
    String *sub1 = string_substring(str, 0, 5);
    assert(strcmp(string_cstr(sub1), "Hello") == 0);
    
    String *sub2 = string_substring(str, 6, 5);
    assert(strcmp(string_cstr(sub2), "World") == 0);
    
    String *sub3 = string_substring(str, 6, 100);
    assert(strcmp(string_cstr(sub3), "World") == 0);
    
    string_destroy(str);
    string_destroy(sub1);
    string_destroy(sub2);
    string_destroy(sub3);
    PASS();
    return 0;
}

int test_copy(void) {
    TEST("copy");
    
    String *str = string_create_from("Hello World");
    String *copy = string_copy(str);
    
    assert(str != copy);
    assert(string_cstr(str) != string_cstr(copy));
    assert(strcmp(string_cstr(str), string_cstr(copy)) == 0);
    
    string_push(copy, '!');
    assert(strcmp(string_cstr(str), "Hello World") == 0);
    assert(strcmp(string_cstr(copy), "Hello World!") == 0);
    
    string_destroy(str);
    string_destroy(copy);
    PASS();
    return 0;
}

int test_clear(void) {
    TEST("clear");
    
    String *str = string_create_from("Hello World");
    assert(string_length(str) == 11);
    
    size_t old_capacity = string_capacity(str);
    
    string_clear(str);
    assert(string_length(str) == 0);
    assert(string_is_empty(str) == 1);
    assert(strcmp(string_cstr(str), "") == 0);
    assert(string_capacity(str) == old_capacity);
    
    string_destroy(str);
    PASS();
    return 0;
}

int test_resize(void) {
    TEST("automatic resize");
    
    String *str = string_create_with_capacity(4);
    
    string_push(str, 'a');
    string_push(str, 'b');
    string_push(str, 'c');
    assert(string_capacity(str) == 4);
    
    string_push(str, 'd');
    assert(string_capacity(str) == 8);
    
    string_append(str, "efghij");
    assert(string_capacity(str) >= 10);
    assert(strcmp(string_cstr(str), "abcdefghij") == 0);
    
    string_destroy(str);
    PASS();
    return 0;
}

int test_error_handling(void) {
    TEST("error handling");
    
    String *str = string_create_from("Hello");
    
    char ch;
    assert(string_get(str, 100, &ch) == -1);
    assert(string_set(str, 100, 'x') == -1);
    assert(string_insert(str, 100, "x") == -1);
    assert(string_insert_char(str, 100, 'x') == -1);
    
    string_clear(str);
    assert(string_pop(str, &ch) == -1);
    
    assert(string_create_from(NULL) == NULL);
    
    string_destroy(str);
    string_destroy(NULL);
    
    PASS();
    return 0;
}

int main(void) {
    printf("=== Running String Tests ===\n\n");
    
    int failed = 0;
    
    failed += test_create_destroy();
    failed += test_create_from();
    failed += test_push_and_get();
    failed += test_pop();
    failed += test_append();
    failed += test_concat();
    failed += test_insert();
    failed += test_set();
    failed += test_find_char();
    failed += test_find();
    failed += test_compare_and_equals();
    failed += test_substring();
    failed += test_copy();
    failed += test_clear();
    failed += test_resize();
    failed += test_error_handling();
    
    printf("\n");
    if (failed == 0) {
        printf("✓ All tests passed!\n");
    } else {
        printf("✗ %d test(s) failed\n", failed);
    }
    
    return failed;
}
