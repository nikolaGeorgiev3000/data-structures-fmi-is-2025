#include <iostream>
#include "array-stack.hpp"

int main()
{
    ArrayStack<int> st;

    st.push(1);
    st.push(2);
    st.push(3);

    std::cout << "Size: " << st.size() << '\n';
    std::cout << "Top: " << st.peek() << '\n';

    st.pop();
    std::cout << "Top after pop: " << st.peek() << '\n';

    ArrayStack<int> copy = st;
    std::cout << "Copy size: " << copy.size() << '\n';
    std::cout << "Copy top : " << copy.peek() << '\n';

    return 0;
}