#include <stdio.h>
#include "../include/deque.h"

int main(void) {
    printf("=== Deque (Double-Ended Queue) Demo ===\n\n");
    
    printf("1. Creating empty deque:\n");
    Deque *deque = deque_create();
    printf("Empty deque: ");
    deque_print(deque);
    printf("\n");
    
    printf("2. Push operations from both ends:\n");
    deque_push_back(deque, 10);
    printf("After push_back(10):  ");
    deque_print(deque);
    
    deque_push_front(deque, 5);
    printf("After push_front(5):  ");
    deque_print(deque);
    
    deque_push_back(deque, 20);
    printf("After push_back(20):  ");
    deque_print(deque);
    
    deque_push_front(deque, 1);
    printf("After push_front(1):  ");
    deque_print(deque);
    printf("\n");
    
    printf("3. Peek operations:\n");
    int val;
    deque_peek_front(deque, &val);
    printf("Front element (peek): %d\n", val);
    
    deque_peek_back(deque, &val);
    printf("Back element (peek):  %d\n", val);
    
    printf("Deque unchanged: ");
    deque_print(deque);
    printf("\n");
    
    printf("4. Pop from front (FIFO style):\n");
    deque_pop_front(deque, &val);
    printf("Popped from front: %d, Deque now: ", val);
    deque_print(deque);
    
    deque_pop_front(deque, &val);
    printf("Popped from front: %d, Deque now: ", val);
    deque_print(deque);
    printf("\n");
    
    printf("5. Pop from back (LIFO style):\n");
    deque_pop_back(deque, &val);
    printf("Popped from back: %d, Deque now: ", val);
    deque_print(deque);
    
    deque_pop_back(deque, &val);
    printf("Popped from back: %d, Deque now: ", val);
    deque_print(deque);
    printf("\n");
    
    printf("6. Demonstrating FIFO behavior:\n");
    printf("Push back: 1, 2, 3, 4, 5\n");
    for (int i = 1; i <= 5; i++) {
        deque_push_back(deque, i);
    }
    printf("Current: ");
    deque_print(deque);
    
    printf("Pop from front: ");
    while (deque_size(deque) > 2) {
        deque_pop_front(deque, &val);
        printf("%d ", val);
    }
    printf("(FIFO order)\n");
    printf("Remaining: ");
    deque_print(deque);
    printf("\n");
    
    printf("7. Demonstrating LIFO behavior:\n");
    deque_clear(deque);
    printf("Push back: 10, 20, 30, 40, 50\n");
    for (int i = 1; i <= 5; i++) {
        deque_push_back(deque, i * 10);
    }
    printf("Current: ");
    deque_print(deque);
    
    printf("Pop from back: ");
    while (deque_size(deque) > 2) {
        deque_pop_back(deque, &val);
        printf("%d ", val);
    }
    printf("(LIFO order)\n");
    printf("Remaining: ");
    deque_print(deque);
    printf("\n");
    
    printf("8. Mixed operations:\n");
    deque_clear(deque);
    printf("Start: ");
    deque_print(deque);
    
    printf("Push front: 5\n");
    deque_push_front(deque, 5);
    deque_print(deque);
    
    printf("Push back: 10\n");
    deque_push_back(deque, 10);
    deque_print(deque);
    
    printf("Push front: 1\n");
    deque_push_front(deque, 1);
    deque_print(deque);
    
    printf("Push back: 15\n");
    deque_push_back(deque, 15);
    deque_print(deque);
    
    printf("Pop front:\n");
    deque_pop_front(deque, &val);
    printf("Removed %d: ", val);
    deque_print(deque);
    
    printf("Pop back:\n");
    deque_pop_back(deque, &val);
    printf("Removed %d: ", val);
    deque_print(deque);
    printf("\n");
    
    printf("9. Clear deque:\n");
    printf("Before clear: ");
    deque_print(deque);
    
    deque_clear(deque);
    printf("After clear:  ");
    deque_print(deque);
    printf("\n");
    
    printf("10. Deque as Queue and Stack:\n");
    printf("As Queue (push_back + pop_front):\n");
    deque_push_back(deque, 1);
    deque_push_back(deque, 2);
    deque_push_back(deque, 3);
    printf("After pushes: ");
    deque_print(deque);
    
    printf("Pop sequence: ");
    while (!deque_is_empty(deque)) {
        deque_pop_front(deque, &val);
        printf("%d ", val);
    }
    printf("(FIFO)\n\n");
    
    printf("As Stack (push_back + pop_back):\n");
    deque_push_back(deque, 1);
    deque_push_back(deque, 2);
    deque_push_back(deque, 3);
    printf("After pushes: ");
    deque_print(deque);
    
    printf("Pop sequence: ");
    while (!deque_is_empty(deque)) {
        deque_pop_back(deque, &val);
        printf("%d ", val);
    }
    printf("(LIFO)\n");
    
    deque_destroy(deque);
    
    printf("\n=== Demo Complete ===\n");
    return 0;
}
