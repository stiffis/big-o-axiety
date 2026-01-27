#include <stdio.h>
#include "../include/stack.h"

int main(void) {
    printf("=== Stack Demo ===\n\n");
    
    printf("1. Creating empty stack:\n");
    Stack *stack = stack_create();
    printf("Empty stack: ");
    stack_print(stack);
    printf("\n");
    
    printf("2. Pushing elements (LIFO):\n");
    stack_push(stack, 10);
    printf("After push(10): ");
    stack_print(stack);
    
    stack_push(stack, 20);
    printf("After push(20): ");
    stack_print(stack);
    
    stack_push(stack, 30);
    printf("After push(30): ");
    stack_print(stack);
    printf("\n");
    
    printf("3. Peeking at top:\n");
    int val;
    stack_peek(stack, &val);
    printf("Top element (peek): %d\n", val);
    printf("Stack after peek: ");
    stack_print(stack);
    printf("\n");
    
    printf("4. Popping elements (LIFO):\n");
    stack_pop(stack, &val);
    printf("Popped: %d, Stack now: ", val);
    stack_print(stack);
    
    stack_pop(stack, &val);
    printf("Popped: %d, Stack now: ", val);
    stack_print(stack);
    
    stack_pop(stack, &val);
    printf("Popped: %d, Stack now: ", val);
    stack_print(stack);
    printf("\n");
    
    printf("5. Checking empty stack:\n");
    printf("Is empty: %s\n\n", stack_is_empty(stack) ? "yes" : "no");
    
    printf("6. Demonstrating LIFO (Last In, First Out):\n");
    printf("Pushing: 1, 2, 3, 4, 5\n");
    stack_push(stack, 1);
    stack_push(stack, 2);
    stack_push(stack, 3);
    stack_push(stack, 4);
    stack_push(stack, 5);
    
    printf("Popping order: ");
    while (!stack_is_empty(stack)) {
        stack_pop(stack, &val);
        printf("%d ", val);
    }
    printf("(reversed order)\n\n");
    
    printf("7. Automatic resizing:\n");
    stack_clear(stack);
    Stack *small = stack_create_with_capacity(2);
    printf("Initial capacity: %zu\n", stack_capacity(small));
    
    small = stack_create_with_capacity(2);
    stack_push(small, 1);
    stack_push(small, 2);
    printf("After 2 pushes: capacity = %zu\n", stack_capacity(small));
    
    stack_push(small, 3);
    printf("After 3rd push:  capacity = %zu (auto-resized)\n", stack_capacity(small));
    stack_destroy(small);
    printf("\n");
    
    printf("8. Clear stack:\n");
    stack_push(stack, 10);
    stack_push(stack, 20);
    stack_push(stack, 30);
    printf("Before clear: ");
    stack_print(stack);
    
    stack_clear(stack);
    printf("After clear:  ");
    stack_print(stack);
    
    stack_destroy(stack);
    
    printf("\n=== Demo Complete ===\n");
    return 0;
}
