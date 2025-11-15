#include <iostream>
#include <queue>
#include <string>

// Print the first `n` positive integers in binary,
// using a queue
void generateFirstNBinaryNumbers(unsigned n)
{
    if (n == 0)
        return; // Nothing to generate

    std::queue<std::string> q;
    q.push("1");

    for (unsigned i = 0; i < n; ++i)
    {
        std::string curr = q.front();
        q.pop();

        std::cout << curr << " ";

        q.push(curr + "0");
        q.push(curr + "1");
    }
    std::cout << std::endl;
}

int main()
{
    generateFirstNBinaryNumbers(10);
    generateFirstNBinaryNumbers(100);
    return 0;
}