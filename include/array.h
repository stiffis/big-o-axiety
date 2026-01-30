#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>

/**
 * Dynamic array with automatic resizing (2x growth factor).
 */
typedef struct DynamicArray DynamicArray;

/**
 * Creates a new dynamic array.
 * @param capacity Initial capacity (0 = default 16)
 * @return Array pointer or NULL on error
 */
DynamicArray *array_create(size_t capacity);

/**
 * Frees all array memory. Pointer becomes invalid after call.
 * @param arr Array to destroy (can be NULL)
 */
void array_destroy(DynamicArray *arr);

/**
 * Appends an element to the end.
 * @return 0 on success, -1 on error
 */
int array_push(DynamicArray *arr, int value);

/**
 * Removes and returns the last element.
 * @param out_value Pointer to store removed value
 * @return 0 on success, -1 on error (empty array)
 */
int array_pop(DynamicArray *arr, int *out_value);

/**
 * Inserts an element at a specific position.
 * @param index Position to insert (0 <= index <= size)
 * @return 0 on success, -1 on error
 */
int array_insert(DynamicArray *arr, size_t index, int value);

/**
 * Removes an element at a specific position.
 * @param out_value Pointer to store removed value (can be NULL)
 * @return 0 on success, -1 on error
 */
int array_remove(DynamicArray *arr, size_t index, int *out_value);

/**
 * Modifies the value at a position.
 * @return 0 on success, -1 on error (index out of range)
 */
int array_set(DynamicArray *arr, size_t index, int value);

/**
 * Removes all elements (size = 0, keeps capacity).
 */
void array_clear(DynamicArray *arr);

/**
 * Gets the value at a position.
 * @param out_value Pointer to store the value
 * @return 0 on success, -1 on error (index out of range)
 */
int array_get(const DynamicArray *arr, size_t index, int *out_value);

/**
 * Returns the number of elements.
 */
size_t array_size(const DynamicArray *arr);

/**
 * Returns the total capacity.
 */
size_t array_capacity(const DynamicArray *arr);

/**
 * Checks if the array is empty.
 * @return 1 if empty, 0 otherwise
 */
int array_is_empty(const DynamicArray *arr);

/**
 * Searches for a value in the array.
 * @return Index of value, or -1 if not found
 */
int array_find(const DynamicArray *arr, int value);

/**
 * Prints the array (for debugging).
 */
void array_print(const DynamicArray *arr);

#endif // ARRAY_H