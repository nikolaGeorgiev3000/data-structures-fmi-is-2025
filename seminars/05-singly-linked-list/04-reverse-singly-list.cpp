#include "Node.h"

template <typename T>
Node<T>* reverse(Node<T>* list)
{
    Node<T>* prev = nullptr;
    Node<T>* curr = list;

    while (curr != nullptr)
    {
        Node<T>* next = curr->next; // Save the chain
        curr->next = prev;          // Reverse the arrow 
        prev = curr;                // Move prev forward
        curr = next;                // Move curr forward
    }
    
    return prev; // Return the new head
}

int main()
{
    Node<int>* l = new Node<int>(1);

    l->add(2);
    l->add(3);
    l->add(4);
    l->add(5);
    l->print();

    l = reverse(l);
    l->print();

    delete l; // Free the heap

    return 0;
}