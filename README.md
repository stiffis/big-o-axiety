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

## 📝 Roadmap

- [x] Dynamic Array
- [ ] Linked List (single)
- [ ] Linked List (double)
- [ ] Stack
- [ ] Queue
- [ ] Hash Table
- [ ] Binary Search Tree
- [ ] Heap
- [ ] Graph

## 📚 Resources

- [Beej's Guide to C](https://beej.us/guide/bgc/)
- [The C Programming Language (K&R)](https://en.wikipedia.org/wiki/The_C_Programming_Language)
- [C Memory Management](https://www.geeksforgeeks.org/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/)

## 📄 License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details.

This is free software: you are free to change and redistribute it under the terms of the GPL-3.0 license.
