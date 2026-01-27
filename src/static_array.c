#include "../include/static_array.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct StaticArray {
    int *data;
    size_t capacity;
};

StaticArray* static_array_create(size_t capacity) {
    if (capacity == 0) {
        return NULL;
    }
    
    struct StaticArray *arr = malloc(sizeof(struct StaticArray));
    if (!arr) {
        return NULL;
    }
    
    arr->data = malloc(capacity * sizeof(int));
    if (!arr->data) {
        free(arr);
        return NULL;
    }
    
    arr->capacity = capacity;
    
    memset(arr->data, 0, capacity * sizeof(int));
    
    return arr;
}

void static_array_destroy(StaticArray *arr) {
    if (!arr) {
        return;
    }
    
    free(arr->data);
    free(arr);
}

int static_array_set(StaticArray *arr, size_t index, int value) {
    if (!arr || index >= arr->capacity) {
        return -1;
    }
    
    arr->data[index] = value;
    return 0;
}

int static_array_fill(StaticArray *arr, int value) {
    if (!arr) {
        return -1;
    }
    
    for (size_t i = 0; i < arr->capacity; i++) {
        arr->data[i] = value;
    }
    
    return 0;
}

void static_array_clear(StaticArray *arr) {
    if (!arr) {
        return;
    }
    
    memset(arr->data, 0, arr->capacity * sizeof(int));
}

int static_array_get(const StaticArray *arr, size_t index, int *out_value) {
    if (!arr || !out_value || index >= arr->capacity) {
        return -1;
    }
    
    *out_value = arr->data[index];
    return 0;
}

size_t static_array_capacity(const StaticArray *arr) {
    if (!arr) {
        return 0;
    }
    
    return arr->capacity;
}

int static_array_find(const StaticArray *arr, int value) {
    if (!arr) {
        return -1;
    }
    
    for (size_t i = 0; i < arr->capacity; i++) {
        if (arr->data[i] == value) {
            return (int)i;
        }
    }
    
    return -1;
}

int static_array_copy(StaticArray *dest, const StaticArray *src) {
    if (!dest || !src || dest->capacity != src->capacity) {
        return -1;
    }
    
    memcpy(dest->data, src->data, src->capacity * sizeof(int));
    return 0;
}

int static_array_reverse(StaticArray *arr) {
    if (!arr) {
        return -1;
    }
    
    size_t left = 0;
    size_t right = arr->capacity - 1;
    
    while (left < right) {
        int temp = arr->data[left];
        arr->data[left] = arr->data[right];
        arr->data[right] = temp;
        
        left++;
        right--;
    }
    
    return 0;
}

void static_array_print(const StaticArray *arr) {
    if (!arr) {
        printf("NULL\n");
        return;
    }
    
    printf("[");
    for (size_t i = 0; i < arr->capacity; i++) {
        printf("%d", arr->data[i]);
        if (i < arr->capacity - 1) {
            printf(", ");
        }
    }
    printf("] (capacity: %zu)\n", arr->capacity);
}
