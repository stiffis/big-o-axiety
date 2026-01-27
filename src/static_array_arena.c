#include "../include/static_array_arena.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Arena {
    unsigned char *buffer;
    size_t capacity;
    size_t used;
};

struct StaticArrayArena {
    int *data;
    size_t capacity;
    Arena *arena;
};

Arena* arena_create(size_t capacity) {
    if (capacity == 0) {
        return NULL;
    }
    
    Arena *arena = malloc(sizeof(Arena));
    if (!arena) {
        return NULL;
    }
    
    arena->buffer = malloc(capacity);
    if (!arena->buffer) {
        free(arena);
        return NULL;
    }
    
    arena->capacity = capacity;
    arena->used = 0;
    
    return arena;
}

void arena_destroy(Arena *arena) {
    if (!arena) {
        return;
    }
    
    free(arena->buffer);
    free(arena);
}

size_t arena_used(const Arena *arena) {
    if (!arena) {
        return 0;
    }
    
    return arena->used;
}

size_t arena_capacity(const Arena *arena) {
    if (!arena) {
        return 0;
    }
    
    return arena->capacity;
}

void arena_reset(Arena *arena) {
    if (!arena) {
        return;
    }
    
    arena->used = 0;
}

static void* arena_alloc(Arena *arena, size_t size, size_t align) {
    if (!arena || size == 0) {
        return NULL;
    }
    
    size_t padding = 0;
    size_t current = arena->used;
    
    if (align > 0 && (current % align) != 0) {
        padding = align - (current % align);
    }
    
    size_t required = current + padding + size;
    if (required > arena->capacity) {
        return NULL;
    }
    
    void *ptr = arena->buffer + current + padding;
    arena->used = required;
    
    return ptr;
}

StaticArrayArena* static_array_arena_create(Arena *arena, size_t capacity) {
    if (!arena || capacity == 0) {
        return NULL;
    }
    
    size_t struct_size = sizeof(StaticArrayArena);
    size_t data_size = sizeof(int) * capacity;
    size_t total_size = struct_size + data_size;
    
    if (arena->used + total_size > arena->capacity) {
        return NULL;
    }
    
    StaticArrayArena *arr = (StaticArrayArena*)arena_alloc(arena, struct_size, sizeof(void*));
    if (!arr) {
        return NULL;
    }
    
    arr->data = (int*)arena_alloc(arena, data_size, sizeof(int));
    if (!arr->data) {
        return NULL;
    }
    
    arr->capacity = capacity;
    arr->arena = arena;
    
    memset(arr->data, 0, data_size);
    
    return arr;
}

int static_array_arena_set(StaticArrayArena *arr, size_t index, int value) {
    if (!arr || index >= arr->capacity) {
        return -1;
    }
    
    arr->data[index] = value;
    return 0;
}

int static_array_arena_get(const StaticArrayArena *arr, size_t index, int *out_value) {
    if (!arr || !out_value || index >= arr->capacity) {
        return -1;
    }
    
    *out_value = arr->data[index];
    return 0;
}

int static_array_arena_fill(StaticArrayArena *arr, int value) {
    if (!arr) {
        return -1;
    }
    
    for (size_t i = 0; i < arr->capacity; i++) {
        arr->data[i] = value;
    }
    
    return 0;
}

void static_array_arena_clear(StaticArrayArena *arr) {
    if (!arr) {
        return;
    }
    
    memset(arr->data, 0, arr->capacity * sizeof(int));
}

int static_array_arena_find(const StaticArrayArena *arr, int value) {
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

size_t static_array_arena_capacity(const StaticArrayArena *arr) {
    if (!arr) {
        return 0;
    }
    
    return arr->capacity;
}

void static_array_arena_print(const StaticArrayArena *arr) {
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
    printf("]\n");
}

void static_array_arena_debug(const StaticArrayArena *arr) {
    if (!arr) {
        printf("StaticArrayArena(NULL)\n");
        return;
    }
    
    printf("StaticArrayArena(capacity: %zu, arena_used: %zu/%zu) ",
           arr->capacity, arena_used(arr->arena), arena_capacity(arr->arena));
    static_array_arena_print(arr);
}
