#include "Node.h"

template <typename T>
void mirror(Node<T>* lst)
{
    if (lst == nullptr)
        return;

    Node<T>* curr = lst;
    while (curr->next != nullptr)
    {
        curr = curr->next;
    }

    Node<T>* tail = curr;
    do
    {
        tail->next = new Node<T>(curr->value, nullptr, tail);
        tail = tail->next;
        curr = curr->prev;
    } while (curr != nullptr);
}

int main()
{
    Node<int> l(1);
    l.addAtEnd(4);
    l.addAtEnd(5);

    l.printFromStart();

    mirror(&l);

    l.printFromStart();

    return 0;
}
