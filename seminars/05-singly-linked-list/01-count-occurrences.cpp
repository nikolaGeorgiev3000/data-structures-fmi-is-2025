#include "Node.h"

template <typename T>
unsigned int countOf(const Node<T>* list, const T& value)
{
    unsigned int count = 0;
    const Node<T>* current = list;

    while (current != nullptr)
    {
        if (current->value == value)
            ++count;

        current = current->next;
    }

    return count;
}

int main()
{
    Node<int> l(1);
    l.add(2);
    l.add(3);
    l.add(1);
    l.add(1);
    std::cout << countOf(&l, 1) << std::endl;

    return 0;
}