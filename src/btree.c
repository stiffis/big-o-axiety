#include "../include/btree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct BTreeNode {
    int *keys;
    struct BTreeNode **children;
    int num_keys;
    bool is_leaf;
} BTreeNode;

struct BTree {
    BTreeNode *root;
    int min_degree;
    size_t size;
};

static BTreeNode* _create_node(int min_degree, bool is_leaf) {
    BTreeNode *node = malloc(sizeof(BTreeNode));
    if (!node) {
        return NULL;
    }
    
    node->keys = malloc((2 * min_degree - 1) * sizeof(int));
    node->children = malloc(2 * min_degree * sizeof(BTreeNode*));
    
    if (!node->keys || !node->children) {
        free(node->keys);
        free(node->children);
        free(node);
        return NULL;
    }
    
    node->num_keys = 0;
    node->is_leaf = is_leaf;
    
    for (int i = 0; i < 2 * min_degree; i++) {
        node->children[i] = NULL;
    }
    
    return node;
}

static void _destroy_node(BTreeNode *node) {
    if (!node) {
        return;
    }
    
    if (!node->is_leaf) {
        for (int i = 0; i <= node->num_keys; i++) {
            _destroy_node(node->children[i]);
        }
    }
    
    free(node->keys);
    free(node->children);
    free(node);
}

static void _split_child(BTreeNode *parent, int index, int min_degree) {
    BTreeNode *full_child = parent->children[index];
    BTreeNode *new_child = _create_node(min_degree, full_child->is_leaf);
    
    int mid = min_degree - 1;
    new_child->num_keys = min_degree - 1;
    
    for (int i = 0; i < min_degree - 1; i++) {
        new_child->keys[i] = full_child->keys[i + min_degree];
    }
    
    if (!full_child->is_leaf) {
        for (int i = 0; i < min_degree; i++) {
            new_child->children[i] = full_child->children[i + min_degree];
        }
    }
    
    full_child->num_keys = min_degree - 1;
    
    for (int i = parent->num_keys; i > index; i--) {
        parent->children[i + 1] = parent->children[i];
    }
    parent->children[index + 1] = new_child;
    
    for (int i = parent->num_keys - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }
    parent->keys[index] = full_child->keys[mid];
    parent->num_keys++;
}

static bool _insert_non_full(BTreeNode *node, int key, int min_degree) {
    int i = node->num_keys - 1;
    
    if (node->is_leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        
        if (i >= 0 && key == node->keys[i]) {
            return false;
        }
        
        node->keys[i + 1] = key;
        node->num_keys++;
        return true;
    }
    
    while (i >= 0 && key < node->keys[i]) {
        i--;
    }
    i++;
    
    if (i > 0 && i <= node->num_keys && node->keys[i - 1] == key) {
        return false;
    }
    
    if (node->children[i]->num_keys == 2 * min_degree - 1) {
        _split_child(node, i, min_degree);
        
        if (key > node->keys[i]) {
            i++;
        } else if (key == node->keys[i]) {
            return false;
        }
    }
    
    return _insert_non_full(node->children[i], key, min_degree);
}

static bool _search_node(BTreeNode *node, int key) {
    if (!node) {
        return false;
    }
    
    int i = 0;
    while (i < node->num_keys && key > node->keys[i]) {
        i++;
    }
    
    if (i < node->num_keys && key == node->keys[i]) {
        return true;
    }
    
    if (node->is_leaf) {
        return false;
    }
    
    return _search_node(node->children[i], key);
}

static int _find_predecessor(BTreeNode *node) {
    while (!node->is_leaf) {
        node = node->children[node->num_keys];
    }
    return node->keys[node->num_keys - 1];
}

static int _find_successor(BTreeNode *node) {
    while (!node->is_leaf) {
        node = node->children[0];
    }
    return node->keys[0];
}

static void _merge(BTreeNode *parent, int idx, int min_degree) {
    BTreeNode *left = parent->children[idx];
    BTreeNode *right = parent->children[idx + 1];
    
    left->keys[min_degree - 1] = parent->keys[idx];
    
    for (int i = 0; i < right->num_keys; i++) {
        left->keys[i + min_degree] = right->keys[i];
    }
    
    if (!left->is_leaf) {
        for (int i = 0; i <= right->num_keys; i++) {
            left->children[i + min_degree] = right->children[i];
        }
    }
    
    left->num_keys += right->num_keys + 1;
    
    for (int i = idx; i < parent->num_keys - 1; i++) {
        parent->keys[i] = parent->keys[i + 1];
    }
    
    for (int i = idx + 1; i < parent->num_keys; i++) {
        parent->children[i] = parent->children[i + 1];
    }
    
    parent->num_keys--;
    
    free(right->keys);
    free(right->children);
    free(right);
}

static void _borrow_from_prev(BTreeNode *parent, int idx) {
    BTreeNode *child = parent->children[idx];
    BTreeNode *sibling = parent->children[idx - 1];
    
    for (int i = child->num_keys - 1; i >= 0; i--) {
        child->keys[i + 1] = child->keys[i];
    }
    
    if (!child->is_leaf) {
        for (int i = child->num_keys; i >= 0; i--) {
            child->children[i + 1] = child->children[i];
        }
        child->children[0] = sibling->children[sibling->num_keys];
    }
    
    child->keys[0] = parent->keys[idx - 1];
    parent->keys[idx - 1] = sibling->keys[sibling->num_keys - 1];
    
    child->num_keys++;
    sibling->num_keys--;
}

static void _borrow_from_next(BTreeNode *parent, int idx) {
    BTreeNode *child = parent->children[idx];
    BTreeNode *sibling = parent->children[idx + 1];
    
    child->keys[child->num_keys] = parent->keys[idx];
    
    if (!child->is_leaf) {
        child->children[child->num_keys + 1] = sibling->children[0];
    }
    
    parent->keys[idx] = sibling->keys[0];
    
    for (int i = 0; i < sibling->num_keys - 1; i++) {
        sibling->keys[i] = sibling->keys[i + 1];
    }
    
    if (!sibling->is_leaf) {
        for (int i = 0; i < sibling->num_keys; i++) {
            sibling->children[i] = sibling->children[i + 1];
        }
    }
    
    child->num_keys++;
    sibling->num_keys--;
}

static void _fill(BTreeNode *parent, int idx, int min_degree) {
    if (idx != 0 && parent->children[idx - 1]->num_keys >= min_degree) {
        _borrow_from_prev(parent, idx);
    } else if (idx != parent->num_keys && parent->children[idx + 1]->num_keys >= min_degree) {
        _borrow_from_next(parent, idx);
    } else {
        if (idx != parent->num_keys) {
            _merge(parent, idx, min_degree);
        } else {
            _merge(parent, idx - 1, min_degree);
        }
    }
}

static bool _delete_from_node(BTreeNode *node, int key, int min_degree) {
    int idx = 0;
    while (idx < node->num_keys && key > node->keys[idx]) {
        idx++;
    }
    
    if (idx < node->num_keys && key == node->keys[idx]) {
        if (node->is_leaf) {
            for (int i = idx; i < node->num_keys - 1; i++) {
                node->keys[i] = node->keys[i + 1];
            }
            node->num_keys--;
            return true;
        } else {
            if (node->children[idx]->num_keys >= min_degree) {
                int pred = _find_predecessor(node->children[idx]);
                node->keys[idx] = pred;
                return _delete_from_node(node->children[idx], pred, min_degree);
            } else if (node->children[idx + 1]->num_keys >= min_degree) {
                int succ = _find_successor(node->children[idx + 1]);
                node->keys[idx] = succ;
                return _delete_from_node(node->children[idx + 1], succ, min_degree);
            } else {
                _merge(node, idx, min_degree);
                return _delete_from_node(node->children[idx], key, min_degree);
            }
        }
    } else {
        if (node->is_leaf) {
            return false;
        }
        
        bool is_in_subtree = (idx == node->num_keys);
        
        if (node->children[idx]->num_keys < min_degree) {
            _fill(node, idx, min_degree);
        }
        
        if (is_in_subtree && idx > node->num_keys) {
            return _delete_from_node(node->children[idx - 1], key, min_degree);
        } else {
            return _delete_from_node(node->children[idx], key, min_degree);
        }
    }
}

static void _traverse(BTreeNode *node, void (*callback)(int, void*), void *user_data) {
    if (!node) {
        return;
    }
    
    int i;
    for (i = 0; i < node->num_keys; i++) {
        if (!node->is_leaf) {
            _traverse(node->children[i], callback, user_data);
        }
        callback(node->keys[i], user_data);
    }
    
    if (!node->is_leaf) {
        _traverse(node->children[i], callback, user_data);
    }
}

static int _get_height(BTreeNode *node) {
    if (!node) {
        return 0;
    }
    
    if (node->is_leaf) {
        return 1;
    }
    
    return 1 + _get_height(node->children[0]);
}

static void _print_node(BTreeNode *node, int level) {
    if (!node) {
        return;
    }
    
    printf("Level %d: [", level);
    for (int i = 0; i < node->num_keys; i++) {
        printf("%d", node->keys[i]);
        if (i < node->num_keys - 1) {
            printf(", ");
        }
    }
    printf("]%s\n", node->is_leaf ? " (leaf)" : "");
    
    if (!node->is_leaf) {
        for (int i = 0; i <= node->num_keys; i++) {
            _print_node(node->children[i], level + 1);
        }
    }
}

static void _to_array_helper(BTreeNode *node, int *array, size_t *index) {
    if (!node) {
        return;
    }
    
    int i;
    for (i = 0; i < node->num_keys; i++) {
        if (!node->is_leaf) {
            _to_array_helper(node->children[i], array, index);
        }
        array[(*index)++] = node->keys[i];
    }
    
    if (!node->is_leaf) {
        _to_array_helper(node->children[i], array, index);
    }
}

BTree* btree_create(int min_degree) {
    if (min_degree < 2) {
        return NULL;
    }
    
    BTree *tree = malloc(sizeof(BTree));
    if (!tree) {
        return NULL;
    }
    
    tree->root = NULL;
    tree->min_degree = min_degree;
    tree->size = 0;
    
    return tree;
}

void btree_destroy(BTree *tree) {
    if (!tree) {
        return;
    }
    
    _destroy_node(tree->root);
    free(tree);
}

int btree_insert(BTree *tree, int key) {
    if (!tree) {
        return -1;
    }
    
    if (!tree->root) {
        tree->root = _create_node(tree->min_degree, true);
        if (!tree->root) {
            return -1;
        }
        tree->root->keys[0] = key;
        tree->root->num_keys = 1;
        tree->size++;
        return 0;
    }
    
    if (tree->root->num_keys == 2 * tree->min_degree - 1) {
        BTreeNode *new_root = _create_node(tree->min_degree, false);
        if (!new_root) {
            return -1;
        }
        
        new_root->children[0] = tree->root;
        _split_child(new_root, 0, tree->min_degree);
        tree->root = new_root;
    }
    
    bool inserted = _insert_non_full(tree->root, key, tree->min_degree);
    if (inserted) {
        tree->size++;
        return 0;
    }
    
    return -1;
}

int btree_delete(BTree *tree, int key) {
    if (!tree || !tree->root) {
        return -1;
    }
    
    bool deleted = _delete_from_node(tree->root, key, tree->min_degree);
    
    if (deleted) {
        tree->size--;
        
        if (tree->root->num_keys == 0) {
            BTreeNode *old_root = tree->root;
            tree->root = tree->root->is_leaf ? NULL : tree->root->children[0];
            
            free(old_root->keys);
            free(old_root->children);
            free(old_root);
        }
        
        return 0;
    }
    
    return -1;
}

void btree_clear(BTree *tree) {
    if (!tree) {
        return;
    }
    
    _destroy_node(tree->root);
    tree->root = NULL;
    tree->size = 0;
}

bool btree_search(const BTree *tree, int key) {
    if (!tree || !tree->root) {
        return false;
    }
    
    return _search_node(tree->root, key);
}

int btree_min(const BTree *tree, int *out_min) {
    if (!tree || !out_min || !tree->root) {
        return -1;
    }
    
    BTreeNode *node = tree->root;
    while (!node->is_leaf) {
        node = node->children[0];
    }
    
    *out_min = node->keys[0];
    return 0;
}

int btree_max(const BTree *tree, int *out_max) {
    if (!tree || !out_max || !tree->root) {
        return -1;
    }
    
    BTreeNode *node = tree->root;
    while (!node->is_leaf) {
        node = node->children[node->num_keys];
    }
    
    *out_max = node->keys[node->num_keys - 1];
    return 0;
}

size_t btree_size(const BTree *tree) {
    return tree ? tree->size : 0;
}

int btree_height(const BTree *tree) {
    return tree ? _get_height(tree->root) : 0;
}

bool btree_is_empty(const BTree *tree) {
    return !tree || tree->size == 0;
}

int btree_min_degree(const BTree *tree) {
    return tree ? tree->min_degree : 0;
}

void btree_traverse(const BTree *tree, void (*callback)(int key, void *user_data), void *user_data) {
    if (!tree || !callback) {
        return;
    }
    
    _traverse(tree->root, callback, user_data);
}

void btree_print(const BTree *tree) {
    if (!tree) {
        printf("NULL\n");
        return;
    }
    
    if (!tree->root) {
        printf("(empty B-tree, t=%d)\n", tree->min_degree);
        return;
    }
    
    printf("B-Tree (size: %zu, height: %d, min_degree: %d):\n", 
           tree->size, btree_height(tree), tree->min_degree);
    _print_node(tree->root, 0);
    printf("\n");
}

int btree_to_array(const BTree *tree, int *out_array, size_t array_size) {
    if (!tree || !out_array || array_size < tree->size) {
        return -1;
    }
    
    size_t index = 0;
    _to_array_helper(tree->root, out_array, &index);
    
    return (int)index;
}

bool btree_is_valid(const BTree *tree) {
    if (!tree) {
        return true;
    }
    
    if (!tree->root) {
        return tree->size == 0;
    }
    
    return true;
}
