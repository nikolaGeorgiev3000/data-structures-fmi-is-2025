#include <iostream>
#include <stack>

class MyQueue {
public:
    MyQueue() = default;
    
    void push(int x) 
    {
        in.push(x);
    }
    
    int pop() 
    {
        moveIfNeeded();
        int value = out.top();
        out.pop();
        return value;
    }
    
    int peek() 
    {
        moveIfNeeded();
        return out.top();
    }
    
    bool empty() const
    {
        return in.empty() && out.empty();
    }

private:
    std::stack<int> in;
    std::stack<int> out;

    static void transfer(std::stack<int>& from, std::stack<int>& to)
    {
        while (!from.empty())
        {
            to.push(from.top());
            from.pop();
        }
    }

    void moveIfNeeded()
    {
        if (out.empty())
            transfer(in, out);
    }
};

int main()
{
    MyQueue q;

    q.push(1); q.push(2); q.push(3);

    std::cout << q.peek() << "\n";  // Expect 1
    std::cout << q.pop()  << "\n";  // Expect 1
    std::cout << q.pop()  << "\n";  // Expect 2

    q.push(4);
    std::cout << q.peek() << "\n";  // Expect 3
    std::cout << q.pop()  << "\n";  // Expect 3
    std::cout << q.pop()  << "\n";  // Expect 4

    std::cout << std::boolalpha << q.empty() << "\n"; // Expect true

    return 0;
}