#ifndef DEQUE_H
#define DEQUE_H

#include <stddef.h>

typedef struct Deque Deque;

Deque *deque_create(void);

void deque_destroy(Deque *deque);

int deque_push_front(Deque *deque, int value);

int deque_push_back(Deque *deque, int value);

int deque_pop_front(Deque *deque, int *out_value);

int deque_pop_back(Deque *deque, int *out_value);

int deque_peek_front(const Deque *deque, int *out_value);

int deque_peek_back(const Deque *deque, int *out_value);

size_t deque_size(const Deque *deque);

int deque_is_empty(const Deque *deque);

void deque_clear(Deque *deque);

void deque_print(const Deque *deque);

#endif
