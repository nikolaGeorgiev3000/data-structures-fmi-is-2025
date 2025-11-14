#pragma once

#include "dynarray-iterators.hpp"
#include <memory>
#include <utility>
#include <cstddef>

namespace Detail
{
    constexpr unsigned GROWTH_FACTOR = 2;
}

template <class T, class Allocator = std::allocator<T>>
class DynArray
{
public:
    using value_type      = T;
    using allocator_type  = Allocator;

    using iterator               = DynArrayIterator<T>;
    using const_iterator         = DynArrayConstIterator<T>;
    using reverse_iterator       = DynArrayReverseIterator<T>;
    using const_reverse_iterator = DynArrayReverseIterator<const T>; 

    // Constructors
    DynArray() = default;
    explicit DynArray(size_t count);
    DynArray(size_t count, const T& initial);

    DynArray(const DynArray& other);
    DynArray& operator=(const DynArray& other);

    DynArray(DynArray&& other) noexcept;
    DynArray& operator=(DynArray&& other) noexcept;

    ~DynArray();

    // Basic modifiers
    void push_back(const T& element);
    void push_back(T&& element);
    void pop_back();

    void clear();

    template <class... Args>
    void emplace_back(Args&&... args);

    void erase(const_iterator position);
    void erase(const_iterator first, const_iterator last);

    // Element access
    T& operator[](size_t idx);
    const T& operator[](size_t idx) const;

    T* data()             { return _data; }
    const T* data() const { return _data; }

    T&       front()       { return _data[0]; }
    const T& front() const { return _data[0]; }

    T&       back()        { return _data[_size - 1]; }
    const T& back()  const { return _data[_size - 1]; }

    // Capacity
    void resize(size_t n);
    void reserve(size_t n);
    void shrink_to_fit();

    size_t size() const     { return _size; }
    size_t capacity() const { return _capacity; }
    bool        empty() const    { return _size == 0; }

    // Iterators
    iterator begin()             { return iterator(_data); }
    iterator end()               { return iterator(_data + _size); }

    const_iterator begin() const { return const_iterator(_data); }
    const_iterator end()   const { return const_iterator(_data + _size); }

    const_iterator cbegin() const { return const_iterator(_data); }
    const_iterator cend()   const { return const_iterator(_data + _size); }

    reverse_iterator rbegin()
    {
        return _size > 0 ? reverse_iterator(_data + _size - 1)
                         : reverse_iterator(nullptr);
    }

    reverse_iterator rend()
    {
        return _size > 0 ? reverse_iterator(_data - 1)
                         : reverse_iterator(nullptr);
    }

private:
    void copy_from(const DynArray& other);
    void move_from(DynArray&& other) noexcept;
    void free();
    size_t next_capacity() const;

    Allocator   _allocator;
    T*          _data     = nullptr;
    size_t _size     = 0;
    size_t _capacity = 0;
};

/// IMPLEMENTATION

// Default-fill [count] elements
template <class T, class Allocator>
DynArray<T, Allocator>::DynArray(size_t count)
    : _data(count ? _allocator.allocate(count) : nullptr)
    , _size(count)
    , _capacity(count)
{
    for (size_t i = 0; i < _size; ++i)
        _allocator.construct(_data + i);
}

// Fill [count] elements with [initial]
template <class T, class Allocator>
DynArray<T, Allocator>::DynArray(size_t count, const T& initial)
    : _data(count ? _allocator.allocate(count) : nullptr)
    , _size(count)
    , _capacity(count)
{
    for (size_t i = 0; i < _size; ++i)
        _allocator.construct(_data + i, initial);
}

template <class T, class Allocator>
DynArray<T, Allocator>::DynArray(const DynArray& other)
{
    copy_from(other);
}

template <class T, class Allocator>
DynArray<T, Allocator>& DynArray<T, Allocator>::operator=(const DynArray& other)
{
    if (this != &other)
    {
        free();
        copy_from(other);
    }
    return *this;
}

template <class T, class Allocator>
DynArray<T, Allocator>::DynArray(DynArray&& other) noexcept
{
    move_from(std::move(other));
}

template <class T, class Allocator>
DynArray<T, Allocator>& DynArray<T, Allocator>::operator=(DynArray&& other) noexcept
{
    if (this != &other)
    {
        free();
        move_from(std::move(other));
    }
    return *this;
}

template <class T, class Allocator>
DynArray<T, Allocator>::~DynArray()
{
    free();
}

template <class T, class Allocator>
void DynArray<T, Allocator>::copy_from(const DynArray& other)
{
    if (other._capacity == 0)
    {
        _data = nullptr;
        _size = _capacity = 0;
        return;
    }

    _data     = _allocator.allocate(other._capacity);
    _size     = other._size;
    _capacity = other._capacity;

    for (size_t i = 0; i < _size; ++i)
        _allocator.construct(_data + i, other._data[i]);
}

template <class T, class Allocator>
void DynArray<T, Allocator>::move_from(DynArray&& other) noexcept
{
    _data     = other._data;
    _size     = other._size;
    _capacity = other._capacity;

    other._data = nullptr;
    other._size = other._capacity = 0;
}

template <class T, class Allocator>
void DynArray<T, Allocator>::free()
{
    if (_data)
    {
        for (size_t i = 0; i < _size; ++i)
            _allocator.destroy(_data + i);

        _allocator.deallocate(_data, _capacity);
    }

    _data = nullptr;
    _size = _capacity = 0;
}

template <class T, class Allocator>
size_t DynArray<T, Allocator>::next_capacity() const
{
    if (_capacity == 0) return 1;
    return _capacity * Detail::GROWTH_FACTOR;
}

/// Capacity operations

template <class T, class Allocator>
void DynArray<T, Allocator>::reserve(size_t n)
{
    if (n <= _capacity)
        return;

    T* newData = _allocator.allocate(n);

    for (size_t i = 0; i < _size; ++i)
        _allocator.construct(newData + i, std::move(_data[i]));

    if (_data)
        _allocator.deallocate(_data, _capacity);

    _data     = newData;
    _capacity = n;
}

template <class T, class Allocator>
void DynArray<T, Allocator>::shrink_to_fit()
{
    if (_capacity == _size)
        return;

    if (_size == 0)
    {
        free();
        return;
    }

    T* newData = _allocator.allocate(_size);
    for (size_t i = 0; i < _size; ++i)
        _allocator.construct(newData + i, std::move(_data[i]));

    if (_data)
        _allocator.deallocate(_data, _capacity);

    _data     = newData;
    _capacity = _size;
}

template <class T, class Allocator>
void DynArray<T, Allocator>::resize(size_t n)
{
    if (n < _size)
    {
        for (size_t i = n; i < _size; ++i)
            _allocator.destroy(_data + i);
        _size = n;
    }
    else if (n > _size)
    {
        if (n > _capacity)
            reserve(n);

        for (size_t i = _size; i < n; ++i)
            _allocator.construct(_data + i);
        _size = n;
    }
}

/// Modifiers

template <class T, class Allocator>
void DynArray<T, Allocator>::push_back(const T& element)
{
    if (_size == _capacity)
        reserve(next_capacity());

    _allocator.construct(_data + _size, element);
    ++_size;
}

template <class T, class Allocator>
void DynArray<T, Allocator>::push_back(T&& element)
{
    if (_size == _capacity)
        reserve(next_capacity());

    _allocator.construct(_data + _size, std::move(element));
    ++_size;
}

template <class T, class Allocator>
template <class... Args>
void DynArray<T, Allocator>::emplace_back(Args&&... args)
{
    if (_size == _capacity)
        reserve(next_capacity());

    _allocator.construct(_data + _size, std::forward<Args>(args)...);
    ++_size;
}

template <class T, class Allocator>
void DynArray<T, Allocator>::pop_back()
{
    if (_size == 0) return;

    --_size;
    _allocator.destroy(_data + _size);
}

template <class T, class Allocator>
void DynArray<T, Allocator>::clear()
{
    for (size_t i = 0; i < _size; ++i)
        _allocator.destroy(_data + i);

    _size = 0;
}

template <class T, class Allocator>
void DynArray<T, Allocator>::erase(const_iterator position)
{
    erase(position, position + 1);
}

template <class T, class Allocator>
void DynArray<T, Allocator>::erase(const_iterator first, const_iterator last)
{
    int deleted = last - first;
    if (deleted <= 0) return;

    int beginOffset = first - cbegin();
    int endOffset   = last  - cbegin();

    if (last != cend())
    {
        size_t dst = static_cast<size_t>(beginOffset);
        for (size_t src = static_cast<size_t>(endOffset); src < _size; ++src, ++dst)
            _data[dst] = std::move(_data[src]);
    }

    for (size_t i = _size - deleted; i < _size; ++i)
        _allocator.destroy(_data + i);

    _size -= deleted;
}

/// Element access

template <class T, class Allocator>
T& DynArray<T, Allocator>::operator[](size_t idx)
{
    return _data[idx];
}

template <class T, class Allocator>
const T& DynArray<T, Allocator>::operator[](size_t idx) const
{
    return _data[idx];
}