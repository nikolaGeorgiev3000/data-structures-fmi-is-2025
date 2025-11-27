#ifndef _NODE_T_H_ // Doubly Linked List Node
#define _NODE_T_H_

#include <iostream>

template <typename T>
class Node
{
public:
    T value;
    Node<T>* next;
    Node<T>* prev;

    Node(T value = T(), Node* next = nullptr, Node* prev = nullptr) 
    : value(value), next(next), prev(prev) {}

    ~Node() 
    {
        if (next != nullptr)
        {
            delete next;
        }
    }

    void addAtEnd(T value)
    {
        Node<T>* last = this;
        while (last->next != nullptr)
        {
            last = last->next;
        }
        last->next = new Node<T>(value, nullptr, last);
    }

    void remove()
    {
        if (prev)
            prev->next = next;
        if (next)
            next->prev = prev;

        prev = nullptr;
        next = nullptr;
        delete this;
    }

    void printFromStart() const
    {
        const Node<T>* curr = this;
        while (curr->prev != nullptr)
        {
            curr = curr->prev;
        }
        while (curr->next != nullptr)
        {
            std::cout << curr->value << " -> ";
            curr = curr->next;
        }
        std::cout << curr->value << std::endl;
    }
};

#endif // _NODE_T_H_