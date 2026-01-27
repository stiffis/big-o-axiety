#include "../include/avl.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct AVLNode {
    int key;
    int height;
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;

struct AVL {
    AVLNode *root;
    size_t size;
};

static int _max(int a, int b) {
    return (a > b) ? a : b;
}

static int _node_height(AVLNode *node) {
    return node ? node->height : 0;
}

static int _balance_factor(AVLNode *node) {
    return node ? _node_height(node->right) - _node_height(node->left) : 0;
}

static void _update_height(AVLNode *node) {
    if (node) {
        node->height = 1 + _max(_node_height(node->left), _node_height(node->right));
    }
}

static AVLNode* _rotate_left(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;
    
    y->left = x;
    x->right = T2;
    
    _update_height(x);
    _update_height(y);
    
    return y;
}

static AVLNode* _rotate_right(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;
    
    x->right = y;
    y->left = T2;
    
    _update_height(y);
    _update_height(x);
    
    return x;
}

static AVLNode* _balance(AVLNode *node) {
    if (!node) {
        return NULL;
    }
    
    _update_height(node);
    int bf = _balance_factor(node);
    
    if (bf > 1) {
        if (_balance_factor(node->right) < 0) {
            node->right = _rotate_right(node->right);
        }
        return _rotate_left(node);
    }
    
    if (bf < -1) {
        if (_balance_factor(node->left) > 0) {
            node->left = _rotate_left(node->left);
        }
        return _rotate_right(node);
    }
    
    return node;
}

static AVLNode* _create_node(int key) {
    AVLNode *node = malloc(sizeof(AVLNode));
    if (!node) {
        return NULL;
    }
    
    node->key = key;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    
    return node;
}

static AVLNode* _insert_node(AVLNode *node, int key, bool *inserted) {
    if (!node) {
        *inserted = true;
        return _create_node(key);
    }
    
    if (key < node->key) {
        node->left = _insert_node(node->left, key, inserted);
    } else if (key > node->key) {
        node->right = _insert_node(node->right, key, inserted);
    } else {
        *inserted = false;
        return node;
    }
    
    return _balance(node);
}

static AVLNode* _find_min_node(AVLNode *node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

static AVLNode* _delete_node(AVLNode *node, int key, bool *deleted) {
    if (!node) {
        *deleted = false;
        return NULL;
    }
    
    if (key < node->key) {
        node->left = _delete_node(node->left, key, deleted);
    } else if (key > node->key) {
        node->right = _delete_node(node->right, key, deleted);
    } else {
        *deleted = true;
        
        if (!node->left || !node->right) {
            AVLNode *temp = node->left ? node->left : node->right;
            free(node);
            return temp;
        }
        
        AVLNode *successor = _find_min_node(node->right);
        node->key = successor->key;
        node->right = _delete_node(node->right, successor->key, deleted);
        *deleted = true;
    }
    
    return _balance(node);
}

static bool _search_node(AVLNode *node, int key) {
    if (!node) {
        return false;
    }
    
    if (key == node->key) {
        return true;
    } else if (key < node->key) {
        return _search_node(node->left, key);
    } else {
        return _search_node(node->right, key);
    }
}

static void _destroy_nodes(AVLNode *node) {
    if (!node) {
        return;
    }
    
    _destroy_nodes(node->left);
    _destroy_nodes(node->right);
    free(node);
}

static void _inorder_traverse(AVLNode *node, void (*callback)(int, void*), void *user_data) {
    if (!node) {
        return;
    }
    
    _inorder_traverse(node->left, callback, user_data);
    callback(node->key, user_data);
    _inorder_traverse(node->right, callback, user_data);
}

static void _preorder_traverse(AVLNode *node, void (*callback)(int, void*), void *user_data) {
    if (!node) {
        return;
    }
    
    callback(node->key, user_data);
    _preorder_traverse(node->left, callback, user_data);
    _preorder_traverse(node->right, callback, user_data);
}

static void _postorder_traverse(AVLNode *node, void (*callback)(int, void*), void *user_data) {
    if (!node) {
        return;
    }
    
    _postorder_traverse(node->left, callback, user_data);
    _postorder_traverse(node->right, callback, user_data);
    callback(node->key, user_data);
}

static bool _check_balanced(AVLNode *node) {
    if (!node) {
        return true;
    }
    
    int bf = _balance_factor(node);
    if (bf < -1 || bf > 1) {
        return false;
    }
    
    return _check_balanced(node->left) && _check_balanced(node->right);
}

static void _print_tree_helper(AVLNode *node, int space, int level) {
    if (!node) {
        return;
    }
    
    space += level;
    
    _print_tree_helper(node->right, space, level);
    
    printf("\n");
    for (int i = level; i < space; i++) {
        printf(" ");
    }
    printf("%d(%d)\n", node->key, node->height);
    
    _print_tree_helper(node->left, space, level);
}

static void _to_array_helper(AVLNode *node, int *array, size_t *index) {
    if (!node) {
        return;
    }
    
    _to_array_helper(node->left, array, index);
    array[(*index)++] = node->key;
    _to_array_helper(node->right, array, index);
}

AVL* avl_create(void) {
    AVL *tree = malloc(sizeof(AVL));
    if (!tree) {
        return NULL;
    }
    
    tree->root = NULL;
    tree->size = 0;
    
    return tree;
}

void avl_destroy(AVL *tree) {
    if (!tree) {
        return;
    }
    
    _destroy_nodes(tree->root);
    free(tree);
}

int avl_insert(AVL *tree, int key) {
    if (!tree) {
        return -1;
    }
    
    bool inserted = false;
    tree->root = _insert_node(tree->root, key, &inserted);
    
    if (inserted) {
        tree->size++;
        return 0;
    }
    
    return -1;
}

int avl_delete(AVL *tree, int key) {
    if (!tree) {
        return -1;
    }
    
    bool deleted = false;
    tree->root = _delete_node(tree->root, key, &deleted);
    
    if (deleted) {
        tree->size--;
        return 0;
    }
    
    return -1;
}

void avl_clear(AVL *tree) {
    if (!tree) {
        return;
    }
    
    _destroy_nodes(tree->root);
    tree->root = NULL;
    tree->size = 0;
}

bool avl_search(const AVL *tree, int key) {
    if (!tree) {
        return false;
    }
    
    return _search_node(tree->root, key);
}

int avl_min(const AVL *tree, int *out_min) {
    if (!tree || !out_min || !tree->root) {
        return -1;
    }
    
    AVLNode *min_node = _find_min_node(tree->root);
    *out_min = min_node->key;
    return 0;
}

int avl_max(const AVL *tree, int *out_max) {
    if (!tree || !out_max || !tree->root) {
        return -1;
    }
    
    AVLNode *node = tree->root;
    while (node->right) {
        node = node->right;
    }
    
    *out_max = node->key;
    return 0;
}

size_t avl_size(const AVL *tree) {
    return tree ? tree->size : 0;
}

int avl_height(const AVL *tree) {
    return tree ? _node_height(tree->root) : 0;
}

bool avl_is_empty(const AVL *tree) {
    return !tree || tree->size == 0;
}

bool avl_is_balanced(const AVL *tree) {
    if (!tree) {
        return true;
    }
    
    return _check_balanced(tree->root);
}

void avl_inorder(const AVL *tree, void (*callback)(int key, void *user_data), void *user_data) {
    if (!tree || !callback) {
        return;
    }
    
    _inorder_traverse(tree->root, callback, user_data);
}

void avl_preorder(const AVL *tree, void (*callback)(int key, void *user_data), void *user_data) {
    if (!tree || !callback) {
        return;
    }
    
    _preorder_traverse(tree->root, callback, user_data);
}

void avl_postorder(const AVL *tree, void (*callback)(int key, void *user_data), void *user_data) {
    if (!tree || !callback) {
        return;
    }
    
    _postorder_traverse(tree->root, callback, user_data);
}

void avl_print(const AVL *tree) {
    if (!tree) {
        printf("NULL\n");
        return;
    }
    
    if (!tree->root) {
        printf("(empty tree)\n");
        return;
    }
    
    printf("AVL Tree (size: %zu, height: %d):\n", tree->size, avl_height(tree));
    _print_tree_helper(tree->root, 0, 4);
    printf("\n");
}

int avl_to_array(const AVL *tree, int *out_array, size_t array_size) {
    if (!tree || !out_array || array_size < tree->size) {
        return -1;
    }
    
    size_t index = 0;
    _to_array_helper(tree->root, out_array, &index);
    
    return (int)index;
}
