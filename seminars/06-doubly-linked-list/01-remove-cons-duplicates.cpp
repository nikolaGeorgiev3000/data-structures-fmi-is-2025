#include "Node.h"

template <typename T>
void removeConsecutiveDuplicates(Node<T>* lst)
{
    if (lst == nullptr)
        return;

    Node<T>* curr = lst;
    
    while (curr->prev != nullptr)
    {
        curr = curr->prev;
    }
    
    while (curr->next != nullptr)
    {
        if (curr->value == curr->next->value)
        {
            curr->next->remove();
        }
        else
        {
            curr = curr->next;
        }
    }
}

int main()
{
    Node<int> l(1);
    l.addAtEnd(1);
    l.addAtEnd(2);
    l.addAtEnd(2);
    l.addAtEnd(1);
    l.addAtEnd(1);
    l.addAtEnd(2);
    l.addAtEnd(2);
    l.addAtEnd(2);
    l.addAtEnd(1);
    l.addAtEnd(2);
    l.addAtEnd(1);
    l.addAtEnd(2);

    l.printFromStart();

    removeConsecutiveDuplicates(&l);

    l.printFromStart();

    return 0;
}