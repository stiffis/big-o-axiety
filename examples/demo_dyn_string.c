#include <stdio.h>
#include "../include/dyn_string.h"

int main(void) {
    printf("=== Dynamic String Demo ===\n\n");
    
    // Create empty string
    printf("1. Creating empty string:\n");
    String *str1 = string_create();
    string_debug(str1);
    printf("\n");
    
    // Create from literal
    printf("2. Creating from literal:\n");
    String *str2 = string_create_from("Hello, World!");
    string_debug(str2);
    printf("\n");
    
    // Push characters
    printf("3. Pushing characters:\n");
    String *str3 = string_create();
    string_push(str3, 'C');
    string_push(str3, ' ');
    string_push(str3, 'i');
    string_push(str3, 's');
    string_push(str3, ' ');
    string_push(str3, 'f');
    string_push(str3, 'u');
    string_push(str3, 'n');
    string_push(str3, '!');
    printf("After pushing: ");
    string_debug(str3);
    printf("\n");
    
    // Append
    printf("4. Appending strings:\n");
    String *greeting = string_create_from("Hello");
    printf("Initial: ");
    string_print(greeting);
    printf("\n");
    
    string_append(greeting, ", ");
    string_append(greeting, "World");
    string_push(greeting, '!');
    printf("After appending: ");
    string_print(greeting);
    printf("\n\n");
    
    // Concatenation
    printf("5. Concatenating two strings:\n");
    String *first = string_create_from("Data ");
    String *second = string_create_from("Structures");
    printf("First: ");
    string_print(first);
    printf("\nSecond: ");
    string_print(second);
    
    string_concat(first, second);
    printf("\nConcatenated: ");
    string_print(first);
    printf("\n\n");
    
    // Insert
    printf("6. Inserting text:\n");
    String *sentence = string_create_from("I  C!");
    printf("Before: ");
    string_print(sentence);
    
    string_insert(sentence, 2, "love");
    printf("\nAfter inserting 'love': ");
    string_print(sentence);
    printf("\n\n");
    
    // Find
    printf("7. Finding substrings:\n");
    String *text = string_create_from("The quick brown fox jumps over the lazy dog");
    printf("Text: ");
    string_print(text);
    printf("\n");
    
    int pos1 = string_find(text, "fox");
    printf("Position of 'fox': %d\n", pos1);
    
    int pos2 = string_find(text, "dog");
    printf("Position of 'dog': %d\n", pos2);
    
    int pos3 = string_find(text, "cat");
    printf("Position of 'cat': %d (not found)\n\n", pos3);
    
    // Substring
    printf("8. Creating substrings:\n");
    String *original = string_create_from("Hello, World!");
    printf("Original: ");
    string_print(original);
    printf("\n");
    
    String *sub1 = string_substring(original, 0, 5);
    printf("Substring [0, 5): ");
    string_print(sub1);
    printf("\n");
    
    String *sub2 = string_substring(original, 7, 5);
    printf("Substring [7, 12): ");
    string_print(sub2);
    printf("\n\n");
    
    // Comparison
    printf("9. Comparing strings:\n");
    String *apple = string_create_from("apple");
    String *banana = string_create_from("banana");
    
    printf("Comparing 'apple' and 'apple': %s\n", 
           string_equals(apple, "apple") ? "equal" : "not equal");
    printf("Comparing 'apple' and 'banana': %s\n",
           string_equals(apple, "banana") ? "equal" : "not equal");
    
    int cmp = string_compare(apple, "banana");
    printf("'apple' vs 'banana': %s\n", 
           cmp < 0 ? "apple < banana" : "apple >= banana");
    printf("\n");
    
    // Pop
    printf("10. Popping characters:\n");
    String *stack = string_create_from("ABC");
    printf("Initial: ");
    string_print(stack);
    printf("\n");
    
    char ch;
    while (!string_is_empty(stack)) {
        string_pop(stack, &ch);
        printf("Popped: '%c', Remaining: ", ch);
        string_print(stack);
        printf("\n");
    }
    printf("\n");
    
    // Copy
    printf("11. Copying strings:\n");
    String *orig = string_create_from("Original");
    String *copy = string_copy(orig);
    
    printf("Original: ");
    string_print(orig);
    printf("\nCopy: ");
    string_print(copy);
    
    string_append(copy, " (modified)");
    printf("\n\nAfter modifying copy:\n");
    printf("Original: ");
    string_print(orig);
    printf("\nCopy: ");
    string_print(copy);
    printf("\n\n");
    
    // Clear
    printf("12. Clearing string:\n");
    String *temp = string_create_from("This will be cleared");
    printf("Before clear: ");
    string_debug(temp);
    
    string_clear(temp);
    printf("After clear: ");
    string_debug(temp);
    printf("Is empty: %s\n\n", string_is_empty(temp) ? "yes" : "no");
    
    // Cleanup
    string_destroy(str1);
    string_destroy(str2);
    string_destroy(str3);
    string_destroy(greeting);
    string_destroy(first);
    string_destroy(second);
    string_destroy(sentence);
    string_destroy(text);
    string_destroy(original);
    string_destroy(sub1);
    string_destroy(sub2);
    string_destroy(apple);
    string_destroy(banana);
    string_destroy(stack);
    string_destroy(orig);
    string_destroy(copy);
    string_destroy(temp);
    
    printf("=== Demo Complete ===\n");
    return 0;
}
