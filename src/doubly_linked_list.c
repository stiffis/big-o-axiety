#include "../include/doubly_linked_list.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

struct DoublyLinkedList {
    Node *head;
    Node *tail;
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

DoublyLinkedList* dlist_create(void) {
    struct DoublyLinkedList *list = malloc(sizeof(struct DoublyLinkedList));
    if (!list) {
        return NULL;
    }
    
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    
    return list;
}

void dlist_destroy(DoublyLinkedList *list) {
    if (!list) {
        return;
    }
    
    Node *current = list->head;
    while (current) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    
    free(list);
}

int dlist_push_front(DoublyLinkedList *list, int value) {
    if (!list) {
        return -1;
    }
    
    Node *node = _node_create(value);
    if (!node) {
        return -1;
    }
    
    if (!list->head) {
        list->head = node;
        list->tail = node;
    } else {
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }
    
    list->size++;
    return 0;
}

int dlist_push_back(DoublyLinkedList *list, int value) {
    if (!list) {
        return -1;
    }
    
    Node *node = _node_create(value);
    if (!node) {
        return -1;
    }
    
    if (!list->tail) {
        list->head = node;
        list->tail = node;
    } else {
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }
    
    list->size++;
    return 0;
}

int dlist_pop_front(DoublyLinkedList *list, int *out_value) {
    if (!list || !out_value || !list->head) {
        return -1;
    }
    
    Node *old_head = list->head;
    *out_value = old_head->data;
    
    list->head = old_head->next;
    
    if (list->head) {
        list->head->prev = NULL;
    } else {
        list->tail = NULL;
    }
    
    free(old_head);
    list->size--;
    
    return 0;
}

int dlist_pop_back(DoublyLinkedList *list, int *out_value) {
    if (!list || !out_value || !list->tail) {
        return -1;
    }
    
    Node *old_tail = list->tail;
    *out_value = old_tail->data;
    
    list->tail = old_tail->prev;
    
    if (list->tail) {
        list->tail->next = NULL;
    } else {
        list->head = NULL;
    }
    
    free(old_tail);
    list->size--;
    
    return 0;
}

int dlist_insert_at(DoublyLinkedList *list, size_t index, int value) {
    if (!list || index > list->size) {
        return -1;
    }
    
    if (index == 0) {
        return dlist_push_front(list, value);
    }
    
    if (index == list->size) {
        return dlist_push_back(list, value);
    }
    
    Node *current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    
    Node *node = _node_create(value);
    if (!node) {
        return -1;
    }
    
    node->next = current;
    node->prev = current->prev;
    current->prev->next = node;
    current->prev = node;
    
    list->size++;
    return 0;
}

int dlist_remove_at(DoublyLinkedList *list, size_t index, int *out_value) {
    if (!list || !list->head || index >= list->size) {
        return -1;
    }
    
    if (index == 0) {
        return dlist_pop_front(list, out_value);
    }
    
    if (index == list->size - 1) {
        return dlist_pop_back(list, out_value);
    }
    
    Node *current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    
    if (out_value) {
        *out_value = current->data;
    }
    
    current->prev->next = current->next;
    current->next->prev = current->prev;
    
    free(current);
    list->size--;
    
    return 0;
}

int dlist_get(const DoublyLinkedList *list, size_t index, int *out_value) {
    if (!list || !out_value || index >= list->size) {
        return -1;
    }
    
    Node *current;
    if (index < list->size / 2) {
        current = list->head;
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }
    } else {
        current = list->tail;
        for (size_t i = list->size - 1; i > index; i--) {
            current = current->prev;
        }
    }
    
    *out_value = current->data;
    return 0;
}

int dlist_set(DoublyLinkedList *list, size_t index, int value) {
    if (!list || index >= list->size) {
        return -1;
    }
    
    Node *current;
    if (index < list->size / 2) {
        current = list->head;
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }
    } else {
        current = list->tail;
        for (size_t i = list->size - 1; i > index; i--) {
            current = current->prev;
        }
    }
    
    current->data = value;
    return 0;
}

size_t dlist_size(const DoublyLinkedList *list) {
    if (!list) {
        return 0;
    }
    
    return list->size;
}

int dlist_is_empty(const DoublyLinkedList *list) {
    if (!list) {
        return 1;
    }
    
    return list->size == 0;
}

int dlist_find(const DoublyLinkedList *list, int value) {
    if (!list) {
        return -1;
    }
    
    Node *current = list->head;
    size_t index = 0;
    
    while (current) {
        if (current->data == value) {
            return (int)index;
        }
        current = current->next;
        index++;
    }
    
    return -1;
}

void dlist_clear(DoublyLinkedList *list) {
    if (!list) {
        return;
    }
    
    Node *current = list->head;
    while (current) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void dlist_reverse(DoublyLinkedList *list) {
    if (!list || !list->head) {
        return;
    }
    
    Node *current = list->head;
    Node *temp = NULL;
    
    while (current) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    
    temp = list->head;
    list->head = list->tail;
    list->tail = temp;
}

void dlist_print(const DoublyLinkedList *list) {
    if (!list) {
        printf("NULL\n");
        return;
    }
    
    printf("[");
    Node *current = list->head;
    while (current) {
        printf("%d", current->data);
        if (current->next) {
            printf(" <-> ");
        }
        current = current->next;
    }
    printf("] (size: %zu)\n", list->size);
}

void dlist_print_reverse(const DoublyLinkedList *list) {
    if (!list) {
        printf("NULL\n");
        return;
    }
    
    printf("[");
    Node *current = list->tail;
    while (current) {
        printf("%d", current->data);
        if (current->prev) {
            printf(" <-> ");
        }
        current = current->prev;
    }
    printf("] (size: %zu)\n", list->size);
}
