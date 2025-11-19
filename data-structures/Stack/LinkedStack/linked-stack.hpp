#pragma once

#include <stdexcept>

template <typename T>
class LinkedStack {
public:
    LinkedStack();
    LinkedStack(const LinkedStack& other);
    LinkedStack& operator=(const LinkedStack& other);
    ~LinkedStack();

    void push(const T& value);   // O(1)
    void pop();                  // O(1), throws if empty
    const T& peek() const;       // O(1), throws if empty

    bool isEmpty() const noexcept;

private:
    struct Node {
        T data;
        Node* next;

        Node(const T& value, Node* nextPtr = nullptr)
            : data(value), next(nextPtr) {}
    };

    Node* head;

    void copyFrom(const LinkedStack& other);
    void free();
};

template <typename T>
LinkedStack<T>::LinkedStack()
    : head(nullptr)
{
}

template <typename T>
LinkedStack<T>::LinkedStack(const LinkedStack& other)
    : head(nullptr)
{
    copyFrom(other);
}

template <typename T>
LinkedStack<T>& LinkedStack<T>::operator=(const LinkedStack& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

template <typename T>
LinkedStack<T>::~LinkedStack()
{
    free();
}

template <typename T>
void LinkedStack<T>::free()
{
    while (head != nullptr) {
        Node* toDelete = head;
        head = head->next;
        delete toDelete;
    }
}

template <typename T>
void LinkedStack<T>::copyFrom(const LinkedStack& other)
{
    if (other.head == nullptr) {
        head = nullptr;
        return;
    }

    // Copy first node
    head = new Node(other.head->data);
    Node* thisIter = head;
    Node* otherIter = other.head->next;

    // Copy the rest
    while (otherIter != nullptr) {
        thisIter->next = new Node(otherIter->data);
        thisIter = thisIter->next;
        otherIter = otherIter->next;
    }
}

template <typename T>
void LinkedStack<T>::push(const T& value)
{
    head = new Node(value, head);
}

template <typename T>
void LinkedStack<T>::pop()
{
    if (isEmpty())
        throw std::runtime_error("LinkedStack is empty");

    Node* toDelete = head;
    head = head->next;
    delete toDelete;
}

template <typename T>
const T& LinkedStack<T>::peek() const
{
    if (isEmpty())
        throw std::runtime_error("LinkedStack is empty");

    return head->data;
}

template <typename T>
bool LinkedStack<T>::isEmpty() const noexcept
{
    return head == nullptr;
}