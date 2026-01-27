#include "../include/array2d.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Array2D {
    int *data;
    size_t rows;
    size_t cols;
};

Array2D* array2d_create(size_t rows, size_t cols) {
    if (rows == 0 || cols == 0) {
        return NULL;
    }
    
    struct Array2D *arr = malloc(sizeof(struct Array2D));
    if (!arr) {
        return NULL;
    }
    
    arr->data = malloc(rows * cols * sizeof(int));
    if (!arr->data) {
        free(arr);
        return NULL;
    }
    
    arr->rows = rows;
    arr->cols = cols;
    
    memset(arr->data, 0, rows * cols * sizeof(int));
    
    return arr;
}

void array2d_destroy(Array2D *arr) {
    if (!arr) {
        return;
    }
    
    free(arr->data);
    free(arr);
}

int array2d_set(Array2D *arr, size_t row, size_t col, int value) {
    if (!arr || row >= arr->rows || col >= arr->cols) {
        return -1;
    }
    
    arr->data[row * arr->cols + col] = value;
    return 0;
}

int array2d_fill(Array2D *arr, int value) {
    if (!arr) {
        return -1;
    }
    
    for (size_t i = 0; i < arr->rows * arr->cols; i++) {
        arr->data[i] = value;
    }
    
    return 0;
}

void array2d_clear(Array2D *arr) {
    if (!arr) {
        return;
    }
    
    memset(arr->data, 0, arr->rows * arr->cols * sizeof(int));
}

int array2d_fill_row(Array2D *arr, size_t row, int value) {
    if (!arr || row >= arr->rows) {
        return -1;
    }
    
    size_t start = row * arr->cols;
    for (size_t i = 0; i < arr->cols; i++) {
        arr->data[start + i] = value;
    }
    
    return 0;
}

int array2d_fill_col(Array2D *arr, size_t col, int value) {
    if (!arr || col >= arr->cols) {
        return -1;
    }
    
    for (size_t row = 0; row < arr->rows; row++) {
        arr->data[row * arr->cols + col] = value;
    }
    
    return 0;
}

int array2d_get(const Array2D *arr, size_t row, size_t col, int *out_value) {
    if (!arr || !out_value || row >= arr->rows || col >= arr->cols) {
        return -1;
    }
    
    *out_value = arr->data[row * arr->cols + col];
    return 0;
}

size_t array2d_rows(const Array2D *arr) {
    if (!arr) {
        return 0;
    }
    
    return arr->rows;
}

size_t array2d_cols(const Array2D *arr) {
    if (!arr) {
        return 0;
    }
    
    return arr->cols;
}

int array2d_get_row(const Array2D *arr, size_t row, int *out_buffer, size_t buffer_size) {
    if (!arr || !out_buffer || row >= arr->rows || buffer_size < arr->cols) {
        return -1;
    }
    
    size_t start = row * arr->cols;
    memcpy(out_buffer, &arr->data[start], arr->cols * sizeof(int));
    
    return 0;
}

int array2d_get_col(const Array2D *arr, size_t col, int *out_buffer, size_t buffer_size) {
    if (!arr || !out_buffer || col >= arr->cols || buffer_size < arr->rows) {
        return -1;
    }
    
    for (size_t row = 0; row < arr->rows; row++) {
        out_buffer[row] = arr->data[row * arr->cols + col];
    }
    
    return 0;
}

int array2d_transpose(Array2D *arr) {
    if (!arr || arr->rows != arr->cols) {
        return -1;
    }
    
    size_t n = arr->rows;
    
    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            int temp = arr->data[i * n + j];
            arr->data[i * n + j] = arr->data[j * n + i];
            arr->data[j * n + i] = temp;
        }
    }
    
    return 0;
}

Array2D* array2d_transpose_copy(const Array2D *arr) {
    if (!arr) {
        return NULL;
    }
    
    Array2D *transposed = array2d_create(arr->cols, arr->rows);
    if (!transposed) {
        return NULL;
    }
    
    for (size_t i = 0; i < arr->rows; i++) {
        for (size_t j = 0; j < arr->cols; j++) {
            transposed->data[j * arr->rows + i] = arr->data[i * arr->cols + j];
        }
    }
    
    return transposed;
}

int array2d_find(const Array2D *arr, int value, size_t *out_row, size_t *out_col) {
    if (!arr) {
        return -1;
    }
    
    for (size_t i = 0; i < arr->rows; i++) {
        for (size_t j = 0; j < arr->cols; j++) {
            if (arr->data[i * arr->cols + j] == value) {
                if (out_row) {
                    *out_row = i;
                }
                if (out_col) {
                    *out_col = j;
                }
                return 0;
            }
        }
    }
    
    return -1;
}

int array2d_copy(Array2D *dest, const Array2D *src) {
    if (!dest || !src || dest->rows != src->rows || dest->cols != src->cols) {
        return -1;
    }
    
    memcpy(dest->data, src->data, src->rows * src->cols * sizeof(int));
    return 0;
}

void array2d_print(const Array2D *arr) {
    if (!arr) {
        printf("NULL\n");
        return;
    }
    
    printf("[\n");
    for (size_t i = 0; i < arr->rows; i++) {
        printf("  [");
        for (size_t j = 0; j < arr->cols; j++) {
            printf("%4d", arr->data[i * arr->cols + j]);
            if (j < arr->cols - 1) {
                printf(", ");
            }
        }
        printf("]");
        if (i < arr->rows - 1) {
            printf(",");
        }
        printf("\n");
    }
    printf("] (%zux%zu)\n", arr->rows, arr->cols);
}
