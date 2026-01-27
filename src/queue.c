#include "../include/queue.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

struct Queue {
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
    
    return node;
}

Queue* queue_create(void) {
    struct Queue *queue = malloc(sizeof(struct Queue));
    if (!queue) {
        return NULL;
    }
    
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    
    return queue;
}

void queue_destroy(Queue *queue) {
    if (!queue) {
        return;
    }
    
    Node *current = queue->front;
    while (current) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    
    free(queue);
}

int queue_enqueue(Queue *queue, int value) {
    if (!queue) {
        return -1;
    }
    
    Node *node = _node_create(value);
    if (!node) {
        return -1;
    }
    
    if (!queue->rear) {
        queue->front = node;
        queue->rear = node;
    } else {
        queue->rear->next = node;
        queue->rear = node;
    }
    
    queue->size++;
    return 0;
}

int queue_dequeue(Queue *queue, int *out_value) {
    if (!queue || !out_value || !queue->front) {
        return -1;
    }
    
    Node *old_front = queue->front;
    *out_value = old_front->data;
    
    queue->front = old_front->next;
    
    if (!queue->front) {
        queue->rear = NULL;
    }
    
    free(old_front);
    queue->size--;
    
    return 0;
}

int queue_peek(const Queue *queue, int *out_value) {
    if (!queue || !out_value || !queue->front) {
        return -1;
    }
    
    *out_value = queue->front->data;
    return 0;
}

size_t queue_size(const Queue *queue) {
    if (!queue) {
        return 0;
    }
    
    return queue->size;
}

int queue_is_empty(const Queue *queue) {
    if (!queue) {
        return 1;
    }
    
    return queue->size == 0;
}

void queue_clear(Queue *queue) {
    if (!queue) {
        return;
    }
    
    Node *current = queue->front;
    while (current) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}

void queue_print(const Queue *queue) {
    if (!queue) {
        printf("NULL\n");
        return;
    }
    
    printf("[");
    Node *current = queue->front;
    while (current) {
        printf("%d", current->data);
        if (current->next) {
            printf(" <- ");
        }
        current = current->next;
    }
    printf("] (size: %zu, front: ", queue->size);
    
    if (queue->front) {
        printf("%d", queue->front->data);
    } else {
        printf("empty");
    }
    printf(", rear: ");
    
    if (queue->rear) {
        printf("%d", queue->rear->data);
    } else {
        printf("empty");
    }
    printf(")\n");
}
