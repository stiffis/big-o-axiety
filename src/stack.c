#include "../include/stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_CAPACITY 16
#define GROWTH_FACTOR 2

struct Stack {
    int *data;
    size_t size;
    size_t capacity;
};

static int _stack_resize(struct Stack *stack, size_t new_capacity) {
    if (!stack || new_capacity < stack->size) {
        return -1;
    }
    
    int *new_data = realloc(stack->data, new_capacity * sizeof(int));
    if (!new_data) {
        return -1;
    }
    
    stack->data = new_data;
    stack->capacity = new_capacity;
    return 0;
}

Stack* stack_create(void) {
    return stack_create_with_capacity(DEFAULT_CAPACITY);
}

Stack* stack_create_with_capacity(size_t capacity) {
    if (capacity == 0) {
        capacity = DEFAULT_CAPACITY;
    }
    
    struct Stack *stack = malloc(sizeof(struct Stack));
    if (!stack) {
        return NULL;
    }
    
    stack->data = malloc(capacity * sizeof(int));
    if (!stack->data) {
        free(stack);
        return NULL;
    }
    
    stack->size = 0;
    stack->capacity = capacity;
    
    return stack;
}

void stack_destroy(Stack *stack) {
    if (!stack) {
        return;
    }
    
    free(stack->data);
    free(stack);
}

int stack_push(Stack *stack, int value) {
    if (!stack) {
        return -1;
    }
    
    if (stack->size >= stack->capacity) {
        size_t new_capacity = stack->capacity * GROWTH_FACTOR;
        if (_stack_resize(stack, new_capacity) != 0) {
            return -1;
        }
    }
    
    stack->data[stack->size] = value;
    stack->size++;
    
    return 0;
}

int stack_pop(Stack *stack, int *out_value) {
    if (!stack || !out_value || stack->size == 0) {
        return -1;
    }
    
    stack->size--;
    *out_value = stack->data[stack->size];
    
    return 0;
}

int stack_peek(const Stack *stack, int *out_value) {
    if (!stack || !out_value || stack->size == 0) {
        return -1;
    }
    
    *out_value = stack->data[stack->size - 1];
    return 0;
}

size_t stack_size(const Stack *stack) {
    if (!stack) {
        return 0;
    }
    
    return stack->size;
}

size_t stack_capacity(const Stack *stack) {
    if (!stack) {
        return 0;
    }
    
    return stack->capacity;
}

int stack_is_empty(const Stack *stack) {
    if (!stack) {
        return 1;
    }
    
    return stack->size == 0;
}

void stack_clear(Stack *stack) {
    if (!stack) {
        return;
    }
    
    stack->size = 0;
}

void stack_print(const Stack *stack) {
    if (!stack) {
        printf("NULL\n");
        return;
    }
    
    printf("[");
    for (size_t i = 0; i < stack->size; i++) {
        printf("%d", stack->data[i]);
        if (i < stack->size - 1) {
            printf(", ");
        }
    }
    printf("] (size: %zu, capacity: %zu, top: ", stack->size, stack->capacity);
    
    if (stack->size > 0) {
        printf("%d", stack->data[stack->size - 1]);
    } else {
        printf("empty");
    }
    printf(")\n");
}
