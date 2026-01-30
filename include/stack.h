#ifndef STACK_H
#define STACK_H

#include <stddef.h>

/** LIFO data structure (Last In, First Out). */
typedef struct Stack Stack;

/** Creates an empty stack (default capacity 16). @return Stack or NULL. */
Stack *stack_create(void);

/** Creates a stack with specific capacity. @return Stack or NULL. */
Stack *stack_create_with_capacity(size_t capacity);

/** Frees all stack memory. */
void stack_destroy(Stack *stack);

/** Pushes element onto stack. @return 0 on success, -1 on error. */
int stack_push(Stack *stack, int value);

/** Pops element from stack. @return 0 on success, -1 on error. */
int stack_pop(Stack *stack, int *out_value);

/** Views top element without removing. @return 0 on success, -1 on error. */
int stack_peek(const Stack *stack, int *out_value);

/** Returns number of elements. */
size_t stack_size(const Stack *stack);

/** Returns total capacity. */
size_t stack_capacity(const Stack *stack);

/** Checks if stack is empty. @return 1 if empty, 0 otherwise. */
int stack_is_empty(const Stack *stack);

/** Removes all elements (keeps capacity). */
void stack_clear(Stack *stack);

/** Prints stack for debugging. */
void stack_print(const Stack *stack);

#endif // STACK_H