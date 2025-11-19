#pragma once

#include <cstddef>
#include <deque>

// Generic stack container adapter.
// Works with any container providing:
// - back()
// - push_back()
// - pop_back()
// - empty()
// - size()

template <typename T, typename Container = std::deque<T>>
class Stack
{
public:
    Stack() = default;

    T& top() { return cont.back(); }
    const T& top() const { return cont.back(); }

    void push(const T& value) { cont.push_back(value); }
    void pop() { cont.pop_back(); }

    bool empty() const noexcept { return cont.empty(); }
    std::size_t size() const noexcept { return cont.size(); }

private:
    Container cont;
};