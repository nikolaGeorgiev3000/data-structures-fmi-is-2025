#include <iostream>
#include <vector>
#include <stack>

bool validateStackSequences(const std::vector<int>& pushed,
                            const std::vector<int>& popped)
{
    std::stack<int> st;
    int j = 0; // Popped index

    for (int x : pushed)
    {
        st.push(x);

        while (!st.empty() && st.top() == popped[j])
        {
            st.pop();
            j++;
        }
    }
    return j == popped.size();
}

int main()
{
    std::vector<int> pushed1 = {1, 2, 3, 4, 5};
    std::vector<int> popped1 = {4, 5, 3, 2, 1};

    std::cout << "Example 1: " << std::boolalpha << validateStackSequences(pushed1, popped1) << '\n'; // true

    std::vector<int> pushed2 = {1, 2, 3, 4, 5};
    std::vector<int> popped2 = {4, 3, 5, 1, 2};

    std::cout << "Example 2: " << std::boolalpha << validateStackSequences(pushed2, popped2) << '\n'; // false

    return 0;
}