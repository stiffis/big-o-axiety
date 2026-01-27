#ifndef AVL_H
#define AVL_H

#include <stddef.h>
#include <stdbool.h>

/**
 * AVL Tree - Self-balancing binary search tree
 * 
 * Key concepts:
 * - Height-balanced BST (balance factor: -1, 0, +1)
 * - Automatic rebalancing via rotations after insert/delete
 * - O(log n) search, insert, delete operations
 * - Balance factor = height(right) - height(left)
 * 
 * Rotations:
 * - Left rotation (LL)
 * - Right rotation (RR)
 * - Left-Right rotation (LR)
 * - Right-Left rotation (RL)
 */

typedef struct AVL AVL;

/* ========== CONSTRUCTORS AND DESTRUCTORS ========== */

/**
 * Creates a new empty AVL tree
 * @return Pointer to tree, or NULL if malloc fails
 */
AVL* avl_create(void);

/**
 * Frees all tree memory (nodes and tree structure)
 * @param tree Tree to destroy (can be NULL)
 */
void avl_destroy(AVL *tree);

/* ========== MODIFIERS ========== */

/**
 * Inserts a key into the tree (maintains balance)
 * @param tree Target tree
 * @param key Key to insert
 * @return 0 on success, -1 on error (duplicate key or NULL tree)
 * 
 * Automatically rebalances after insertion
 * Complexity: O(log n)
 */
int avl_insert(AVL *tree, int key);

/**
 * Deletes a key from the tree (maintains balance)
 * @param tree Target tree
 * @param key Key to delete
 * @return 0 on success, -1 on error (key not found or NULL tree)
 * 
 * Automatically rebalances after deletion
 * Complexity: O(log n)
 */
int avl_delete(AVL *tree, int key);

/**
 * Removes all nodes from the tree
 * @param tree Target tree
 */
void avl_clear(AVL *tree);

/* ========== ACCESSORS (QUERY) ========== */

/**
 * Searches for a key in the tree
 * @param tree Target tree
 * @param key Key to search for
 * @return true if found, false otherwise
 * 
 * Complexity: O(log n)
 */
bool avl_search(const AVL *tree, int key);

/**
 * Finds the minimum key in the tree
 * @param tree Target tree
 * @param out_min Pointer to store minimum key
 * @return 0 on success, -1 if tree is empty or NULL
 * 
 * Complexity: O(log n)
 */
int avl_min(const AVL *tree, int *out_min);

/**
 * Finds the maximum key in the tree
 * @param tree Target tree
 * @param out_max Pointer to store maximum key
 * @return 0 on success, -1 if tree is empty or NULL
 * 
 * Complexity: O(log n)
 */
int avl_max(const AVL *tree, int *out_max);

/**
 * Returns the number of nodes in the tree
 * @param tree Target tree
 * @return Number of nodes (0 if tree is NULL or empty)
 */
size_t avl_size(const AVL *tree);

/**
 * Returns the height of the tree
 * @param tree Target tree
 * @return Height (0 for empty tree, 1 for single node)
 */
int avl_height(const AVL *tree);

/**
 * Checks if the tree is empty
 * @param tree Target tree
 * @return true if empty or NULL, false otherwise
 */
bool avl_is_empty(const AVL *tree);

/**
 * Checks if the tree is balanced (for testing/validation)
 * @param tree Target tree
 * @return true if balanced, false otherwise
 * 
 * Verifies that all nodes have balance factor in [-1, 0, +1]
 */
bool avl_is_balanced(const AVL *tree);

/* ========== TRAVERSALS ========== */

/**
 * Performs in-order traversal (left, root, right)
 * @param tree Target tree
 * @param callback Function to call for each key
 * @param user_data User data passed to callback
 * 
 * Visits nodes in sorted order
 * Complexity: O(n)
 */
void avl_inorder(const AVL *tree, void (*callback)(int key, void *user_data), void *user_data);

/**
 * Performs pre-order traversal (root, left, right)
 * @param tree Target tree
 * @param callback Function to call for each key
 * @param user_data User data passed to callback
 * 
 * Complexity: O(n)
 */
void avl_preorder(const AVL *tree, void (*callback)(int key, void *user_data), void *user_data);

/**
 * Performs post-order traversal (left, right, root)
 * @param tree Target tree
 * @param callback Function to call for each key
 * @param user_data User data passed to callback
 * 
 * Complexity: O(n)
 */
void avl_postorder(const AVL *tree, void (*callback)(int key, void *user_data), void *user_data);

/* ========== UTILITIES ========== */

/**
 * Prints the tree structure (useful for debugging)
 * @param tree Target tree
 */
void avl_print(const AVL *tree);

/**
 * Converts tree to sorted array (in-order)
 * @param tree Target tree
 * @param out_array Output array (must have space for avl_size(tree) elements)
 * @param array_size Size of output array
 * @return Number of elements written, or -1 on error
 * 
 * Complexity: O(n)
 */
int avl_to_array(const AVL *tree, int *out_array, size_t array_size);

#endif // AVL_H
