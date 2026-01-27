#include "../include/array.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_CAPACITY 16
#define GROWTH_FACTOR 2

struct DynamicArray {
    int *data;
    size_t size;
    size_t capacity;
};

static int _array_resize(struct DynamicArray *arr, size_t new_capacity) {
    if (!arr || new_capacity < arr->size) {
        return -1;
    }
    
    int *new_data = realloc(arr->data, new_capacity * sizeof(int));
    if (!new_data) {
        return -1;
    }
    
    arr->data = new_data;
    arr->capacity = new_capacity;
    return 0;
}

DynamicArray* array_create(size_t capacity) {
    if (capacity == 0) {
        capacity = DEFAULT_CAPACITY;
    }
    
    struct DynamicArray *arr = malloc(sizeof(struct DynamicArray));
    if (!arr) {
        return NULL;
    }
    
    arr->data = malloc(capacity * sizeof(int));
    if (!arr->data) {
        free(arr);
        return NULL;
    }
    
    arr->size = 0;
    arr->capacity = capacity;
    
    return arr;
}

void array_destroy(DynamicArray *arr) {
    if (!arr) {
        return;
    }
    
    free(arr->data);
    free(arr);
}

int array_push(DynamicArray *arr, int value) {
    if (!arr) {
        return -1;
    }
    
    if (arr->size >= arr->capacity) {
        size_t new_capacity = arr->capacity * GROWTH_FACTOR;
        if (_array_resize(arr, new_capacity) != 0) {
            return -1;
        }
    }
    
    arr->data[arr->size] = value;
    arr->size++;
    
    return 0;
}

int array_pop(DynamicArray *arr, int *out_value) {
    if (!arr || !out_value || arr->size == 0) {
        return -1;
    }
    
    arr->size--;
    *out_value = arr->data[arr->size];
    
    return 0;
}

int array_insert(DynamicArray *arr, size_t index, int value) {
    if (!arr || index > arr->size) {
        return -1;
    }
    
    if (arr->size >= arr->capacity) {
        size_t new_capacity = arr->capacity * GROWTH_FACTOR;
        if (_array_resize(arr, new_capacity) != 0) {
            return -1;
        }
    }
    
    memmove(&arr->data[index + 1], &arr->data[index], 
            (arr->size - index) * sizeof(int));
    
    arr->data[index] = value;
    arr->size++;
    
    return 0;
}

int array_remove(DynamicArray *arr, size_t index, int *out_value) {
    if (!arr || index >= arr->size) {
        return -1;
    }
    
    if (out_value) {
        *out_value = arr->data[index];
    }
    
    memmove(&arr->data[index], &arr->data[index + 1],
            (arr->size - index - 1) * sizeof(int));
    
    arr->size--;
    
    return 0;
}

int array_set(DynamicArray *arr, size_t index, int value) {
    if (!arr || index >= arr->size) {
        return -1;
    }
    
    arr->data[index] = value;
    
    return 0;
}

void array_clear(DynamicArray *arr) {
    if (!arr) {
        return;
    }
    
    arr->size = 0;
}

int array_get(const DynamicArray *arr, size_t index, int *out_value) {
    if (!arr || !out_value || index >= arr->size) {
        return -1;
    }
    
    *out_value = arr->data[index];
    
    return 0;
}

size_t array_size(const DynamicArray *arr) {
    if (!arr) {
        return 0;
    }
    
    return arr->size;
}

size_t array_capacity(const DynamicArray *arr) {
    if (!arr) {
        return 0;
    }
    
    return arr->capacity;
}

int array_is_empty(const DynamicArray *arr) {
    if (!arr) {
        return 1;
    }
    
    return arr->size == 0;
}

int array_find(const DynamicArray *arr, int value) {
    if (!arr) {
        return -1;
    }
    
    for (size_t i = 0; i < arr->size; i++) {
        if (arr->data[i] == value) {
            return (int)i;
        }
    }
    
    return -1;
}

void array_print(const DynamicArray *arr) {
    if (!arr) {
        printf("NULL\n");
        return;
    }
    
    printf("[");
    for (size_t i = 0; i < arr->size; i++) {
        printf("%d", arr->data[i]);
        if (i < arr->size - 1) {
            printf(", ");
        }
    }
    printf("] (size: %zu, capacity: %zu)\n", arr->size, arr->capacity);
}
