#include <stdio.h>
#include "../include/avl.h"

static void print_key(int key, void *user_data) {
    int *count = (int *)user_data;
    if (*count > 0) {
        printf(", ");
    }
    printf("%d", key);
    (*count)++;
}

int main(void) {
    printf("=== AVL Tree Demo ===\n\n");
    
    AVL *tree = avl_create();
    if (!tree) {
        fprintf(stderr, "Error: Could not create tree\n");
        return 1;
    }
    
    printf("1. Tree created (empty)\n");
    printf("   Size: %zu, Height: %d, Empty: %s\n", 
           avl_size(tree), avl_height(tree), avl_is_empty(tree) ? "yes" : "no");
    
    printf("\n2. Inserting values: 50, 30, 70, 20, 40, 60, 80\n");
    avl_insert(tree, 50);
    avl_insert(tree, 30);
    avl_insert(tree, 70);
    avl_insert(tree, 20);
    avl_insert(tree, 40);
    avl_insert(tree, 60);
    avl_insert(tree, 80);
    
    printf("   Size: %zu, Height: %d\n", avl_size(tree), avl_height(tree));
    printf("   Balanced: %s\n", avl_is_balanced(tree) ? "yes" : "no");
    
    printf("\n3. Tree visualization:\n");
    avl_print(tree);
    
    printf("\n4. Searching for values\n");
    printf("   Search 40: %s\n", avl_search(tree, 40) ? "found" : "not found");
    printf("   Search 99: %s\n", avl_search(tree, 99) ? "found" : "not found");
    
    int min, max;
    avl_min(tree, &min);
    avl_max(tree, &max);
    printf("\n5. Min: %d, Max: %d\n", min, max);
    
    printf("\n6. In-order traversal (sorted): ");
    int count = 0;
    avl_inorder(tree, print_key, &count);
    printf("\n");
    
    printf("\n7. Pre-order traversal: ");
    count = 0;
    avl_preorder(tree, print_key, &count);
    printf("\n");
    
    printf("\n8. Post-order traversal: ");
    count = 0;
    avl_postorder(tree, print_key, &count);
    printf("\n");
    
    printf("\n9. Converting to sorted array\n");
    int array[10];
    int n = avl_to_array(tree, array, 10);
    printf("   Array: [");
    for (int i = 0; i < n; i++) {
        printf("%d", array[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
    
    printf("\n10. Deleting value 30\n");
    avl_delete(tree, 30);
    printf("    Size: %zu, Height: %d, Balanced: %s\n", 
           avl_size(tree), avl_height(tree), avl_is_balanced(tree) ? "yes" : "no");
    avl_print(tree);
    
    printf("\n11. Testing automatic rebalancing with sequential inserts\n");
    AVL *tree2 = avl_create();
    printf("    Inserting 1, 2, 3, 4, 5, 6, 7, 8, 9, 10\n");
    for (int i = 1; i <= 10; i++) {
        avl_insert(tree2, i);
    }
    printf("    Size: %zu, Height: %d (would be 10 without balancing)\n", 
           avl_size(tree2), avl_height(tree2));
    printf("    Balanced: %s\n", avl_is_balanced(tree2) ? "yes" : "no");
    avl_print(tree2);
    
    printf("\n12. Testing rotations\n");
    AVL *tree3 = avl_create();
    
    printf("    a) Left-Left (RR) case: inserting 30, 20, 10\n");
    avl_insert(tree3, 30);
    avl_insert(tree3, 20);
    avl_insert(tree3, 10);
    printf("       Height: %d, Balanced: %s\n", 
           avl_height(tree3), avl_is_balanced(tree3) ? "yes" : "no");
    avl_print(tree3);
    
    avl_clear(tree3);
    
    printf("\n    b) Right-Right (LL) case: inserting 10, 20, 30\n");
    avl_insert(tree3, 10);
    avl_insert(tree3, 20);
    avl_insert(tree3, 30);
    printf("       Height: %d, Balanced: %s\n", 
           avl_height(tree3), avl_is_balanced(tree3) ? "yes" : "no");
    avl_print(tree3);
    
    avl_clear(tree3);
    
    printf("\n    c) Left-Right (LR) case: inserting 30, 10, 20\n");
    avl_insert(tree3, 30);
    avl_insert(tree3, 10);
    avl_insert(tree3, 20);
    printf("       Height: %d, Balanced: %s\n", 
           avl_height(tree3), avl_is_balanced(tree3) ? "yes" : "no");
    avl_print(tree3);
    
    avl_clear(tree3);
    
    printf("\n    d) Right-Left (RL) case: inserting 10, 30, 20\n");
    avl_insert(tree3, 10);
    avl_insert(tree3, 30);
    avl_insert(tree3, 20);
    printf("       Height: %d, Balanced: %s\n", 
           avl_height(tree3), avl_is_balanced(tree3) ? "yes" : "no");
    avl_print(tree3);
    
    printf("\n13. Testing duplicate insert (should fail)\n");
    if (avl_insert(tree, 50) == -1) {
        printf("    ✓ Correctly rejected duplicate key 50\n");
    }
    
    printf("\n14. Testing delete non-existent (should fail)\n");
    if (avl_delete(tree, 999) == -1) {
        printf("    ✓ Correctly rejected delete of non-existent key 999\n");
    }
    
    printf("\n15. Clearing tree\n");
    avl_clear(tree);
    printf("    Size: %zu, Empty: %s\n", avl_size(tree), avl_is_empty(tree) ? "yes" : "no");
    
    avl_destroy(tree);
    avl_destroy(tree2);
    avl_destroy(tree3);
    printf("\n16. All trees destroyed successfully\n");
    
    return 0;
}
