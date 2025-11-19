#ifndef _NODE_H_
#define _NODE_H_

#include <iostream>

template <typename T>
struct Node
{
    T value;
    Node<T>* next;

    Node(T value = T(), Node* next = nullptr) 
    : value(value), next(next) {}
    ~Node() 
    {
        // std::cout << "Deleting " << value << ", next is: " << next << std::endl;
        delete next;
    }

    void add(T value)
    {
        Node<T>* last = this;
        while (last->next != nullptr)
        {
            last = last->next;
        }
        last->next = new Node<T>(value);
    }

    void print() const
    {
        const Node<T>* curr = this;
        while (curr->next != nullptr)
        {
            std::cout << curr->value << " -> ";
            curr = curr->next;
        }
        std::cout << curr->value << std::endl;
    }
};

#endif // _NODE_H_