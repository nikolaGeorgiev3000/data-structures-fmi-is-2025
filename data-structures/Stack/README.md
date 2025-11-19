# Stack Implementations

This folder contains three minimal C++ stack implementations:

## 1. ArrayStack
- Stack over a dynamic array  
- `push`, `pop`, `peek` – O(1) amortized  
- Manual resize, deep copy support  

## 2. LinkedStack
- Stack over a singly linked list  
- `push` / `pop` – O(1)  
- No reallocations, deep copy support  

## 3. StackWithContainer
- Generic stack adapter: `template<class T, class Container = std::deque<T>>`  
- Uses any container with `push_back`, `pop_back`, `back`, `empty`, `size`  
- Default: `std::deque<T>`

Each subfolder has a small `main.cpp` with example usage.