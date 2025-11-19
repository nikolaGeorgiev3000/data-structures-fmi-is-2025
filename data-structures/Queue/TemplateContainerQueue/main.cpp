#include <iostream>
#include "template-queue.hpp"

int main()
{
    Queue<int> q;

    q.push(1);
    q.push(2);
    q.push(3);

    int x = 4;
    q.push(std::move(x));

    std::cout << q.front() << ' ' << q.back() << '\n';

    q.pop();

    std::cout << q.front() << ' ' << q.size() << '\n';

    return 0;
}