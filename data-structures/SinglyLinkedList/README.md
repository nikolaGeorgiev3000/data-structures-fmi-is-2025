# SinglyLinkedList

This folder contains a minimal C++ implementation of a singly linked list.

## Features
- `pushFront` / `pushBack` – O(1)
- `popFront` – O(1)
- `front`, `back` – O(1)
- Forward iterator and const iterator support
- Deep copy and move semantics
- `insertAfter` / `removeAfter`
- `concat(lhs, rhs)` — links two lists in O(1)

## Notes
- Node structure: `{ data, next }`
- The list stores `head`, `tail`, and `size`
- `concat` empties both input lists
- Iterators support: `++`, `+`, `+=`, `==`, `!=`

A `main.cpp` file with a complete test suite is included.