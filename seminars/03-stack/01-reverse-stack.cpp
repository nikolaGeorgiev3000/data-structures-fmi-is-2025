#include <iostream>
#include <stack>

// Helper stack print function
template <typename T>
void printStack(std::stack<T> s)
{
    while(!s.empty())
    {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << '\n';
}

// Stack reverse function (generic)
template <typename T>
void reverse(std::stack<T>& s)
{
    std::stack<T> temp;

    while (!s.empty())
    {
        temp.push(s.top());
        s.pop();
    }

    s = std::move(temp); // Move, in order to avoid unnecessary copying
}

int main()
{
    std::stack<int> stackExample;
    stackExample.push(1);
    stackExample.push(2);
    stackExample.push(3);
    stackExample.push(4);
    stackExample.push(5);

    std::cout << "Stack before reverse: ";
    printStack(stackExample);

    reverse(stackExample);

    std::cout << "Stack after reverse: ";
    printStack(stackExample);

    return 0;
}