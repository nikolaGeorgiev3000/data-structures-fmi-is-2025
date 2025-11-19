#pragma once

#include <cstddef>
#include <stdexcept>

template <typename T>
class LinkedQueue
{
public:
    LinkedQueue();
    LinkedQueue(const LinkedQueue& other);
    LinkedQueue& operator=(const LinkedQueue& other);
    ~LinkedQueue();

    bool isEmpty() const;

    void enqueue(const T& value);
    void dequeue();
    const T& peek() const;
private:
    struct Node
    {
        T value;
        Node* next;

        explicit Node(const T& v, Node* n = nullptr)
            : value(v), next(n)
        {}
    };

    Node* head; // Front of the queue
    Node* tail; // Back of the queue

    void free();
    void copyFrom(const LinkedQueue& other);
};

// Implementations
template <typename T>
LinkedQueue<T>::LinkedQueue() 
    : head(nullptr), tail(nullptr) 
{}

template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue& other)
    : head(nullptr), tail(nullptr)
{
    copyFrom(other);
}

template <typename T>
LinkedQueue<T>& LinkedQueue<T>::operator=(const LinkedQueue& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
    free();
}

template <typename T>
bool LinkedQueue<T>::isEmpty() const
{
    return head == nullptr; // Tail is nullptr iff head is nullptr
}

template <typename T>
void LinkedQueue<T>::enqueue(const T& value)
{
    Node* node = new Node(value);

    if (isEmpty())
    {
        head = tail = node;
    } else
    {
        tail->next = node;
        tail = node;
    }
}

template <typename T>
void LinkedQueue<T>::dequeue()
{
    if (isEmpty())
        throw std::runtime_error("Queue is empty");

    Node* oldHead = head;
    head = head->next;

    if (!head) // Queue became empty
        tail = nullptr;

    delete oldHead;
}

template <typename T>
const T& LinkedQueue<T>::peek() const
{
    if (isEmpty())
        throw std::runtime_error("Queue is empty");

    return head->value;
}

template <typename T>
void LinkedQueue<T>::free()
{
    Node* curr = head;
    while (curr)
    {
        Node* next = curr->next;
        delete curr;
        curr = next;
    }
    head = tail = nullptr;
}

template <typename T>
void LinkedQueue<T>::copyFrom(const LinkedQueue& other)
{
    head = tail = nullptr;

    Node* curr = other.head;
    while (curr)
    {
        enqueue(curr->value);
        curr = curr->next;
    }
}