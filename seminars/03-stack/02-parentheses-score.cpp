#include <iostream>
#include <stack>
#include <string>

// Space: O(n); Time: O(n)
int scoreOfParentheses(std::string_view str) // string_view has better performance than const std::string&
{
    std::stack<int> st;
    st.push(0); // Base score

    for (char c : str)
    {
        if (c == '(')
        {
            st.push(0); // New group of parentheses
        }
        else // ')'
        {
            int inner = st.top(); st.pop();
            int outer = st.top(); st.pop();
            st.push(outer + (inner == 0 ? 1 : inner * 2));
        }
    }

    return st.top();
}

int main()
{
    std::cout << scoreOfParentheses("()") << std::endl;
    std::cout << scoreOfParentheses("(())") << std::endl;
    std::cout << scoreOfParentheses("()()") << std::endl;

    std::cout << scoreOfParentheses("(()(()))") << std::endl; // 2 * (1 + 2 * 1)

    return 0;
}