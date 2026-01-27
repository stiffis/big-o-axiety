#include <stdio.h>
#include "../include/bitset.h"

int main(void) {
    printf("=== Bitset Demo ===\n\n");
    
    printf("1. Creating bitset with 16 bits:\n");
    Bitset *bs = bitset_create(16);
    printf("Initial: ");
    bitset_debug(bs);
    printf("\n");
    
    printf("2. Setting individual bits:\n");
    bitset_set(bs, 0);
    bitset_set(bs, 5);
    bitset_set(bs, 10);
    bitset_set(bs, 15);
    printf("After setting bits 0, 5, 10, 15: ");
    bitset_debug(bs);
    printf("\n");
    
    printf("3. Testing bits:\n");
    printf("Bit 0: %d\n", bitset_test(bs, 0));
    printf("Bit 5: %d\n", bitset_test(bs, 5));
    printf("Bit 7: %d\n", bitset_test(bs, 7));
    printf("Total set bits: %zu\n\n", bitset_count(bs));
    
    printf("4. Clearing a bit:\n");
    bitset_clear(bs, 5);
    printf("After clearing bit 5: ");
    bitset_debug(bs);
    printf("\n");
    
    printf("5. Flipping bits:\n");
    bitset_flip(bs, 0);
    bitset_flip(bs, 7);
    printf("After flipping bits 0 and 7: ");
    bitset_debug(bs);
    printf("\n");
    
    printf("6. Set all bits:\n");
    Bitset *bs2 = bitset_create(8);
    bitset_set_all(bs2);
    printf("All bits set: ");
    bitset_debug(bs2);
    printf("All set? %s\n", bitset_all(bs2) ? "yes" : "no");
    printf("Any set? %s\n", bitset_any(bs2) ? "yes" : "no");
    printf("None set? %s\n\n", bitset_none(bs2) ? "yes" : "no");
    
    printf("7. Clear all bits:\n");
    bitset_clear_all(bs2);
    printf("All bits cleared: ");
    bitset_debug(bs2);
    printf("None set? %s\n\n", bitset_none(bs2) ? "yes" : "no");
    
    printf("8. Flip all bits:\n");
    bitset_set(bs2, 0);
    bitset_set(bs2, 2);
    bitset_set(bs2, 4);
    printf("Before flip_all: ");
    bitset_debug(bs2);
    bitset_flip_all(bs2);
    printf("After flip_all:  ");
    bitset_debug(bs2);
    printf("\n");
    
    printf("9. Bitwise AND:\n");
    Bitset *bsA = bitset_create(8);
    Bitset *bsB = bitset_create(8);
    
    bitset_set(bsA, 0);
    bitset_set(bsA, 2);
    bitset_set(bsA, 4);
    bitset_set(bsA, 6);
    
    bitset_set(bsB, 0);
    bitset_set(bsB, 3);
    bitset_set(bsB, 4);
    bitset_set(bsB, 7);
    
    printf("A:      ");
    bitset_debug(bsA);
    printf("B:      ");
    bitset_debug(bsB);
    
    bitset_and(bsA, bsB);
    printf("A & B:  ");
    bitset_debug(bsA);
    printf("\n");
    
    printf("10. Bitwise OR:\n");
    Bitset *bsC = bitset_create(8);
    Bitset *bsD = bitset_create(8);
    
    bitset_set(bsC, 0);
    bitset_set(bsC, 2);
    
    bitset_set(bsD, 1);
    bitset_set(bsD, 2);
    bitset_set(bsD, 3);
    
    printf("C:      ");
    bitset_debug(bsC);
    printf("D:      ");
    bitset_debug(bsD);
    
    bitset_or(bsC, bsD);
    printf("C | D:  ");
    bitset_debug(bsC);
    printf("\n");
    
    printf("11. Bitwise XOR:\n");
    Bitset *bsE = bitset_create(8);
    Bitset *bsF = bitset_create(8);
    
    bitset_set(bsE, 0);
    bitset_set(bsE, 2);
    bitset_set(bsE, 4);
    
    bitset_set(bsF, 0);
    bitset_set(bsF, 3);
    bitset_set(bsF, 4);
    
    printf("E:      ");
    bitset_debug(bsE);
    printf("F:      ");
    bitset_debug(bsF);
    
    bitset_xor(bsE, bsF);
    printf("E ^ F:  ");
    bitset_debug(bsE);
    printf("\n");
    
    printf("12. Equality check:\n");
    Bitset *bsX = bitset_create(8);
    Bitset *bsY = bitset_create(8);
    
    bitset_set(bsX, 1);
    bitset_set(bsX, 3);
    
    printf("X and Y equal? %s\n", bitset_equals(bsX, bsY) ? "yes" : "no");
    
    bitset_set(bsY, 1);
    bitset_set(bsY, 3);
    
    printf("After setting same bits: %s\n\n", bitset_equals(bsX, bsY) ? "yes" : "no");
    
    printf("13. Non-byte-aligned bitset:\n");
    Bitset *bs13 = bitset_create(13);
    bitset_set_all(bs13);
    printf("13-bit bitset (all set): ");
    bitset_debug(bs13);
    
    bitset_destroy(bs);
    bitset_destroy(bs2);
    bitset_destroy(bsA);
    bitset_destroy(bsB);
    bitset_destroy(bsC);
    bitset_destroy(bsD);
    bitset_destroy(bsE);
    bitset_destroy(bsF);
    bitset_destroy(bsX);
    bitset_destroy(bsY);
    bitset_destroy(bs13);
    
    printf("\n=== Demo Complete ===\n");
    return 0;
}
