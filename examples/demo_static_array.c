#include <stdio.h>
#include "../include/static_array.h"

int main(void) {
    printf("=== Static Array Demo ===\n\n");
    
    StaticArray *arr = static_array_create(10);
    if (!arr) {
        fprintf(stderr, "Error: Could not create array\n");
        return 1;
    }
    
    printf("1. Array created with fixed capacity 10\n");
    static_array_print(arr);
    
    printf("\n2. Setting values at specific indices\n");
    static_array_set(arr, 0, 100);
    static_array_set(arr, 1, 200);
    static_array_set(arr, 5, 500);
    static_array_set(arr, 9, 900);
    static_array_print(arr);
    
    int value;
    if (static_array_get(arr, 5, &value) == 0) {
        printf("\n3. Value at index 5: %d\n", value);
    }
    
    printf("\n4. Filling array with value 42\n");
    static_array_fill(arr, 42);
    static_array_print(arr);
    
    printf("\n5. Setting incremental values (0-9)\n");
    for (size_t i = 0; i < static_array_capacity(arr); i++) {
        static_array_set(arr, i, (int)i * 10);
    }
    static_array_print(arr);
    
    int index = static_array_find(arr, 50);
    if (index >= 0) {
        printf("\n6. Found value 50 at index %d\n", index);
    } else {
        printf("\n6. Value 50 not found\n");
    }
    
    printf("\n7. Reversing array\n");
    static_array_reverse(arr);
    static_array_print(arr);
    
    StaticArray *arr2 = static_array_create(10);
    printf("\n8. Created second array\n");
    static_array_print(arr2);
    
    printf("\n9. Copying first array to second\n");
    static_array_copy(arr2, arr);
    static_array_print(arr2);
    
    printf("\n10. Clearing first array\n");
    static_array_clear(arr);
    static_array_print(arr);
    
    printf("\n11. Capacity of arrays: %zu\n", static_array_capacity(arr));
    
    printf("\n12. Testing bounds checking\n");
    if (static_array_set(arr, 100, 999) != 0) {
        printf("    ✓ Correctly rejected out-of-bounds write\n");
    }
    
    if (static_array_get(arr, 100, &value) != 0) {
        printf("    ✓ Correctly rejected out-of-bounds read\n");
    }
    
    static_array_destroy(arr);
    static_array_destroy(arr2);
    printf("\n13. Arrays destroyed successfully\n");
    
    return 0;
}
