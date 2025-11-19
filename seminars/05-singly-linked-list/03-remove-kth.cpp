#include "Node.h"
#include <cstddef>

template <typename T>
Node<T>* removeNthThenEveryKth(Node<T>* list, size_t n, size_t k)
{
    if (!list)
        return nullptr;

    // If k == 0 -> don't remove anything
    if (k == 0)
        return list;

    if (n <= 1)
    {
        Node<T>* next = list->next;

        list->next = nullptr;
        delete list;

        // Next element we remove is k-th
        return removeNthThenEveryKth(next, k, k);
    }

    list->next = removeNthThenEveryKth(list->next, n - 1, k);
    return list;
}

template <typename T>
Node<T>* removeKth(Node<T>* list, size_t k)
{
    if (k == 0)
        return list;

    // k == 1 -> remove the whole list
    if (k == 1)
    {
        Node<T>* curr = list;
        while (curr)
        {
            Node<T>* toDelete = curr;
            curr = curr->next;

            toDelete->next = nullptr;
            delete toDelete;
        }
        return nullptr;
    }

    return removeNthThenEveryKth(list, k, k);
}

int main()
{
    Node<int>* l = new Node<int>(1);

    l->add(2);
    l->add(3);
    l->add(4);
    l->add(5);
    l->add(6);
    l->add(7);

    l->print();

    l = removeKth(l, 2);
    l->print(); // 1 -> 3 -> 5 -> 7

    delete l; // Free the heap

    return 0;
}