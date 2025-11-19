#include <iostream>
#include "template-stack.hpp"

int main()
{
    Stack<int> st; // Default uses std::deque<int>
    st.push(3);
    st.push(10);

    std::cout << "Top: " << st.top() << '\n';

    st.pop();
    std::cout << "Now top: " << st.top() << '\n';

    std::cout << "Size: " << st.size() << '\n';
    std::cout << "Empty: " << std::boolalpha << st.empty() << '\n';

    // Example using a different underlying container
    Stack<int, std::vector<int>> vStack;
    vStack.push(7);
    vStack.push(9);

    std::cout << "Vector stack top: " << vStack.top() << '\n';
    vStack.pop();
    std::cout << "Vector stack top, after pop: " << vStack.top() << '\n';


    return 0;
}