#include <iostream>
#include <queue>

// Time: O(n), Space: O(n)
template <typename T>
std::queue<T> dropEverySecond(std::queue<T> q)
{
    std::queue<T> result;
    bool keep = true; // keep -> push, !keep -> skip

    while (!q.empty())
    {
        if (keep)
            result.push(q.front());

        q.pop();
        keep = !keep;
    }

    return result;
}

template <typename T>
void printQueue(std::queue<T> q)
{
    while (!q.empty())
    {
        std::cout << q.front() << " ";
        q.pop();
    }
}

int main()
{
    std::queue<int> q;
    for (int x : {1,2,3,4,5})
        q.push(x);

    auto filtered = dropEverySecond(q);
    printQueue(filtered); // expected: 1 3 5

    return 0;
}