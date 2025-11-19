#include <iostream>
#include "linked-stack.hpp"

int main()
{
    LinkedStack<int> st;
    st.push(15);
    st.push(20);

    std::cout << "Top: " << st.peek() << '\n';
    st.pop();
    std::cout << "Is empty: " << std::boolalpha << st.isEmpty() << '\n';
    std::cout << "Top: " << st.peek() << '\n';

    st.pop();
    st.push(100);

    LinkedStack<int> copy = st;
    std::cout << "Copy top: " << copy.peek() << '\n';

    return 0;
}