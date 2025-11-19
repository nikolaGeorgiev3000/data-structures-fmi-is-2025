#pragma once

#include <cstddef>      // std::size_t
#include <stdexcept>    // std::runtime_error

template <typename T>
class CircularQueue
{
public:
    CircularQueue();
    CircularQueue(const CircularQueue& other);
    CircularQueue& operator=(const CircularQueue& other);
    ~CircularQueue();

    bool isEmpty() const;
    std::size_t size() const;

    void enqueue(const T& value);
    void dequeue();
    const T& peek() const;

private:
    T* data;
    std::size_t capacity;
    std::size_t count;

    std::size_t head;   // Index of current front element
    std::size_t tail;   // Index of first free position after the back

    void copyFrom(const CircularQueue& other);
    void free();
    void resize(std::size_t newCapacity);
};

template <typename T>
CircularQueue<T>::CircularQueue()
    : data(nullptr),
      capacity(4),
      count(0),
      head(0),
      tail(0)
{
    data = new T[capacity];
}

template <typename T>
CircularQueue<T>::CircularQueue(const CircularQueue& other)
    : data(nullptr),
      capacity(0),
      count(0),
      head(0),
      tail(0)
{
    copyFrom(other);
}

template <typename T>
CircularQueue<T>& CircularQueue<T>::operator=(const CircularQueue& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

template <typename T>
CircularQueue<T>::~CircularQueue()
{
    free();
}

template <typename T>
void CircularQueue<T>::copyFrom(const CircularQueue& other)
{
    data = new T[other.capacity];

    // Copy elements in logical order starting from other's head
    for (std::size_t i = 0; i < other.count; ++i)
    {
        std::size_t index = (other.head + i) % other.capacity;
        data[i] = other.data[index];
    }

    capacity = other.capacity;
    count    = other.count;
    head     = 0;
    tail     = count;
}

template <typename T>
void CircularQueue<T>::free()
{
    delete[] data;
    data     = nullptr;
    capacity = 0;
    count    = 0;
    head     = 0;
    tail     = 0;
}

template <typename T>
bool CircularQueue<T>::isEmpty() const
{
    return count == 0;
}

template <typename T>
std::size_t CircularQueue<T>::size() const
{
    return count;
}

template <typename T>
void CircularQueue<T>::resize(std::size_t newCapacity)
{
    T* newData = new T[newCapacity];

    // Copy elements in correct order
    for (std::size_t i = 0; i < count; ++i)
    {
        std::size_t index = (head + i) % capacity;
        newData[i] = data[index];
    }

    delete[] data;
    data     = newData;
    capacity = newCapacity;
    head     = 0;
    tail     = count;
}

template <typename T>
void CircularQueue<T>::enqueue(const T& value)
{
    if (count == capacity)
    {
        resize(capacity * 2);
    }

    data[tail] = value;
    tail = (tail + 1) % capacity;
    ++count;
}

template <typename T>
void CircularQueue<T>::dequeue()
{
    if (isEmpty())
    {
        throw std::runtime_error("Queue is empty");
    }

    head = (head + 1) % capacity;
    --count;
}

template <typename T>
const T& CircularQueue<T>::peek() const
{
    if (isEmpty())
    {
        throw std::runtime_error("Queue is empty");
    }

    return data[head];
}