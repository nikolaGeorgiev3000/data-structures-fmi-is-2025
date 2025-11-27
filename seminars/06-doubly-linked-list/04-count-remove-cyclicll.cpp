#include <iostream>

template <typename T>
struct Node
{
    T value;
    Node* next;

    Node(T value = T(), Node* next = nullptr)
        : value(value), next(next)
    {
        if (next == nullptr)
            this->next = this;
    }

    ~Node()
    {
        // std::cout << "Destructor for " << this << "; next is " << next << std::endl;
        Node* current = next;
        while (current != nullptr && current != this)
        {
            Node* toDelete = current;
            current = current->next;
            toDelete->next = nullptr;
            // std::cout << "Deleting " << toDelete->value << "; next is " << current << std::endl;
            delete toDelete;
        }
    }

    void add(const T& value)
    {
        Node* last = next;
        while (last->next != this)
        {
            last = last->next;
        }
        last->next = new Node(value, this);
    }

    void print() const
    {
        const Node* curr = this;
        while (curr->next != this)
        {
            std::cout << curr->value << " -> ";
            curr = curr->next;
        }
        std::cout << curr->value << std::endl;
    }
};

// Count occurrences (for Cyclic Linked List)
template <typename T>
unsigned int countOf(const Node<T>* list, const T& value)
{
    if (!list)
        return 0;

    unsigned int count = 0;
    const Node<T>* curr = list;

    do
    {
        if (curr->value == value)
            ++count;
        curr = curr->next;

    } while (curr != list);

    return count;
}

// Remove occ. (for CLL)
template <typename T>
Node<T>* removeAll(Node<T>* list, const T& value)
{
    Node<T>* curr = list;
    while (curr->next != list)
    {
        if (curr->next->value == value)
        {
            Node<T>* toDelete = curr->next;
            curr->next = toDelete->next;
            toDelete->next = nullptr;

            delete toDelete;
        }
        else
        {
            curr = curr->next;
        }
    }

    if (list->value == value) // Head node contains `value`
    {
        curr->next = list->next;
        list->next = nullptr;
        delete list;

        if (curr == list)
            return nullptr;

        return curr->next;
    }

    return list;
}

template <typename T>
void print(const Node<T>* list)
{
    std::cout << "Printing list at address " << list << ':' << std::endl;
    if (list != nullptr)
        list->print();
}

int main()
{
    auto* l = new Node<int>(1);
    l->add(2);
    l->add(3);
    l->add(1);
    l->add(1);
    print(l);

    std::cout << countOf(l, 1) << " times 1" << std::endl;

    l = removeAll(l, 1);
    print(l);

    l = removeAll(l, 2);
    print(l);

    l = removeAll(l, 3);
    print(l);

    delete l;
    return 0;
}
