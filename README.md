# Data Structures in C

Pure C implementations of classic data structures.

## 📂 Project Structure

```
data-structures.c/
├── include/         # Public headers (.h)
├── src/            # Implementations (.c)
├── examples/       # Usage examples
├── tests/          # Unit tests
├── Makefile        # Build system
└── README.md
```

## 🚀 Build and Run

### Build everything
```bash
make
```

### Build and run examples
```bash
make examples
make run-examples
```

### Build and run tests
```bash
make tests
make run-tests
```

### Clean build
```bash
make clean
```

## 📚 Implemented Structures

### ✅ Dynamic Array
- `array_create()` / `array_destroy()`
- `array_push()` / `array_pop()`
- `array_insert()` / `array_remove()`
- `array_get()` / `array_set()`
- Automatic resizing (2x growth factor)

**See:** `include/array.h`, `examples/demo_array.c`

### ✅ Static Array
- `static_array_create()` / `static_array_destroy()`
- `static_array_set()` / `static_array_get()`
- `static_array_fill()` / `static_array_clear()`
- `static_array_find()` / `static_array_copy()` / `static_array_reverse()`
- Fixed capacity (no resizing)

**See:** `include/static_array.h`, `examples/demo_static_array.c`

### ✅ Static Array Arena
- `arena_create()` / `arena_destroy()` / `arena_reset()`
- `static_array_arena_create()` / `static_array_arena_destroy()`
- `static_array_arena_set()` / `static_array_arena_get()`
- `static_array_arena_fill()` / `static_array_arena_clear()` / `static_array_arena_find()`
- Fast allocation from pre-allocated memory

**See:** `include/static_array_arena.h`, `tests/test_static_array_arena.c`

### ✅ Array 2D (Matrix)
- `array2d_create()` / `array2d_destroy()`
- `array2d_set()` / `array2d_get()`
- `array2d_get_row()` / `array2d_get_col()`
- `array2d_fill_row()` / `array2d_fill_col()`
- `array2d_transpose()` / `array2d_transpose_copy()`
- `array2d_find()` / `array2d_copy()`
- Row-major layout

**See:** `include/array2d.h`, `examples/demo_array2d.c`

### ✅ AVL Tree
- `avl_create()` / `avl_destroy()`
- `avl_insert()` / `avl_delete()` / `avl_search()`
- `avl_min()` / `avl_max()`
- `avl_inorder()` / `avl_preorder()` / `avl_postorder()`
- Self-balancing binary search tree

**See:** `include/avl.h`, `examples/demo_avl.c`

### ✅ B-Tree
- `btree_create(min_degree)` / `btree_destroy()`
- `btree_insert()` / `btree_delete()` / `btree_search()`
- `btree_min()` / `btree_max()`
- `btree_traverse()` / `btree_to_array()`
- Self-balancing multiway search tree

**See:** `include/btree.h`, `examples/demo_btree.c`

### ✅ Dynamic String
- `string_create()` / `string_create_from()` / `string_destroy()`
- `string_push()` / `string_pop()` / `string_append()` / `string_concat()`
- `string_insert()` / `string_find()` / `string_substring()`
- `string_compare()` / `string_equals()` / `string_copy()`
- Safe variants: `string_create_from_n()`, `string_append_n()`, `string_insert_n()`

**See:** `include/dyn_string.h`, `examples/demo_dyn_string.c`

### ✅ Bitset
- `bitset_create()` / `bitset_destroy()`
- `bitset_set()` / `bitset_clear()` / `bitset_flip()` / `bitset_test()`
- `bitset_count()` / `bitset_all()` / `bitset_any()` / `bitset_none()`
- `bitset_and()` / `bitset_or()` / `bitset_xor()` / `bitset_equals()`
- Compact bit storage with fast operations

**See:** `include/bitset.h`, `examples/demo_bitset.c`

### ✅ Singly Linked List
- `slist_create()` / `slist_destroy()`
- `slist_push_front()` / `slist_push_back()` / `slist_pop_front()` / `slist_pop_back()`
- `slist_insert_after()` / `slist_remove_at()`
- `slist_find()` / `slist_reverse()` / `slist_clear()`

**See:** `include/singly_linked_list.h`, `examples/demo_singly_linked_list.c`

### ✅ Doubly Linked List
- `dlist_create()` / `dlist_destroy()`
- `dlist_push_front()` / `dlist_push_back()` / `dlist_pop_front()` / `dlist_pop_back()`
- `dlist_insert_at()` / `dlist_remove_at()`
- `dlist_get()` / `dlist_set()` / `dlist_find()` / `dlist_reverse()`

**See:** `include/doubly_linked_list.h`, `examples/demo_doubly_linked_list.c`

### ✅ Stack
- `stack_create()` / `stack_destroy()`
- `stack_push()` / `stack_pop()` / `stack_peek()`
- `stack_size()` / `stack_is_empty()` / `stack_clear()`
- LIFO (Last In, First Out)

**See:** `include/stack.h`, `examples/demo_stack.c`

### ✅ Queue
- `queue_create()` / `queue_destroy()`
- `queue_enqueue()` / `queue_dequeue()` / `queue_peek()`
- `queue_size()` / `queue_is_empty()` / `queue_clear()`
- FIFO (First In, First Out)

**See:** `include/queue.h`, `examples/demo_queue.c`

### ✅ Deque (Double-Ended Queue)
- `deque_create()` / `deque_destroy()`
- `deque_push_front()` / `deque_push_back()` / `deque_pop_front()` / `deque_pop_back()`
- `deque_peek_front()` / `deque_peek_back()`
- `deque_size()` / `deque_is_empty()` / `deque_clear()`

**See:** `include/deque.h`, `examples/demo_deque.c`

### ✅ Ring Buffer
- `ring_buffer_create()` / `ring_buffer_destroy()`
- `ring_buffer_write()` / `ring_buffer_read()` / `ring_buffer_peek()`
- `ring_buffer_size()` / `ring_buffer_capacity()` / `ring_buffer_is_full()`
- Fixed-size circular buffer

**See:** `include/ring_buffer.h`, `examples/demo_ring_buffer.c`

### ✅ Priority Queue
- `pqueue_create()` / `pqueue_destroy()`
- `pqueue_push()` / `pqueue_pop()` / `pqueue_peek()`
- `pqueue_size()` / `pqueue_is_empty()` / `pqueue_clear()`
- Binary min-heap implementation

**See:** `include/priority_queue.h`, `examples/demo_priority_queue.c`

## 📖 Basic Usage

```c
#include "array.h"

int main(void) {
    DynamicArray *arr = array_create(10);

    array_push(arr, 42);
    array_push(arr, 100);

    int value;
    array_get(arr, 0, &value);
    printf("First element: %d\n", value);

    array_print(arr);

    array_destroy(arr);
    return 0;
}
```

## 📝 Roadmap

- [x] Dynamic Array
- [x] Static Array
- [x] Static Array Arena
- [x] Array 2D (Matrix)
- [x] AVL Tree
- [x] B-Tree
- [x] Dynamic String
- [x] Bitset
- [x] Singly Linked List
- [x] Doubly Linked List
- [x] Stack
- [x] Queue
- [x] Deque
- [x] Ring Buffer
- [x] Priority Queue
- [ ] Hash Table
- [ ] Binary Search Tree
- [ ] Graph

## 📚 Resources

- [Beej's Guide to C](https://beej.us/guide/bgc/)
- [The C Programming Language (K&R)](https://en.wikipedia.org/wiki/The_C_Programming_Language)

## 📄 License

GPL-3.0