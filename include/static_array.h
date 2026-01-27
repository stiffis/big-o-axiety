#ifndef STATIC_ARRAY_H
#define STATIC_ARRAY_H

#include <stddef.h>

/**
 * Static Array - Fixed-size array (no dynamic resizing)
 * 
 * Key concepts:
 * - Fixed capacity set at creation
 * - No automatic resizing
 * - Faster than dynamic array (no realloc overhead)
 * - Less memory overhead
 */

typedef struct StaticArray StaticArray;

/* ========== CONSTRUCTORS AND DESTRUCTORS ========== */

/**
 * Creates a new static array with fixed capacity
 * @param capacity Fixed size (cannot be changed later)
 * @return Pointer to array, or NULL if malloc fails
 */
StaticArray* static_array_create(size_t capacity);

/**
 * Frees all array memory
 * @param arr Array to destroy (can be NULL)
 */
void static_array_destroy(StaticArray *arr);

/* ========== MODIFIERS ========== */

/**
 * Adds element at specific index (overwrites existing)
 * @param arr Target array
 * @param index Position to set
 * @param value Value to store
 * @return 0 on success, -1 on error (index out of bounds)
 * 
 * Complexity: O(1)
 */
int static_array_set(StaticArray *arr, size_t index, int value);

/**
 * Fills entire array with a value
 * @param arr Target array
 * @param value Value to fill with
 * @return 0 on success, -1 on error
 * 
 * Complexity: O(n)
 */
int static_array_fill(StaticArray *arr, int value);

/**
 * Clears array (sets all elements to 0)
 * @param arr Target array
 */
void static_array_clear(StaticArray *arr);

/* ========== ACCESSORS (QUERY) ========== */

/**
 * Gets value at specific index
 * @param arr Target array
 * @param index Position to read
 * @param out_value Pointer to store the value
 * @return 0 on success, -1 on error (index out of bounds)
 * 
 * Complexity: O(1)
 */
int static_array_get(const StaticArray *arr, size_t index, int *out_value);

/**
 * Returns the fixed capacity of the array
 * @param arr Target array
 * @return Capacity (0 if arr is NULL)
 */
size_t static_array_capacity(const StaticArray *arr);

/* ========== UTILITIES ========== */

/**
 * Finds first occurrence of a value
 * @param arr Target array
 * @param value Value to search for
 * @return Index of value, or -1 if not found
 * 
 * Complexity: O(n)
 */
int static_array_find(const StaticArray *arr, int value);

/**
 * Copies all elements from source to destination
 * @param dest Destination array
 * @param src Source array
 * @return 0 on success, -1 on error (different sizes or NULL)
 * 
 * Both arrays must have same capacity
 * Complexity: O(n)
 */
int static_array_copy(StaticArray *dest, const StaticArray *src);

/**
 * Reverses the array in-place
 * @param arr Target array
 * @return 0 on success, -1 on error
 * 
 * Complexity: O(n)
 */
int static_array_reverse(StaticArray *arr);

/**
 * Prints the array (useful for debugging)
 * @param arr Target array
 */
void static_array_print(const StaticArray *arr);

#endif // STATIC_ARRAY_H
