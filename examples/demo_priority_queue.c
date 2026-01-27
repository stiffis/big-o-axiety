#include <stdio.h>
#include "../include/priority_queue.h"

int main(void) {
    printf("=== Priority Queue (Min-Heap) Demo ===\n\n");
    
    printf("1. Creating priority queue:\n");
    PriorityQueue *pq = pqueue_create(10);
    printf("Empty queue: ");
    pqueue_print(pq);
    printf("\n");
    
    printf("2. Pushing elements (unordered):\n");
    printf("Push: 50, 30, 70, 10, 40\n");
    pqueue_push(pq, 50);
    pqueue_push(pq, 30);
    pqueue_push(pq, 70);
    pqueue_push(pq, 10);
    pqueue_push(pq, 40);
    
    printf("Internal heap: ");
    pqueue_print(pq);
    printf("(Note: Min element is at root)\n\n");
    
    printf("3. Peek at minimum:\n");
    int val;
    pqueue_peek(pq, &val);
    printf("Minimum element: %d\n", val);
    printf("Queue unchanged: ");
    pqueue_print(pq);
    printf("\n");
    
    printf("4. Popping in priority order (ascending):\n");
    printf("Pop sequence: ");
    while (pqueue_size(pq) > 2) {
        pqueue_pop(pq, &val);
        printf("%d ", val);
    }
    printf("\n");
    printf("Remaining: ");
    pqueue_print(pq);
    printf("\n");
    
    printf("5. Clear and rebuild:\n");
    pqueue_clear(pq);
    printf("After clear: ");
    pqueue_print(pq);
    
    printf("\nPushing: 100, 20, 80, 5, 60, 90, 40\n");
    pqueue_push(pq, 100);
    pqueue_push(pq, 20);
    pqueue_push(pq, 80);
    pqueue_push(pq, 5);
    pqueue_push(pq, 60);
    pqueue_push(pq, 90);
    pqueue_push(pq, 40);
    
    printf("Queue: ");
    pqueue_print(pq);
    printf("\n");
    
    printf("6. Extracting all in priority order:\n");
    printf("Elements: ");
    while (!pqueue_is_empty(pq)) {
        pqueue_pop(pq, &val);
        printf("%d ", val);
    }
    printf("(sorted!)\n\n");
    
    printf("7. Handling duplicate priorities:\n");
    pqueue_push(pq, 5);
    pqueue_push(pq, 3);
    pqueue_push(pq, 5);
    pqueue_push(pq, 3);
    pqueue_push(pq, 1);
    
    printf("Pushed: 5, 3, 5, 3, 1\n");
    printf("Queue: ");
    pqueue_print(pq);
    
    printf("Pop order: ");
    while (!pqueue_is_empty(pq)) {
        pqueue_pop(pq, &val);
        printf("%d ", val);
    }
    printf("\n\n");
    
    printf("8. Negative values:\n");
    pqueue_push(pq, 10);
    pqueue_push(pq, -5);
    pqueue_push(pq, 0);
    pqueue_push(pq, -10);
    pqueue_push(pq, 5);
    
    printf("Pushed: 10, -5, 0, -10, 5\n");
    printf("Queue: ");
    pqueue_print(pq);
    
    printf("Pop order: ");
    while (!pqueue_is_empty(pq)) {
        pqueue_pop(pq, &val);
        printf("%d ", val);
    }
    printf("\n\n");
    
    printf("9. Use case: Task scheduler\n");
    printf("Tasks (priority, lower = more urgent):\n");
    printf("  - Email (3)\n");
    printf("  - Critical Bug (1)\n");
    printf("  - Meeting (2)\n");
    printf("  - Documentation (5)\n");
    printf("  - Code Review (4)\n\n");
    
    pqueue_push(pq, 3);
    pqueue_push(pq, 1);
    pqueue_push(pq, 2);
    pqueue_push(pq, 5);
    pqueue_push(pq, 4);
    
    const char *tasks[] = {
        "",
        "Critical Bug",
        "Meeting",
        "Email",
        "Code Review",
        "Documentation"
    };
    
    printf("Execution order:\n");
    int priority = 1;
    while (!pqueue_is_empty(pq)) {
        pqueue_pop(pq, &val);
        printf("%d. %s (priority %d)\n", priority++, tasks[val], val);
    }
    printf("\n");
    
    printf("10. Auto-resize demonstration:\n");
    printf("Creating queue with capacity 2\n");
    pqueue_destroy(pq);
    pq = pqueue_create(2);
    printf("Initial capacity: %zu\n", pqueue_capacity(pq));
    
    pqueue_push(pq, 10);
    pqueue_push(pq, 20);
    printf("After 2 pushes: capacity = %zu\n", pqueue_capacity(pq));
    
    pqueue_push(pq, 5);
    printf("After 3 pushes: capacity = %zu (auto-resized!)\n", pqueue_capacity(pq));
    
    printf("Queue maintains heap property: ");
    pqueue_print(pq);
    
    printf("Min element: ");
    pqueue_peek(pq, &val);
    printf("%d\n", val);
    
    pqueue_destroy(pq);
    
    printf("\n=== Demo Complete ===\n");
    return 0;
}
