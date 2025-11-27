#include <iostream>

struct Node
{
    int value;
    Node* next;

    Node(int value)
        : value(value), next(nullptr) {}
};

int findTheWinner(int n, int k)
{
    Node* first = new Node(1);
    Node* curr = first;
    for (int i = 2; i <= n; ++i)
    {
        curr->next = new Node(i);
        curr = curr->next;
    }
    curr->next = first; // Cyclic Linked List

    while (curr->next != curr) // Until only 1 node left
    {
        for (int i = 1; i < k; ++i)
            curr = curr->next;

        Node* toDelete = curr->next;
        curr->next = toDelete->next;
        delete toDelete;
    }

    int result = curr->value;
    delete curr;
    return result;
}

int main()
{
    std::cout << "Winner of a circular game, where:\n";

    std::cout << "n = 5, k = 2, is: " << findTheWinner(5, 2) << std::endl;
    std::cout << "n = 6, k = 5, is: " << findTheWinner(6, 5) << std::endl;

    return 0;
}