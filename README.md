# Data Structures in C

Implementation of data structures in pure C for learning systems programming and low-level development.

## 🎯 Objective

This project implements classic data structures in C following these principles:
- Manual memory management
- Opaque pointers for encapsulation
- Clean public interface (stdlib style)
- Code without external dependencies

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

### ✅ Static Array Arena (True Static Allocation)
- `arena_create()` / `arena_destroy()` / `arena_reset()`
- `static_array_arena_create()` - allocates from arena (no malloc per array)
- `static_array_arena_set()` / `static_array_arena_get()`
- `static_array_arena_fill()` / `static_array_arena_clear()` / `static_array_arena_find()`
- **Bump allocator (arena)** - O(1) allocation without heap fragmentation
- Multiple arrays can share same arena
- Deterministic memory usage for embedded/real-time systems
- No per-array malloc/free overhead

**See:** `include/static_array_arena.h`, `tests/test_static_array_arena.c`

### ✅ Array 2D (Matrix)
- `array2d_create()` / `array2d_destroy()`
- `array2d_set()` / `array2d_get()`
- `array2d_get_row()` / `array2d_get_col()`
- `array2d_fill_row()` / `array2d_fill_col()`
- `array2d_transpose()` / `array2d_transpose_copy()`
- `array2d_find()` / `array2d_copy()`
- Row-major memory layout
- Matrix operations (transpose, row/col access)

**See:** `include/array2d.h`, `examples/demo_array2d.c`

### ✅ AVL Tree
- `avl_create()` / `avl_destroy()`
- `avl_insert()` / `avl_delete()` / `avl_search()`
- `avl_min()` / `avl_max()`
- `avl_inorder()` / `avl_preorder()` / `avl_postorder()`
- Self-balancing binary search tree
- O(log n) operations
- Automatic rotations (LL, RR, LR, RL)

**See:** `include/avl.h`, `examples/demo_avl.c`

### ✅ B-Tree
- `btree_create(min_degree)` / `btree_destroy()`
- `btree_insert()` / `btree_delete()` / `btree_search()`
- `btree_min()` / `btree_max()`
- `btree_traverse()` / `btree_to_array()`
- Self-balancing multiway search tree
- Configurable minimum degree (t >= 2)
- Automatic node splitting/merging
- Optimized for disk I/O

**See:** `include/btree.h`, `examples/demo_btree.c`

## 🧠 Key Concepts in C

### 1. Opaque Pointers
```c
typedef struct DynamicArray DynamicArray;
```
User doesn't see internal implementation.

### 2. Manual Memory Management
```c
DynamicArray *arr = array_create(10);
array_destroy(arr);
```
Always `_create()` → `_destroy()` to avoid memory leaks.

### 3. Error Handling
```c
int result = array_push(arr, 42);
if (result != 0) {
    // Error
}
```
Functions return error codes (0 = success, -1 = error).

### 4. Output Parameters
```c
int value;
array_get(arr, 0, &value);
```
Output values are passed by pointer.

## 🔧 Code Conventions

- **Naming:** `structure_action()` (e.g., `array_push()`)
- **Private prefix:** `_array_resize()` (static functions)
- **Errors:** Return -1 or NULL
- **Constness:** `const` in read-only functions

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

## 🛠️ Recommended Tools

- **Compiler:** GCC or Clang with `-Wall -Wextra -Werror`
- **Debugger:** `gdb` or `lldb`
- **Memory leaks:** `valgrind --leak-check=full ./program`
- **Static analysis:** `clang-tidy`, `cppcheck`

### ✅ Dynamic String
- `string_create()` / `string_create_from()` / `string_destroy()`
- `string_push()` / `string_pop()` / `string_append()` / `string_concat()`
- `string_insert()` / `string_find()` / `string_substring()`
- `string_compare()` / `string_equals()` / `string_copy()`
- **Safe variants (buffer overflow protection):**
  - `string_create_from_n()` / `string_append_n()` / `string_insert_n()` / `string_find_n()`
- Automatic resizing with 2x growth factor
- String manipulation and searching
- **Optimized:** Buffer-safe functions prevent unterminated string vulnerabilities

**See:** `include/dyn_string.h`, `examples/demo_dyn_string.c`

### ✅ Bitset
- `bitset_create()` / `bitset_destroy()`
- `bitset_set()` / `bitset_clear()` / `bitset_flip()` / `bitset_test()`
- `bitset_count()` / `bitset_all()` / `bitset_any()` / `bitset_none()`
- `bitset_and()` / `bitset_or()` / `bitset_xor()` / `bitset_equals()`
- Bit manipulation with compact storage
- Supports non-byte-aligned sizes
- **Optimized:** 64-bit word operations with hardware popcount (`__builtin_popcountll`)
- ~64x faster than bit-by-bit counting

**See:** `include/bitset.h`, `examples/demo_bitset.c`

### ✅ Singly Linked List
- `slist_create()` / `slist_destroy()`
- `slist_push_front()` / `slist_push_back()` / `slist_pop_front()` / `slist_pop_back()`
- `slist_insert_after()` / `slist_remove_at()`
- `slist_find()` / `slist_reverse()` / `slist_clear()`
- Classic single-direction linked list
- O(1) push/pop front

**See:** `include/singly_linked_list.h`, `examples/demo_singly_linked_list.c`

### ✅ Doubly Linked List
- `dlist_create()` / `dlist_destroy()`
- `dlist_push_front()` / `dlist_push_back()` / `dlist_pop_front()` / `dlist_pop_back()`
- `dlist_insert_at()` / `dlist_remove_at()`
- `dlist_get()` / `dlist_set()` / `dlist_find()` / `dlist_reverse()`
- Bidirectional traversal with prev/next pointers
- Optimized get/set using closest end

**See:** `include/doubly_linked_list.h`, `examples/demo_doubly_linked_list.c`

### ✅ Stack
- `stack_create()` / `stack_destroy()`
- `stack_push()` / `stack_pop()` / `stack_peek()`
- `stack_size()` / `stack_is_empty()` / `stack_clear()`
- LIFO (Last In, First Out) behavior
- Array-based with auto-resize

**See:** `include/stack.h`, `examples/demo_stack.c`

### ✅ Queue
- `queue_create()` / `queue_destroy()`
- `queue_enqueue()` / `queue_dequeue()` / `queue_peek()`
- `queue_size()` / `queue_is_empty()` / `queue_clear()`
- FIFO (First In, First Out) behavior
- Linked-list based for efficient operations

**See:** `include/queue.h`, `examples/demo_queue.c`

### ✅ Deque (Double-Ended Queue)
- `deque_create()` / `deque_destroy()`
- `deque_push_front()` / `deque_push_back()` / `deque_pop_front()` / `deque_pop_back()`
- `deque_peek_front()` / `deque_peek_back()`
- `deque_size()` / `deque_is_empty()` / `deque_clear()`
- Operations at both ends in O(1)
- Can function as both stack and queue

**See:** `include/deque.h`, `examples/demo_deque.c`

### ✅ Ring Buffer (Circular Queue)
- `ring_buffer_create()` / `ring_buffer_destroy()`
- `ring_buffer_write()` / `ring_buffer_read()` / `ring_buffer_peek()`
- `ring_buffer_size()` / `ring_buffer_capacity()` / `ring_buffer_is_full()`
- Fixed-size circular buffer with wraparound
- Efficient for streaming data

**See:** `include/ring_buffer.h`, `examples/demo_ring_buffer.c`

### ✅ Priority Queue (Min-Heap)
- `pqueue_create()` / `pqueue_destroy()`
- `pqueue_push()` / `pqueue_pop()` / `pqueue_peek()`
- `pqueue_size()` / `pqueue_is_empty()` / `pqueue_clear()`
- Binary min-heap implementation
- O(log n) push/pop operations
- Auto-resizing array-based storage
- **Optimized:** Iterative heapify (no recursion) - stack-safe for embedded systems

**See:** `include/priority_queue.h`, `examples/demo_priority_queue.c`

## 🚀 Performance Optimizations

This project includes **kernel/systems-level optimizations**:

| Structure | Optimization | Impact |
|-----------|--------------|--------|
| **Bitset** | 64-bit word operations + `__builtin_popcountll()` | ~64x faster popcount (hardware POPCNT) |
| **Priority Queue** | Iterative heapify (no recursion) | Stack-safe for embedded systems (MISRA-C) |
| **Dynamic String** | Buffer-safe `_n` variants | Prevents buffer overflow vulnerabilities |
| **Arena Allocator** | Bump allocator (no malloc per object) | O(1) allocation, zero fragmentation |

**Real-world applications:**
- Bitset popcount: Linux kernel CPU affinity, network packet filters
- No recursion: SpaceX flight software, medical devices (MISRA-C Rule 16.2)
- Buffer safety: Prevents CVE-class bugs (Heartbleed, Cloudflare parser)
- Arena allocators: Game engines (Unreal), audio DSP, real-time systems

## 📝 Roadmap

- [x] Dynamic Array
- [x] Static Array
- [x] Static Array Arena (Bump Allocator)
- [x] Array 2D (Matrix)
- [x] AVL Tree
- [x] B-Tree
- [x] Dynamic String (with buffer-safe variants)
- [x] Bitset (with hardware popcount)
- [x] Singly Linked List
- [x] Doubly Linked List
- [x] Stack
- [x] Queue
- [x] Deque
- [x] Ring Buffer
- [x] Priority Queue (iterative, stack-safe)
- [ ] Hash Table
- [ ] Binary Search Tree
- [ ] Graph

## 📚 Resources

- [Beej's Guide to C](https://beej.us/guide/bgc/)
- [The C Programming Language (K&R)](https://en.wikipedia.org/wiki/The_C_Programming_Language)
- [C Memory Management](https://www.geeksforgeeks.org/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/)

## 📄 License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details.

This is free software: you are free to change and redistribute it under the terms of the GPL-3.0 license.
