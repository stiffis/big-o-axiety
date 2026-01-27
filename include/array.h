#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>

/**
 * Dynamic Array - Self-growing data structure
 *
 * Key concepts:
 * - size: current number of elements
 * - capacity: total available space
 * - When size == capacity, resize happens (typically 2x)
 */

// Opaque pointer - hides internal implementation
// User cannot access fields directly
typedef struct DynamicArray DynamicArray;

/* ========== CONSTRUCTORS AND DESTRUCTORS ========== */

/**
 * Creates a new dynamic array
 * @param capacity Initial capacity (if 0, uses default of 16)
 * @return Pointer to array, or NULL if malloc fails
 */
DynamicArray *array_create(size_t capacity);

/**
 * Frees all array memory
 * @param arr Array to destroy (can be NULL)
 *
 * IMPORTANT: After calling this, the arr pointer is invalid
 */
void array_destroy(DynamicArray *arr);

/* ========== MODIFIERS ========== */

/**
 * Appends an element to the end of the array
 * @param arr Target array
 * @param value Value to append
 * @return 0 on success, -1 on error (NULL or out of memory)
 *
 * Complexity: O(1) amortized (O(n) when resizing)
 */
int array_push(DynamicArray *arr, int value);

/**
 * Removes and returns the last element
 * @param arr Target array
 * @param out_value Pointer to store the removed value
 * @return 0 on success, -1 on error (NULL or empty array)
 *
 * Complexity: O(1)
 */
int array_pop(DynamicArray *arr, int *out_value);

/**
 * Inserts an element at a specific position
 * @param arr Target array
 * @param index Index where to insert (0 <= index <= size)
 * @param value Value to insert
 * @return 0 on success, -1 on error
 *
 * Complexity: O(n) - requires shifting elements
 */
int array_insert(DynamicArray *arr, size_t index, int value);

/**
 * Removes an element at a specific position
 * @param arr Target array
 * @param index Index of element to remove
 * @param out_value Pointer to store removed value (can be NULL)
 * @return 0 on success, -1 on error
 *
 * Complexity: O(n) - requires shifting elements
 */
int array_remove(DynamicArray *arr, size_t index, int *out_value);

/**
 * Modifies the value at a position
 * @param arr Target array
 * @param index Index to modify
 * @param value New value
 * @return 0 on success, -1 on error (index out of range)
 *
 * Complexity: O(1)
 */
int array_set(DynamicArray *arr, size_t index, int value);

/**
 * Removes all elements (size = 0, but keeps capacity)
 * @param arr Target array
 */
void array_clear(DynamicArray *arr);

/* ========== ACCESSORS (QUERY) ========== */

/**
 * Gets the value at a position
 * @param arr Target array
 * @param index Index to query
 * @param out_value Pointer to store the value
 * @return 0 on success, -1 on error (index out of range)
 *
 * Complexity: O(1)
 */
int array_get(const DynamicArray *arr, size_t index, int *out_value);

/**
 * Number of elements in the array
 * @param arr Target array
 * @return Current size (0 if arr is NULL)
 */
size_t array_size(const DynamicArray *arr);

/**
 * Total capacity of the array
 * @param arr Target array
 * @return Capacity (0 if arr is NULL)
 */
size_t array_capacity(const DynamicArray *arr);

/**
 * Checks if the array is empty
 * @param arr Target array
 * @return 1 if empty, 0 if it has elements
 */
int array_is_empty(const DynamicArray *arr);

/* ========== UTILITIES ========== */

/**
 * Searches for a value in the array
 * @param arr Target array
 * @param value Value to search for
 * @return Index of the value, or -1 if not found
 *
 * Complexity: O(n)
 */
int array_find(const DynamicArray *arr, int value);

/**
 * Prints the array (useful for debugging)
 * @param arr Target array
 */
void array_print(const DynamicArray *arr);

#endif // ARRAY_H
