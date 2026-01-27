#include <stdio.h>
#include "../include/singly_linked_list.h"

int main(void) {
    printf("=== Singly Linked List Demo ===\n\n");
    
    printf("1. Creating empty list:\n");
    SinglyLinkedList *list = slist_create();
    printf("Empty list: ");
    slist_print(list);
    printf("\n");
    
    printf("2. Push front:\n");
    slist_push_front(list, 30);
    slist_push_front(list, 20);
    slist_push_front(list, 10);
    printf("After push_front(30, 20, 10): ");
    slist_print(list);
    printf("\n");
    
    printf("3. Push back:\n");
    slist_clear(list);
    slist_push_back(list, 10);
    slist_push_back(list, 20);
    slist_push_back(list, 30);
    printf("After push_back(10, 20, 30): ");
    slist_print(list);
    printf("\n");
    
    printf("4. Get elements:\n");
    int val;
    slist_get(list, 0, &val);
    printf("Element at index 0: %d\n", val);
    slist_get(list, 1, &val);
    printf("Element at index 1: %d\n", val);
    slist_get(list, 2, &val);
    printf("Element at index 2: %d\n\n", val);
    
    printf("5. Set element:\n");
    slist_set(list, 1, 99);
    printf("After setting index 1 to 99: ");
    slist_print(list);
    printf("\n");
    
    printf("6. Insert after:\n");
    slist_clear(list);
    slist_push_back(list, 10);
    slist_push_back(list, 30);
    slist_push_back(list, 40);
    printf("Before insert: ");
    slist_print(list);
    slist_insert_after(list, 0, 20);
    printf("After insert_after(0, 20): ");
    slist_print(list);
    printf("\n");
    
    printf("7. Pop front:\n");
    slist_clear(list);
    slist_push_back(list, 10);
    slist_push_back(list, 20);
    slist_push_back(list, 30);
    printf("Before pop: ");
    slist_print(list);
    slist_pop_front(list, &val);
    printf("Popped: %d, After pop_front: ", val);
    slist_print(list);
    printf("\n");
    
    printf("8. Pop back:\n");
    slist_clear(list);
    slist_push_back(list, 10);
    slist_push_back(list, 20);
    slist_push_back(list, 30);
    printf("Before pop: ");
    slist_print(list);
    slist_pop_back(list, &val);
    printf("Popped: %d, After pop_back: ", val);
    slist_print(list);
    printf("\n");
    
    printf("9. Remove at index:\n");
    slist_clear(list);
    slist_push_back(list, 10);
    slist_push_back(list, 20);
    slist_push_back(list, 30);
    slist_push_back(list, 40);
    printf("Before remove: ");
    slist_print(list);
    slist_remove_at(list, 2, &val);
    printf("Removed index 2 (value %d): ", val);
    slist_print(list);
    printf("\n");
    
    printf("10. Find element:\n");
    slist_clear(list);
    slist_push_back(list, 10);
    slist_push_back(list, 20);
    slist_push_back(list, 30);
    printf("List: ");
    slist_print(list);
    printf("Index of 20: %d\n", slist_find(list, 20));
    printf("Index of 99: %d (not found)\n\n", slist_find(list, 99));
    
    printf("11. Reverse:\n");
    slist_clear(list);
    slist_push_back(list, 10);
    slist_push_back(list, 20);
    slist_push_back(list, 30);
    slist_push_back(list, 40);
    printf("Before reverse: ");
    slist_print(list);
    slist_reverse(list);
    printf("After reverse:  ");
    slist_print(list);
    printf("\n");
    
    printf("12. Clear list:\n");
    slist_clear(list);
    slist_push_back(list, 10);
    slist_push_back(list, 20);
    slist_push_back(list, 30);
    printf("Before clear: ");
    slist_print(list);
    slist_clear(list);
    printf("After clear:  ");
    slist_print(list);
    printf("Is empty: %s\n", slist_is_empty(list) ? "yes" : "no");
    
    slist_destroy(list);
    
    printf("\n=== Demo Complete ===\n");
    return 0;
}
