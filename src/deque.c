#include "../include/deque.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

struct Deque {
    Node *front;
    Node *rear;
    size_t size;
};

static Node* _node_create(int value) {
    Node *node = malloc(sizeof(Node));
    if (!node) {
        return NULL;
    }
    
    node->data = value;
    node->next = NULL;
    node->prev = NULL;
    
    return node;
}

Deque* deque_create(void) {
    Deque *deque = malloc(sizeof(Deque));
    if (!deque) {
        return NULL;
    }
    
    deque->front = NULL;
    deque->rear = NULL;
    deque->size = 0;
    
    return deque;
}

void deque_destroy(Deque *deque) {
    if (!deque) {
        return;
    }
    
    Node *current = deque->front;
    while (current) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    
    free(deque);
}

int deque_push_front(Deque *deque, int value) {
    if (!deque) {
        return -1;
    }
    
    Node *node = _node_create(value);
    if (!node) {
        return -1;
    }
    
    if (!deque->front) {
        deque->front = node;
        deque->rear = node;
    } else {
        node->next = deque->front;
        deque->front->prev = node;
        deque->front = node;
    }
    
    deque->size++;
    return 0;
}

int deque_push_back(Deque *deque, int value) {
    if (!deque) {
        return -1;
    }
    
    Node *node = _node_create(value);
    if (!node) {
        return -1;
    }
    
    if (!deque->rear) {
        deque->front = node;
        deque->rear = node;
    } else {
        node->prev = deque->rear;
        deque->rear->next = node;
        deque->rear = node;
    }
    
    deque->size++;
    return 0;
}

int deque_pop_front(Deque *deque, int *out_value) {
    if (!deque || !out_value || !deque->front) {
        return -1;
    }
    
    Node *old_front = deque->front;
    *out_value = old_front->data;
    
    deque->front = old_front->next;
    
    if (deque->front) {
        deque->front->prev = NULL;
    } else {
        deque->rear = NULL;
    }
    
    free(old_front);
    deque->size--;
    
    return 0;
}

int deque_pop_back(Deque *deque, int *out_value) {
    if (!deque || !out_value || !deque->rear) {
        return -1;
    }
    
    Node *old_rear = deque->rear;
    *out_value = old_rear->data;
    
    deque->rear = old_rear->prev;
    
    if (deque->rear) {
        deque->rear->next = NULL;
    } else {
        deque->front = NULL;
    }
    
    free(old_rear);
    deque->size--;
    
    return 0;
}

int deque_peek_front(const Deque *deque, int *out_value) {
    if (!deque || !out_value || !deque->front) {
        return -1;
    }
    
    *out_value = deque->front->data;
    return 0;
}

int deque_peek_back(const Deque *deque, int *out_value) {
    if (!deque || !out_value || !deque->rear) {
        return -1;
    }
    
    *out_value = deque->rear->data;
    return 0;
}

size_t deque_size(const Deque *deque) {
    if (!deque) {
        return 0;
    }
    
    return deque->size;
}

int deque_is_empty(const Deque *deque) {
    if (!deque) {
        return 1;
    }
    
    return deque->size == 0;
}

void deque_clear(Deque *deque) {
    if (!deque) {
        return;
    }
    
    Node *current = deque->front;
    while (current) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    
    deque->front = NULL;
    deque->rear = NULL;
    deque->size = 0;
}

void deque_print(const Deque *deque) {
    if (!deque) {
        printf("NULL\n");
        return;
    }
    
    printf("[");
    Node *current = deque->front;
    while (current) {
        printf("%d", current->data);
        if (current->next) {
            printf(" <-> ");
        }
        current = current->next;
    }
    printf("] (size: %zu)\n", deque->size);
}
