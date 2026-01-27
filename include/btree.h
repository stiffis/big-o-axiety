#ifndef BTREE_H
#define BTREE_H

#include <stddef.h>
#include <stdbool.h>

/**
 * B-Tree - Self-balancing multiway search tree
 * 
 * Key concepts:
 * - Minimum degree t (t >= 2): each node has at least t-1 keys
 * - Each node has at most 2t-1 keys
 * - All leaves are at the same depth
 * - Node splits when full (2t-1 keys)
 * - Optimized for disk I/O (high branching factor)
 * 
 * Properties for node with n keys:
 * - Keys: k[0] < k[1] < ... < k[n-1]
 * - Children: n+1 pointers
 * - All keys in child[i] < k[i] < all keys in child[i+1]
 */

typedef struct BTree BTree;

/* ========== CONSTRUCTORS AND DESTRUCTORS ========== */

/**
 * Creates a new empty B-tree with minimum degree t
 * @param min_degree Minimum degree (must be >= 2)
 * @return Pointer to tree, or NULL if malloc fails or t < 2
 * 
 * min_degree = 2 -> 2-3-4 tree (max 3 keys per node)
 * min_degree = 3 -> max 5 keys per node
 */
BTree* btree_create(int min_degree);

/**
 * Frees all tree memory (nodes and tree structure)
 * @param tree Tree to destroy (can be NULL)
 */
void btree_destroy(BTree *tree);

/* ========== MODIFIERS ========== */

/**
 * Inserts a key into the tree (maintains B-tree properties)
 * @param tree Target tree
 * @param key Key to insert
 * @return 0 on success, -1 on error (duplicate key or NULL tree)
 * 
 * Automatically splits nodes when full
 * Complexity: O(t * log_t(n))
 */
int btree_insert(BTree *tree, int key);

/**
 * Deletes a key from the tree (maintains B-tree properties)
 * @param tree Target tree
 * @param key Key to delete
 * @return 0 on success, -1 on error (key not found or NULL tree)
 * 
 * Automatically merges/borrows when nodes become too small
 * Complexity: O(t * log_t(n))
 */
int btree_delete(BTree *tree, int key);

/**
 * Removes all nodes from the tree
 * @param tree Target tree
 */
void btree_clear(BTree *tree);

/* ========== ACCESSORS (QUERY) ========== */

/**
 * Searches for a key in the tree
 * @param tree Target tree
 * @param key Key to search for
 * @return true if found, false otherwise
 * 
 * Complexity: O(t * log_t(n))
 */
bool btree_search(const BTree *tree, int key);

/**
 * Finds the minimum key in the tree
 * @param tree Target tree
 * @param out_min Pointer to store minimum key
 * @return 0 on success, -1 if tree is empty or NULL
 */
int btree_min(const BTree *tree, int *out_min);

/**
 * Finds the maximum key in the tree
 * @param tree Target tree
 * @param out_max Pointer to store maximum key
 * @return 0 on success, -1 if tree is empty or NULL
 */
int btree_max(const BTree *tree, int *out_max);

/**
 * Returns the number of keys in the tree
 * @param tree Target tree
 * @return Number of keys (0 if tree is NULL or empty)
 */
size_t btree_size(const BTree *tree);

/**
 * Returns the height of the tree
 * @param tree Target tree
 * @return Height (0 for empty tree)
 */
int btree_height(const BTree *tree);

/**
 * Checks if the tree is empty
 * @param tree Target tree
 * @return true if empty or NULL, false otherwise
 */
bool btree_is_empty(const BTree *tree);

/**
 * Returns the minimum degree of the tree
 * @param tree Target tree
 * @return Minimum degree (0 if tree is NULL)
 */
int btree_min_degree(const BTree *tree);

/* ========== TRAVERSALS ========== */

/**
 * Performs in-order traversal (visits keys in sorted order)
 * @param tree Target tree
 * @param callback Function to call for each key
 * @param user_data User data passed to callback
 * 
 * Complexity: O(n)
 */
void btree_traverse(const BTree *tree, void (*callback)(int key, void *user_data), void *user_data);

/* ========== UTILITIES ========== */

/**
 * Prints the tree structure (useful for debugging)
 * @param tree Target tree
 */
void btree_print(const BTree *tree);

/**
 * Converts tree to sorted array (in-order)
 * @param tree Target tree
 * @param out_array Output array (must have space for btree_size(tree) elements)
 * @param array_size Size of output array
 * @return Number of elements written, or -1 on error
 * 
 * Complexity: O(n)
 */
int btree_to_array(const BTree *tree, int *out_array, size_t array_size);

/**
 * Validates B-tree properties (for testing)
 * @param tree Target tree
 * @return true if valid, false otherwise
 * 
 * Checks:
 * - All leaves at same depth
 * - Keys in sorted order
 * - Node key counts within bounds
 * - Subtree key ordering
 */
bool btree_is_valid(const BTree *tree);

#endif // BTREE_H
