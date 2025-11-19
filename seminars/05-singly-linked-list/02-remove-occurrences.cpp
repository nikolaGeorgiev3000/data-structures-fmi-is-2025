#include "Node.h"

template <typename T>
Node<T>* removeAll(Node<T>* list, const T& value)
{
    // Remove all first elements, if they are == value
    while (list != nullptr && list->value == value)
    {
        Node<T>* toDelete = list;
        list = list->next; // Move forward
        toDelete->next = nullptr; // So we don't delete the whole list in the destructor
        delete toDelete;
    }

    if (list == nullptr) return nullptr; // Empty list

    // Go through the rest
    Node<T>* current = list;
    while (current->next != nullptr)
    {
        if (current->next->value == value)
        {
            Node<T>* toDelete = current->next;
            current->next = toDelete->next; // Move forward
            
            toDelete->next = nullptr; // Protection from delete next in the destructor
            delete toDelete;
        } else
        {
            current = current->next;
        }
    }

    return list;
}

int main()
{
    Node<int>* l = new Node<int>(1);
    l->add(2);
    l->add(1);
    l->add(3);
    l->add(1);
    l->print(); // 1 -> 2 -> 1 -> 3 -> 1

    l = removeAll(l, 1);
    l->print(); // 2 -> 3

    delete l;

    return 0;
}