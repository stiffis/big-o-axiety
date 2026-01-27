#include <stdio.h>
#include "../include/static_array_arena.h"

int main(void) {
    printf("=== Static Array Arena Demo ===\n");
    printf("Arena Allocator: Deterministic memory allocation for embedded/real-time systems\n\n");
    
    Arena *arena = arena_create(4096);
    if (!arena) {
        fprintf(stderr, "Error: Could not create arena\n");
        return 1;
    }
    
    printf("1. Arena created with capacity: %zu bytes\n", arena_capacity(arena));
    printf("   Used: %zu bytes\n\n", arena_used(arena));
    
    printf("2. Creating first array (capacity 10) from arena\n");
    StaticArrayArena *arr1 = static_array_arena_create(arena, 10);
    if (!arr1) {
        fprintf(stderr, "Error: Could not create array from arena\n");
        arena_destroy(arena);
        return 1;
    }
    printf("   Arena used: %zu bytes\n", arena_used(arena));
    static_array_arena_print(arr1);
    
    printf("\n3. Setting values in first array\n");
    for (size_t i = 0; i < 10; i++) {
        static_array_arena_set(arr1, i, (int)i * 10);
    }
    static_array_arena_print(arr1);
    
    printf("\n4. Creating second array (capacity 20) from same arena\n");
    StaticArrayArena *arr2 = static_array_arena_create(arena, 20);
    if (!arr2) {
        fprintf(stderr, "Error: Could not create second array from arena\n");
        arena_destroy(arena);
        return 1;
    }
    printf("   Arena used: %zu bytes\n", arena_used(arena));
    static_array_arena_fill(arr2, 42);
    static_array_arena_print(arr2);
    
    printf("\n5. Creating third array (capacity 5) from same arena\n");
    StaticArrayArena *arr3 = static_array_arena_create(arena, 5);
    if (!arr3) {
        fprintf(stderr, "Error: Could not create third array from arena\n");
        arena_destroy(arena);
        return 1;
    }
    printf("   Arena used: %zu / %zu bytes (%.1f%% used)\n", 
           arena_used(arena), 
           arena_capacity(arena),
           100.0 * arena_used(arena) / arena_capacity(arena));
    
    printf("\n6. All three arrays coexist in same arena:\n");
    printf("   Array 1: ");
    static_array_arena_print(arr1);
    printf("   Array 2: ");
    static_array_arena_print(arr2);
    printf("   Array 3: ");
    static_array_arena_print(arr3);
    
    int value;
    if (static_array_arena_get(arr1, 5, &value) == 0) {
        printf("\n7. Reading from arr1[5]: %d\n", value);
    }
    
    int index = static_array_arena_find(arr1, 70);
    if (index >= 0) {
        printf("   Found value 70 at index %d in arr1\n", index);
    }
    
    printf("\n8. Clearing arr2 (fill with zeros)\n");
    static_array_arena_clear(arr2);
    printf("   Array 2: ");
    static_array_arena_print(arr2);
    
    printf("\n9. Demonstrating arena reset (reuse without free/malloc)\n");
    printf("   Arena used before reset: %zu bytes\n", arena_used(arena));
    arena_reset(arena);
    printf("   Arena used after reset: %zu bytes\n", arena_used(arena));
    printf("   (All arrays are now invalid, but memory is reusable)\n");
    
    printf("\n10. Creating new array after arena reset\n");
    StaticArrayArena *arr4 = static_array_arena_create(arena, 15);
    if (arr4) {
        static_array_arena_fill(arr4, 99);
        printf("   Arena used: %zu bytes\n", arena_used(arena));
        printf("   Array 4: ");
        static_array_arena_print(arr4);
    }
    
    printf("\n11. Key benefits of Arena Allocator:\n");
    printf("    ✓ O(1) allocation (bump pointer, no malloc overhead)\n");
    printf("    ✓ Zero fragmentation (contiguous memory)\n");
    printf("    ✓ Batch deallocation (single arena_destroy)\n");
    printf("    ✓ Deterministic performance (no hidden allocator locks)\n");
    printf("    ✓ Cache-friendly (spatial locality)\n");
    printf("    ✓ Ideal for: games, audio DSP, embedded systems, parsers\n");
    
    printf("\n12. Testing bounds checking\n");
    if (static_array_arena_set(arr4, 100, 999) != 0) {
        printf("    ✓ Correctly rejected out-of-bounds write\n");
    }
    
    if (static_array_arena_get(arr4, 100, &value) != 0) {
        printf("    ✓ Correctly rejected out-of-bounds read\n");
    }
    
    arena_destroy(arena);
    printf("\n13. Arena destroyed (all arrays freed at once)\n");
    printf("    No individual array_destroy() needed!\n");
    
    return 0;
}
