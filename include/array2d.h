#ifndef ARRAY2D_H
#define ARRAY2D_H

#include <stddef.h>

/**
 * 2D array (matrix) with row-major layout.
 * O(1) random access via [row][col].
 */
typedef struct Array2D Array2D;

/**
 * Creates a 2D array with fixed dimensions.
 * @return Pointer to array or NULL on error
 */
Array2D* array2d_create(size_t rows, size_t cols);

/** Frees all array memory. */
void array2d_destroy(Array2D *arr);

/** Sets value at [row, col]. @return 0 on success, -1 on error. */
int array2d_set(Array2D *arr, size_t row, size_t col, int value);

/** Fills entire matrix with a value. @return 0 on success, -1 on error. */
int array2d_fill(Array2D *arr, int value);

/** Clears matrix (sets all elements to 0). */
void array2d_clear(Array2D *arr);

/** Fills a specific row with a value. @return 0 on success, -1 on error. */
int array2d_fill_row(Array2D *arr, size_t row, int value);

/** Fills a specific column with a value. @return 0 on success, -1 on error. */
int array2d_fill_col(Array2D *arr, size_t col, int value);

/** Gets value at [row, col]. @return 0 on success, -1 on error. */
int array2d_get(const Array2D *arr, size_t row, size_t col, int *out_value);

/** Returns number of rows. */
size_t array2d_rows(const Array2D *arr);

/** Returns number of columns. */
size_t array2d_cols(const Array2D *arr);

/**
 * Copies a row to output buffer.
 * @return 0 on success, -1 on error
 */
int array2d_get_row(const Array2D *arr, size_t row, int *out_buffer, size_t buffer_size);

/**
 * Copies a column to output buffer.
 * @return 0 on success, -1 on error
 */
int array2d_get_col(const Array2D *arr, size_t col, int *out_buffer, size_t buffer_size);

/**
 * Transposes square matrix in-place.
 * @return 0 on success, -1 on error
 */
int array2d_transpose(Array2D *arr);

/**
 * Creates a transposed copy.
 * @return New transposed array or NULL on error
 */
Array2D* array2d_transpose_copy(const Array2D *arr);

/**
 * Finds first occurrence of a value.
 * @return 0 if found, -1 if not found
 */
int array2d_find(const Array2D *arr, int value, size_t *out_row, size_t *out_col);

/**
 * Copies all elements from source to destination.
 * @return 0 on success, -1 on error
 */
int array2d_copy(Array2D *dest, const Array2D *src);

/** Prints matrix for debugging. */
void array2d_print(const Array2D *arr);

#endif // ARRAY2D_H