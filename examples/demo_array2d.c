#include <stdio.h>
#include "../include/array2d.h"

int main(void) {
    printf("=== Array2D (Matrix) Demo ===\n\n");
    
    Array2D *matrix = array2d_create(3, 4);
    if (!matrix) {
        fprintf(stderr, "Error: Could not create matrix\n");
        return 1;
    }
    
    printf("1. Matrix created (3x4)\n");
    array2d_print(matrix);
    
    printf("\n2. Setting values at specific positions\n");
    array2d_set(matrix, 0, 0, 1);
    array2d_set(matrix, 0, 1, 2);
    array2d_set(matrix, 0, 2, 3);
    array2d_set(matrix, 0, 3, 4);
    array2d_set(matrix, 1, 0, 5);
    array2d_set(matrix, 1, 1, 6);
    array2d_set(matrix, 1, 2, 7);
    array2d_set(matrix, 1, 3, 8);
    array2d_set(matrix, 2, 0, 9);
    array2d_set(matrix, 2, 1, 10);
    array2d_set(matrix, 2, 2, 11);
    array2d_set(matrix, 2, 3, 12);
    array2d_print(matrix);
    
    int value;
    if (array2d_get(matrix, 1, 2, &value) == 0) {
        printf("\n3. Value at position [1][2]: %d\n", value);
    }
    
    printf("\n4. Getting row 1\n");
    int row_buffer[4];
    if (array2d_get_row(matrix, 1, row_buffer, 4) == 0) {
        printf("   Row 1: [");
        for (int i = 0; i < 4; i++) {
            printf("%d", row_buffer[i]);
            if (i < 3) printf(", ");
        }
        printf("]\n");
    }
    
    printf("\n5. Getting column 2\n");
    int col_buffer[3];
    if (array2d_get_col(matrix, 2, col_buffer, 3) == 0) {
        printf("   Column 2: [");
        for (int i = 0; i < 3; i++) {
            printf("%d", col_buffer[i]);
            if (i < 2) printf(", ");
        }
        printf("]\n");
    }
    
    printf("\n6. Filling entire matrix with 99\n");
    array2d_fill(matrix, 99);
    array2d_print(matrix);
    
    printf("\n7. Clearing matrix (set all to 0)\n");
    array2d_clear(matrix);
    array2d_print(matrix);
    
    printf("\n8. Filling row 1 with value 10\n");
    array2d_fill_row(matrix, 1, 10);
    array2d_print(matrix);
    
    printf("\n9. Filling column 2 with value 20\n");
    array2d_fill_col(matrix, 2, 20);
    array2d_print(matrix);
    
    printf("\n10. Creating a square matrix (3x3) for transpose demo\n");
    Array2D *square = array2d_create(3, 3);
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            array2d_set(square, i, j, (int)(i * 3 + j + 1));
        }
    }
    printf("    Original:\n");
    array2d_print(square);
    
    printf("\n11. Transposing square matrix in-place\n");
    array2d_transpose(square);
    printf("    Transposed:\n");
    array2d_print(square);
    
    printf("\n12. Creating transpose copy of rectangular matrix\n");
    Array2D *rect = array2d_create(2, 3);
    array2d_set(rect, 0, 0, 1);
    array2d_set(rect, 0, 1, 2);
    array2d_set(rect, 0, 2, 3);
    array2d_set(rect, 1, 0, 4);
    array2d_set(rect, 1, 1, 5);
    array2d_set(rect, 1, 2, 6);
    printf("    Original (2x3):\n");
    array2d_print(rect);
    
    Array2D *transposed = array2d_transpose_copy(rect);
    printf("\n    Transposed copy (3x2):\n");
    array2d_print(transposed);
    
    printf("\n13. Finding value 5 in transposed matrix\n");
    size_t found_row, found_col;
    if (array2d_find(transposed, 5, &found_row, &found_col) == 0) {
        printf("    Found at position [%zu][%zu]\n", found_row, found_col);
    } else {
        printf("    Not found\n");
    }
    
    printf("\n14. Copying matrix\n");
    Array2D *copy = array2d_create(3, 3);
    array2d_copy(copy, square);
    printf("    Copy of square matrix:\n");
    array2d_print(copy);
    
    printf("\n15. Testing bounds checking\n");
    if (array2d_set(matrix, 100, 0, 999) != 0) {
        printf("    ✓ Correctly rejected out-of-bounds write\n");
    }
    
    if (array2d_get(matrix, 0, 100, &value) != 0) {
        printf("    ✓ Correctly rejected out-of-bounds read\n");
    }
    
    printf("\n16. Matrix dimensions\n");
    printf("    Rows: %zu, Columns: %zu\n", array2d_rows(matrix), array2d_cols(matrix));
    
    array2d_destroy(matrix);
    array2d_destroy(square);
    array2d_destroy(rect);
    array2d_destroy(transposed);
    array2d_destroy(copy);
    printf("\n17. All matrices destroyed successfully\n");
    
    return 0;
}
