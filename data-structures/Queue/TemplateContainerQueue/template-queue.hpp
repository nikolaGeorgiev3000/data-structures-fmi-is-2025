#pragma once

#include <deque>
#include <utility>   // std::move
#include <cstddef>   // std::size_t

// Generic queue on top of an arbitrary container.
// The container must support:
//  - push_back
//  - pop_front
//  - front / back
//  - empty / size

template <typename T, typename Container = std::deque<T>>
class Queue
{
public:
    void push(const T& value) { container.push_back(value); }
    void push(T&& value) { container.push_back(std::move(value)); }
    void pop() { container.pop_front(); }

    T& front() { return container.front(); }
    const T& front() const { return container.front(); }
    T& back() { return container.back(); }
    const T& back() const { return container.back(); }

    bool empty() const { return container.empty(); }
    std::size_t size() const { return container.size(); }
private:
    Container container;
};