#ifndef STATIC_ARRAY_H
#define STATIC_ARRAY_H

#include <stddef.h>

/**
 * Fixed-size array (no dynamic resizing).
 */
typedef struct StaticArray StaticArray;

/**
 * Creates a static array with fixed capacity.
 * @return Array pointer or NULL on error
 */
StaticArray* static_array_create(size_t capacity);

/**
 * Frees all array memory.
 * @param arr Array to destroy (can be NULL)
 */
void static_array_destroy(StaticArray *arr);

/**
 * Sets element at index (overwrites existing).
 * @return 0 on success, -1 on error
 */
int static_array_set(StaticArray *arr, size_t index, int value);

/**
 * Fills entire array with a value.
 * @return 0 on success, -1 on error
 */
int static_array_fill(StaticArray *arr, int value);

/**
 * Clears array (sets all elements to 0).
 */
void static_array_clear(StaticArray *arr);

/**
 * Gets value at specific index.
 * @param out_value Pointer to store the value
 * @return 0 on success, -1 on error
 */
int static_array_get(const StaticArray *arr, size_t index, int *out_value);

/**
 * Returns the fixed capacity.
 */
size_t static_array_capacity(const StaticArray *arr);

/**
 * Finds first occurrence of a value.
 * @return Index of value, or -1 if not found
 */
int static_array_find(const StaticArray *arr, int value);

/**
 * Copies all elements from source to destination.
 * @return 0 on success, -1 on error
 */
int static_array_copy(StaticArray *dest, const StaticArray *src);

/**
 * Reverses the array in-place.
 * @return 0 on success, -1 on error
 */
int static_array_reverse(StaticArray *arr);

/**
 * Prints the array (for debugging).
 */
void static_array_print(const StaticArray *arr);

#endif // STATIC_ARRAY_H