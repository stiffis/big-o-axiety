#include <stdio.h>
#include "../include/btree.h"

static void print_key(int key, void *user_data) {
    int *count = (int *)user_data;
    if (*count > 0) {
        printf(", ");
    }
    printf("%d", key);
    (*count)++;
}

int main(void) {
    printf("=== B-Tree Demo ===\n\n");
    
    BTree *tree = btree_create(3);
    if (!tree) {
        fprintf(stderr, "Error: Could not create tree\n");
        return 1;
    }
    
    printf("1. B-Tree created (t=3, max 5 keys per node)\n");
    printf("   Size: %zu, Height: %d, Empty: %s\n", 
           btree_size(tree), btree_height(tree), btree_is_empty(tree) ? "yes" : "no");
    
    printf("\n2. Inserting values: 10, 20, 5, 6, 12, 30, 7, 17\n");
    btree_insert(tree, 10);
    btree_insert(tree, 20);
    btree_insert(tree, 5);
    btree_insert(tree, 6);
    btree_insert(tree, 12);
    btree_insert(tree, 30);
    btree_insert(tree, 7);
    btree_insert(tree, 17);
    
    printf("   Size: %zu, Height: %d\n", btree_size(tree), btree_height(tree));
    btree_print(tree);
    
    printf("\n3. Searching for values\n");
    printf("   Search 12: %s\n", btree_search(tree, 12) ? "found" : "not found");
    printf("   Search 99: %s\n", btree_search(tree, 99) ? "found" : "not found");
    
    int min, max;
    btree_min(tree, &min);
    btree_max(tree, &max);
    printf("\n4. Min: %d, Max: %d\n", min, max);
    
    printf("\n5. In-order traversal (sorted): ");
    int count = 0;
    btree_traverse(tree, print_key, &count);
    printf("\n");
    
    printf("\n6. Converting to sorted array\n");
    int array[10];
    int n = btree_to_array(tree, array, 10);
    printf("   Array: [");
    for (int i = 0; i < n; i++) {
        printf("%d", array[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
    
    printf("\n7. Deleting value 6\n");
    btree_delete(tree, 6);
    printf("   Size: %zu, Height: %d\n", btree_size(tree), btree_height(tree));
    btree_print(tree);
    
    printf("\n8. Testing with t=2 (2-3-4 tree, max 3 keys per node)\n");
    BTree *tree2 = btree_create(2);
    printf("   Inserting 1 through 15\n");
    for (int i = 1; i <= 15; i++) {
        btree_insert(tree2, i);
    }
    printf("   Size: %zu, Height: %d\n", btree_size(tree2), btree_height(tree2));
    btree_print(tree2);
    
    printf("\n9. Testing node splitting with sequential inserts\n");
    BTree *tree3 = btree_create(3);
    printf("   Inserting 1, 2, 3, ..., 20\n");
    for (int i = 1; i <= 20; i++) {
        btree_insert(tree3, i);
        if (i == 5 || i == 10 || i == 15 || i == 20) {
            printf("   After inserting %d: size=%zu, height=%d\n", 
                   i, btree_size(tree3), btree_height(tree3));
        }
    }
    btree_print(tree3);
    
    printf("\n10. Testing deletion sequence\n");
    printf("    Deleting 1, 5, 10, 15, 20\n");
    btree_delete(tree3, 1);
    btree_delete(tree3, 5);
    btree_delete(tree3, 10);
    btree_delete(tree3, 15);
    btree_delete(tree3, 20);
    printf("    Size: %zu, Height: %d\n", btree_size(tree3), btree_height(tree3));
    
    printf("\n    Remaining keys (in-order): ");
    count = 0;
    btree_traverse(tree3, print_key, &count);
    printf("\n");
    
    printf("\n11. Testing with larger dataset\n");
    BTree *tree4 = btree_create(4);
    printf("    Inserting 100 keys\n");
    for (int i = 1; i <= 100; i++) {
        btree_insert(tree4, i);
    }
    printf("    Size: %zu, Height: %d\n", btree_size(tree4), btree_height(tree4));
    printf("    Min: %d, Max: %d\n", 1, 100);
    
    printf("\n    Deleting first 50 keys\n");
    for (int i = 1; i <= 50; i++) {
        btree_delete(tree4, i);
    }
    printf("    Size: %zu, Height: %d\n", btree_size(tree4), btree_height(tree4));
    
    btree_min(tree4, &min);
    btree_max(tree4, &max);
    printf("    New Min: %d, New Max: %d\n", min, max);
    
    printf("\n12. Testing duplicate insert (should fail)\n");
    if (btree_insert(tree, 10) == -1) {
        printf("    ✓ Correctly rejected duplicate key 10\n");
    }
    
    printf("\n13. Testing delete non-existent (should fail)\n");
    if (btree_delete(tree, 999) == -1) {
        printf("    ✓ Correctly rejected delete of non-existent key 999\n");
    }
    
    printf("\n14. Testing invalid min_degree (t=1, should fail)\n");
    BTree *invalid = btree_create(1);
    if (invalid == NULL) {
        printf("    ✓ Correctly rejected min_degree < 2\n");
    }
    
    printf("\n15. Clearing tree\n");
    btree_clear(tree);
    printf("    Size: %zu, Empty: %s\n", btree_size(tree), btree_is_empty(tree) ? "yes" : "no");
    
    btree_destroy(tree);
    btree_destroy(tree2);
    btree_destroy(tree3);
    btree_destroy(tree4);
    printf("\n16. All trees destroyed successfully\n");
    
    return 0;
}
