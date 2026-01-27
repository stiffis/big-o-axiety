#ifndef ARRAY2D_H
#define ARRAY2D_H

#include <stddef.h>

/**
 * Array2D - 2D Array (Matrix) with row-major layout
 * 
 * Key concepts:
 * - Fixed dimensions (rows x cols)
 * - Row-major memory layout (contiguous rows)
 * - O(1) random access via [row][col]
 * - Support for matrix operations
 * 
 * Memory layout example (3x4 matrix):
 * [0,0] [0,1] [0,2] [0,3] [1,0] [1,1] [1,2] [1,3] [2,0] [2,1] [2,2] [2,3]
 */

typedef struct Array2D Array2D;

/* ========== CONSTRUCTORS AND DESTRUCTORS ========== */

/**
 * Creates a new 2D array with fixed dimensions
 * @param rows Number of rows
 * @param cols Number of columns
 * @return Pointer to array, or NULL if malloc fails or dimensions are 0
 */
Array2D* array2d_create(size_t rows, size_t cols);

/**
 * Frees all array memory
 * @param arr Array to destroy (can be NULL)
 */
void array2d_destroy(Array2D *arr);

/* ========== MODIFIERS ========== */

/**
 * Sets value at specific position
 * @param arr Target array
 * @param row Row index (0-based)
 * @param col Column index (0-based)
 * @param value Value to store
 * @return 0 on success, -1 on error (out of bounds)
 * 
 * Complexity: O(1)
 */
int array2d_set(Array2D *arr, size_t row, size_t col, int value);

/**
 * Fills entire matrix with a value
 * @param arr Target array
 * @param value Value to fill with
 * @return 0 on success, -1 on error
 * 
 * Complexity: O(rows * cols)
 */
int array2d_fill(Array2D *arr, int value);

/**
 * Clears matrix (sets all elements to 0)
 * @param arr Target array
 */
void array2d_clear(Array2D *arr);

/**
 * Fills a specific row with a value
 * @param arr Target array
 * @param row Row index
 * @param value Value to fill with
 * @return 0 on success, -1 on error (row out of bounds)
 * 
 * Complexity: O(cols)
 */
int array2d_fill_row(Array2D *arr, size_t row, int value);

/**
 * Fills a specific column with a value
 * @param arr Target array
 * @param col Column index
 * @param value Value to fill with
 * @return 0 on success, -1 on error (col out of bounds)
 * 
 * Complexity: O(rows)
 */
int array2d_fill_col(Array2D *arr, size_t col, int value);

/* ========== ACCESSORS (QUERY) ========== */

/**
 * Gets value at specific position
 * @param arr Target array
 * @param row Row index
 * @param col Column index
 * @param out_value Pointer to store the value
 * @return 0 on success, -1 on error (out of bounds)
 * 
 * Complexity: O(1)
 */
int array2d_get(const Array2D *arr, size_t row, size_t col, int *out_value);

/**
 * Returns number of rows
 * @param arr Target array
 * @return Number of rows (0 if arr is NULL)
 */
size_t array2d_rows(const Array2D *arr);

/**
 * Returns number of columns
 * @param arr Target array
 * @return Number of columns (0 if arr is NULL)
 */
size_t array2d_cols(const Array2D *arr);

/**
 * Copies an entire row to output array
 * @param arr Source array
 * @param row Row index
 * @param out_buffer Output buffer (must have space for cols elements)
 * @param buffer_size Size of output buffer
 * @return 0 on success, -1 on error (invalid row or buffer too small)
 * 
 * Complexity: O(cols)
 */
int array2d_get_row(const Array2D *arr, size_t row, int *out_buffer, size_t buffer_size);

/**
 * Copies an entire column to output array
 * @param arr Source array
 * @param col Column index
 * @param out_buffer Output buffer (must have space for rows elements)
 * @param buffer_size Size of output buffer
 * @return 0 on success, -1 on error (invalid col or buffer too small)
 * 
 * Complexity: O(rows)
 */
int array2d_get_col(const Array2D *arr, size_t col, int *out_buffer, size_t buffer_size);

/* ========== MATRIX OPERATIONS ========== */

/**
 * Transposes the matrix in-place (only works for square matrices)
 * @param arr Target array (must be square: rows == cols)
 * @return 0 on success, -1 on error (not square or NULL)
 * 
 * Complexity: O(rows * cols)
 */
int array2d_transpose(Array2D *arr);

/**
 * Creates a transposed copy of the matrix
 * @param arr Source array
 * @return New transposed array, or NULL on error
 * 
 * Result dimensions: cols x rows
 * Caller must free with array2d_destroy()
 * Complexity: O(rows * cols)
 */
Array2D* array2d_transpose_copy(const Array2D *arr);

/* ========== UTILITIES ========== */

/**
 * Finds first occurrence of a value (searches row by row)
 * @param arr Target array
 * @param value Value to search for
 * @param out_row Pointer to store row index (can be NULL)
 * @param out_col Pointer to store column index (can be NULL)
 * @return 0 if found, -1 if not found or error
 * 
 * Complexity: O(rows * cols)
 */
int array2d_find(const Array2D *arr, int value, size_t *out_row, size_t *out_col);

/**
 * Copies all elements from source to destination
 * @param dest Destination array
 * @param src Source array
 * @return 0 on success, -1 on error (different dimensions or NULL)
 * 
 * Both arrays must have same dimensions
 * Complexity: O(rows * cols)
 */
int array2d_copy(Array2D *dest, const Array2D *src);

/**
 * Prints the matrix (useful for debugging)
 * @param arr Target array
 */
void array2d_print(const Array2D *arr);

#endif // ARRAY2D_H
