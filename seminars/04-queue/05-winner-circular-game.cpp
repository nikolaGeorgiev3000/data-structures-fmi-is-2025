#include <iostream>
#include <queue>
#include <cassert>

// Queue-based solution: direct simulation with a circular queue.
// Time: O(n * k) in worst case, Space: O(n)
int findTheWinnerQueue(int n, int k)
{
    assert(n >= 1 && k >= 1);

    std::queue<int> q;

    for (int i = 1; i <= n; ++i)
        q.push(i);

    while (q.size() > 1)
    {
        // Move the first k-1 players to the back
        for (int i = 1; i < k; ++i)
        {
            q.push(q.front());
            q.pop();
        }

        // Eliminate the k-th player
        q.pop();
    }

    return q.front();
}

// Josephus formula solution: O(n) time, O(1) extra memory.
// Winner is maintained 0-based; at the end we convert to 1-based.
int findTheWinnerJosephus(int n, int k)
{
    assert(n >= 1 && k >= 1);

    int winner = 0; // 0-based index

    for (int i = 1; i <= n; ++i)
        winner = (winner + k) % i;

    return winner + 1; // Convert to 1-based
}

int main()
{
    // Basic LeetCode examples
    assert(findTheWinnerQueue(5, 2) == 3);
    assert(findTheWinnerJosephus(5, 2) == 3);

    assert(findTheWinnerQueue(6, 5) == 1);
    assert(findTheWinnerJosephus(6, 5) == 1);

    // Cross-check both implementations on a small grid of inputs
    for (int n = 1; n <= 10; ++n)
    {
        for (int k = 1; k <= 10; ++k)
        {
            int qWinner  = findTheWinnerQueue(n, k);
            int jWinner  = findTheWinnerJosephus(n, k);
            assert(qWinner == jWinner);
        }
    }

    std::cout << "All tests passed for findTheWinnerQueue and findTheWinnerJosephus.\n";
    return 0;
}