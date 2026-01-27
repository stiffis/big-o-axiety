#include <stdio.h>
#include "../include/queue.h"

int main(void) {
    printf("=== Queue Demo ===\n\n");
    
    printf("1. Creating empty queue:\n");
    Queue *queue = queue_create();
    printf("Empty queue: ");
    queue_print(queue);
    printf("\n");
    
    printf("2. Enqueueing elements (FIFO):\n");
    queue_enqueue(queue, 10);
    printf("After enqueue(10): ");
    queue_print(queue);
    
    queue_enqueue(queue, 20);
    printf("After enqueue(20): ");
    queue_print(queue);
    
    queue_enqueue(queue, 30);
    printf("After enqueue(30): ");
    queue_print(queue);
    printf("\n");
    
    printf("3. Peeking at front:\n");
    int val;
    queue_peek(queue, &val);
    printf("Front element (peek): %d\n", val);
    printf("Queue after peek: ");
    queue_print(queue);
    printf("\n");
    
    printf("4. Dequeueing elements (FIFO):\n");
    queue_dequeue(queue, &val);
    printf("Dequeued: %d, Queue now: ", val);
    queue_print(queue);
    
    queue_dequeue(queue, &val);
    printf("Dequeued: %d, Queue now: ", val);
    queue_print(queue);
    
    queue_dequeue(queue, &val);
    printf("Dequeued: %d, Queue now: ", val);
    queue_print(queue);
    printf("\n");
    
    printf("5. Checking empty queue:\n");
    printf("Is empty: %s\n\n", queue_is_empty(queue) ? "yes" : "no");
    
    printf("6. Demonstrating FIFO (First In, First Out):\n");
    printf("Enqueueing: 1, 2, 3, 4, 5\n");
    queue_enqueue(queue, 1);
    queue_enqueue(queue, 2);
    queue_enqueue(queue, 3);
    queue_enqueue(queue, 4);
    queue_enqueue(queue, 5);
    
    printf("Dequeueing order: ");
    while (!queue_is_empty(queue)) {
        queue_dequeue(queue, &val);
        printf("%d ", val);
    }
    printf("(same order)\n\n");
    
    printf("7. Mixed operations:\n");
    printf("Enqueue 10, 20, 30\n");
    queue_enqueue(queue, 10);
    queue_enqueue(queue, 20);
    queue_enqueue(queue, 30);
    queue_print(queue);
    
    printf("Dequeue once\n");
    queue_dequeue(queue, &val);
    printf("Dequeued: %d\n", val);
    queue_print(queue);
    
    printf("Enqueue 40, 50\n");
    queue_enqueue(queue, 40);
    queue_enqueue(queue, 50);
    queue_print(queue);
    printf("\n");
    
    printf("8. Clear queue:\n");
    printf("Before clear: ");
    queue_print(queue);
    
    queue_clear(queue);
    printf("After clear:  ");
    queue_print(queue);
    
    queue_destroy(queue);
    
    printf("\n=== Demo Complete ===\n");
    return 0;
}
