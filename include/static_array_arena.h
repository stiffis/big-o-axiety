#ifndef STATIC_ARRAY_ARENA_H
#define STATIC_ARRAY_ARENA_H

#include <stddef.h>
#include <stdint.h>

typedef struct Arena Arena;
typedef struct StaticArrayArena StaticArrayArena;

Arena* arena_create(size_t capacity);

void arena_destroy(Arena *arena);

size_t arena_used(const Arena *arena);

size_t arena_capacity(const Arena *arena);

void arena_reset(Arena *arena);

StaticArrayArena* static_array_arena_create(Arena *arena, size_t capacity);

int static_array_arena_set(StaticArrayArena *arr, size_t index, int value);

int static_array_arena_get(const StaticArrayArena *arr, size_t index, int *out_value);

int static_array_arena_fill(StaticArrayArena *arr, int value);

void static_array_arena_clear(StaticArrayArena *arr);

int static_array_arena_find(const StaticArrayArena *arr, int value);

size_t static_array_arena_capacity(const StaticArrayArena *arr);

void static_array_arena_print(const StaticArrayArena *arr);

void static_array_arena_debug(const StaticArrayArena *arr);

#endif
