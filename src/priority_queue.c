#include "../include/priority_queue.h"
#include <stdlib.h>
#include <stdio.h>

struct PriorityQueue {
    int *data;
    size_t size;
    size_t capacity;
};

static void _swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void _heapify_up(PriorityQueue *pq, size_t index) {
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        
        if (pq->data[index] >= pq->data[parent]) {
            break;
        }
        
        _swap(&pq->data[index], &pq->data[parent]);
        index = parent;
    }
}

static void _heapify_down(PriorityQueue *pq, size_t index) {
    while (1) {
        size_t smallest = index;
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;
        
        if (left < pq->size && pq->data[left] < pq->data[smallest]) {
            smallest = left;
        }
        
        if (right < pq->size && pq->data[right] < pq->data[smallest]) {
            smallest = right;
        }
        
        if (smallest == index) {
            break;
        }
        
        _swap(&pq->data[index], &pq->data[smallest]);
        index = smallest;
    }
}

PriorityQueue* pqueue_create(size_t capacity) {
    if (capacity == 0) {
        capacity = 16;
    }
    
    PriorityQueue *pq = malloc(sizeof(PriorityQueue));
    if (!pq) {
        return NULL;
    }
    
    pq->data = malloc(sizeof(int) * capacity);
    if (!pq->data) {
        free(pq);
        return NULL;
    }
    
    pq->size = 0;
    pq->capacity = capacity;
    
    return pq;
}

void pqueue_destroy(PriorityQueue *pq) {
    if (!pq) {
        return;
    }
    
    free(pq->data);
    free(pq);
}

int pqueue_push(PriorityQueue *pq, int value) {
    if (!pq) {
        return -1;
    }
    
    if (pq->size == pq->capacity) {
        size_t new_capacity = pq->capacity * 2;
        int *new_data = realloc(pq->data, sizeof(int) * new_capacity);
        if (!new_data) {
            return -1;
        }
        pq->data = new_data;
        pq->capacity = new_capacity;
    }
    
    pq->data[pq->size] = value;
    _heapify_up(pq, pq->size);
    pq->size++;
    
    return 0;
}

int pqueue_pop(PriorityQueue *pq, int *out_value) {
    if (!pq || !out_value || pq->size == 0) {
        return -1;
    }
    
    *out_value = pq->data[0];
    
    pq->size--;
    if (pq->size > 0) {
        pq->data[0] = pq->data[pq->size];
        _heapify_down(pq, 0);
    }
    
    return 0;
}

int pqueue_peek(const PriorityQueue *pq, int *out_value) {
    if (!pq || !out_value || pq->size == 0) {
        return -1;
    }
    
    *out_value = pq->data[0];
    return 0;
}

size_t pqueue_size(const PriorityQueue *pq) {
    if (!pq) {
        return 0;
    }
    
    return pq->size;
}

size_t pqueue_capacity(const PriorityQueue *pq) {
    if (!pq) {
        return 0;
    }
    
    return pq->capacity;
}

int pqueue_is_empty(const PriorityQueue *pq) {
    if (!pq) {
        return 1;
    }
    
    return pq->size == 0;
}

void pqueue_clear(PriorityQueue *pq) {
    if (!pq) {
        return;
    }
    
    pq->size = 0;
}

void pqueue_print(const PriorityQueue *pq) {
    if (!pq) {
        printf("NULL\n");
        return;
    }
    
    printf("[");
    for (size_t i = 0; i < pq->size; i++) {
        printf("%d", pq->data[i]);
        if (i < pq->size - 1) {
            printf(", ");
        }
    }
    printf("] (size: %zu, capacity: %zu)\n", pq->size, pq->capacity);
}
