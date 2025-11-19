#include <iostream>
#include "circular-queue.hpp"

int main()
{
    CircularQueue<int> q;

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    q.enqueue(5);

    std::cout << q.peek() << '\n'; // 1
    q.dequeue();
    std::cout << q.peek() << '\n'; // 2
    q.dequeue();
    std::cout << q.peek() << '\n'; // 3

    CircularQueue<int> q2 = q;     // Copy
    std::cout << q2.peek() << '\n'; // 3

    while (!q2.isEmpty())
    {
        std::cout << q2.peek() << ' ';
        q2.dequeue();
    }
    std::cout << '\n';

    return 0;
}