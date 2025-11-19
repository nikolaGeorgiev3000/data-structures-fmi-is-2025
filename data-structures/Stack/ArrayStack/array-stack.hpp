#pragma once

#include <cstddef>
#include <stdexcept>

template <typename T>
class ArrayStack
{
public:
    ArrayStack();
    ArrayStack(const ArrayStack& other);
    ArrayStack& operator=(const ArrayStack& other);
    ~ArrayStack();

    void push(const T& value); // Amortized: O(1)
    void pop();                // O(1), throws if empty
    const T& peek() const;     // O(1), throws if empty

    std::size_t size() const noexcept;
    bool isEmpty() const noexcept;

private:
    T* data;
    std::size_t currentSize;
    std::size_t capacity;

    void copyFrom(const ArrayStack& other);
    void free();
    void resize(std::size_t newCapacity);
};

// Implementations
template <typename T>
ArrayStack<T>::ArrayStack()
    : data(nullptr), currentSize(0), capacity(0)
{
    data = new T[capacity];
}

template <typename T>
ArrayStack<T>::ArrayStack(const ArrayStack& other)
    : data(nullptr), currentSize(0), capacity(0)
{
    this->copyFrom(other);
}

template <typename T>
ArrayStack<T>& ArrayStack<T>::operator=(const ArrayStack& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }

    return *this;
}

template <typename T>
ArrayStack<T>::~ArrayStack()
{
    free();
}

template <typename T>
void ArrayStack<T>::copyFrom(const ArrayStack& other)
{
    data = new T[other.capacity];

    for (std::size_t i = 0; i < other.currentSize; ++i)
        data[i] = other.data[i];
    
    currentSize = other.currentSize;
    capacity = other.capacity;
}

template <typename T>
void ArrayStack<T>::free()
{
    delete[] data;
    data = nullptr;
    currentSize = 0;
    capacity = 0;
}

template <typename T>
void ArrayStack<T>::resize(std::size_t newCapacity)
{
    if (newCapacity < currentSize)
        newCapacity = currentSize;

    T* newData = new T[newCapacity];

    for (std::size_t i = 0; i < currentSize; ++i)
        newData[i] = data[i];
    
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

template <typename T>
void ArrayStack<T>::push(const T& value)
{
    if (currentSize == capacity)
        resize(capacity * 2);
    
    data[currentSize++] = value;
}

template <typename T>
void ArrayStack<T>::pop()
{
    if (isEmpty())
        throw std::runtime_error("Stack is empty");

    --currentSize;

    if (currentSize * 4 <= capacity && capacity > 4) // Reduce the capacity a bit
        resize(capacity / 2);
}

template <typename T>
const T& ArrayStack<T>::peek() const
{
    if (isEmpty())
        throw std::runtime_error("Stack is empty");

    return data[currentSize - 1];
}

template <typename T>
std::size_t ArrayStack<T>::size() const noexcept
{
    return currentSize;
}

template <typename T>
bool ArrayStack<T>::isEmpty() const noexcept
{
    return currentSize == 0;
}