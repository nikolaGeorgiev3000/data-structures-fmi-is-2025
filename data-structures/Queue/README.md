# Queue Implementations

This folder contains three minimal C++ queue implementations:

## 1. CircularQueue
- Queue over a circular dynamic array  
- `enqueue` / `dequeue` – O(1) amortized  
- Efficient wrap-around indexing (`getIter` / `putIter`)  
- Manual resize and deep copy support  

## 2. LinkedQueue
- Queue over a singly linked list  
- `enqueue` at tail / `dequeue` from head – O(1)  
- No reallocations, deep copy support  
- Simple, pointer-based FIFO structure  

## 3. QueueWithContainer
- Generic queue adapter: `template<class T, class Container = std::deque<T>>`  
- Uses any container supporting `push_back`, `pop_front`, `front`, `back`, `empty`, `size`  
- Default: `std::deque<T>`

Each subfolder includes a small `main.cpp` with example usage.