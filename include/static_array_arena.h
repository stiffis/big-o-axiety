#ifndef STATIC_ARRAY_ARENA_H
#define STATIC_ARRAY_ARENA_H

#include <stddef.h>
#include <stdint.h>

/** Bump allocator for O(1) allocations without fragmentation. */
typedef struct Arena Arena;
/** Static array that allocates from arena (no malloc per array). */
typedef struct StaticArrayArena StaticArrayArena;

/**
 * Creates an arena allocator.
 * @return Arena pointer or NULL on error
 */
Arena* arena_create(size_t capacity);

/** Frees all arena memory. */
void arena_destroy(Arena *arena);

/** Returns bytes used in arena. */
size_t arena_used(const Arena *arena);

/** Returns total capacity. */
size_t arena_capacity(const Arena *arena);

/** Resets arena (sets offset to 0, keeps capacity). */
void arena_reset(Arena *arena);

/**
 * Creates a static array that allocates from arena.
 * @return Array pointer or NULL if insufficient space
 */
StaticArrayArena* static_array_arena_create(Arena *arena, size_t capacity);

/** Sets element at index. @return 0 on success, -1 on error. */
int static_array_arena_set(StaticArrayArena *arr, size_t index, int value);

/** Gets value at index. @return 0 on success, -1 on error. */
int static_array_arena_get(const StaticArrayArena *arr, size_t index, int *out_value);

/** Fills array with value. @return 0 on success, -1 on error. */
int static_array_arena_fill(StaticArrayArena *arr, int value);

/** Clears array (sets elements to 0). */
void static_array_arena_clear(StaticArrayArena *arr);

/** Finds first occurrence of value. @return Index or -1. */
int static_array_arena_find(const StaticArrayArena *arr, int value);

/** Returns fixed capacity. */
size_t static_array_arena_capacity(const StaticArrayArena *arr);

/** Prints array for debugging. */
void static_array_arena_print(const StaticArrayArena *arr);

/** Prints detailed debug info. */
void static_array_arena_debug(const StaticArrayArena *arr);

#endif