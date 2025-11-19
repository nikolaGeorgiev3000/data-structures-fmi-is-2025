#include <iostream>
#include "linked-queue.hpp"

int main()
{
    LinkedQueue<int> q;

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    q.enqueue(5);

    std::cout << q.peek() << '\n';
    q.dequeue();
    std::cout << q.peek() << '\n';
    q.dequeue();
    std::cout << q.peek() << '\n';
    q.dequeue();
    std::cout << q.peek() << '\n';
    q.dequeue();
    std::cout << q.peek() << '\n';
    q.dequeue();

    std::cout << std::boolalpha << q.isEmpty() << '\n';

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    LinkedQueue<int> q2(q);

    std::cout << q.peek() << '\n';
    q.dequeue();
    std::cout << q.peek() << '\n';
    q.dequeue();
    std::cout << q.peek() << '\n';
    q.dequeue();

    std::cout << std::boolalpha << q.isEmpty() << '\n';
    std::cout << q2.peek() << '\n';

    return 0;
}