#pragma once

#include <cstddef>

template <class T>
class DynArrayConstIterator
{
public:
    explicit DynArrayConstIterator(const T* ptr = nullptr) : memPtr(ptr) {}
    DynArrayConstIterator(const T* ptr, size_t offset) : memPtr(ptr + offset) {}

    DynArrayConstIterator operator+(int off) const
    {
        return DynArrayConstIterator(memPtr + off);
    }

    DynArrayConstIterator operator-(int off) const
    {
        return DynArrayConstIterator(memPtr - off);
    }

    int operator-(const DynArrayConstIterator& other) const
    {
        return static_cast<int>(memPtr - other.memPtr);
    }

    const T* operator->() const noexcept { return memPtr; }
    const T& operator*()  const noexcept { return *memPtr; }

    bool operator==(const DynArrayConstIterator& it) const { return memPtr == it.memPtr; }
    bool operator!=(const DynArrayConstIterator& it) const { return !(memPtr == it.memPtr); }

private:
    const T* memPtr;
};

template <class T>
class DynArrayIterator
{
public:
    explicit DynArrayIterator(T* ptr = nullptr) : memPtr(ptr) {}
    DynArrayIterator(T* ptr, size_t offset) : memPtr(ptr + offset) {}

    DynArrayIterator& operator++()
    {
        ++memPtr;
        return *this;
    }

    DynArrayIterator operator++(int)
    {
        DynArrayIterator tmp(*this);
        ++(*this);
        return tmp;
    }

    DynArrayIterator& operator--()
    {
        --memPtr;
        return *this;
    }

    DynArrayIterator operator--(int)
    {
        DynArrayIterator tmp(*this);
        --(*this);
        return tmp;
    }

    operator DynArrayConstIterator<T>() const
    {
        return DynArrayConstIterator<T>(memPtr);
    }

    DynArrayIterator operator+(int off) const
    {
        return DynArrayIterator(memPtr + off);
    }

    DynArrayIterator operator-(int off) const
    {
        return DynArrayIterator(memPtr - off);
    }

    T*       operator->()       { return memPtr; }
    const T* operator->() const { return memPtr; }

    T&       operator*()        { return *memPtr; }
    const T& operator*()  const { return *memPtr; }

    bool operator==(const DynArrayIterator& it) const { return memPtr == it.memPtr; }
    bool operator!=(const DynArrayIterator& it) const { return !(memPtr == it.memPtr); }

private:
    T* memPtr;
};

template <class T>
class DynArrayReverseIterator
{
public:
    explicit DynArrayReverseIterator(T* ptr = nullptr) : memPtr(ptr) {}
    DynArrayReverseIterator(T* ptr, std::size_t offset) : memPtr(ptr + offset) {}

    DynArrayReverseIterator& operator++()
    {
        --memPtr;
        return *this;
    }

    DynArrayReverseIterator operator++(int)
    {
        DynArrayReverseIterator tmp(*this);
        --(*this);
        return tmp;
    }

    DynArrayReverseIterator& operator--()
    {
        ++memPtr;
        return *this;
    }

    DynArrayReverseIterator operator--(int)
    {
        DynArrayReverseIterator tmp(*this);
        ++(*this);
        return tmp;
    }

    DynArrayReverseIterator operator+(int off) const
    {
        return DynArrayReverseIterator(memPtr - off);
    }

    DynArrayReverseIterator operator-(int off) const
    {
        return DynArrayReverseIterator(memPtr + off);
    }

    T*       operator->()       { return memPtr; }
    const T* operator->() const { return memPtr; }

    T&       operator*()        { return *memPtr; }
    const T& operator*()  const { return *memPtr; }

    bool operator==(const DynArrayReverseIterator& it) const { return memPtr == it.memPtr; }
    bool operator!=(const DynArrayReverseIterator& it) const { return !(memPtr == it.memPtr); }

private:
    T* memPtr;
};