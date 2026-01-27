#include <stdio.h>
#include "../include/doubly_linked_list.h"

int main(void) {
    printf("=== Doubly Linked List Demo ===\n\n");
    
    printf("1. Creating empty list:\n");
    DoublyLinkedList *list = dlist_create();
    printf("Empty list: ");
    dlist_print(list);
    printf("\n");
    
    printf("2. Push back:\n");
    dlist_push_back(list, 10);
    dlist_push_back(list, 20);
    dlist_push_back(list, 30);
    printf("After push_back(10, 20, 30): ");
    dlist_print(list);
    printf("\n");
    
    printf("3. Push front:\n");
    dlist_clear(list);
    dlist_push_front(list, 30);
    dlist_push_front(list, 20);
    dlist_push_front(list, 10);
    printf("After push_front(30, 20, 10): ");
    dlist_print(list);
    printf("\n");
    
    printf("4. Bidirectional printing:\n");
    dlist_clear(list);
    dlist_push_back(list, 10);
    dlist_push_back(list, 20);
    dlist_push_back(list, 30);
    printf("Forward:  ");
    dlist_print(list);
    printf("Backward: ");
    dlist_print_reverse(list);
    printf("\n");
    
    printf("5. Insert at index:\n");
    dlist_clear(list);
    dlist_push_back(list, 10);
    dlist_push_back(list, 30);
    dlist_push_back(list, 40);
    printf("Before insert: ");
    dlist_print(list);
    dlist_insert_at(list, 1, 20);
    printf("After insert_at(1, 20): ");
    dlist_print(list);
    printf("\n");
    
    printf("6. Pop front:\n");
    int val;
    printf("Before pop: ");
    dlist_print(list);
    dlist_pop_front(list, &val);
    printf("Popped: %d, After pop_front: ", val);
    dlist_print(list);
    printf("\n");
    
    printf("7. Pop back:\n");
    dlist_clear(list);
    dlist_push_back(list, 10);
    dlist_push_back(list, 20);
    dlist_push_back(list, 30);
    printf("Before pop: ");
    dlist_print(list);
    dlist_pop_back(list, &val);
    printf("Popped: %d, After pop_back: ", val);
    dlist_print(list);
    printf("\n");
    
    printf("8. Remove at index:\n");
    dlist_clear(list);
    dlist_push_back(list, 10);
    dlist_push_back(list, 20);
    dlist_push_back(list, 30);
    dlist_push_back(list, 40);
    printf("Before remove: ");
    dlist_print(list);
    dlist_remove_at(list, 2, &val);
    printf("Removed index 2 (value %d): ", val);
    dlist_print(list);
    printf("\n");
    
    printf("9. Get and set:\n");
    dlist_clear(list);
    dlist_push_back(list, 10);
    dlist_push_back(list, 20);
    dlist_push_back(list, 30);
    printf("List: ");
    dlist_print(list);
    dlist_get(list, 1, &val);
    printf("Element at index 1: %d\n", val);
    dlist_set(list, 1, 99);
    printf("After setting index 1 to 99: ");
    dlist_print(list);
    printf("\n");
    
    printf("10. Find element:\n");
    dlist_clear(list);
    dlist_push_back(list, 10);
    dlist_push_back(list, 20);
    dlist_push_back(list, 30);
    printf("List: ");
    dlist_print(list);
    printf("Index of 20: %d\n", dlist_find(list, 20));
    printf("Index of 99: %d (not found)\n\n", dlist_find(list, 99));
    
    printf("11. Reverse:\n");
    dlist_clear(list);
    dlist_push_back(list, 10);
    dlist_push_back(list, 20);
    dlist_push_back(list, 30);
    dlist_push_back(list, 40);
    printf("Before reverse: ");
    dlist_print(list);
    dlist_reverse(list);
    printf("After reverse:  ");
    dlist_print(list);
    printf("Backward after reverse: ");
    dlist_print_reverse(list);
    printf("\n");
    
    printf("12. Clear:\n");
    dlist_clear(list);
    dlist_push_back(list, 10);
    dlist_push_back(list, 20);
    dlist_push_back(list, 30);
    printf("Before clear: ");
    dlist_print(list);
    dlist_clear(list);
    printf("After clear:  ");
    dlist_print(list);
    printf("Is empty: %s\n", dlist_is_empty(list) ? "yes" : "no");
    
    dlist_destroy(list);
    
    printf("\n=== Demo Complete ===\n");
    return 0;
}
