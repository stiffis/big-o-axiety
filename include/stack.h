#ifndef STACK_H
#define STACK_H

#include <stddef.h>

typedef struct Stack Stack;

Stack *stack_create(void);

Stack *stack_create_with_capacity(size_t capacity);

void stack_destroy(Stack *stack);

int stack_push(Stack *stack, int value);

int stack_pop(Stack *stack, int *out_value);

int stack_peek(const Stack *stack, int *out_value);

size_t stack_size(const Stack *stack);

size_t stack_capacity(const Stack *stack);

int stack_is_empty(const Stack *stack);

void stack_clear(Stack *stack);

void stack_print(const Stack *stack);

#endif // STACK_H
