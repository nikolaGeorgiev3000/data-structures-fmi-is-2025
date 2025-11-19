#include "Node.h"
#include <new> // For std::bad_alloc

template <typename T>
Node<T>* cloneReversed(const Node<T>* first)
{
    if (first == nullptr)
        return nullptr;
    
    Node<T>* newHead = nullptr;

    try
    {
        const Node<T>* current = first;

        while (current != nullptr)
        {
            // Create new node for the copy
            Node<T>* newNode = new Node<T>(current->value); 
            
            // Attach at the beginning of the new list
            newNode->next = newHead;
            newHead = newNode;

            current = current->next;
        }
    }
    catch(std::bad_alloc& e)
    {
        delete newHead; // Free, before throw
        throw;
    }
    
    return newHead;
}

int main()
{
    Node<int>* l = new Node<int>(1);
    l->add(2);
    l->add(3);
    l->add(4);
    l->add(5);

    std::cout << "Original: ";
    l->print();

    Node<int>* rev = cloneReversed(l);

    std::cout << "Cloned reversed: ";
    rev->print();

    delete l;
    delete rev;

    return 0;
}