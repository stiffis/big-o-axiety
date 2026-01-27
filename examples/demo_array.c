#include <stdio.h>
#include "../include/array.h"

int main(void) {
    printf("=== Dynamic Array Demo ===\n\n");
    
    DynamicArray *arr = array_create(4);
    if (!arr) {
        fprintf(stderr, "Error: Could not create array\n");
        return 1;
    }
    
    printf("1. Array created with capacity 4\n");
    array_print(arr);
    
    printf("\n2. Pushing elements: 10, 20, 30, 40, 50\n");
    array_push(arr, 10);
    array_push(arr, 20);
    array_push(arr, 30);
    array_push(arr, 40);
    array_push(arr, 50);
    array_print(arr);
    
    int value;
    if (array_get(arr, 2, &value) == 0) {
        printf("\n3. Element at index 2: %d\n", value);
    }
    
    printf("\n4. Inserting 99 at index 1\n");
    array_insert(arr, 1, 99);
    array_print(arr);
    
    printf("\n5. Removing element at index 3\n");
    if (array_remove(arr, 3, &value) == 0) {
        printf("   Removed value: %d\n", value);
    }
    array_print(arr);
    
    printf("\n6. Popping last element\n");
    if (array_pop(arr, &value) == 0) {
        printf("   Popped value: %d\n", value);
    }
    array_print(arr);
    
    printf("\n7. Setting index 0 to 777\n");
    array_set(arr, 0, 777);
    array_print(arr);
    
    int search_value = 99;
    int index = array_find(arr, search_value);
    if (index >= 0) {
        printf("\n8. Found %d at index %d\n", search_value, index);
    }
    
    printf("\n9. Array stats:\n");
    printf("   Size: %zu\n", array_size(arr));
    printf("   Capacity: %zu\n", array_capacity(arr));
    printf("   Is empty: %s\n", array_is_empty(arr) ? "yes" : "no");
    
    printf("\n10. Clearing array\n");
    array_clear(arr);
    array_print(arr);
    printf("    Is empty now: %s\n", array_is_empty(arr) ? "yes" : "no");
    
    array_destroy(arr);
    printf("\n11. Array destroyed successfully\n");
    
    return 0;
}
