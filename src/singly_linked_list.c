#include "../include/singly_linked_list.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

struct SinglyLinkedList {
    Node *head;
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

SinglyLinkedList* slist_create(void) {
    struct SinglyLinkedList *list = malloc(sizeof(struct SinglyLinkedList));
    if (!list) {
        return NULL;
    }
    
    list->head = NULL;
    list->size = 0;
    
    return list;
}

void slist_destroy(SinglyLinkedList *list) {
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

int slist_push_front(SinglyLinkedList *list, int value) {
    if (!list) {
        return -1;
    }
    
    Node *node = _node_create(value);
    if (!node) {
        return -1;
    }
    
    node->next = list->head;
    list->head = node;
    list->size++;
    
    return 0;
}

int slist_push_back(SinglyLinkedList *list, int value) {
    if (!list) {
        return -1;
    }
    
    Node *node = _node_create(value);
    if (!node) {
        return -1;
    }
    
    if (!list->head) {
        list->head = node;
    } else {
        Node *current = list->head;
        while (current->next) {
            current = current->next;
        }
        current->next = node;
    }
    
    list->size++;
    return 0;
}

int slist_pop_front(SinglyLinkedList *list, int *out_value) {
    if (!list || !out_value || !list->head) {
        return -1;
    }
    
    Node *old_head = list->head;
    *out_value = old_head->data;
    
    list->head = old_head->next;
    free(old_head);
    list->size--;
    
    return 0;
}

int slist_pop_back(SinglyLinkedList *list, int *out_value) {
    if (!list || !out_value || !list->head) {
        return -1;
    }
    
    if (!list->head->next) {
        *out_value = list->head->data;
        free(list->head);
        list->head = NULL;
        list->size--;
        return 0;
    }
    
    Node *current = list->head;
    while (current->next->next) {
        current = current->next;
    }
    
    *out_value = current->next->data;
    free(current->next);
    current->next = NULL;
    list->size--;
    
    return 0;
}

int slist_insert_after(SinglyLinkedList *list, size_t index, int value) {
    if (!list || index >= list->size) {
        return -1;
    }
    
    Node *current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    
    Node *node = _node_create(value);
    if (!node) {
        return -1;
    }
    
    node->next = current->next;
    current->next = node;
    list->size++;
    
    return 0;
}

int slist_remove_at(SinglyLinkedList *list, size_t index, int *out_value) {
    if (!list || !list->head || index >= list->size) {
        return -1;
    }
    
    if (index == 0) {
        return slist_pop_front(list, out_value);
    }
    
    Node *current = list->head;
    for (size_t i = 0; i < index - 1; i++) {
        current = current->next;
    }
    
    Node *to_remove = current->next;
    if (out_value) {
        *out_value = to_remove->data;
    }
    
    current->next = to_remove->next;
    free(to_remove);
    list->size--;
    
    return 0;
}

int slist_get(const SinglyLinkedList *list, size_t index, int *out_value) {
    if (!list || !out_value || index >= list->size) {
        return -1;
    }
    
    Node *current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    
    *out_value = current->data;
    return 0;
}

int slist_set(SinglyLinkedList *list, size_t index, int value) {
    if (!list || index >= list->size) {
        return -1;
    }
    
    Node *current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    
    current->data = value;
    return 0;
}

size_t slist_size(const SinglyLinkedList *list) {
    if (!list) {
        return 0;
    }
    
    return list->size;
}

int slist_is_empty(const SinglyLinkedList *list) {
    if (!list) {
        return 1;
    }
    
    return list->size == 0;
}

int slist_find(const SinglyLinkedList *list, int value) {
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

void slist_clear(SinglyLinkedList *list) {
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
    list->size = 0;
}

void slist_reverse(SinglyLinkedList *list) {
    if (!list || !list->head) {
        return;
    }
    
    Node *prev = NULL;
    Node *current = list->head;
    Node *next = NULL;
    
    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    list->head = prev;
}

void slist_print(const SinglyLinkedList *list) {
    if (!list) {
        printf("NULL\n");
        return;
    }
    
    printf("[");
    Node *current = list->head;
    while (current) {
        printf("%d", current->data);
        if (current->next) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("] (size: %zu)\n", list->size);
}
